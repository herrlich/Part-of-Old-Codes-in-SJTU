#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_PRODUCER_NUM 5
#define MAX_CONSUMER_NUM 5
#define MAX_SLEEP_TIME 60
#define BUFFER_SIZE 5
#define MAX_PROCESS_SLEEP 10
#define MAX_RAND 1000
#define TRUE 1

typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE];
sem_t full,empty;
pthread_mutex_t mutex;
int in = 0, out = 0;

int insert_item(buffer_item item) {
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	buffer[in] = item;
	printf("buffer[%d]:", in);
	in = (in + 1) % BUFFER_SIZE;
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
	return 0;
}

int remove_item(buffer_item *item) {
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	*item = buffer[out];
	buffer[out] = -1;
	printf("buffer[%d]:", out);
	out = (out + 1) % BUFFER_SIZE;
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
	return 0;
}

void *producer(void *param) {
	buffer_item rand_item;
	int sleep_time;

	while (TRUE) {
		sleep_time = rand() % MAX_PROCESS_SLEEP + 1;
		sleep(sleep_time);
		rand_item = rand() % MAX_RAND + 1;
		if (insert_item(rand_item))
			printf("Insert item %d failed!\n", rand_item);
		printf("Producer produced %d\n", rand_item);
	}
}

void *consumer(void * param) {
	buffer_item rand_item;
	int sleep_time;

	while (TRUE) {
		sleep_time = rand() % MAX_PROCESS_SLEEP + 1;
		sleep(sleep_time);
		if (remove_item (&rand_item))
			printf("Remove item failed!\n");
		printf("Consumer consumed %d\n", rand_item);
	}
}

int main(int argc, char *argv[]) {
	int producer_num, consumer_num, sleep_time;
	pthread_t pid[MAX_PRODUCER_NUM];
	pthread_t cid[MAX_CONSUMER_NUM];
	int i, value;
	for (i = 0; i < BUFFER_SIZE; ++i) buffer[i] = -1;
	if (argc >= 4) {
		producer_num = atoi(argv[1]);
		consumer_num = atoi(argv[2]);
		sleep_time = atoi(argv[3]);
	}
	else {
		if (argc == 3) {
			producer_num = atoi(argv[1]);
			consumer_num = atoi(argv[2]);
			sleep_time = MAX_SLEEP_TIME;
		}
		else {
			if (argc == 2) {
				producer_num = atoi(argv[1]);
				consumer_num = MAX_CONSUMER_NUM;
				sleep_time = MAX_SLEEP_TIME;
			}
			else {
				producer_num = MAX_PRODUCER_NUM;
				consumer_num = MAX_CONSUMER_NUM;
				sleep_time = MAX_SLEEP_TIME;
			}
		}
	}
	if (producer_num > MAX_PRODUCER_NUM) {
		printf("MAX_PRODUCER_NUM = 5!\n");
		producer_num = MAX_PRODUCER_NUM;
	}
	if (consumer_num > MAX_CONSUMER_NUM) {
		printf("MAX_CONSUMER_NUM = 5!\n");
		consumer_num = MAX_CONSUMER_NUM;
	}
	if (sleep_time > MAX_SLEEP_TIME) {
		printf("MAX_SLEEP_TIME = 60!\n");
		sleep_time = MAX_SLEEP_TIME;
	}
	printf("producer num = %d, consumer num = %d, sleep time = %d\n", producer_num, consumer_num, sleep_time);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, BUFFER_SIZE);
	pthread_mutex_init(&mutex, NULL);
	srand(time(NULL));

	for (i = 0; i < producer_num; ++i) {
		value = pthread_create(&pid[i], NULL, (void *)producer, NULL);
		if (value != 0)
			perror("Create producers error!\n");
	}
	for (i = 0; i < consumer_num; ++i) {
		value = pthread_create(&cid[i], NULL, (void *)consumer, NULL);
		if (value != 0)
			perror("Create consumers error!\n");
	}
	sleep(sleep_time);
	return 0;
}
