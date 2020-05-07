#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/reg.h>
#include <wait.h>


int main(int argc, char *argv[])
{
    int orig_rax,rax;
    int status,pid,ret;

    /* 
     * Bring the process from /proc direcotory and attach to the ptrace 
     * For this we use command line arguments and to convert the stirng 
     * into the signed long type integer strtol() syscall. 
     */
    
    if(argc<2 || argv[1]=="--help"){
        fprintf(stdout,"Usage: ./omega /proc/[pid]\n");
        exit(EXIT_FAILURE);
    }
    
    pid=strtol(argv[1],NULL,10);
    printf("The pid of a process is :%d\n",pid);

    if(ptrace(PTRACE_ATTACH,pid,0,0)!=0)
        printf("Couldnot attach the user \n");


    /* 
     * Now check what the process was executing in the /proc directory. 
     */

       while(1) {
            wait(&status);
            ptrace(PTRACE_SETOPTIONS,pid,0,PTRACE_O_EXITKILL);

            if(WIFEXITED(status))
            break;
            struct user_regs_struct regs;
            ptrace(PTRACE_GETREGS, pid, 0, &regs);
             long syscall = regs.orig_rax;

            /* Print a representation of the system call */
                fprintf(stderr, "%ld(%ld, %ld, %ld, %ld, %ld, %ld)\n",
                syscall,
                (long)regs.rdi, (long)regs.rsi, (long)regs.rdx,
                (long)regs.r10, (long)regs.r8,  (long)regs.r9);


            ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
        }
    }
