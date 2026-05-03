#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll_no;
    char name[50];
    float marks[3];
    float total;
} Student;

void add_record() {
    FILE *fp = fopen("records.dat", "ab");
    if (!fp) { printf("Error opening file!\n"); return; }

    Student s;
    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll_no);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    s.total = 0;
    for(int i = 0; i < 3; i++) {
        printf("Enter Mark %d: ", i + 1);
        scanf("%f", &s.marks[i]);
        s.total += s.marks[i];
    }

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Record added successfully!\n");
}

void display_records() {
    FILE *fp = fopen("records.dat", "rb");
    if (!fp) { printf("No records found.\n"); return; }

    Student s;
    printf("\n--- Student Records ---\n");
    printf("%-10s %-20s %-10s\n", "Roll No", "Name", "Total");
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%-10d %-20s %-10.2f\n", s.roll_no, s.name, s.total);
    }
    fclose(fp);
}

void generate_rank_list() {
    FILE *fp = fopen("records.dat", "rb");
    if (!fp) { printf("No records found.\n"); return; }

    Student students[100], temp;
    int count = 0;

    while (fread(&students[count], sizeof(Student), 1, fp)) {
        count++;
    }
    fclose(fp);

    // Sorting in descending order of total marks
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].total < students[j+1].total) {
                temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            }
        }
    }

    printf("\n--- Rank List (Descending Order) ---\n");
    printf("%-5s %-10s %-20s %-10s\n", "Rank", "Roll No", "Name", "Total");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-10d %-20s %-10.2f\n", i + 1, students[i].roll_no, students[i].name, students[i].total);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Add Student Record\n2. Display All Records\n3. Generate Rank List\n4. Exit\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_record(); break;
            case 2: display_records(); break;
            case 3: generate_rank_list(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
