#include "mainmat.h"
#include "mymat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
This function performs the memory freeing for the passed matrix list.
*/
void teardown_mats(mat_list* mats)
{
  free(mats);
}

/*
This function will get a command line inputted by the user.
Will allow as large of a command line as wanted by a user.
Will raise an error if an EOF is sent.
*/
char* get_command_line()
{
  int i = 0;
  int capacity = BUFFER_SIZE;
  char c;
  char* str = (char*) malloc(BUFFER_SIZE * sizeof(char));
  char* tmp;

  /*Check that memory allocation did not fail*/  
  if (str == NULL)
  {
    perror("Memory allocation failed\n");
    return NULL;
  }

  while ((c = getchar()) != '\n')
  {
    /*If an EOF is inputted- raise an error*/
    if (c == EOF)
    {
      free(str);
      perror("EOF inputted.\n");
      return NULL;
    }
    
    /*If the remaining free space is too low- realloc more memory*/
    if (i == capacity - 3)
    {
      capacity = capacity + BUFFER_SIZE;
      tmp = realloc(str, capacity);
      
      /*Check if the memory reallcoation failed*/
      if (tmp == NULL)
      {
        free(str);
        perror("Memory allocation failed.\n");
        return NULL;
      }

      if (tmp != str)
      {
        free(str);
        str = tmp;
      }
    }
    
    str[i] = c;
    i++;
  }
  
  str[i] = '\0';
  return str;
}

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
Will return if the command line only contains newlines/tabs/spaces.
*/
bool is_command_line_empty(char* command_line)
{
  int i = 0;
  
  while (command_line[i] != '\0')
  {
    if (command_line[i] != ' ' && command_line[i] != '\t' && command_line[i] != '\n')
      return false;
    i++;
  }
  return true;
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

/*
Parse a matrix argument, and enforce the syntax for arguments of commands.
Move the index whose pointer was passed to the argument, parse the matrix name and enforce it's validity.
If the matrix is the final argument for the command line- ensure that the rest of the line is whitespaces.
if the matrix is not the final argument- push the index whose pointer was passed to the next argument, and ensure a single comma appears.
*/
mat* parse_matrix_argument(char* command_line, int* index_p, bool last_argument, mat_list* mats)
{
  int j = 0;
  char* mat_name = (char*) malloc(MAT_NAME_LEN * sizeof(char));
  mat* matrix;
  bool comma_appeared = false;

  if (mat_name == NULL)
  {
    perror("Memory allocation failed");
    return NULL;
  }

  /*Advance the index through any whitespaces*/  
  while (command_line[*index_p] == ' ' || command_line[*index_p] == '\t')
  {
    /*String end reached, but the matrix argument isn't in the command line*/
    if (command_line[*index_p] == '\0')
    {
      printf("Missing argument");
      free(mat_name);
      return NULL;
    }
  }

  /*Find the matrix name*/
  while (!(last_argument && command_line[*index_p] == '\0') && command_line[*index_p] != ' ' && command_line[*index_p] != '\t' && command_line[*index_p] != ',')
  {
    /*String end reached, but the argument is not the final one*/
    if (command_line[*index_p] == '\0')
    {
      mat_name[j] = '\0';
      matrix = get_mat_from_name(mat_name, mats);
      
      if (matrix == NULL)
        printf("Undefined matrix name.\n");
      else
        printf("Missing argument\n");
      
      free(mat_name);
      return NULL;
    }
    
    mat_name[j] = command_line[*index_p];
    j++;
    *index_p = *index_p + 1;
  }

  mat_name[j] = '\0';
  matrix = get_mat_from_name(mat_name, mats);
  free(mat_name);
  
  if (matrix == NULL)
  {
    printf("Undefined matrix name.\n");
    return NULL;
  }

  /*If this is the last argument- make sure there isn't extra text after*/
  if (last_argument)
  {
    while (last_argument && command_line[*index_p] != '\0')
    {
      if (command_line[*index_p] != ' ' && command_line[*index_p] != '\t')
      {
        printf("Extraneous text after end of command.\n");
        return NULL;
      }
      *index_p = *index_p + 1;
    }
    return matrix;
  }
  
  /*Push the pointer to the next argument, and make sure that a comma appears between arguments- but only once*/
  while (command_line[*index_p] == ' ' || command_line[*index_p] == '\t' || command_line[*index_p] == ',')
  {
    if (command_line[*index_p] == ',')
    {
      if (comma_appeared)
      {
        printf("Multiple consecutive commas.\n");
        return NULL;
      }
      comma_appeared = true;
    }
    *index_p = *index_p + 1;
  }
  
  if (!comma_appeared)
  {
    printf("Missing comma.\n");
    return NULL;
  }
  return matrix;
}

int parse_int(char* str, int* index_p);
matrix_values* parse_int_list(char*, int* index_p);
mat* get_matrix_from_name(char* mat_name, mat_list* mat_list_p);

/*
Handle a supposed stop command- check that no other non space characters follow.
If it truely is a valid stop command- change the value of should continue to false.
*/
void handle_stop(char* str, int* index_p, bool* should_continue_p)
{
  while (str[*index_p] != '\0' && str[*index_p] != '\n')
  {
    if (str[*index_p] != ' ' && str[*index_p] != '\t')
    {
      printf("Extraneous text after end of command.\n");
      return;
    }
    *index_p = *index_p + 1;
    
  }
  *should_continue_p = false;
}

void handle_three_matrix_command(char* command, char* command_line, int* index_p);
void handle_two_matrix_command(char* command, char* command_line, int* index_p);
void handle_one_matrix_comamnd(char* command, char* command_line, int* index_p);

int main()
{
  int i;
  char* command_line;
  matrix_operation command;
  bool should_continue = true;
  mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;

  while (should_continue)
  {
    command_line = get_command_line();
    /*If the command line is null, memory allocation failed or EOF was inputted*/
    if (command_line == NULL)
      break;

    command = get_command(command_line, &i);
    if (command == undefined)
      continue;

    if (command == stop)
      handle_stop(command_line, &i, &should_continue);
    
    free(command_line);
  }

  printf("Successful stop.\n");
  return 0;
}
