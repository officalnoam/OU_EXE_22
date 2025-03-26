#include "matrixoperation.h"
#include "string_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
This function will compare thre passed command to all recognized commands- and return the matching enum option for the command.
This is done for easier comparison in the future- for example:
command == read_mat vs strncmp(command, "read_mat", 8) == 0
*/
matrix_operation convert_command_to_enum(char* command)
{
  if (strncmp(command, "read_mat", 8) == 0)
    return read_mat;
  if (strncmp(command, "print_mat", 9) == 0)
    return print_mat;
  if (strncmp(command, "add_mat", 7) == 0)
    return add_mat;
  if (strncmp(command, "sub_mat", 7) == 0)
    return sub_mat;
  if (strncmp(command, "mul_mat", 7) == 0)
    return mul_mat;
  if (strncmp(command, "mul_scalar", 10) == 0)
    return mul_scalar;
  if (strncmp(command, "trans_mat", 9) == 0)
    return trans_mat;
  if (strncmp(command, "stop", 4) == 0)
    return stop;
  
  /*If the command is not equal to any of the recognized commands- return undefined*/
  return undefined;
}


/*
Get the command from the user which is the first word..
*/
matrix_operation get_command(char* command_line, int* index_p)
{
  char* command = (char*) malloc(LARGEST_COMMAND * sizeof(char));
  matrix_operation com_name;

  *index_p = 0;
  while(command_line[*index_p] != ' ' && command_line[*index_p] != '\t' && command_line[*index_p] != '\0')
  {
    /*Check that the command does not contain or include a comma.*/
    if (command_line[*index_p] == ',')
    {
      printf("Illegal comma.\n");
      return undefined;
    }
     
    /*If the 'command' is past the length of the largest command- it cannot be a valid command.*/
    if (*index_p == LARGEST_COMMAND)
    {
      printf("Undefined command name.\n");
      return undefined;
    }
    
    command[*index_p] = command_line[*index_p];
    *index_p = *index_p + 1;
  }

  command[*index_p] = '\0';
  com_name = convert_command_to_enum(command);
  free(command);

  if (com_name == undefined && !is_command_line_empty(command_line))
    printf("Undefined command name.\n");

  return com_name;
}
