// FILE 		:	assembly.c
// PROJECT 		:	PROG2030 - Assignment #2
// PROGRAMMER 	:	Mustafa Efiloglu
// DATE 		:	02/02/2022
// DESCRIPTION 	:	Logic file for assembly.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Define header file
#include "../inc/encodeInput.h"
// Define dc.b line lenght
#define DC_B_LENG 256

// Create a function that read bytes from input.
// After reading binary input convert it to dcb assembly.
// Last oututput it.
int ASMFunction( FILE* inputFile, FILE* outputFile ) {
    // Create a boolean operation for output is complete or not.
    // Default false.
    bool outData = false;
    // Create a while loop function.
    // Run loop while boolean is false.
    while( outData == false ) {
        // Define variables.
        // inptLine is not convertd data
        unsigned char inptLine[DC_B_LENG] = {0};
        // This is fomatted out put
        char dcbData[DC_B_LENG] = {'\0'};
        // Define lengthOfData to gauge how many success bytes read
        int lengthOfData = 0;
        // Add strcpy to function to copy dc.b and add it to dcbData
        strcpy( dcbData, "dc.b" );
        // Read an array of DC_B_LENG elements.
        // 1 is bytes for elements to read.
        // inptLine Pointer to a block of memory.
        // input is the pointer of file object.
        lengthOfData += fread( inptLine, 1, DC_B_LENG, inputFile );
        // Create if statement and feof function to clear data.
        if( feof(inputFile) ) {
            // After that set outData boolean operation to true.
            // This will stop while loop.
            outData = true;
        }
        // Create a for loop to write data to output.
        // Execute for loop till lengthOfData
        for( int i = 0; i < lengthOfData; i++ ){
            // Pass to input data into convertHexToASM function with dcbData.
            convertHexToASM(dcbData, inptLine[i]);
            // Create if statement to add "," to seperate data line.
            if( i < lengthOfData-1 ) {
                // Appends a copy of the "," string to the destination dcbData string.
                strcat( dcbData, "," );
            }
        }
        // Appends a copy of the "\n" string to the destination dcbData string.
        // This "\n" means create a new line.
        strcat( dcbData, "\n" );
        // Print formatted data to stdout
        // This means print dcbData each line.
        printf( "%s\n", dcbData );
        // Writes the C string pointed by dcbData to the output.
        fputs( dcbData, outputFile );
    }
}

// Create a convertHexToASM function.
// This function takes 2 parameters 1) char* str and unsigned char stream
void convertHexToASM( char* str, unsigned char stream ) {
    // Create stred char
    char stred[5];
    // Write formatted data to string
    sprintf(stred, " $%02X", stream);
    // Appends a copy of the stred string to the str string.
    strcat(str, stred);
    // Return function.
    return;
}