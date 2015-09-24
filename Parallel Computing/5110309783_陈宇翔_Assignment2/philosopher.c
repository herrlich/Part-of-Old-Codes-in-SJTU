#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_PHILOSOPHER_NUM 5
#define MAX_SLEEP_TIME 15 
#define MAX_EAT_TIME 5
#define TRUE 1
#define TRYING_SEGMENTS 3

int buffer[5] = {0, 0, 0, 0, 0}; //presenting the forks
pthread_mutex_t mutex;

int getting(int person) {//trying to get the forks
	pthread_mutex_lock(&mutex);
	int left = person % 5;
	int right = (person + 4) % 5;
	if (buffer[left] == 0 && buffer[right] == 0) {
		buffer[left] = 1;
		buffer[right] = 1;
		pthread_mutex_unlock(&mutex);
		printf("The %dth philosopher is eating!\n", person);
		return 0;
	}
	pthread_mutex_unlock(&mutex);
	return 1;
}

int releasing(int person) {
	pthread_mutex_lock(&mutex);
	int left = person % 5;
	int right = (person + 4) % 5;
	buffer[left] = 0;
	buffer[right] = 0;
	printf("The %dth philosopher finished!\n", person);
	pthread_mutex_unlock(&mutex);
	return 0;
}

void *dining(void *args) {
	int num = (int)args;
	int sleep_time, eat_time;

	while (TRUE) {
		sleep_time = rand() % TRYING_SEGMENTS + 1;
		sleep(sleep_time);
		eat_time = rand() % MAX_EAT_TIME + 1;
		if (getting(num) == 0) {
			sleep(eat_time);
			releasing(num);
		}
		else 
			printf("Someone is using the fork of %dth philosopher!\n", num);
	}
}

int main(int argc, char *argv[]) {
	int sleep_time = MAX_SLEEP_TIME;
	pthread_t pid[MAX_PHILOSOPHER_NUM];
	int i, value;
	printf("Eat time = 1~%d\n", MAX_EAT_TIME);
	pthread_mutex_init(&mutex, NULL);
	srand(time(NULL));
	for (i = 0; i < 5; ++i) {
		value = pthread_create(&pid[i], NULL, dining, (void *)i);
		if (value != 0)
			perror("Create dining error!\n");
	}
	sleep(sleep_time);
	return 0;
}
