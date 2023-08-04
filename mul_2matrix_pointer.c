#include <stdio.h>
#include <stdlib.h>
int M,N,R,C;//global variable to be accessed in the function

int **creat_mat(int **arr1,int **arr2); //**pointer to return 2D array

void get_mat(int** mat,int row,int column);
void print_mat(int**mat,int row,int column);
int main()
{
	//to get the result
    int **matrix; 
	
    int **mat_1,**mat_2;
	
	//counters
	int i,j;
	
    printf("enter row of matrix A\n");
    scanf("%d",&M);
    printf("enter column of matrix A\n");
    scanf("%d",&N);
	/*dinamic memory allocation for M rows with size of int*pointer */
	
    mat_1= malloc(sizeof(int*)*M);
    for(i=0;i < M;i++)
        mat_1[i]=malloc(sizeof(int)*N);

    printf("enter the matrix A\n");

	/*get the matrix from user*/
    get_mat(mat_1,M,N);
	
    printf("-------------------------\n");
    printf("enter row of matrix B\n");
    scanf("%d",&C);
    printf("enter column of matrix B\n");
    scanf("%d",&R);
	
	/*dinamic memory allocation for C rows with size of int*pointer */
    mat_2=malloc(sizeof(int*)*C);

    for(int i=0;i < C;i++)
        mat_2[i]=malloc(sizeof(int)*R);

    printf("enter the matrix B\n");
	
	/*get the matrix from user*/
    get_mat(mat_2,C,R);
    printf("-------------------------\n");

   if (C!=N)
    printf("----multiplicatiom error----");
   else
   {
        matrix = creat_mat(mat_1,mat_2);

		print_mat(matrix,M,R);
   }

    return 0;
}
void get_mat(int** mat,int row,int column)
{
	for(int i=0;i<row;i++)
    {
       for(int j=0;j<column;j++)
       {
           scanf("%d",&mat[i][j]);
       }
    }
}

void print_mat(int**mat,int row,int column)
{
	for(int i=0;i<row;i++)
       {
        for(int j=0;j<column;j++)
            printf("%d\t",*(*(mat+i)+j));

        printf("\n");
       }
}

int **creat_mat(int **arr1,int **arr2)
{
    int **matrix;

    matrix = malloc(sizeof(int *)*M);
    for(int i=0;i < M;i++)
        matrix[i]=malloc(sizeof(int)*R);
	
    int s,i,j,sum;
	
    for(s=0;s<M;s++)
    {
        for(j=0;j<R;j++)
        {
            matrix[s][j]=0;
            for(i=0;i<N;i++)
                matrix[s][j]+=arr1[s][i]*arr2[i][j];
        }
    }
    return matrix;
}