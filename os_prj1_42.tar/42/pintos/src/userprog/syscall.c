#include "userprog/syscall.h"
#include <stdio.h>
#include <string.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
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
  //printf ("system call!\n");
	int sys_num = *(int*)f->esp;
	if((!is_user_vaddr(f->esp) )|| (!is_user_vaddr(f->esp+4)) )
		sys_exit(-1);
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

	}
}

void sys_halt(void){
	shutdown_power_off();
}
void sys_exit(int status){
	struct thread * cur = thread_current();
	char * tmp;
	char * parse;
	cur->exit_status=status;
	parse = strtok_r(cur->name," ",&tmp);
	strlcpy(cur->name,parse,strlen(parse)+1);
	printf("%s: exit(%d)\n",cur->name,cur->exit_status);
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
	if(fd == 0 )
	{
		for(i=0;i<(int)size;i++)
		{
			((char*)buffer)[i] = input_getc();
			if(((char*)buffer)[i] ==0)
				break;
		}
	}
	return i;
}
int sys_write(int fd,const void * buffer,unsigned size)
{
	if(fd == 1)
	{
		putbuf(buffer,size);
	   return (int)size;
	}
	else 
		return -1;
}
