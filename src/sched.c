#include "cotype.h"
#include "colib/config.h"
#include "colib/co.h"
#include "colib/sched.h"
#include <stdlib.h>
#include <string.h>

struct run_queue {
    co_context_t head;
    co_context_t tail;
};

struct co_sched
{
    co_alloc_t alloc;
    struct run_queue run_queue;
    co_context_t current;
    co_context_t main;
};

struct co_sched* co_sched_new(co_alloc_t alloc)
{
    if (!alloc) {
        alloc = default_alloc();
    }
    struct co_sched* sched = (struct co_sched*)alloc->alloc(sizeof(struct co_sched));
    sched->alloc = alloc;
    memset(sched, 0, sizeof(struct co_sched));
}

void co_sched_delete(struct co_sched* sched)
{
    sched->alloc->free(sched, sizeof(struct co_sched));
}

static
void co_sched_append(struct co_sched* sched, co_context_t ctx)
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

struct spawn_arg
{
    struct co_sched* sched;
    co_proc proc;
    void* arg;
    size_t need_free;
};

enum {
    F_NEED_FREE = 1,
    F_NEED_EXIT = 2,
};

static
void co_sched_warp(void* p)
{
    struct spawn_arg* sarg = (struct spawn_arg*)p;
    (*sarg->proc)(sarg->arg);
    sarg->sched->current->flags |= F_NEED_EXIT;
    if (sarg->need_free) {
        sarg->sched->current->flags |= F_NEED_FREE;
    }
    co_sched_schedule(sarg->sched);
}

enum { DEFAULT_STACK_SIZE = 4096 };


void co_sched_spawn(struct co_sched* sched, co_proc proc, void* arg,
        void* stack, size_t stackSize)
{
    struct spawn_arg* sarg = (struct spawn_arg*)stack;
    if (!stack) {
        stackSize = stackSize > DEFAULT_STACK_SIZE ? stackSize : DEFAULT_STACK_SIZE;
        stack = (void*)malloc(stackSize);
        sarg = (struct spawn_arg*)stack;
        sarg->need_free = 1;
    }
    else {
        sarg->need_free = 0;
    }
    sarg->sched = sched;
    sarg->proc = proc;
    sarg->arg = arg;

    stack = (char*)stack + sizeof(struct spawn_arg);
    stackSize -= sizeof(struct spawn_arg);
    co_context_t ctx = co_create(co_sched_warp, sarg, stack, stackSize);
    ctx->flags = 0;

    co_sched_append(sched, ctx);
}


static
void co_sched_run_next_(struct co_sched* sched)
{
    struct run_queue* rq = &sched->run_queue;
    while (rq->head) {
        co_context_t ctx = rq->head;
        if (ctx->next) {
            ctx->next->prev = 0;
        }
        rq->head = ctx->next;
        if (!rq->head) {
            rq->tail = 0;
        }
        ctx->next = 0;
        ctx->prev = 0;

        if (ctx->flags & F_NEED_EXIT) {
            if (ctx->flags & F_NEED_FREE) {
                // printf("free fiber\n");
                free(ctx->sp);
            }
            // printf("exit fiber\n");
            continue;
        }
        // printf("run fiber\n");

        co_context_t current = sched->current;
        sched->current = ctx;
        co_transfer(current, ctx);
        sched->current = current;
        return;
    }
    co_transfer(sched->current, sched->main);
}

void co_sched_run(struct co_sched* sched)
{
    char stack[64];
    sched->main = co_create(0, 0, stack, sizeof(stack));
    sched->current = sched->main;

    struct run_queue* rq = &sched->run_queue;

    while(rq->head) {
        // printf("run next\n");
        co_sched_run_next_(sched);
    }
    // printf("run exit\n");
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

