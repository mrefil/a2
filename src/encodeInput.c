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
enum Mode{Assembly, SRecord};
// Max length for path
#define MAX_PATH 4096

int main( int argc, char *argv[] ) {
    // Create a mode to filter output
    enum Mode mode = Assembly;
    // Define a file name string from input
    char inFile[MAX_PATH] = {'\0'};
    // Define a file name string from input for output
    char outFile[MAX_PATH] = {'\0'};
    // Create a pointer for input
    FILE* inPtr;
    // Create a pointer for output
    FILE* outPtr;

    // Create a for loop to read arguments
    for( int i=0; i < argc; ++i ) {
        // Create if else statement.
        // Compare strings.
        // Continue till it match 0
        if( strcmp( argv[i], "-srec" ) == 0 ) {
            // If it match then execute following code.
            // This means -srec.
            mode = SRecord;
        } else if( strcmp( argv[i], "-h" ) == 0 ) {
            // Help argument for the command line.
            // Tell user to write following format.
            printf("Usage: encodeInput [-i<InputFilename>] [-o<OutputFilename>] [-srec] [-h]\n");
            // argc equal to i then =>
            i = argc;
            // return function.
            return 0;
        } else if (strncmp(argv[i], "-i", 2) == 0) {
            // -i means it starts with input -i
            // Copy source to destination string
            strcpy(inFile, &argv[i][2]);
        } else if (strncmp(argv[i], "-o", 2) == 0) {
            // -o means it starts with output -o
            // Copy source to destination string
            strcpy(outFile, &argv[i][2]);
        }
    }

    // Create if else statement to check if input file giving
    if(inFile[0] != 0) {
        // Check if the file ready to read.
        if(access(inFile, R_OK) != 0){ 
            // Print error message.
            // It means there is no input file.
            perror("[ERROR] - Input Error");
            // Return -1
            return -1;
        } else {
            // Open the file that specified in the parameter.
            inPtr = fopen(inFile, "r");
        }
        // Same like input, output not specified in the parameter
        if(outFile[0] == 0) {
            // In here if the user didnt specify output file
            // Copy source to destination output string
            strcpy(outFile, inFile);
            // Create a if else statement to check mode
            if( mode == Assembly ) {
                // Appends a copy of the source string to the destination string.
                // File extension must be .asm
                strcat( outFile, ".asm" );
            } else {
                // Appends a copy of the source string to the destination string.
                // File extension must be .srec
                strcat( outFile, ".srec" );
            }
        }
    } else {
        // Get the input string from console application.
        inPtr = stdin;
    }
    // Create if else statement to check if output file giving
    if(outFile[0] != 0) {    
        // Open/Create the output file that specified in the parameter.
        if((outPtr = fopen(outFile, "w")) == NULL) {
            // Print error message.
            // It means there is no input file.
            perror("[ERROR] - Output Error");
            // Return -1
            return -1;
        }
    }  else {
        // This means user didn't add the input/output.
        // User Standard output stream
        outPtr = stdout;
    }

    // Create if else statement to output file in selected mode.
    if(mode == SRecord) {
        //  Create if else statement for srecord.
        if (sRecordLogic(inPtr, outPtr) != 0) {
            // Print error to user if the srecord gives an error.
            printf("[ERROR] - Something went wrong with s-record filter\n");
            // REturn -1
            return -1;
        }
    } else {
        // Start Assmbly mode function
        if (ASMFunction(inPtr, outPtr) != 0) {
            // Print error to user if the assembly gives an error.
            printf("[ERROR] - Something went wrong with assembly filter\n");
            // Return -1
            return -1;
        }
    }
    // Return 0 - End application.
    return 0;
}
