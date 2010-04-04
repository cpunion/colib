#ifndef COLIB_CO_H_
#define COLIB_CO_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct co_context* co_context_t;

typedef void (*co_func)(void *);


co_context_t
co_create (co_func func, void *arg, void *stack, size_t ssize);

void
co_delete(co_context_t ctx);

void
__attribute__ ((__noinline__, __regparm__(2)))
co_transfer (co_context_t from, co_context_t to);


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* COLIB_CO_H_ */

