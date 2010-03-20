#ifndef COLIB_CONFIG_H_
#define COLIB_CONFIG_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


struct co_alloc
{
    void* (*alloc)(unsigned long size);
    void (*free)(void* p, unsigned long size);
};

static
void __default_free(void* p, unsigned long size)
{
    free(p);
}

static
struct co_alloc* default_alloc()
{
    static struct co_alloc alloc = {0, 0};
    if (!alloc.alloc) {
        alloc.alloc = malloc;
        alloc.free = __default_free;
    }
    return &alloc;
}


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* COLIB_CONFIG_H_ */

