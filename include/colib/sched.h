#ifndef COLIB_SCHED_H_
#define COLIB_SCHED_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct co_alloc;

typedef struct co_sched* co_sched_t;

typedef void(*co_proc)(void*);

co_sched_t co_sched_new(struct co_alloc* alloc);

void co_sched_delete(co_sched_t sched);

void co_sched_spawn(co_sched_t sched, co_proc proc, void* arg,
        void* stack, unsigned long stackSize);

void co_sched_run(co_sched_t sched);

void co_sched_yield(co_sched_t sched);

void co_sched_schedule(co_sched_t sched);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* COLIB_SCHED_H_ */

