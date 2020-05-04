#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc,char *argv[]) 
{
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

            if(WIFEXITED(status))
            break;

            orig_rax=ptrace(PTRACE_PEEKUSER,pid,8*ORIG_RAX,NULL);
            if(orig_rax == SYS_mmap){

            if(insyscall==0) {
            /* Entrypoint for the syscall. */
                insyscall=1;
                count++;

            } else {
                /* Exit point for the syscall */
                rax=ptrace(PTRACE_PEEKUSER,pid,8*RAX,NULL);
                insyscall=0;
                 }
            }
            ptrace(PTRACE_SYSCALL,pid,NULL,NULL);
        }
        printf("mmap() syscall invoked for %d times\n",count);
    }
    return 0;
}
