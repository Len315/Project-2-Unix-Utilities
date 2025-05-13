/*
Sources:
AI usage: This code is commented using Copilot-style comments, and has been edi
ted and added by the creator based on those suggestions.
*/

// This is a simplified version of the UNIX 'cat' command.
// It reads one or more files specified on the command line
// and prints the contents of each file to standard output.

#include <stdio.h>
#include <stdlib.h>

// Error message
#define ERROR_OPEN_FILE "wcat: cannot open file\n"

void printFileContents(char *pFilename){
  char cBuffer[4096];// Buffer to store each line of the file
  FILE *file = NULL;

  file = fopen(pFilename, "r");
  if(!file){// Print error message and exit if the file cannot be opened
    fprintf(stdout, ERROR_OPEN_FILE);
    exit(1);
  }
  while(fgets(cBuffer, sizeof(cBuffer), file) != NULL){// Print each line to standard output
    printf("%s", cBuffer);
  }
  fclose(file);
}

int main(int argc, char *argv[]){
  if(argc > 1){// Iterate through each file specified on the command line if there are any arguments
    for(int i = 1; i < argc; i++){
      printFileContents(argv[i]);
    }
  }

  return 0;// Exit with status code 0 on success
}
