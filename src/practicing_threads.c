#include <threads.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
	int num1;
	int num2;
} curr_numbers;

mtx_t lock;
cnd_t cond;

int add_numbers(void* arg) //Need to be of return type int
{
	curr_numbers* given_nums = (curr_numbers*) arg;
	while(true)
	{
		if((given_nums->num1 + given_nums->num2) % 5 == 0)
		{
			mtx_lock(&lock);
			cnd_signal(&cond);
			mtx_unlock(&lock);
		}
		thrd_sleep(&(struct timespec) {.tv_sec=1}, NULL);
		given_nums->num1 += 1;
	}
	return EXIT_SUCCESS;
}

int print_divisible(void* arg)
{
	curr_numbers* given_nums = (curr_numbers*) arg;
	while(true)
	{
	        time_t start_time = time(NULL);	
		mtx_lock(&lock);
		cnd_wait(&cond, &lock);
		double elapsed_time = difftime(time(NULL), start_time);
		printf("Number %d is divisible by 5, received time in %f\n", (given_nums->num1) + (given_nums->num2), difftime(time(NULL), start_time));
		mtx_unlock(&lock);
	}
	return EXIT_SUCCESS;
}

int main(void)
{

	thrd_t add_numbers_thrd_ptr;
	thrd_t print_divisible_thrd_ptr;

	mtx_init(&lock, mtx_plain);
	cnd_init(&cond);

	curr_numbers sample;
	sample.num1 =  5; 
	sample.num2 =  5; 

	thrd_create(&add_numbers_thrd_ptr, add_numbers, (void*) &sample);
	thrd_create(&print_divisible_thrd_ptr, print_divisible, (void*) &sample);

	int result;
	thrd_join(add_numbers_thrd_ptr, &result);
	thrd_join(print_divisible_thrd_ptr, &result);

	mtx_destroy(&lock);
	cnd_destroy(&cond);
	return EXIT_SUCCESS;
}

