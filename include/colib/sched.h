#ifndef CO_SCHED_H_
#define CO_SCHED_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct co_sched;
struct co_context;

typedef void(*co_proc)(void*);

struct co_sched* co_sched_new();

void co_sched_delete(struct co_sched* sched);

void co_sched_spawn(struct co_sched* sched, co_proc proc, void* arg,
        void* stack, unsigned long stackSize);

void co_sched_append(struct co_sched* sched, struct co_context* ctx);

void co_sched_run(struct co_sched* sched);

void co_sched_yield(struct co_sched* sched);

void co_sched_schedule(struct co_sched* sched);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CO_SCHED_H_

