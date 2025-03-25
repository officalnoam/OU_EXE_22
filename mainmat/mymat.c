#include "mymat.h"
#include <stdlib.h>
#include <stdio.h>

/*
Creates a copy of a passed matrix.
Goes over the data field and copies each value to the new matrix copy.
*/
mat* copy_matrix(mat* matrix)
{
  int i;
  int j;
  mat* matrix_copy = (mat*) malloc(sizeof(mat));
  
  if (matrix_copy == NULL)
    perror("Memory allocatiomn failed\n");
  
  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
      matrix_copy->data[i][j] = matrix->data[i][j];
  }
  
  return matrix_copy;
}

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
  
  /*Copy the source matrix's so that if one of them is also the target- that changing the values of target change the values of the source.*/
  mat* source_matrix_a_cp = copy_matrix(source_matrix_a);
  mat* source_matrix_b_cp = copy_matrix(source_matrix_b);
  
  /*Initialize the matrix so that the initial values of the matrix don't affect the result.*/
  initialize_matrix(target_matrix);

  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
    {
      for (k = 0; k < MATRIX_SIZE; k++)
        target_matrix->data[i][j] = target_matrix->data[i][j] + source_matrix_a_cp->data[i][k] * source_matrix_b_cp->data[k][j];
    }
  }
  
  free(source_matrix_a_cp);
  free(source_matrix_b_cp);
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
  
  /*Copy the source matrix so that if the source and target matrixes are the same- that the transpose isn't affected by already changed items.*/
  mat* source_matrix_cp = copy_matrix(source_matrix);

  for (i = 0; i < MATRIX_SIZE; i++)
  {
    for (j = 0; j < MATRIX_SIZE; j++)
      target_matrix->data[i][j] = source_matrix_cp->data[j][i];
  }
  
  free(source_matrix_cp);
}

