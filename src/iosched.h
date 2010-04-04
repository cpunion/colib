#ifndef COLIB_IOSCHED_H_
#define COLIB_IOSCHED_H_

#include "colib/config.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct co_iosched* co_iosched_t;

co_iosched_t co_iosched_new(co_alloc_t alloc);

void co_iosched_delete(co_iosched_t sched);

int co_iosched_run(co_iosched_t sched);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* COLIB_IOSCHED_H_ */

