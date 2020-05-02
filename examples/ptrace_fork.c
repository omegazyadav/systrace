#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>

int main(int argc, char *argv[]) 
{
    pid_t pid;
    long ret;
    struct user_regs_struct value;

    pid = fork();


    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        // Perform a syscall after ptrace call.     
        execl("/bin/ls", "ls", NULL);
    } else {
        wait(NULL);
        ret = ptrace(PTRACE_PEEKUSER, pid, 4*value.orig_rax, NULL);
        printf("Child executed a system call with number %ld\n",ret);
        ptrace(PTRACE_CONT, pid, NULL, NULL);

    }

    return 0;
}

