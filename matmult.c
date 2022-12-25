#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>

typedef struct arg_struct {
    int *A;
    int *B;
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
            for(int k=0; k<m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}


void* mul_element(void* argument){
    struct arg_struct *args = (struct arg_struct *)argument;

    int  *sum = (int *)malloc(sizeof(int));
    int s = 0;

    for(int k=0; k<args->m; k++)
        s+= Item(args->A, args->i, k, args->m) * Item(args->B, k, args->j, args->n);

    *sum = s;
    pthread_exit(sum);

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
    int thread_cnt = l*n;
    pthread_t t[thread_cnt];
    int cnt = -1;
    void* sum;

    arg_struct *args = (arg_struct *) malloc(sizeof(arg_struct));
    args->A = A; args->B = B;
    args->m = m ; args->n = n; args->l = l;

    for (int i=0; i<l; i++){
        for(int j=0; j<n; j++)
        {
            cnt++;
            args->i = i; args->j = j;
            pthread_create(&t[cnt],NULL,mul_element, args);
        }
    }

    cnt = -1;
    for (int i = 0 ; i< l ; i++){
        for(int j = 0 ; j < n ; j++){
            cnt++;
            pthread_join(t[cnt],&sum);
            int *p = (int*)sum;
            Item(C, i, j, n) = *p;
        }
    }  
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
