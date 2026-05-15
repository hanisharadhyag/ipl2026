#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[30];
    float gpa;
} Student;

// Function Prototypes
void addRecords(const char* filename);
void displayMthRecord(const char* filename);
void deleteRecord(const char* filename)
long getTotalRecords(FILE* fp);

int main() {
    const char* filename = "students.dat";
    int choice;

    while(1) {
        printf("\n1. Add Records\n2. Display M-th Record\n3. Delete Record\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addRecords(filename); break;
            case 2: displayMthRecord(filename); break;
            case 3: deleteRecord(filename); break;
            case 4: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}

// Appends n records to the file
void addRecords(const char* filename) {
    FILE* fp = fopen(filename, "ab"); // Open in append mode
    if (!fp) return;

    int n;
    Student s;
    printf("How many records to add? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter ID, Name, GPA: ");
        scanf("%d %s %f", &s.id, s.name, &s.gpa);
        fwrite(&s, sizeof(Student), 1, fp);
    }
    fclose(fp);
}

// Logic to get M-th record with boundary checking
void displayMthRecord(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) return;

    int m;
    long total = getTotalRecords(fp);
    
    printf("Enter record index to display (0 to %ld): ", total - 1);
    scanf("%d", &m);

    if (m >= 0 && m < total) {
        fseek(fp, m * sizeof(Student), SEEK_SET);
        Student s;
        fread(&s, sizeof(Student), 1, fp);
        printf("\n[Record %d] ID: %d, Name: %s, GPA: %.2f\n", m, s.id, s.name, s.gpa);
    } else {
        printf("Error: Index out of bounds.\n");
    }
    fclose(fp);
}

// Helper function to count records using file pointers
long getTotalRecords(FILE* fp) {
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    rewind(fp);
    return fileSize / sizeof(Student);
}

void deleteRecord(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) { printf("File not found.\n"); return; }

    FILE* temp = fopen("temp.dat", "wb");
    int targetId, found = 0;
    Student s;

    printf("Enter Student ID to delete: ");
    scanf("%d", &targetId);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id != targetId) {
            fwrite(&s, sizeof(Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.dat", filename);

    if (found) printf("Record deleted.\n");
    else printf("Record ID not found.\n");
}