#include "mymat.h"
#include <stdlib.h>
#include <stdio.h>

/*
Goes over all items in the matrix
*/
void initialize_matrix(mat* matrix)
{
  int i;
  int j;
 
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
      matrix->data[i][j] = 0;
  }
}

/*
Sets matrix values to the values in arr.
If there are more values in arr then the amount of items in the matrix- ignore additional values in vals.
If there are less values in arr then the amount of items in the matrix- all other items in the matrix should be set as 0.
*/
void set_matrix_values(mat* matrix, matrix_values* vals)
{
  int i;

  /*Set all matrix values as 0- so that if there are not enough values in vals, the rest of the values will already be 0.*/
  initialize_matrix(matrix);

  for (i = 0; i < MIN(vals->len, MATRIX_SIZE * MATRIX_SIZE); i++)
    matrix->data[i / MATRIX_SIZE][i % MATRIX_SIZE] = vals->data[i];
}

/*
Prints the passed matrix.
*/
void print_matrix(mat* matrix)
{
  int i;
  int j;

  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
      /*%7.2f prints a double, with the first two decimals after the decimal point, and adding spaces so that the length of the number is at least 7 (with spaces).*/
      printf("%7.2f ", matrix->data[i][j]);

    printf("\n");
  }
}

/*
Performs the matrix operation of MAT_A + MAT_B = MAT_C
Every item in C will be equal sum of the items in A and B in the same position to them.
*/
void add_matrix(mat* source_matrix_a, mat* source_matrix_b, mat* target_matrix)
{
  int i;
  int j;
  
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
      target_matrix->data[i][j] = source_matrix_a->data[i][j] + source_matrix_b->data[i][j];
  }
}

/*
Performs the matrix operation of MAT_A - MAT_B = MAT_C.
Every item in C is equal to the difference between the items in A and B in the matching position.
*/
void sub_matrix(mat* source_matrix_a, mat* source_matrix_b, mat* target_matrix)
{
  int i;
  int j;
  
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
      target_matrix->data[i][j] = source_matrix_a->data[i][j] - source_matrix_b->data[i][j]; 
  }
}

/*
Performs the matrix operagtion of MAT_A * MAT_B = MAT_C
Each item in C, in row i and column j- is equal to a sum of products between items in row i in MAT_A with the matching items in column j in MAT_B
*/
void mult_matrix(mat* source_matrix_a, mat* source_matrix_b, mat* target_matrix)
{
  int i;
  int j;
  int k;
  
  initialize_matrix(target_matrix);

  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
    {
      for (k = 0; k < MATRIX_SIZE; k++)
        target_matrix->data[i][j] = target_matrix->data[i][j] + source_matrix_a->data[i][k] * source_matrix_b->data[k][j];
    }
  }
}

/*
This function performs the matrix operation of MAT_SOURCE * SCALAR + MAT_TARGET.
Every item in the target is equal to the matching item in the source times the scalar.
*/
void mult_matrix_scalar(mat* source_matrix, mat* target_matrix, double* scalar)
{
  int i;
  int j;
  
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
      target_matrix->data[i][j] = source_matrix->data[i][j] * *scalar;
  }
}

/*
This function performs the matrix operation of transpose on MAT_SOURCE.
Every item in the target in row i and column j, is equal to the item in row j column i in the source matrix.
*/
void transpose(mat* source_matrix, mat* target_matrix)
{
  int i;
  int j;

  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
      target_matrix->data[i][j] = source_matrix->data[j][i];
  }
}

int main()
{
  double temp[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  mat matrix1;
  mat matrix2;
  mat matrix3;
  matrix_values vals;
  vals.data = temp;
  vals.len = 15;
  
  initialize_matrix(&matrix1);
  initialize_matrix(&matrix2);
  initialize_matrix(&matrix3);
  
  set_matrix_values(&matrix1, &vals);
  print_matrix(&matrix1);
  printf("\n\n");
  transpose(&matrix1, &matrix2);
  print_matrix(&matrix2);
  printf("\n\n");
  mult_matrix(&matrix1, &matrix2, &matrix3);
  print_matrix(&matrix3);
  return 1;
}
