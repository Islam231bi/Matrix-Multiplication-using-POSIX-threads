#include<stdlib.h>
#include<pthread.h>

struct arg_struct {
    int *A;
    int *B;
    int i,k,j,n,m;
};



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

void* get_element(void* argument){
    struct arg_struct *args = (struct arg_struct *)argument;

    int  *sum = (int *)malloc(sizeof(int)); 

    *sum+= Item(args->A, args->i, args->k, args->m) * Item(args->B, args->k, args->j, args->n);

    return sum;

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
    pthread_t t[l*n];
    int cnt = -1;

    struct arg_struct *args;
    args->A = A; args->B = B;

    for(int i=0; i<l; i++){
        for(int j=0; j<n; j++)
        {
            cnt++;
            int *sum;
            for(int k=0; k<m; k++){
                args->i = i; args->j = j; args->k = k; args->m = m ; args->n = n;
                pthread_create(&t[cnt],NULL,get_element, args);
                pthread_join(t[cnt],&sum);
            }

            Item(C, i, j, n) = *sum;
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
