#include "userprog/syscall.h"
#include <stdio.h>
#include <string.h>
#include <syscall-nr.h>
#include <stdlib.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "threads/palloc.h"
#include "threads/malloc.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "filesys/off_t.h"
#include "lib/kernel/list.h"
#include "./process.h"
#include "devices/input.h"
#include "devices/shutdown.h"

static void syscall_handler (struct intr_frame *);

	void
syscall_init (void) 
{
	intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	//	printf ("system call!\n");
	int sys_num = *(int*)f->esp;
	if((!is_user_vaddr(f->esp) )|| (!is_user_vaddr(f->esp+4))|| (!is_user_vaddr(f->esp+8)) )
	{
		sys_exit(-1);
	}
	switch(sys_num)
	{
		case SYS_HALT:
			sys_halt();
			break;
		case SYS_EXIT:
			sys_exit(*(int*)(f->esp+4));
			break;
		case SYS_EXEC:
			f->eax = sys_exec(*(char**)(f->esp+4));
			break;
		case SYS_WAIT:
			f->eax = sys_wait(*(int*)(f->esp+4));
			break;
		case SYS_READ:
			f->eax = sys_read(*(int*)(f->esp+4),*(void**)(f->esp+8),*(unsigned*)(f->esp+12));
			break;
		case SYS_WRITE:
			f->eax = sys_write(*(int*)(f->esp+4),*(void**)(f->esp+8),*(unsigned*)(f->esp+12));
			break;

		case SYS_CREATE:
			f->eax = sys_create(*(char**)(f->esp+4),*(unsigned*)(f->esp+8));
			break;

		case SYS_REMOVE:
			f->eax =sys_remove(*(char **)(f->esp+4));
			break;

		case SYS_OPEN:
			f->eax = sys_open(*(char**)(f->esp+4));
			break;
		case SYS_FILESIZE:
			f->eax = sys_filesize(*(int*)(f->esp+4));
			break;
		case SYS_CLOSE:
			sys_close(*(int*)(f->esp+4));
			break;
		case SYS_SEEK:
			sys_seek(*(int*)(f->esp+4),*(unsigned*)(f->esp+8));
			break;
		case SYS_TELL:
			f->eax = sys_tell(*(int*)(f->esp+4));
			break;

	}
}

void sys_halt(void){
	shutdown_power_off();
}
void sys_exit(int status){
	struct thread * cur = thread_current();
	struct list_elem *tmp1;
	struct fd *f;
	char * tmp;
	char * parse;
	cur->exit_status=status;
	parse = strtok_r(cur->name," ",&tmp);
	strlcpy(cur->name,parse,strlen(parse)+1);
	printf("%s: exit(%d)\n",cur->name,cur->exit_status);
	
	for(tmp1 = list_begin(&(cur->fd_list));tmp1 != list_end(&(cur->fd_list));)
	{
		f = list_entry(tmp1,struct fd,elem);
		tmp1 = list_remove(tmp1);
		file_close(f->file);
		free(f);
	}
	thread_exit();
}
int sys_exec(const char *cmd_line)
{
	int i = process_execute(cmd_line);
	return i;
}
int sys_wait(int pid){
	return process_wait(pid);
}
int sys_read (int fd,const void * buffer, unsigned size)
{
	int i=0;
	if(buffer>PHYS_BASE)
		sys_exit(-1);
	if(fd == 0 )
	{
		for(i=0;i<(int)size;i++)
		{
			((char*)buffer)[i] = input_getc();
			if(((char*)buffer)[i] ==0)
				break;
		}
		return i;
	}
	else 
	{	
		struct thread * cur =thread_current();
		struct fd *f;
		struct list_elem *tmp;
		int res;
		for(tmp = list_begin(&(cur->fd_list));tmp != list_end(&(cur->fd_list));tmp=list_next(tmp))
		{
			f = list_entry(tmp,struct fd,elem);
			if(f->fd_num == fd)
			{
			//	printf("%s12\n%s12\n\n",cur->name,f->name);
				res = file_read(f->file,(void*)buffer,(off_t)size);
				return res;
			}
		}
	}
	return -1;
}
int sys_write(int fd,const void * buffer,unsigned size)
{
	int res=-1;
	if(fd == 1)
	{
		putbuf(buffer,size);
		return (int)size;
	}
	else
	{

		struct thread * cur =thread_current();
		struct fd *f;
		struct list_elem *tmp;
		for(tmp = list_begin(&(cur->fd_list));tmp != list_end(&(cur->fd_list));tmp=list_next(tmp))
		{
			f = list_entry(tmp,struct fd,elem);
			if(f->fd_num == fd)
			{
				if((f->file)->deny_write)
					res=0;
				else
				{
					res =file_write(f->file,buffer,size);

				}
				return res;

			}
		}
	}
	sys_exit(-1);
	return res;
}


bool sys_create(const char * file , unsigned initial_size){
	if(file!=NULL)
		return filesys_create(file,initial_size);
	else
		sys_exit(-1);
	return -1;
}
bool sys_remove(const char *file){
	return filesys_remove(file);
}

int sys_open(const char *file){
	struct file *new_file;
	struct thread *t = thread_current();
	struct fd * f;
	if(file==NULL)
	{
		sys_exit(-1);
		return -1;
	}
	new_file  =  filesys_open(file);
	if(new_file==NULL)
		return -1;
	f = (struct fd*)malloc(sizeof(struct fd)*1);
	f->file = new_file;
	strlcpy(f->name,file,strlen(file)+1);
	list_push_back(&t->fd_list,&f->elem);
	f->fd_num = ++(t->fd_size)+1;
	//	printf("%s12\n%s12\n",t->name,file);
	if(strcmp(t->name,file)==0)
	{
		file_deny_write(new_file);
	}
	return f->fd_num;
}
int sys_filesize(int fd)
{

	struct thread * cur =thread_current();
	struct fd *f;
	struct list_elem *tmp;

	for(tmp = list_begin(&(cur->fd_list));tmp != list_end(&(cur->fd_list));tmp=list_next(tmp))
	{
		f = list_entry(tmp,struct fd,elem);
		if(f->fd_num == fd)
			return file_length(f->file);
	}
	sys_exit(-1);
	return -1;
}
void sys_close(int fd)
{

	struct thread * cur =thread_current();
	struct fd *f;
	struct list_elem *tmp;

	for(tmp = list_begin(&(cur->fd_list));tmp != list_end(&(cur->fd_list));tmp=list_next(tmp))
	{
		f = list_entry(tmp,struct fd,elem);
		if(f->fd_num == fd)
		{
			list_remove(tmp);
			file_close(f->file);
			break;
		}
	}
	return ;
}
void sys_seek(int fd,unsigned position)
{

	struct thread * cur =thread_current();
	struct fd *f;
	struct list_elem *tmp;

	for(tmp = list_begin(&(cur->fd_list));tmp != list_end(&(cur->fd_list));tmp=list_next(tmp))
	{
		f = list_entry(tmp,struct fd,elem);
		if(f->fd_num == fd)
		{
			file_seek(f->file,position);
			break;
		}
	}
	return;

}
unsigned sys_tell(int fd)
{

	struct thread * cur =thread_current();
	struct fd *f;
	struct list_elem *tmp;

	for(tmp = list_begin(&(cur->fd_list));tmp != list_end(&(cur->fd_list));tmp=list_next(tmp))
	{
		f = list_entry(tmp,struct fd,elem);
		if(f->fd_num == fd)
			return file_tell(f->file);
	}
	return -1;
}
