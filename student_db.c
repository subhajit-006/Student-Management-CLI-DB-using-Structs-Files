#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

void add_student() {
    Student s;
    FILE *fp = fopen("students.dat", "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student added successfully.\n");
}

void view_students() {
    Student s;
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("No student data found.\n");
        return;
    }

    printf("\nRoll\tName\t\tMarks\n");
    printf("-------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%d\t%-15s%.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void search_student() {
    int roll;
    Student s;
    int found = 0;

    printf("Enter Roll No to search: ");
    scanf("%d", &roll);

    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("No student data found.\n");
        return;
    }

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll == roll) {
            printf("Found: %d\t%s\t%.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_student(); break;
            case 2: view_students(); break;
            case 3: search_student(); break;
            case 4: exit(0);
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}
