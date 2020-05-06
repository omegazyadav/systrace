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

    /* Bring the process from /proc direcotory and attach to the ptrace 
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

    ret=waitpid(pid,&status,WUNTRACED);

    /* 
     * Now check what the process was executing in the /proc directory. 
     */
    orig_rax=ptrace(PTRACE_SYSCALL,pid,8*ORIG_RAX,0);
    printf("The syscall associated with the child is %d\n",orig_rax);

    return 0;

}
