#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>

#define N 512
#define T 14
#define W 5
#define MAXV 256
#define MAXAB(a,b) ((a) > (b) ? (a) : (b)) 
#define MINAB(a,b) ((a) < (b) ? (a) : (b)) 

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
//int test[N][N] = {
//    {1,2,3,4,5,6,7,8,9,10},
//    {2,3,4,5,6,0,1,2,3,4},
//    {2,3,9,8,5,5,1,7,3,6},
//    {2,3,4,7,6,9,5,9,7,4},
//    {5,6,9,5,8,8,5,2,3,6},
//    {2,3,6,9,8,9,1,9,9,4},
//    {2,3,6,5,6,5,8,7,3,8},
//    {0,6,4,7,6,8,1,2,7,4},
//    {1,3,4,5,6,6,8,2,3,4},
//    {7,3,4,5,6,0,1,2,3,4},
//};
//



int test[N][N];
int result[N][N];

void median(void) {
    int n = omp_get_thread_num();
    // each threads calculate some points
    // as if there are only T-1 threads 
    // and the last thread may do few things
   
    int per_thread;
    per_thread = N * N / T;    
    int start = n * per_thread;
    int end = start + per_thread;
    int is, js, ie, je, i, j;
    int total;
    int tmp[MAXV];
    int left = N * N - per_thread * T;

    while (start < end) {
        is = MAXAB(start / N - W / 2, 0);
        js = MAXAB(start % N - W / 2, 0);
        ie = MINAB(is + W, N-1);
        je = MINAB(js + W, N-1);

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
    
    if (n < left){
        start =  per_thread * T+n;

        is = MAXAB(start / N - W / 2, 0);
        js = MAXAB(start % N - W / 2, 0);
        ie = MINAB(is + W, N-1);
        je = MINAB(js + W, N-1);

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
