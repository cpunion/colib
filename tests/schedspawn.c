#include "colib/co.h"
#include "colib/sched.h"
#include <stdio.h>

struct co_sched* g_sched;

void test2(void* p)
{
    while (1) {
        printf("test2\n");
        co_sched_schedule(g_sched);
    }
}
void test1(void* p)
{
    while (1) {
        printf("test1\n");
        co_sched_schedule(g_sched);
    }
}
int main()
{
    g_sched = co_sched_new();

    char stack1[4096+24];
    char stack2[4096+24];
    co_sched_spawn(g_sched, test1, (void*)0, stack1, sizeof(stack1));
    co_sched_spawn(g_sched, test2, (void*)0, stack2, sizeof(stack2));

    co_sched_run(g_sched);

    co_sched_delete(g_sched);

    return 0;
}

