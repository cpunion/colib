#include "colib/co.h"
#include "colib/sched.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct co_sched* g_sched;

static int counter = 0;

void test(void* p)
{
    while (1)
    {
        if (++counter > 2 * 10000 * 10000)
            _exit(0);
        co_sched_schedule(g_sched);
    }
}

int main()
{
    g_sched = co_sched_new();

    enum { THREAD_COUNT = 1000 };
    enum { STACK_SIZE = 2048 };
    char* stack = malloc(THREAD_COUNT * STACK_SIZE);
    int i;
    for (i = 0; i < THREAD_COUNT; i ++) {
        co_sched_append(g_sched, co_create(test, (void*)0, stack + i * STACK_SIZE, STACK_SIZE));
    }

    co_sched_run(g_sched);

    co_sched_delete(g_sched);

    return 0;
}

