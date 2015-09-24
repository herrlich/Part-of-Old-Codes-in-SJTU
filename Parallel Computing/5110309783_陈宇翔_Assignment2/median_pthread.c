#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define N 5
#define T 4
#define WINDOW_SIZE 3
#define MAXV 256
#define GETMAX(a,b) ((a) > (b) ? (a) : (b)) 
#define GETMIN(a,b) ((a) < (b) ? (a) : (b)) 


int test[N][N];
int result[N][N];

void median(void *args) {
    int n = (int)args;
    int pixel_per_thread = N * N / T;    
    int start = n * pixel_per_thread;
    int end = start + pixel_per_thread;
    int is, js, ie, je, i, j;
    int total;
    int temp[MAXV];
    int left = N * N - pixel_per_thread * T;

    while (start < end) {
        is = GETMAX(start / N - WINDOW_SIZE / 2, 0);
        js = GETMAX(start % N - WINDOW_SIZE / 2, 0);
        ie = GETMIN(is + WINDOW_SIZE, N);
        je = GETMIN(js + WINDOW_SIZE, N);

        for (i = 0; i < MAXV; ++i) temp[i] = 0;

        for (i = is; i < ie; ++i)
            for (j = js; j < je; ++j)
                temp[test[i][j]]++;
        
        total = 0;
        i = 0;
        while (total < (je - js) * (ie - is)/2 + 1) total += temp[i++];
        result[start/N][start%N] = i - 1;
        start++;
    }
    
    if (n < left){
        start =  pixel_per_thread * T+n;

        is = GETMAX(start / N - WINDOW_SIZE / 2, 0);
        js = GETMAX(start % N - WINDOW_SIZE / 2, 0);
        ie = GETMIN(is + WINDOW_SIZE, N-1);
        je = GETMIN(js + WINDOW_SIZE, N-1);

        for (i = 0; i < MAXV; ++i) temp[i] = 0;

        for (i = is;i < ie; ++i)
            for (j = js;j < je; ++j)
                temp[test[i][j]]++;
        
        total = 0;
        i = 0;
        while (total < (je - js) * (ie - is)/2 + 1) total += temp[i++];
        result[start/N][start%N] = i - 1;
    }
}

int main (int argc, char *argv[]) {
    
    FILE *f = fopen("img.txt", "r");
   
    int m, n, i, j;
	int value;
    for (m = 0; m < N; ++m)
        for (n = 0; n < N; ++n)
            fscanf(f, "%d", &test[m][n]);
   
	pthread_t pid[T];
	for (i = 0; i < 5; ++i) {
		value = pthread_create(&pid[i], NULL, (void*) median, (void *)i);
		if (value != 0)
			perror("Create pthread error!\n");
	}

    for (i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            printf("%d ", result[i][j]);
		}
        printf("\n");
    }
    return 0;
}
