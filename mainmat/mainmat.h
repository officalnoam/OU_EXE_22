#ifndef MAIN_MAT
  #include "boolean.h"
  #include "mymat.h"
  
  #define MAIN_MAT
  #define BUFFER_SIZE 50
  #define LARGEST_COMMAND 10
  
  typedef struct {
    mat* source_matrix_a;
    mat* source_matrix_b;
    mat* target_matrix;
    matrix_values* int_list;
    int scalar;

  } parameters;

  typedef struct {
    mat* mat_a;
    mat* mat_b;
    mat* mat_c;
    mat* mat_d;
    mat* mat_e;
    mat* mat_f;
  } mat_list;

  mat_list* initialize_mats(mat* MAT_A, mat* MAT_B, mat* MAT_C, mat* MAT_D, mat* MAT_E, mat* MAT_F);
  void teardown_mats(mat_list* mats);
  char* get_command_line();
  char* get_command(char* str, int* index_p);
  char* parse_matrix_argument(char* str, int* index_p);
  int parse_int(char* str, int* index_p);
  matrix_values* parse_int_list(char*, int* index_p); 
  mat* get_matrix_from_name(char* mat_name, mat_list* mat_list_p);
  void handle_stop(char* str, int* index_p, bool* should_continue_p);
  void handle_three_matrix_command(char* command, char* command_line, int* index_p);
  void handle_two_matrix_command(char* command, char* command_line, int* index_p);
  void handle_one_matrix_comamnd(char* command, char* command_line, int* index_p);
  
#endif
