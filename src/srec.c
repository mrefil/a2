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
enum RecordType{ header=0, data=1, summation=5, trailer=9 };
// Define max bytes
#define SREC_ENCODED_LENGTH 44
// Define min bytes
#define MIN_BYTE_COUNT 3
// Define statistic data
const char HEADERTEXT[] = "Mustafa";
// Create a function that read bytes from input line and convert it to srecord format and output
int sRecordLogic(FILE* input, FILE* output) {
    // Define type of record.
    enum RecordType rType = header;
    // Add counter
    unsigned short dataCount = 0;
    // Store it to mem
    unsigned short memPosition = 0;
    // Boolean expression for quit loop
    bool outputComplete = false;
    // Create a while loop function.
    // Run loop while boolean is false.
    while(outputComplete == false) {
        // Define variables.
        // inputData is not convertd data
        unsigned char inputData[DATA_RAW_MAX_LENGTH] = {0};
        // This is fomatted out put
        unsigned char dataLength = 0;
        // Address data
        unsigned short address = 0;
        // This is fomatted out put
        char sRecord[SREC_ENCODED_LENGTH] = {'\0'};
        // This is the calculation bytes
        unsigned short byteSum = 0;
        // Create switch case function
        switch (rType) {
        case header:
            // Add strcpy to function to copy S0 and add it to sRecord[0]
            strcpy(&sRecord[0], "S0");
            // Add strcpy to function to copy HEADERTEXT and add it to inputData
            strcpy(inputData, HEADERTEXT);
            // Add lenght to dataLength
            dataLength += strlen(HEADERTEXT);
            // Create a while loop and add data to bytesum
            for(int i = 0; i < dataLength; i++) {
                // Add data to bytesum
                byteSum += inputData[i];
            }
            // Address is 0x0 in header
            address = 0;
            // Assign to data to rType
            rType = data;
            // Break function
            break;
        case data:
            // Add strcpy to function to copy S1 and add it to sRecord[0]
            strcpy(&sRecord[0], "S1");
            // Read data from input
            dataLength += fread(inputData, 1, DATA_RAW_MAX_LENGTH, input);
            // Create a while loop and add data to bytesum
            for(int i = 0; i < dataLength; i++) {
                // Add data to bytesum
                byteSum += inputData[i];
            }
            // Set address
            address = memPosition;
            // Increase memory everytime
            memPosition += 16;
            // Increase counter everytime
            ++dataCount;
            // Create if statement and feof function to add summation next.
            if(feof(input)) {
                // Assign summation to rType
                rType = summation;
            }
            // Break function
            break;
        case summation:
            // Add strcpy to function to copy S5 and add it to sRecord[0]
            strcpy(&sRecord[0], "S5");
            // In here assign dataCount value to address
            address = dataCount;
            // Assign to data to rType
            rType = trailer;
            // Break function
            break;
        case trailer:
            // Add strcpy to function to copy S9 and add it to sRecord[0]
            strcpy(&sRecord[0], "S9");
            // Address is 0x0 in header
            address = 0;
            // Tell program that outoComplete finish and set it to true
            outputComplete = true;
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
        writeHex(sRecord, 1, (unsigned char)(MIN_BYTE_COUNT + dataLength));
        // Adding count
        writeHex(sRecord, 2, (unsigned char)(address / 256));
        // Adding count and Max byte
        writeHex(sRecord, 3, (unsigned char)(address & 0xff));
        // Create if else statement to add data
        if(dataLength > 0) {
            // Create for loop to write data
            for(int i = 0; i < dataLength; i++) {
                // Assign data to writeHex function
                writeHex(sRecord, 4+i, inputData[i]);
            }
        }
        // Pass bytes value, count and address.
        byteSum += (MIN_BYTE_COUNT+dataLength) + (address/256) + (address&0xff);
        // Checksum
        writeHex(sRecord, 4+dataLength, (unsigned char)CalculateSum(byteSum));
        // Add new line for record
        strcat(sRecord, "\n");
        // Writing records
        fputs(sRecord, output);
    }
    // Return
    return 0;
}
// Create a function that calculation
unsigned char CalculateSum(unsigned short byteSum) {
    // Set byteSum to itself
    byteSum = ~byteSum;
    // Return last byte
    return (byteSum & 0xFF);
}
// Create a function that write hex char
void writeHex(char* destination, int pos, unsigned char c) {
    // Create stred char
    char converted[3];
    // Write formatted data to string
    sprintf(converted, "%02X", c);
    // Add strcpy to function to copy converted and add it to destination
    strcpy(&destination[pos*2], converted);
    // Return
    return;
}
