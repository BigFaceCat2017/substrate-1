#include "CydiaSubstrate.h"
#include <stdio.h>
#include <dlfcn.h>

typedef int (*fact_t)(int);

fact_t orig_fact;

int my_fact(int n) {
	printf("calling fact_sub(%d)\n", n);
	int res = orig_fact(n);
	printf("res = %d\n", res);
	res *= 2;
	printf("real res = %d\n", res);
	return res;
}

__attribute__ ((constructor))
void init(void) {
	void *handle = dlopen(NULL, RTLD_NOW | RTLD_GLOBAL);
	printf("hooker handle = %p\n", handle);
	void *fact = dlsym(handle, "fact_sub");
	printf("hooker fact_sub = %p\n", fact);
	void *fact2 = dlsym(handle, "fact");
	printf("hooker fact = %p\n", fact2);
	MSHookFunction(fact, (void *)my_fact, (void **)&orig_fact);
}
