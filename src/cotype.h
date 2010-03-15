#ifndef CO_TYPE_H_
#define CO_TYPE_H_

struct co_context {
    void **sp;

    struct co_context* prev;
    struct co_context* next;
    unsigned long flags;
};

#endif // CO_TYPE_H_

