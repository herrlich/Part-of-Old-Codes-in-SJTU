#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX_WORKING_TIME 20
#define BUFFER_SIZE 5
#define MAX_RAND 1000
#define MAX_PROCESS_SLEEP 5

void producer(void);
void consumer(void);

typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];
int full = 0;
int empty = BUFFER_SIZE;
int in = 0, out = 0, cutting = 0;
int sleep_time;
static omp_lock_t lock;
time_t end_time;

int main(int argc, char *argv[]) {
	int working_time, i;
	for (i = 0; i < BUFFER_SIZE; ++i) buffer[i] = -1;
	working_time = MAX_WORKING_TIME;
	printf("working_time = %d\n", working_time);
	srand(time(NULL));
	end_time = time(NULL) + MAX_WORKING_TIME;
#	pragma omp parallel sections
	{
#	pragma omp section
		producer();
#	pragma omp section
		consumer();
	}
	return 0;
}

int insert_item(buffer_item item) {
	if (empty == 0) return 1;
#	pragma omp atomic
	--empty;
	omp_set_lock(&lock);
	buffer[in] = item;
	if (empty != BUFFER_SIZE - 1 || cutting == 1)
		printf("Customer %d is waiting at the %dth chair!\n", item, in);
	in = (in + 1) % BUFFER_SIZE;
	omp_unset_lock(&lock);
#	pragma omp atomic
	++full;
	return 0;
}

int remove_item(buffer_item *item) {
	while (empty == BUFFER_SIZE) {
		printf("No customer now, so sleeping!\n");
		sleep(1);
	}
#	pragma omp atomic
	--full;
	omp_set_lock(&lock);
	cutting = 1;
	*item = buffer[out];
	buffer[out] = -1;
	printf("Customer %d is having his hair cut!\n", *item);
	out = (out + 1) % BUFFER_SIZE;
	omp_unset_lock(&lock);
#	pragma omp atomic
	++empty;
	return 0;
}

void producer(void) {
	buffer_item rand_item;

	while (end_time > time(NULL)) {
		sleep_time = rand() % MAX_PROCESS_SLEEP;
		sleep(sleep_time);
		rand_item = rand() % MAX_RAND + 1;
		printf("Customer %d comes!\n", rand_item);
		if (insert_item(rand_item))
			printf("Customer %d finds no room and leaves!\n", rand_item);
	}
}

void consumer(void) {
	buffer_item rand_item;

	while (end_time > time(NULL)) {
		if (remove_item (&rand_item)) 
			printf("Remove item failed!\n");
		sleep(5);
		cutting = 0;
		printf("Customer %d finished!\n", rand_item);
	}
}

