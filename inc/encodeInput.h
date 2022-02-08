// FILE 		:	codeInput.h
// PROJECT 		:	PROG2030 - Assignment #2
// PROGRAMMER 	:	Mustafa Efiloglu
// DATE 		:	02/02/2022
// DESCRIPTION 	:	This file contains the prototypes and definitions for the codeInput implementation.

// Definex maximum bytes for the data raw lenght. 
#define MAX_RAW 16

// Define srec.c functions
int SRECFunction(FILE* inputFile, FILE* outputFile);
unsigned char DataSum(unsigned short calcByte);
void convertHex(char* str, int ubu, unsigned char stream);

// Define assembly.c functions
int ASMFunction(FILE* inputFile, FILE* outputFile);
void convertHexToASM(char* str, unsigned char stream);
