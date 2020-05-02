#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/user.h>

int main(int argc, char *argv[]) 
{
    pid_t pid;
    int wstatus;
    long orig_eax;
    struct user_regs_struct value;

    pid = fork();


    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        // Perform a syscall after ptrace call.     
        execl("/bin/ls", "ls", NULL);
    } else {
        waitpid(pid, &wstatus, 0);
      	// wait(NULL);
        orig_eax = ptrace(PTRACE_PEEKUSER, pid, 8 * ORIG_RAX, NULL);
        printf("Child executed a system call with number %ld\n",orig_eax);
        ptrace(PTRACE_CONT, pid, NULL, NULL);

    }

    return 0;
}

