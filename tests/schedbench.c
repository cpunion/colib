#include "colib/co.h"
#include "colib/sched.h"
#include <stdio.h>

struct co_sched* g_sched;

void test(void* p)
{
    int i;
    for (i=0; i<10000 * 10000; i++)
    {
        co_sched_schedule(g_sched);
    }
}

int main()
{
    g_sched = co_sched_new(0);

    char stack1[4096];
    char stack2[4096];

    co_sched_spawn(g_sched, test, (void*)0, stack1, sizeof(stack1));
    co_sched_spawn(g_sched, test, (void*)0, stack2, sizeof(stack2));

    co_sched_run(g_sched);

    co_sched_delete(g_sched);

    return 0;
}

