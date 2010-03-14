#include "co.h"
#include <stdlib.h>
#include <stdio.h>

co_context_t ctx1;
co_context_t ctx2;

void test1(void* p) {
    (void)p;
    int i;
    for (i=0; i<10000 * 10000; i++) {
        co_transfer(ctx1, ctx2);
    }
    exit(0);
}

void test2(void* p) {
    (void)p;
    int i;
    for (i=0; i<10000 * 10000; i++) {
        co_transfer(ctx2, ctx1);
    }
    exit(0);
}

int main() {
    enum {STACK_SIZE = 4096};
    char mainStack[64];
    char stack1[STACK_SIZE];
    char stack2[STACK_SIZE];
    co_context_t mainCtx = co_create(0, 0, mainStack, sizeof(mainStack));
    ctx1 = co_create(test1, (void*)0, stack1, STACK_SIZE);
    ctx2 = co_create(test2, (void*)0, stack2, STACK_SIZE);

    co_transfer(mainCtx, ctx1);
    return 0;
}

