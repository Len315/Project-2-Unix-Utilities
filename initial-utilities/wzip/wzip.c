/*
Sources:
fwrite usage: https://man7.org/linux/man-pages/man3/fwrite.3.html
fgetc usage: https://man7.org/linux/man-pages/man3/fgetc.3.html
AI usage: This code is commented using Copilot-style comments, and has been edited and added by the creator based on those suggestions.
*/

// Implements a simple run-length encoding (RLE) compression algorithm.
// Compresses input files by replacing
// consecutive occurrences of the same character
// with the character and the number of times it appears consecutively.
// Outputs the compressed data in binary format to stdout.
#include <stdio.h>
#include <stdlib.h>

// Error messages                                                               
#define ERROR_OPEN_FILE "wzip: can not open file %s\n"
#define ERROR_ARGUMENTS "wzip: file1 [file2 ...]\n"

// Write the count and character to stdout if count is greater than 0
void writeToStdout(int iCount, char cPreviousCharacter){
  if(iCount > 0){
    fwrite(&iCount, sizeof(int), 1, stdout);
    fwrite(&cPreviousCharacter, sizeof(char), 1, stdout);
  }
}

int main(int argc, char *argv[]){
  char cCurrentCharacter = EOF, cPreviousCharacter = EOF;
  int iCount = 0;
  FILE *file = NULL;

  // Check if at least one file is provided
  if(argc < 2){
    fprintf(stdout, ERROR_ARGUMENTS);
    exit(1);
  }
  // Open each file provided as an argument
  for(int i = 1; i < argc; i++){
    file = fopen(argv[i], "r");// Open the file in read mode
    if(!file){// If the file cannot be opened, print an error message and exit
      fprintf(stderr, ERROR_OPEN_FILE, argv[i]);
      exit(1);
    }
    
    // The compressing process
    while((cCurrentCharacter = fgetc(file)) != EOF){
      // If the current character matches the previous one, the count grows by one
      if(cCurrentCharacter == cPreviousCharacter){
	iCount++;
      }else{// Write the previous character and its count to stdout and reset the count
	writeToStdout(iCount, cPreviousCharacter);
	cPreviousCharacter = cCurrentCharacter;
	iCount = 1;
      }
    }
    fclose(file);// Close the file after processing
  }
  // Write out the final run
  writeToStdout(iCount, cPreviousCharacter);

  return 0;
}
