#ifndef COLIB_CONFIG_H_
#define COLIB_CONFIG_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct co_alloc* co_alloc_t;

struct co_alloc
{
    void* (*alloc)(size_t size);
    void (*free)(void* p, size_t size);
};

static
void __default_free(void* p, size_t size)
{
    free(p);
}

static
co_alloc_t default_alloc()
{
    static struct co_alloc alloc = {0, 0};
    if (!alloc.alloc) {
        alloc.alloc = &malloc;
        alloc.free = __default_free;
    }
    return &alloc;
}


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* COLIB_CONFIG_H_ */

