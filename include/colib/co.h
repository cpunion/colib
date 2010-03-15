#ifndef CO_H_
#define CO_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef void (*co_func)(void *);

struct co_context;

struct co_context*
co_create (co_func func, void *arg, void *stack, unsigned long ssize);

void
__attribute__ ((__noinline__, __regparm__(2)))
co_transfer (struct co_context* from, struct co_context* to);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // CO_H_

