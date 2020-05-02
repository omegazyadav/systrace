# Systrace 
## Customized Strace Implementation
Strace is a popular system call tracing tool which is based on ptrace() syscall. 
Ptrace capture all the system call running inside the OS and has ability to
inject the custom code into the system call invoked by user level program in
order to moniter or alter the performance of the  system. GNU gdb extensively
uses this for debugging the porgram. 

systrace on the other hand does nothing but basic implementation of the ptrace
system call. I have created this just to know more about ptrace syscall and to
learn more about Linux Kernel Internals.  

### Directories 
* exmaple
This directory contains the basic demonstration of ptrace system call.  
