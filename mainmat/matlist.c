#include "matlist.h"
#include <stdlib.h>
#include <string.h>

/*
This function creates a mat list, for convinent accessing of all MATS in the calculator, 
and sets all values of the matrixes to 0.
*/
mat_list* initialize_mats(mat* MAT_A, mat* MAT_B, mat* MAT_C, mat* MAT_D, mat* MAT_E, mat* MAT_F)
{
  mat_list* mats = (mat_list*) malloc(sizeof(mat_list));

  /*Set all values in all matrixes to 0.*/  
  initialize_matrix(MAT_A);
  initialize_matrix(MAT_B);
  initialize_matrix(MAT_C);
  initialize_matrix(MAT_D);
  initialize_matrix(MAT_E);
  initialize_matrix(MAT_F);
  
  /*Save all mats into a mat list, for convinence of accessing*/
  mats->mat_a = MAT_A;
  mats->mat_b = MAT_B;
  mats->mat_c = MAT_C;
  mats->mat_d = MAT_D;
  mats->mat_e = MAT_E;
  mats->mat_f = MAT_F;

  return mats;
}

/*
This function will return the pointer to the matrix matching the passed matrix name.
*/
mat* get_mat_from_name(char* mat_name, mat_list* mats)
{
  if (strncmp(mat_name, "MAT_A", MAT_NAME_LEN) == 0)
    return mats->mat_a; 

  if (strncmp(mat_name, "MAT_B", MAT_NAME_LEN) == 0)
    return mats->mat_b;

  if (strncmp(mat_name, "MAT_C", MAT_NAME_LEN) == 0)
    return mats->mat_c;
  
  if (strncmp(mat_name, "MAT_D", MAT_NAME_LEN) == 0)
    return mats->mat_d;

  if (strncmp(mat_name, "MAT_E", MAT_NAME_LEN) == 0)
    return mats->mat_e;
  
  if (strncmp(mat_name, "MAT_F", MAT_NAME_LEN) == 0)
    return mats->mat_f;

  return NULL;
}