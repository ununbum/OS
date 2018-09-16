# Making PintOS
making PintOs at Linux Server

## Basic Code
> Pre-step before making PintOS

**TODO List**
- Make Functions which using data Structures
  - List
  - Hash
  - Bitmap

## [1st Assignment](https://github.com/ununbum/OS/tree/master/os_prj1_42.tar/42)
> Making User-space Stack & Add New System Call

**TODO List**
- Parse User's input and stack them at ESP
  - each instruction(input) has some rules depend on OS
  - Awareness of align and argc and argv's address
- Making System calls that use at perform users instructions
  - sys_halt()
  - sys_exit()
  - sys_exec()
  - sys_read()
  - sys_write()
  > Plus System calls
  - ~~Pibonacci()~~
  - ~~sum_of_four_integer()~~
- ~~Make Thread Using busy waiting~~
- Make Thread using semaphore 
  - Make Thread tree



## [2nd Assingment](https://github.com/ununbum/OS/tree/master/os_prj1_2_42.tar/42)
> Modify 'wait' and  'exec' System Call that use busy waiting to Semaphore and schedule thread

**TODO List**
- Make BSD scheduler 
- Priority Scheduling
- Use Alarm clock
- Make Floating point calculate system


## [3rd Assignment](https://github.com/ununbum/OS/tree/master/os_prj2_2_2_42.tar/42)
> Complete synch and 

**TODO List**
- Make File Descritptor
- Add File system call
	- create
	- remove
	- open
	- close
	- read
	- write
	- seek
	- tell

- Synchronization of parent and child thread
	-synchronization between read and wirte
	-	"	 between exec and exit

###*~ how to Pass Multi-OOM ~*
'Multi-OOM' test 40 thread 40 times
so to pass this test, each thread must free ~ exact all memeory ~
If you fail this test, check below 

	1. Does thread(struct) be free?
	2. Does array that used in thread all free?
	3. Does thread instruction free in memory stack(esp)?
	4. If instruction is failed parsing, is instuction not loaded on stack?

## [Fianl Assignment](https://github.com/ununbum/OS/tree/master/os_prj3_42.tar/42)
> Add User space to exec user program

**TODO List**
- Make Page and Page table to manamge memory
	- page managing Algotrithm
	- page fault scinario

- Make Virtual Space for page swap

~- exec user program~




