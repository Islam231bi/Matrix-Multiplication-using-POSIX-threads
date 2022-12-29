#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>


// struct to hold data passed to each thread
typedef struct arg_struct {
    int *A;
    int *B;
    int *C;
    int i,j,n,m,l;
}arg_struct;



#define Item(X, I, J, NCOL)      X[((J) + (I) * (NCOL))]

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult(int* A, int* B, int* C, int l, int m, int n)
{
    for(int i=0; i<l; i++)
        for(int j=0; j<n; j++)
        {
            int sum = 0;
            for(int k=0; k<m; k++){
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            }
            Item(C, i, j, n) = sum;
        }
}

void* mul_element(void* argument){
    struct arg_struct *args = (struct arg_struct *)argument;

    int s = 0;
    for(int k=0; k<args->m; k++){
        s+= Item(args->A, args->i, k, args->m) * Item(args->B, k, args->j, args->n);
    }
    int *p = (int*)malloc(sizeof(int));
    *p = s;
    pthread_exit(p);
}

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult_v1(int* A, int* B, int* C, int l, int m, int n)
{
    // thread pool size (size of resulted matrix)
    int thread_cnt = l*n;
    pthread_t *t;
	t = (pthread_t*)malloc(thread_cnt*sizeof(pthread_t));
    int cnt = -1;
    
    for (int i=0; i<l; i++){
        for(int j=0; j<n; j++)
        {   
            // passing data to each struct 
            arg_struct *args = (arg_struct *) malloc(sizeof(arg_struct));
            args->A = A; args->B = B; args->C = C;
            args->m = m ; args->n = n; args->l = l;
            args->i = i; args->j = j;
            cnt++;
            // starting each thread
            pthread_create(&t[cnt],NULL,mul_element, (void*)args);
        }
    }

    cnt = 0;
    for (int i = 0 ; i< l ; i++){
        for(int j = 0 ; j < n ; j++){
            void* sum;
            pthread_join(t[cnt++],&sum);
            int *p = (int*)sum;

            // setting result in the output matrix
            Item(C, i, j, n) = *p;
        }
    }  
}


void* mul_row (void* argument){

    
}


/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult_v2(int* A, int* B, int* C, int l, int m, int n)
{

}

