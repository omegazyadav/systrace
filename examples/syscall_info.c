#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/ptrace.h>

#include "sys_info.h"

int main(int argc, char *argv[])
{
    int status;
    struct user_regs_struct regs;

    struct ptrace_syscall_info sys_info;
    
    pid_t pid;
    pid=fork();

    if(pid==0){
        ptrace(PTRACE_TRACEME,pid,0,0);
        execvp(argv[1],argv+1);

    } else {
            while(1){
                waitpid(pid,&status,0);
                //wait(&status);
                ptrace(PTRACE_SETOPTIONS,pid,0,PTRACE_O_EXITKILL);
           
                if(WIFEXITED(status))
                break;
                
                struct user_regs_struct regs;
                ptrace(PTRACE_GETREGS,pid,0,&regs);
                
                ptrace(PTRACE_GET_SYSCALL_INFO,pid,sizeof(sys_info),&sys_info);
                 
                ptrace(PTRACE_SYSCALL,pid,0,0);
               
                print_regs(regs);
                print_syscall_info(sys_info);
                
            }
        }
    return 0;
}
