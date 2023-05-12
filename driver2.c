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

    int ptr1Size = 1300;
    char* ptr1 = (char*)malloc(sizeof(char) * ptr1Size);
    numBytes += sizeof(char) * ptr1Size;

    int ptr2Size = 125;
    char* ptr2 = malloc(sizeof(char) * ptr2Size);
    numBytes += sizeof(char) * ptr2Size;
    
    int ptr3Size = 132;
    char* ptr3 = malloc(sizeof(char) * ptr3Size);
    numBytes += sizeof(char) * ptr3Size;

    int ptr4Size = 245;
    char* ptr4 = malloc(sizeof(char)*ptr4Size);
    numBytes += sizeof(char) * ptr4Size;

    int ptr5Size = 151;
    char* ptr5 = malloc(sizeof(char)*ptr5Size);
    numBytes += sizeof(char) * ptr5Size;

    int ptr6Size = 212;
    char* ptr6 = malloc(sizeof(char)* ptr6Size);
    numBytes += sizeof(char) * ptr6Size;

    int ptr7Size = 165;
    char* ptr7 = malloc(sizeof(char)*ptr7Size);
    numBytes += sizeof(char) * ptr7Size;

    int ptr8Size = 223;
    char* ptr8 = malloc(sizeof(char) * ptr8Size);
    numBytes += sizeof(char) * ptr8Size;

    int ptr9Size = 110;
    char* ptr9 = malloc(sizeof(char) * ptr9Size);
    numBytes += sizeof(char) * ptr9Size;

    int ptr10Size = 145;
    char* ptr10 = malloc(sizeof(char) * ptr10Size);
    numBytes += sizeof(char) * ptr10Size;

    int newptr1Size = 40;
    ptr1 = realloc(ptr1, sizeof(char) * newptr1Size);
    numBytes = numBytes + newptr1Size - ptr1Size;

    int newptr2Size = 150;
    ptr2 = realloc(ptr2, sizeof(char) * newptr2Size);
    numBytes = numBytes + newptr2Size - ptr2Size;

    int newptr3Size = 37;
    ptr3 = realloc(ptr3, sizeof(char) * newptr3Size);
    numBytes = numBytes + newptr3Size - ptr3Size;

    free (ptr2);
    numBytes = numBytes - newptr2Size;

    int newptr4Size = 18;
    ptr4 = realloc(ptr4, sizeof(char) * newptr4Size);
    numBytes = numBytes + newptr4Size - ptr4Size;;

    int newptr5Size = 76;
    ptr5 = realloc(ptr5, sizeof(char) * newptr5Size);
    numBytes = numBytes + newptr5Size - ptr5Size;

    free(ptr1);
    numBytes = numBytes - newptr1Size;

    int newptr6Size = 132;
    ptr6 = realloc(ptr6, sizeof(char) * newptr6Size);
    numBytes = numBytes + newptr6Size - ptr6Size;

    int newptr7Size = 82;
    ptr7 = realloc(ptr7, sizeof(char) * newptr7Size);
    numBytes = numBytes + newptr7Size - ptr7Size;

    free (ptr5);
    numBytes = numBytes - newptr5Size;

    int newptr8Size = 108;
    ptr8 = realloc(ptr8, sizeof(char) * newptr8Size);
    numBytes = numBytes + newptr8Size - ptr8Size;

    int newptr9Size = 67;
    ptr9 = realloc(ptr9, sizeof(char) * newptr9Size);
    numBytes = numBytes + newptr9Size - ptr9Size;

    free(ptr7);
    numBytes = numBytes - newptr7Size;

    int newptr10Size = 45;
    ptr10 = realloc(ptr10, sizeof(char) * newptr10Size);
    numBytes = numBytes + newptr10Size - ptr10Size;

    free(ptr3);
    numBytes = numBytes - newptr3Size;	

    free(ptr4);
    numBytes = numBytes - newptr4Size;

    free(ptr6);
    numBytes = numBytes - newptr6Size;

    free(ptr8);
    numBytes = numBytes - newptr8Size;

    free(ptr9);
    numBytes = numBytes - newptr9Size;

    free(ptr10);
    numBytes = numBytes - newptr10Size;

    int ptr11Size = 13;
    char* ptr11 = calloc(ptr11Size, sizeof(char));
    numBytes = numBytes + ptr11Size;

    int ptr12Size = 73;
    char* ptr12 = calloc(ptr12Size, sizeof(char));
    numBytes = numBytes + ptr12Size;

    int ptr13Size = 19;
    char* ptr13 = calloc(ptr13Size, sizeof(char));
    numBytes = numBytes + ptr13Size;

    free(ptr12);
    numBytes = numBytes - ptr12Size;

    int ptr14Size = 92;
    char* ptr14 = calloc(ptr14Size, sizeof(char));
    numBytes = numBytes + ptr14Size;

    int ptr15Size = 27;
    char* ptr15 = calloc(ptr15Size, sizeof(char));
    numBytes = numBytes + ptr15Size;
    
    free(ptr11);
    numBytes = numBytes - ptr11Size;

    int ptr16Size = 123;
    char* ptr16 = calloc(ptr16Size, sizeof(char));
    numBytes = numBytes + ptr16Size;

    free(ptr14);
    numBytes = numBytes - ptr14Size;

    int ptr17Size = 74;
    char* ptr17 = calloc(ptr17Size, sizeof(char));
    numBytes = numBytes + ptr17Size;

    int ptr18Size = 108;
    char* ptr18 = calloc(ptr18Size, sizeof(char));
    numBytes = numBytes + ptr18Size;

    free(ptr13);
    numBytes = numBytes - ptr13Size;

    int ptr19Size = 223;
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
//
    printf("Start Address: %p \n", startAddress);
    printf("End Address: %p \n", endAddress);

    long difference = endAddress - startAddress;

//  printf("Difference in Addresses: %ld \n", difference);

    printf("Memory Leak: %ld \n", difference - numBytes);

    return 0;
}
