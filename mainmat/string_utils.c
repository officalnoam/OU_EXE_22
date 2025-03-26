#include "string_utils.h"

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