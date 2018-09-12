#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);

void sys_halt(void);
void sys_exit(int status);
int sys_exec(const char *cmd_line);
int sys_wait(int pid);
int sys_read (int fd,const void * buffer, unsigned size);
int sys_write(int fd,const void * buffer,unsigned size);
#endif /* userprog/syscall.h */
