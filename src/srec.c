// FILE 		:	srec.c
// PROJECT 		:	PROG2030 - Assignment #2
// PROGRAMMER 	:	Mustafa Efiloglu
// DATE 		:	02/02/2022
// DESCRIPTION 	:	This file contains the prototypes and definitions for the srec implementation.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
// Define header file
#include "../inc/encodeInput.h"
// Filter type of output
enum RcrdKind { 
    header = 0, 
    data = 1, 
    summation = 5, 
    trailer = 9
};
// Define max bytes
#define SREC_LEN 44
// Define min bytes
#define BYTE_MIN 3
// Define statistic data
const char HEADPH[] = "Mustafa";
// Create a function that read bytes from input line and convert it to srecord format and output
int SRECFunction(FILE* inputFile, FILE* outputFile) {
    // Define type of record.
    enum RcrdKind rcrdType = header;
    // Add counter
    unsigned short countData = 0;
    // Store it to mem
    unsigned short memoryPos = 0;
    // Boolean expression for quit loop
    bool otpFinish = false;
    // Create a while loop function.
    // Run loop while boolean is false.
    while(otpFinish == false) {
        // Define variables.
        // inptChar is not convertd data
        unsigned char inptChar[MAX_RAW] = {0};
        // This is fomatted out put
        unsigned char charLeng = 0;
        // Address data
        unsigned short adresData = 0;
        // This is fomatted out put
        char srecRcrd[SREC_LEN] = {'\0'};
        // This is the calculation bytes
        unsigned short calcByte = 0;
        // Create switch case function
        switch (rcrdType) {
        case header:
            // Add strcpy to function to copy S0 and add it to srecRcrd[0]
            strcpy(&srecRcrd[0], "S0");
            // Add strcpy to function to copy HEADPH and add it to inptChar
            strcpy(inptChar, HEADPH);
            // Add lenght to charLeng
            charLeng += strlen(HEADPH);
            // Create a while loop and add data to calcByte
            for(int i = 0; i < charLeng; i++) {
                // Add data to calcByte
                calcByte += inptChar[i];
            }
            // Address is 0x0 in header
            adresData = 0;
            // Assign to data to rcrdType
            rcrdType = data;
            // Break function
            break;
        case data:
            // Add strcpy to function to copy S1 and add it to srecRcrd[0]
            strcpy(&srecRcrd[0], "S1");
            // Read data from input
            charLeng += fread(inptChar, 1, MAX_RAW, inputFile);
            // Create a while loop and add data to calcByte
            for(int i = 0; i < charLeng; i++) {
                // Add data to calcByte
                calcByte += inptChar[i];
            }
            // Set adresData
            adresData = memoryPos;
            // Increase memory everytime
            memoryPos += 16;
            // Increase counter everytime
            ++countData;
            // Create if statement and feof function to add summation next.
            if(feof(inputFile)) {
                // Assign summation to rcrdType
                rcrdType = summation;
            }
            // Break function
            break;
        case summation:
            // Add strcpy to function to copy S5 and add it to srecRcrd[0]
            strcpy(&srecRcrd[0], "S5");
            // In here assign countData value to adresData
            adresData = countData;
            // Assign to data to rcrdType
            rcrdType = trailer;
            // Break function
            break;
        case trailer:
            // Add strcpy to function to copy S9 and add it to srecRcrd[0]
            strcpy(&srecRcrd[0], "S9");
            // Address is 0x0 in header
            adresData = 0;
            // Tell program that outoComplete finish and set it to true
            otpFinish = true;
            // Break function
            break;
        default:
            // This value not expected
            return -1;
            // Break function
            break;
        }
        // Convert data to srecord format
        // Adding count
        convertHex(srecRcrd, 1, (unsigned char)(BYTE_MIN + charLeng));
        // Adding count
        convertHex(srecRcrd, 2, (unsigned char)(adresData / 256));
        // Adding count and Max byte
        convertHex(srecRcrd, 3, (unsigned char)(adresData & 0xff));
        // Create if else statement to add data
        if(charLeng > 0) {
            // Create for loop to write data
            for(int i = 0; i < charLeng; i++) {
                // Assign data to convertHex function
                convertHex(srecRcrd, 4+i, inptChar[i]);
            }
        }
        // Pass bytes value, count and adresData.
        calcByte += (BYTE_MIN+charLeng) + (adresData/256) + (adresData&0xff);
        // Checksum
        convertHex(srecRcrd, 4+charLeng, (unsigned char)DataSum(calcByte));
        // Add new line for record
        strcat(srecRcrd, "\n");
        // Writing records
        fputs(srecRcrd, outputFile);
    }
    // Return
    return 0;
}
// Create a function that calculation
unsigned char DataSum(unsigned short calcByte) {
    // Set calcByte to itself
    calcByte = ~calcByte;
    // Return last byte
    return (calcByte & 0xFF);
}
// Create a function that write hex char
void convertHex(char* str, int ubu, unsigned char stream) {
    // Create stred char
    char converted[3];
    // Write formatted data to string
    sprintf(converted, "%02X", stream);
    // Add strcpy to function to copy converted and add it to destination
    strcpy(&str[ubu*2], converted);
    // Return
    return;
}
