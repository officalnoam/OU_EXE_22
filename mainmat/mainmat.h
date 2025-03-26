#ifndef MAIN_MAT
  #include "boolean.h"
  #include "mymat.h"
  #include "matlist.h"
  
  #define MAIN_MAT
  #define BUFFER_SIZE 50
  
  typedef struct {
    mat* source_matrix_a;
    mat* source_matrix_b;
    mat* target_matrix;
    matrix_values* int_list;
    int scalar;

  } parameters;

  void teardown_mats(mat_list* mats);
  char* get_command_line();
  mat* parse_matrix_argument(char* command_line, int* index_p, bool last_argument, mat_list* mats);
  int parse_int(char* str, int* index_p);
  matrix_values* parse_int_list(char*, int* index_p); 
  mat* get_matrix_from_name(char* mat_name, mat_list* mat_list_p);
  void handle_stop(char* str, int* index_p, bool* should_continue_p);
  void handle_three_matrix_command(char* command, char* command_line, int* index_p);
  void handle_two_matrix_command(char* command, char* command_line, int* index_p);
  void handle_one_matrix_comamnd(char* command, char* command_line, int* index_p);
  
#endif
