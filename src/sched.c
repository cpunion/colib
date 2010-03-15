#include "cotype.h"
#include "colib/co.h"
#include "colib/sched.h"
#include <stdlib.h>
#include <string.h>

struct run_queue {
    struct co_context* head;
    struct co_context* tail;
};

struct co_sched
{
    struct run_queue run_queue;
    struct co_context* current;
    struct co_context* main;
};

struct co_sched* co_sched_new()
{
    struct co_sched* sched = (struct co_sched*)malloc(sizeof(struct co_sched));
    memset(sched, 0, sizeof(struct co_sched));
}

void co_sched_delete(struct co_sched* sched)
{
    free(sched);
}

void co_sched_append(struct co_sched* sched, struct co_context* ctx)
{
    struct run_queue* rq = &sched->run_queue;

    if (rq->tail) {
        rq->tail->next = ctx;
        ctx->prev = rq->tail;
    }
    rq->tail = ctx;

    if (!rq->head) {
        rq->head = ctx;
    }

    ctx->next = 0;
}

static
void co_sched_run_next_(struct co_sched* sched)
{
    struct run_queue* rq = &sched->run_queue;
    struct co_context* ctx = rq->head;
    if (ctx->next) {
        ctx->next->prev = 0;
    }
    rq->head = ctx->next;
    if (!rq->head) {
        rq->tail = 0;
    }
    ctx->next = 0;
    ctx->prev = 0;

    struct co_context* current = sched->current;
    sched->current = ctx;
    co_transfer(current, ctx);
    sched->current = current;
}

void co_sched_run(struct co_sched* sched)
{
    char stack[64];
    sched->main = co_create(0, 0, stack, sizeof(stack));
    sched->current = sched->main;

    struct run_queue* rq = &sched->run_queue;

    while(rq->head) {
        co_sched_run_next_(sched);
    }
}

void co_sched_yield(struct co_sched* sched)
{
    co_transfer(sched->current, sched->main);
}

void co_sched_schedule(struct co_sched* sched)
{
    co_sched_append(sched, sched->current);
    co_sched_run_next_(sched);
}

