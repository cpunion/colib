#ifndef CO_H_
#define CO_H_

typedef void (*co_func)(void *);

typedef struct co_context* co_context_t;

co_context_t
co_create (co_func func, void *arg, void *stack, unsigned long ssize);

void
__attribute__ ((__noinline__, __regparm__(2)))
co_transfer (co_context_t from, co_context_t to);

#endif // CO_H_

