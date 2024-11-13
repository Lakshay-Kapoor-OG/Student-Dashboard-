


#include <stdio.h>
#include <stdlib.h>


// Function declarations
void AddStudents();
void StudentRecord();
void SearchStudent();
void Delete();

// Struct definition for student
struct student {
    char fullname[40];
    int roll_no;
    char Sem[10];
    char Address[100];
    float CGP;
};

int main() {
    int choice = 0;

    while (choice != 5) {
        printf("\n================STUDENT DATABASE MANAGEMENT SYSTEM===================\n");
        printf("1. Add student record\n");
        printf("2. Display student records\n");
        printf("3. Search student record\n");
        printf("4. Delete student record\n");
        printf("5. EXIT\n");
        printf("----------------------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AddStudents();
                break;
            case 2:
                StudentRecord();
                break;
            case 3:
                SearchStudent();
                break;
            case 4:
                Delete();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to add student records
void AddStudents() {
    char another = 'y';
    FILE *ptr;
    struct student info;

    ptr = fopen("student_info.txt", "a");
    if (ptr == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    while (another == 'y' || another == 'Y') {
        printf("\n=========== Add Student Info ============\n");

        printf("Enter full name: ");
        scanf(" %[^\n]", info.fullname);
        printf("Enter roll number: ");
        scanf("%d", &info.roll_no);
        printf("Enter semester: ");
        scanf("%s", info.Sem);
        printf("Enter address: ");
        scanf(" %[^\n]", info.Address);
        printf("Enter CGPA: ");
        scanf("%f", &info.CGP);

        fwrite(&info, sizeof(struct student), 1, ptr);

        printf("Record stored successfully.\n");

        printf("Do you want to add another record? (y/n): ");
        scanf(" %c", &another);
    }

    fclose(ptr);
}

// Function to display all student records
// Updated StudentRecord function
void StudentRecord() {
    FILE *ptr;
    struct student info;

    ptr = fopen("student_info.txt", "r");
    if (ptr == NULL) {
        fprintf(stderr, "No such file exists.\n");
        return;
    }

    printf("\n=========== Student Records ===========\n");

    int record_found = 0; // Flag to check if records exist
    while (fread(&info, sizeof(struct student), 1, ptr)) {
        printf("\nStudent Name: %s", info.fullname);
        printf("\nRoll No: %d", info.roll_no);
        printf("\nSemester: %s", info.Sem);
        printf("\nAddress: %s", info.Address);
        printf("\nCGPA: %.2f", info.CGP);
        printf("\n--------------------------------------\n");
        record_found = 1;
    }

    fclose(ptr);

    if (!record_found) {
        printf("No records found.\n");
    }

    printf("Press any key to return to the main menu...");
    getch(); // Pauses and waits for user input
}


// Function to search for a student record by roll number
void SearchStudent() {
    FILE *ptr;
    struct student info;
    int roll_no, found = 0;

    ptr = fopen("student_info.txt", "r");
    if (ptr == NULL) {
        fprintf(stderr, "No such file exists.\n");
        return;
    }

    printf("Enter the roll number of the student to search: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, ptr)) {
        if (info.roll_no == roll_no) {
            printf("\nStudent found:\n");
            printf("Name: %s\n", info.fullname);
            printf("Roll No: %d\n", info.roll_no);
            printf("Semester: %s\n", info.Sem);
            printf("Address: %s\n", info.Address);
            printf("CGPA: %.2f\n", info.CGP);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with roll number %d not found.\n", roll_no);
    }

    fclose(ptr);
}

// Function to delete a student record by roll number
void Delete() {
    FILE *ptr, *temp;
    struct student info;
    int roll_no, found = 0;

    ptr = fopen("student_info.txt", "r");
    if (ptr == NULL) {
        fprintf(stderr, "No such file exists.\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        fprintf(stderr, "Error opening temporary file.\n");
        fclose(ptr);
        return;
    }

    printf("Enter the roll number of the student to delete: ");
    scanf("%d", &roll_no);

    while (fread(&info, sizeof(struct student), 1, ptr)) {
        if (info.roll_no != roll_no) {
            fwrite(&info, sizeof(struct student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(ptr);
    fclose(temp);

    remove("student_info.txt");
    rename("temp.txt", "student_info.txt");

    if (found) {
        printf("Record deleted successfully.\n");
    } else {
        printf("Student with roll number %d not found.\n", roll_no);
    }
}
