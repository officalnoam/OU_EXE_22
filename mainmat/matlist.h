#ifndef MAT_LIST
  #include "mymat.h"
  
  #define MAT_LIST

  typedef struct {
    mat* mat_a;
    mat* mat_b;
    mat* mat_c;
    mat* mat_d;
    mat* mat_e;
    mat* mat_f;
  } mat_list;

  /*
  This function intiialiszes all of the passed matrixes by setting all of their values to 0.
  Create a mat list from all of these matrixes, and return it.

  Input-
    mat* MAT_A: The matrix reffered to as MAT_A within the calculator.
    mat* MAT_B: The matrix reffered to as MAT_B within the calculator.
    mat* MAT_C: The matrix reffered to as MAT_C within the calculator.
    mat* MAT_D: The matrix reffered to as MAT_D within the calculator.
    mat* MAT_E: The matrix reffered to as MAT_E within the calculator.
    mat* MAT_F: The matrix reffered to as MAT_F within the calculator.
  Output-
    mat_list*: The created mat_list of all of the input matrixes.
  */
  mat_list* initialize_mats(mat* MAT_A, mat* MAT_B, mat* MAT_C, mat* MAT_D, mat* MAT_E, mat* MAT_F);

  /*
  This function will return a pointer to a matrix based on the name of the matrix.
  If the matrix name isn't supported- NULL is returned.
  
  Input-
    char* mat_name: The name of the matrix.
    mat_list* mats: The list of the matrixes supported by the calculator.
  Output-
    mat*: The matrix matching the matrix name.
  */
  mat* get_mat_from_name(char* mat_name, mat_list* mats);
#endif