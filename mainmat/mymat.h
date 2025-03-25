#ifndef MY_MAT
  #define MY_MAT
  #define MATRIX_SIZE 4
  #define MIN(x, y) ((x) < (y) ? (x) : (y))

  typedef struct {
    double data[MATRIX_SIZE][MATRIX_SIZE];
  } mat;
  
  typedef struct {
    double* data;
    int len;
  } matrix_values;
  
  /*
  This function will create a copy of a matrix.
  
  Input-
    mat* matrix: The matrix being copied.
  Output-
    mat* matrix: The copy of the matrix.
  */
  mat* copy_matrix(mat* matrix);
  /*
  This function receives a matrix and initializes all of its values to 0.
  
  Input-
    mat* matrix: The initialized matrix.
  */  
  void initialize_matrix(mat* matrix);
  
  /*
  This function will set the matrix values according to the passed array.
  If the array is smaller than the amount of values in the matrix- the rest of the values will be 0.
  
  Input-
    mat matrix*: The matrix.
    matrix_values* vals: The list of numbers the matrix values should be set to
  */
  void set_matrix_values(mat* matrix, matrix_values* vals);
  
  /*
  This function will print the passed matrix.
  
  Input-
    mat* matrix: The matrix.
  */
  void print_matrix(mat* matrix);  
  /*
  This function will add source_matrix_a and source_matrix_b into target_matrix.

  Input-
    mat* source_matrix_a: The first matrix being added.
    mat* source_matrix_b: The second matrix being added.
    mat* target_matrix: The matrix the result is stored in.
  */
  void add_matrix(mat* source_matrix_a, mat* source_matrix_b, mat* target_matrix);
  
  /*
  This function will perform source_matrix_a - source_matrix_b and store that in target_matrix.
  
  Input-
    mat* source_matrix_a: The matrix that will be subtracted from.
    mat* source_matrix_b: The matrix that will be subtracted.
    mat* target_matrix: The matrix the result is stored in.
  */
  void sub_matrix(mat* source_matrix_a, mat* source_matrix_b, mat* target_matrix);
  
  /*
  This function will perform source_matrix_a * source_matrix_b and store it in target_matrix.
  
  Input-
    mat* source_matrix_a: The first matrix being multiplied.
    mat* source_matrix_b: The second matrix being multiplied.
    mat* target_matrix: The matrix the result is stored in.
  */
  void mult_matrix(mat* source_matrix_a, mat* source_matrix_b, mat* target_matrix);
  
  /*
  This function will multiply the source_matrix by the scalar and store it in the target matrix.
  
  Input-
    mat* source_matrix: The matrix being multiplied.
    mat* target_matrix: The matrix the result is stored in.
    double* scalar: The scalar being multiplied.
  */
  void mult_matrix_scalar(mat* source_matrix, mat* target_matrix, double* scalar);
  
  /*
  This function will perform a transpose on the source matrix and store it in the target matrix.
  
  Input-
    mat* source_matrix: The matrix being transposed.
    mat* target_matrix: The matrix the result is stored in.
  */
  void transpose(mat* source_matrix, mat* target_matrix);
#endif
