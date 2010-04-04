#include "iosched.h"
#include <sys/epoll.h>

struct co_iosched
{
    co_alloc_t alloc;
	int epollfd;
};

co_iosched_t co_iosched_new(co_alloc_t alloc)
{
	co_iosched_t sched = (co_iosched_t)
		alloc->alloc(sizeof(struct co_iosched));

	sched->epollfd = epoll_create(1024);
	if (-1 == sched->epollfd) {
		return 0;
	}

	sched->alloc = alloc;
	return sched;
}

void co_iosched_delete(co_iosched_t sched)
{
	sched->alloc->free(sched, sizeof(struct co_iosched));
}

int co_iosched_run(co_iosched_t sched)
{
	enum { MAX_EVENTS = 64 };
	struct epoll_event events[MAX_EVENTS];

	int ret = epoll_wait(sched->epollfd, events, MAX_EVENTS, -1);
	if (-1 == ret) {
		return -1;
	}

	int i;
	for (i = 0; i < ret; ++ i) {
		struct epoll_event* event = &events[i];
	}

	return 0;
}

