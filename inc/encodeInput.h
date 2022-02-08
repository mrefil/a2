// FILE 		:	codeInput.h
// PROJECT 		:	PROG2030 - Assignment #2
// PROGRAMMER 	:	Mustafa Efiloglu
// DATE 		:	02/02/2022
// DESCRIPTION 	:	This file contains the prototypes and definitions for the codeInput implementation.

// Definex maximum bytes for the data raw lenght. 
#define MAX_RAW 16

// Define srec.c functions
int sRecordLogic(FILE* input, FILE* output);
unsigned char CalculateSum(unsigned short byteSum);
void writeHex(char* destination, int pos, unsigned char c);

// Define assembly.c functions
int ASMFunction(FILE* input, FILE* output);
void convertHexToASM(char* str, unsigned char stream);
