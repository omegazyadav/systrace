#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc,char *argv[]) 
{
    if(argc < 2) {
        fprintf(stdout,"Usage: %s [command]\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    long orig_rax,rax;
    int status,count=0;
    pid_t pid;
    int insyscall=0;

    pid = fork();

    if (pid==0) {
       ptrace(PTRACE_TRACEME,pid,NULL,NULL);
       // execl("/bin/ls","ls",NULL);
        execvp(argv[1],argv+1);
    } else {
       // waitpid(pid,&status,0);
         
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
    return 0;
}
