#ifndef COLIB_SCHED_H_
#define COLIB_SCHED_H_

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct co_sched* co_sched_t;

typedef void(*co_proc)(void*);

co_sched_t co_sched_new(co_alloc_t alloc);

void co_sched_delete(co_sched_t sched);

void co_sched_spawn(co_sched_t sched, co_proc proc, void* arg,
        void* stack, size_t stackSize);

void co_sched_run(co_sched_t sched);

void co_sched_yield(co_sched_t sched);

void co_sched_schedule(co_sched_t sched);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* COLIB_SCHED_H_ */

