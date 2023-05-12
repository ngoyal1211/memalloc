#include "memoryfunctions.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    long numBytes = 0;
    char* startAddress;
    char* endAddress;

    startAddress = (char*)sbrk(0);

    int ptr1Size = 500;
    char* ptr1 = (char*)malloc(sizeof(char) * ptr1Size);
    numBytes += sizeof(char) * ptr1Size;

    int ptr2Size = 400;
    char* ptr2 = malloc(sizeof(char) * ptr2Size);
    numBytes += sizeof(char) * ptr2Size;
    
    int ptr3Size = 300;
    char* ptr3 = malloc(sizeof(char) * ptr3Size);
    numBytes += sizeof(char) * ptr3Size;

    int ptr4Size = 200;
    char* ptr4 = malloc(sizeof(char)*ptr4Size);
    numBytes += sizeof(char) * ptr4Size;

    int ptr5Size = 100;
    char* ptr5 = malloc(sizeof(char)*ptr5Size);
    numBytes += sizeof(char) * ptr5Size;

    free(ptr1);
    numBytes = numBytes - ptr1Size;

    free(ptr2);
    numBytes = numBytes - ptr2Size;

    free(ptr3);
    numBytes = numBytes - ptr3Size;

    free(ptr4);
    numBytes = numBytes - ptr4Size;

    free(ptr5);
    numBytes = numBytes - ptr5Size;

    int ptr6Size = 100;
    char* ptr6 = malloc(sizeof(char)* ptr6Size);
    numBytes += sizeof(char) * ptr6Size;

    int ptr7Size = 200;
    char* ptr7 = malloc(sizeof(char)*ptr7Size);
    numBytes += sizeof(char) * ptr7Size;

    int ptr8Size = 300;
    char* ptr8 = malloc(sizeof(char) * ptr8Size);
    numBytes += sizeof(char) * ptr8Size;

    int ptr9Size = 400;
    char* ptr9 = malloc(sizeof(char) * ptr9Size);
    numBytes += sizeof(char) * ptr9Size;

    int ptr10Size = 500;
    char* ptr10 = malloc(sizeof(char) * ptr10Size);
    numBytes += sizeof(char) * ptr10Size;

    int newptr6Size = 400;
    ptr6 = realloc(ptr6, sizeof(char) * newptr6Size);
    numBytes = numBytes + newptr6Size - ptr6Size;

    newptr6Size = 367;
    ptr6 = realloc(ptr6, sizeof(char) * newptr6Size);
    numBytes = numBytes + newptr6Size - ptr6Size;

    newptr6Size = 398;
    ptr6 = realloc(ptr6, sizeof(char) * newptr6Size);
    numBytes = numBytes + newptr6Size - ptr6Size;

    int newptr7Size = 456;
    ptr7 = realloc(ptr7, sizeof(char) * newptr7Size);
    numBytes = numBytes + newptr7Size - ptr7Size;;

    newptr7Size = 16;
    ptr7 = realloc(ptr7, sizeof(char) * newptr7Size);
    numBytes = numBytes + newptr7Size - ptr7Size;

    newptr6Size = 400;
    ptr6 = realloc(ptr6, sizeof(char) * newptr6Size);
    numBytes = numBytes + newptr6Size - ptr6Size;

    newptr7Size = 197;
    ptr7 = realloc(ptr7, sizeof(char) * newptr7Size);
    numBytes = numBytes + newptr7Size - ptr7Size;

    int newptr8Size = 18;
    ptr8 = realloc(ptr8, sizeof(char) * newptr8Size);
    numBytes = numBytes + newptr8Size - ptr8Size;

    int newptr9Size = 17;
    ptr9 = realloc(ptr9, sizeof(char) * newptr9Size);
    numBytes = numBytes + newptr9Size - ptr9Size;

    int newptr10Size = 14;
    ptr10 = realloc(ptr10, sizeof(char) * newptr10Size);
    numBytes = numBytes + newptr10Size - ptr10Size;

    free(ptr6);
    numBytes = numBytes - ptr6Size;

    free(ptr7);
    numBytes = numBytes - ptr7Size;

    free(ptr8);
    numBytes = numBytes - ptr8Size;

    free(ptr9);
    numBytes = numBytes - ptr9Size;

    free(ptr10);
    numBytes = numBytes - ptr10Size;

    int ptr11Size = 13;
    char* ptr11 = calloc(ptr11Size, sizeof(char));
    numBytes = numBytes + ptr11Size;

    int ptr12Size = 3;
    char* ptr12 = calloc(ptr12Size, sizeof(char));
    numBytes = numBytes + ptr12Size;

    int ptr13Size = 10;
    char* ptr13 = calloc(ptr13Size, sizeof(char));
    numBytes = numBytes + ptr13Size;

    free(ptr12);
    numBytes = numBytes - ptr12Size;

    int ptr14Size = 91;
    char* ptr14 = calloc(ptr14Size, sizeof(char));
    numBytes = numBytes + ptr14Size;

    int ptr15Size = 73;
    char* ptr15 = calloc(ptr15Size, sizeof(char));
    numBytes = numBytes + ptr15Size;
    
    free(ptr11);
    numBytes = numBytes - ptr11Size;

    int ptr16Size = 31;
    char* ptr16 = calloc(ptr16Size, sizeof(char));
    numBytes = numBytes + ptr16Size;

    free(ptr14);
    numBytes = numBytes - ptr14Size;

    int ptr17Size = 124;
    char* ptr17 = calloc(ptr17Size, sizeof(char));
    numBytes = numBytes + ptr17Size;

    int ptr18Size = 108;
    char* ptr18 = calloc(ptr18Size, sizeof(char));
    numBytes = numBytes + ptr18Size;

    free(ptr13);
    numBytes = numBytes - ptr13Size;

    int ptr19Size = 23;
    char* ptr19 = calloc(ptr19Size, sizeof(char));
    numBytes = numBytes + ptr19Size;

    int ptr20Size = 69;
    char* ptr20 = calloc(ptr20Size, sizeof(char));
    numBytes = numBytes + ptr20Size;

    free(ptr15);
    numBytes = numBytes - ptr15Size;

    free(ptr16);
    numBytes = numBytes - ptr16Size;

    free(ptr17);
    numBytes = numBytes - ptr17Size;

    free(ptr18);
    numBytes = numBytes - ptr18Size;

    free(ptr19);
    numBytes = numBytes - ptr19Size;

    free(ptr20);
    numBytes = numBytes - ptr20Size;


    endAddress = (char*)sbrk(0);
//    printf("Number of Bytes: %ld \n", numBytes);

    long difference = endAddress - startAddress;
    long leak = difference - numBytes;
    printf("Start Address: %p \n", startAddress);
    printf("End Address: %p \n", endAddress);


//  printf("Difference in Addresses: %ld \n", difference);

    printf("Memory Leak: %ld \n", leak);

    return 0;
}
