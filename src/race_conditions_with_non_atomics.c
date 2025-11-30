#include <stdio.h>
#include <threads.h>
#include <stdbool.h>
#include <time.h>

int x = 5;

int checker(void* arg)
{
	while(true)
	{
		if((x % 5) == 0)
		{
			//Introduce redudant task:
			for (volatile int i = 0; i < 100000; i++);
			int y = x;
			printf("Value of y should be divisible by 5, but is %d\n", y);
		}
		thrd_sleep(&(struct timespec) { .tv_sec = 0, .tv_nsec = 330000000}, NULL);
	}

	return 0;
}

int modifier(void* arg)
{
	while(true)
	{
		x++;
		thrd_sleep(&(struct timespec) { .tv_sec = 0, .tv_nsec = 3300000}, NULL);
	}
	return 0;
}

int main(void)
{
	thrd_t checker_thrd;
	thrd_t modifier_thrd;

	thrd_create(&checker_thrd, checker, NULL);
	thrd_create(&modifier_thrd, modifier, NULL);

	int result;
	thrd_join(checker_thrd, &result);
	thrd_join(modifier_thrd, &result);

	return 0;
}
