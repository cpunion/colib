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
    g_sched = co_sched_new();

    char stack1[4096];
    struct co_context* ctx1 = co_create(test, (void*)0, stack1, sizeof(stack1));
    char stack2[4096];
    struct co_context* ctx2 = co_create(test, (void*)0, stack2, sizeof(stack2));

    co_sched_append(g_sched, ctx1);
    co_sched_append(g_sched, ctx2);

    co_sched_run(g_sched);

    co_sched_delete(g_sched);

    return 0;
}

