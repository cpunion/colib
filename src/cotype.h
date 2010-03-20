#ifndef COLIB_TYPE_H_
#define COLIB_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct co_context {
    void **sp;

    struct co_context* prev;
    struct co_context* next;
    unsigned long flags;
};

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* COLIB_TYPE_H_ */

