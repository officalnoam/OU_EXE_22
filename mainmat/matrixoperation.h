#ifndef MATRIX_OPERATION
  #define MATRIX_OPERATION  
  #define LARGEST_COMMAND 10

  typedef enum {
    read_mat,
    print_mat,
    add_mat,
    sub_mat,
    mul_mat,
    mul_scalar,
    trans_mat,
    stop,
    undefined
  } matrix_operation;

  /*
  This function will return the enum option of the passed command by a string of it.
  If the option isn't one of the supported options- `undefined` will be returned

  Input- 
    char* command: The string form of the command.
  Output-
    matrix_operation: The enum representation for the command.
  */
  matrix_operation convert_command_to_enum(char* command);
  
  /*
  This function parse a command from a command_line.

  Input-
    char* command_line: The command line from the user.
    int* index_p: A pointer to an index that indicates the current character within the command_line
                  that should be gone over for comamnds/arguments.

  Output-
    matrix_operation: The enum representation for the command within the command line.
  */
  matrix_operation get_command(char* command_line, int* index_p);
#endif