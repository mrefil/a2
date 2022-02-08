// FILE 		:	codeInput.c
// PROJECT 		:	PROG2030 - Assignment #2
// PROGRAMMER 	:	Mustafa Efiloglu
// DATE 		:	02/02/2022
// DESCRIPTION 	:	This file contains the prototypes and definitions for the codeInput implementation.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
// Define header file
#include "../inc/encodeInput.h"

// Filter type of output
enum Mode{ASM, SREC};
// Max length for path
#define PATH_MAX 4096

int main( int argc, char *argv[] ) {
    // Create a mode to filter output
    enum Mode mode = ASM;
    // Define a file name string from input
    char fileInput[PATH_MAX] = {'\0'};
    // Define a file name string from input for output
    char fileOutput[PATH_MAX] = {'\0'};
    // Create a pointer for input
    FILE* iPointer;
    // Create a pointer for output
    FILE* oPointer;

    // Create a for loop to read arguments
    for( int i=0; i < argc; ++i ) {
        // Create if else statement.
        // Compare strings.
        // Continue till it match 0
        if( strcmp( argv[i], "-srec" ) == 0 ) {
            // If it match then execute following code.
            // This means -srec.
            mode = SREC;
        } else if( strcmp( argv[i], "-h" ) == 0 ) {
            // Help argument for the command line.
            // Tell user to write following format.
            printf("Usage: encodeInput [-srec] [-h] [-i<fileInputName>] [-o<fileOutputName>]\n");
            // argc equal to i then =>
            i = argc;
            // return function.
            return 0;
        } else if (strncmp(argv[i], "-i", 2) == 0) {
            // -i means it starts with input -i
            // Copy source to destination string
            strcpy(fileInput, &argv[i][2]);
        } else if (strncmp(argv[i], "-o", 2) == 0) {
            // -o means it starts with output -o
            // Copy source to destination string
            strcpy(fileOutput, &argv[i][2]);
        }
    }

    // Create if else statement to check if input file giving
    if(fileInput[0] != 0) {
        // Check if the file ready to read.
        if(access(fileInput, R_OK) != 0) { 
            // Print error message.
            // It means there is no input file.
            perror("[ERROR] - Input Error");
            // Return -1
            return -1;
        } else {
            // Open the file that specified in the parameter.
            iPointer = fopen(fileInput, "r");
        }
        // Same like input, output not specified in the parameter
        if(fileOutput[0] == 0) {
            // In here if the user didnt specify output file
            // Copy source to destination output string
            strcpy(fileOutput, fileInput);
            // Create a if else statement to check mode
            if( mode == ASM ) {
                // Appends a copy of the source string to the destination string.
                // File extension must be .asm
                strcat( fileOutput, ".asm" );
            } else {
                // Appends a copy of the source string to the destination string.
                // File extension must be .srec
                strcat( fileOutput, ".srec" );
            }
        }
    } else {
        // Get the input string from console application.
        iPointer = stdin;
    }
    // Create if else statement to check if output file giving
    if(fileOutput[0] != 0) {    
        // Open/Create the output file that specified in the parameter.
        if((oPointer = fopen(fileOutput, "w")) == NULL) {
            // Print error message.
            // It means there is no input file.
            perror("[ERROR] - Output Error");
            // Return -1
            return -1;
        }
    }  else {
        // This means user didn't add the input/output.
        // User Standard output stream
        oPointer = stdout;
    }

    // Create if else statement to output file in selected mode.
    if(mode == SREC) {
        //  Create if else statement for srecord.
        if (SRECFunction(iPointer, oPointer) != 0) {
            // Print error to user if the srecord gives an error.
            printf("[ERROR] - Something went wrong with s-record filter\n");
            // REturn -1
            return -1;
        }
    } else {
        // Start Assmbly mode function
        if (ASMFunction(iPointer, oPointer) != 0) {
            // Print error to user if the assembly gives an error.
            printf("[ERROR] - Something went wrong with assembly filter\n");
            // Return -1
            return -1;
        }
    }
    // Return 0 - End application.
    return 0;
}
