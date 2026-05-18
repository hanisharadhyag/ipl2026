#include <stdio.h>

/* Structure using bitfields */
typedef struct
{
    unsigned int firstbit  : 1;   // 1 bit
    unsigned int secondbit : 2;   // 2 bits
    unsigned int thirdbit  : 3;   // 3 bits
}Bitfield;

int main()
{
    Bitfield a;

    /* Assign values */
    a.firstbit = 1;
    a.secondbit = 2;
    a.thirdbit = 5;

    /* Display values */
    printf("firstbit  = %u\n", a.firstbit);
    printf("secondbit = %u\n", a.secondbit);
    printf("thirdbit  = %u\n", a.thirdbit);

    /* Display size of structure */
    printf("Size of structure = %lu bytes\n", sizeof(a));

    return 0;
}