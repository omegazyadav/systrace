# Systrace 
## Customized Strace Implementation
Strace is a popular system call tracing tool which is based on ptrace() syscall. 
Ptrace capture all the system call running inside the OS and has ability to
inject the custom code into the system call invoked by user level program in
order to moniter or alter the performance of the  system. GDB extensively
uses this for debugging the porgram. Beside the debugging folks, 
CRIU(Checkpoint and Restore at Userspace) extensively uses ptrace for checkpointing 
the process/task running on the system.

systrace on the other hand does nothing but basic implementation of the ptrace
system call. I have created this just to know more about ptrace syscall and to
learn more about Linux Kernel Internals.  

### Directories 
* exmaple
This directory contains the basic demonstration of ptrace system call.  

### Systrac
This program list all the syscall number invoked by the particular command while running along with different register
value returned by the syscall. 

How to use it?
1. Compile the C progra.
``` gcc -o systrace systrace.c ``` 
2. Run the systrace binary. 
``` ./systrace [command]``` 
for eg. ``` ./systrace ls ```

### Happy Hacking!
