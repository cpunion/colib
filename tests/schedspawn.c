#include "colib/co.h"
#include "colib/sched.h"
#include <stdio.h>

struct co_sched* g_sched;

void test2(void* p)
{
    int i;
    for (i=0; i<2; i++) {
        printf("test2\n");
        co_sched_schedule(g_sched);
    }
    printf("test2 exit\n");
}
void test1(void* p)
{
    int i;
    for (i=0; i<5; i++) {
        printf("test1\n");
        co_sched_schedule(g_sched);
    }
    printf("test1 exit\n");
}
void test3(void* p)
{
    int i;
    for (i=0; i<8; i++) {
        printf("test3\n");
        co_sched_schedule(g_sched);
    }
    printf("test3 exit\n");
}
int main()
{
    g_sched = co_sched_new(0);

    char stack1[4096];
    char stack2[4096];
    char stack3[4096];
    co_sched_spawn(g_sched, test1, (void*)0, stack1, sizeof(stack1));
    co_sched_spawn(g_sched, test2, (void*)0, stack2, sizeof(stack2));
    co_sched_spawn(g_sched, test3, (void*)0, stack3, sizeof(stack3));

    co_sched_run(g_sched);

    co_sched_delete(g_sched);

    return 0;
}

