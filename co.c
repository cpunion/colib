#include "co.h"
#include <stdlib.h>

struct co_context {
  void **sp;
};

enum {
    MIN_STACK_SIZE = 4096
};

static void
co_init (void)
{
    co_func func;
    void* arg;

    asm (
    #if __amd64
        "movq %%r12, %0\n"
        "movq %%r13, %1\n"
    #elif __i386
        "movl %%esi, %0\n"
        "movl %%edi, %1\n"
    #endif
        : "=m"(func), "=m"(arg)
    );

    (*func)((void*)arg);
    abort();
}

asm (
".text\n"
".globl _co_transfer\n"
".globl co_transfer\n"
"_co_transfer:\n"
"co_transfer:\n"
#if __amd64
      #define NUM_SAVED 6
    "\tpush %rbp\n"
    "\tpush %rbx\n"
    "\tpush %r12\n"
    "\tpush %r13\n"
    "\tpush %r14\n"
    "\tpush %r15\n"
    "\tmov  %rsp, (%rdi)\n"
    "\tmov  (%rsi), %rsp\n"
    "\tpop  %r15\n"
    "\tpop  %r14\n"
    "\tpop  %r13\n"
    "\tpop  %r12\n"
    "\tpop  %rbx\n"
    "\tpop  %rbp\n"
#elif __i386
    #define NUM_SAVED 4
    "\tpush %ebp\n"
    "\tpush %ebx\n"
    "\tpush %esi\n"
    "\tpush %edi\n"
    "\tmovl %esp, (%eax)\n"
    "\tmovl (%edx), %esp\n"
    "\tpop  %edi\n"
    "\tpop  %esi\n"
    "\tpop  %ebx\n"
    "\tpop  %ebp\n"
#else
      #error unsupported CPU
#endif
    "\tret\n"
);

co_context_t
co_create (co_func func, void *arg, void *stack, unsigned long ssize)
{
    if (!stack || ssize < sizeof(struct co_context))
        return 0;

    co_context_t ctx = (co_context_t)stack;

    if (!func || ssize < MIN_STACK_SIZE) {
        ctx->sp = 0;
        return ctx;
    }

    stack += sizeof (struct co_context);
    ssize -= sizeof (struct co_context);

    ctx->sp = (void**)(ssize + (char*)stack);
    *--ctx->sp = (void*)abort;
    *--ctx->sp = (void*)co_init;
    *(ctx->sp - 3) = (void*)func;
    *(ctx->sp - 4) = (void*)arg;
    ctx->sp -= NUM_SAVED;
    return ctx;
}

