// The MIT License (MIT)
// 
// Copyright (c) 2016, 2017 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//#define _GNU_SOURCE // Gives a warning on unbuntu about redefining _GNU_SOURCE. Should probably be
                      // uncommented later for Omega.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5     // Mav shell only supports five arguments

struct filesystem
{
  char BS_OEMName[8];
  int16_t BPB_BytsPerSec;
  int8_t BPB_SecPerClus;
  int16_t BPB_RsvdSecCnt;
  int8_t BPB_NumFATs;
  int16_t BPB_RootEntCnt;
  char BS_VolLab[11];
  int32_t BPB_FATSz32;
  int32_t BPB_RootClus;

  int32_t RootDirSectors = 0;
  int32_t FirstDataSector = 0;
  int32_t FirstSectorofCluster = 0;
};

int main()
{
  FILE* image = NULL;
  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
  struct filesystem File_Cup;
    
  while( 1 )
  {
    // Print out the mfs prompt
    printf ("mfs> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *arg_ptr;                                         
                                                           
    char *working_str  = strdup( cmd_str );                

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    // Now print the tokenized input as a debug check
    if(!strcmp(token[0], "open"))
      {
	if(token[1] == NULL)
	  {
	    printf("Usage: open <filename>\n");
	  }
	else
	  {
	    if(image == NULL)
	      {
		image = fopen(token[1], "r");
		if(image == NULL)
		  {
		    printf("Error: File system image not found.\n");
		  }
	      }
	    else
	      {
		printf("Error: File system image already open.\n");
	      }
	  }
      }
    
    if(!strcmp(token[0], "close"))
      {
	if(image != NULL)
	  {
	    fclose(image);
	    image = NULL;
	  }
	else
	  {
	    printf("Error: File system not open\n");
	  }
      }
    
    if(!strcmp(token[0], "exit"))
      {
	break;
      }

    if (!strcmp(token[0], "info"))
      {
	
      }

    if (!strcmp(token[0], "stat"))
      {
	
      }

    if (!strcmp(token[0], "get"))
      {
	
      }

    if (!strcmp(token[0], "put"))
      {
	
      }

    if (!strcmp(token[0], "cd"))
      {
	
      }

    if (!strcmp(token[0], "ls"))
      {
	
      }

    if (!strcmp(token[0], "read"))
      {
	
      }


    
    /*
    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ ) 
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );  
    }
    */
    
    free( working_root );

  }
  return 0;
}
