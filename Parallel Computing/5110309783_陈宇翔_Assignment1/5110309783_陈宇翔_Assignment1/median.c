#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>

#define N 512
#define T 10
#define WINDOW_SIZE 5
#define MAXV 256
#define MAXAB(a,b) ((a) > (b) ? (a) : (b)) 
#define MINAB(a,b) ((a) < (b) ? (a) : (b)) 


int test[N][N];
int result[N][N];

void median(void) {
    int n = omp_get_thread_num();
   
    int pixel_per_thread;
    pixel_per_thread = N * N / T;    
    int start = n * pixel_per_thread;
    int end = start + pixel_per_thread;
    int is, js, ie, je, i, j;
    int total;
    int tmp[MAXV];
    int left = N * N - pixel_per_thread * T;

    while (start < end) {
        is = MAXAB(start / N - WINDOW_SIZE / 2, 0);
        js = MAXAB(start % N - WINDOW_SIZE / 2, 0);
        ie = MINAB(is + WINDOW_SIZE, N-1);
        je = MINAB(js + WINDOW_SIZE, N-1);

        for (i=0; i<MAXV; ++i)
            tmp[i] = 0;

        for (i=is;i<ie;++i) {
            for (j=js;j<je;++j){
                tmp[test[i][j]]++;
            }
        }
        
        total = 0;
        i = 0;
        while (total < (je-js)*(ie-is)/2) total += tmp[i++];
        result[start/N][start%N] = i - 1;
        start++;
    }
    
    if (n < left){//这里分配未被线程整除的数据
        start =  pixel_per_thread * T+n;
        is = MAXAB(start / N - WINDOW_SIZE / 2, 0);
        js = MAXAB(start % N - WINDOW_SIZE / 2, 0);
        ie = MINAB(is + WINDOW_SIZE, N-1);
        je = MINAB(js + WINDOW_SIZE, N-1);
        for (i=0; i<MAXV; ++i)
            tmp[i] = 0;

        for (i=is;i<ie;++i) {
            for (j=js;j<je;++j){
                tmp[test[i][j]]++;
            }
        }
        total = 0;
        i = 0;
        while (total < (je-js)*(ie-is)/2) total += tmp[i++];
        result[start/N][start%N] = i - 1;
    }
}

int main (int argc, char *argv[])
{
    
    FILE *f = fopen("img.txt", "r");
   
    int h, w;
    int i,j;

    // read R data
    for (h = 0; h < N; ++h)
        for (w = 0; w < N; ++w)
            fscanf(f, "%d", &test[h][w]);
   
    #pragma omp parallel num_threads(T)
    median();

    for (i=0;i<N;++i) {
        for(j=0;j<N;++j)
            printf("%d ", result[i][j]);
        printf("\n");
    }

    // read R data
    for (h = 0; h < N; ++h)
        for (w = 0; w < N; ++w)
            fscanf(f, "%d", &test[h][w]);
   
    #pragma omp parallel num_threads(T)
    median();

    for (i=0;i<N;++i) {
        for(j=0;j<N;++j)
            printf("%d ", result[i][j]);
        printf("\n");
    }
    // read R data
    for (h = 0; h < N; ++h)
        for (w = 0; w < N; ++w)
            fscanf(f, "%d", &test[h][w]);
   
    #pragma omp parallel num_threads(T)
    median();

    for (i=0;i<N;++i) {
        for(j=0;j<N;++j)
            printf("%d ", result[i][j]);
        printf("\n");
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
