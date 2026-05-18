#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 50
#define FILE_NAME "records.txt"

/* Structure Definition */
struct Student
{
    int id;
    char name[MAX_NAME];
    float marks;
};

/* Function Prototypes */
void writeRecords(struct Student arr[], int n);
long* createSeekPositions(int n);
void displayRecordAtPosition(long pos);

int main()
{
    int n, i, choice;
    
    printf("Enter number of records: ");
    scanf("%d", &n);

    struct Student students[n];

    /* Input Records */
    for(i = 0; i < n; i++)
    {
        printf("\nEnter details for student %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &students[i].id);

        printf("Enter Name: ");
        scanf("%s", students[i].name);

        printf("Enter Marks: ");
        scanf("%f", &students[i].marks);
    }

    /* Store records in ASCII file */
    writeRecords(students, n);

    /* Create array of seek positions */
    long *positions = createSeekPositions(n);

    printf("\nSeek Positions of Records:\n");
    for(i = 0; i < n; i++)
    {
        printf("Record %d -> %ld\n", i + 1, positions[i]);
    }

    /* Display record using seek position */
    printf("\nEnter record number to display: ");
    scanf("%d", &choice);

    if(choice >= 1 && choice <= n)
    {
        displayRecordAtPosition(positions[choice - 1]);
    }
    else
    {
        printf("Invalid record number\n");
    }

    free(positions);

    return 0;
}

/* Function to write structures into ASCII file */
void writeRecords(struct Student arr[], int n)
{
    FILE *fp;
    int i;

    fp = fopen(FILE_NAME, "w");

    if(fp == NULL)
    {
        printf("File cannot be opened\n");
        exit(1);
    }

    for(i = 0; i < n; i++)
    {
        fprintf(fp, "%d %s %.2f\n",
                arr[i].id,
                arr[i].name,
                arr[i].marks);
    }

    fclose(fp);
}

/* Function to create array of seek positions */
long* createSeekPositions(int n)
{
    FILE *fp;
    long *positions;
    int id;
    char name[MAX_NAME];
    float marks;
    int i = 0;

    positions = (long*)malloc(n * sizeof(long));

    fp = fopen(FILE_NAME, "r");

    if(fp == NULL)
    {
        printf("File cannot be opened\n");
        exit(1);
    }

    while(i < n)
    {
        positions[i] = ftell(fp);

        if(fscanf(fp, "%d %s %f",
                  &id,
                  name,
                  &marks) != 3)
        {
            break;
        }

        i++;
    }

    fclose(fp);

    return positions;
}

/* Function to display record using seek position */
void displayRecordAtPosition(long pos)
{
    FILE *fp;
    struct Student s;

    fp = fopen(FILE_NAME, "r");

    if(fp == NULL)
    {
        printf("File cannot be opened\n");
        exit(1);
    }

    /* Move file pointer to given position */
    fseek(fp, pos, SEEK_SET);

    fscanf(fp, "%d %s %f",
           &s.id,
           s.name,
           &s.marks);

    printf("\nRecord Found:\n");
    printf("ID    : %d\n", s.id);
    printf("Name  : %s\n", s.name);
    printf("Marks : %.2f\n", s.marks);

    fclose(fp);
}