#include "mainmat.h"
#include "mymat.h"
#include <stdlib.h>
#include <stdio.h>

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
Get the command from the user which is the first word..
*/
char* get_command(char* str, int* index_p)
{
  char* command = (char*) malloc(LARGEST_COMMAND * sizeof(char));

  *index_p = 0;
  while(str[*index_p] != ' ' && str[*index_p] != '\t' && str[*index_p] != '\0')
  {
    /*Check that the command does not contain or include a comma.*/
    if (str[*index_p] == ',')
    {
      printf("Illegal comma.\n");
      return NULL;
    }
     
    /*If the 'command' is past the length of the largest command- it cannot be a valid command.*/
    if (*index_p == LARGEST_COMMAND)
    {
      printf("Undefined command name.\n");
      return NULL;
    }
    
    command[*index_p] = str[*index_p];
    *index_p = *index_p + 1;
  }
  command[*index_p] = '\0';

  return command;
}

char* parse_matrix_argument(char* str, int* index_p);
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
  char* command;
  bool should_continue = true;
  mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;

  while (should_continue)
  {
    command_line = get_command_line();
    
    /*If the command line is null, memory allocation failed or EOF was inputted*/
    if (command_line == NULL)
      break;

    command = get_command(command_line, &i);
    if (command == NULL)
      continue;

    if (strncmp(command, "stop", 4) == 0)
      handle_stop(command_line, &i, &should_continue);
    
    free(command);
    free(command_line);
  }

  printf("Successful stop.\n");
  return 0;
}
