#include "colib/sched.h"

void async(void(*func)(co_sched_t))
{
	co_sched_t sched = co_sched_new(0);
	func(sched);
}

void work(co_sched_t sched) {
}

#define LAMBDA(type,body) \
	struct Lambda { \
		type operator()body \
	}

int main() {
	LAMBDA(int,(int a, int b){
		return 0;
	}) x;
	x(3,4);
	async(work);
	return 0;
}

