#ifndef _syscall_info
#define _syscall_info

void *op_to_info(__u8 op) 
{
    switch (op) {
        case (PTRACE_SYSCALL_INFO_NONE):
            printf("NONE");
            break;
        case (PTRACE_SYSCALL_INFO_ENTRY):
            printf("ENTRY");
            break;
        case (PTRACE_SYSCALL_INFO_EXIT):
            printf("EXIT");
            break;
        case (PTRACE_SYSCALL_INFO_SECCOMP):
            printf("SECCOMP");
            break;
    }
}

void print_regs(struct user_regs_struct regs)
{
    /* Print a representation of the system call */
    
    fprintf(stderr, "%ld(%ld, %ld, %ld, %ld, %ld, %ld)\n",
    regs.orig_rax,
    (long)regs.rdi, (long)regs.rsi, (long)regs.rdx,
    (long)regs.r10, (long)regs.r8,  (long)regs.r9);

}

void print_syscall_info(struct ptrace_syscall_info sys_info)
{
   printf("Type of the system call:%llx\n",sys_info.op);
   printf("Architecture:%d\n",sys_info.arch);
}

#endif /* _syscall_info */
