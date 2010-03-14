#ifndef CO_SCHED_H_
#define CO_SCHED_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct co_sched* co_sched_t;

co_sched_t co_sched_new();

void co_sched_delete(co_sched_t sched);

void co_sched_append(co_context_t ctx);

void co_sched_run(co_sched_t sched);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CO_SCHED_H_

