#include<stdio.h>
#include<inttypes.h>

void main()
{
    uint16_t var;   // a 16 bits variable 
    uint8_t *word ; // word pointer of 1 byte or 8 bits

    var=24;         // Assigning any random int value to the variable

    word = (uint8_t*)&var; // type casting the address of last 8 bits(from LSB) of 16 bits

    if(*word==24)
    printf("The memory uses Little-Endian\n");
    else
    printf("The memory uses Big-Endian\n");
    
}