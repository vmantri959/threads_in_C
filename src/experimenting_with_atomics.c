#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

#ifdef USE_ATOMICS
_Atomic int x = 0;
#else
int x = 0;
#endif

int increment(void* arg)
{
	for(int i = 0; i < 1000; i++)
	{
		for(volatile int j = 0; j < 1000; j++); //Uncommenting this line will give the right output for the non-atomic case as well!
#ifdef USE_ATOMICS
                atomic_fetch_add(&x, 1);
#else
		x = x + 1;
#endif
	}
	return 0;
}

int main(void) 
{
	thrd_t thread_A;
	thrd_t thread_B;

	thrd_create(&thread_A, increment, NULL);
	thrd_create(&thread_B, increment, NULL);

	int result;
	thrd_join(thread_A, &result);
	thrd_join(thread_B, &result);
	printf("The value of x is %d\n", x);

	return 0;
}
