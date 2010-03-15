#include "colib/co.h"
#include <stdlib.h>
#include <stdio.h>

enum { THREAD_COUNT = 32 };
enum { STACK_SIZE = 4096 };
struct co_context* ctxs[THREAD_COUNT];
static int cur = 0;

void test(void* p) {
    while(1) {
        //printf("test %d, %d\n", cur, (int)p);
        int old = cur++;
        if (cur >= THREAD_COUNT) cur = 0;
        printf("transfer from %d to %d\n", old, cur);
        co_transfer(ctxs[old], ctxs[cur]);
    }
}

int main() {
    char mainStack[64];
    struct co_context* mainCtx = co_create(0, 0, mainStack, sizeof(mainStack));

    int i;
    for (i=0; i<THREAD_COUNT; i++) {
        char* stack = malloc(STACK_SIZE);
        printf("stack: %p\n", stack);
        ctxs[i] = co_create(test, (void*)(size_t)i, stack, STACK_SIZE);
        //printf("init coroutine: %d\n", i);
    }
    co_transfer(mainCtx, ctxs[0]);
    return 0;
}

