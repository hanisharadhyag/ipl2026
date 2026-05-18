#include <stdio.h>

/* Function to print bits of an integer */
void printIntBits(int n)
{
    int i;

    printf("Bits of integer:\n");

    for(i = 31; i >= 0; i--)
    {
        printf("%d", (n >> i) & 1);

        if(i % 8 == 0)
            printf(" ");
    }

    printf("\n");
}

/* Function to count number of 1 bits */
int countOneBits(int n)
{
    int count = 0;

    while(n != 0)
    {
        count += n & 1;
        n = n >> 1;
    }

    return count;
}

/* Function to check endian format */
void checkEndian()
{
    int x = 1;
    char *ptr = (char*)&x;

    if(*ptr == 1)
        printf("System is Little Endian\n");
    else
        printf("System is Big Endian\n");
}

/* Function to print float bits */
void printFloatBits(float f)
{
    int *ptr = (int*)&f;
    int i;

    printf("Bits of floating point number:\n");

    for(i = 31; i >= 0; i--)
    {
        printf("%d", (*ptr >> i) & 1);

        if(i % 8 == 0)
            printf(" ");
    }

    printf("\n");
}

int main()
{
    int num;
    float fnum;

    /* Integer input */
    printf("Enter an integer: ");
    scanf("%d", &num);

    /* Print integer bits */
    printIntBits(num);

    /* Count 1 bits */
    printf("Number of 1 bits = %d\n", countOneBits(num));

    /* Endian check */
    checkEndian();

    /* Explanation for negative integers */
    if(num < 0)
    {
        printf("Negative integers are stored using Two's Complement representation.\n");
    }

    /* Float input */
    printf("\nEnter a floating point number: ");
    scanf("%f", &fnum);

    /* Print float bits */
    printFloatBits(fnum);

    /* Explanation for negative float */
    if(fnum < 0)
    {
        printf("Negative floating point numbers have sign bit = 1.\n");
    }

    return 0;
}