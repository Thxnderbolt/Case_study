#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILENAME "marks.txt" // File name to store marks

typedef struct {
    char name[50];
    float marks_physics[3];
    float marks_chemistry[3];
    float marks_maths[3];
} Student;

// Function prototypes
void addMarks(Student students[], int *count);
void updateMarks(Student students[], int count);
void deleteMarks(Student students[], int *count);
void displayMarks(Student students[], int count);
char calculateGrade(float percentage);
void saveMarksToFile(Student students[], int count);
void loadMarksFromFile(Student students[], int *count);

int main() {
    Student students[MAX_STUDENTS];
    int choice, count = 0;

    // Load marks from file at the beginning
    loadMarksFromFile(students, &count);

    do {
        printf("\nMenu:\n");
        printf("1. Add marks\n");
        printf("2. Update marks\n");
        printf("3. Delete marks\n");
        printf("4. Display marks\n");
        printf("5. Exit program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addMarks(students, &count);
                break;
            case 2:
                updateMarks(students, count);
                break;
            case 3:
                deleteMarks(students, &count);
                break;
            case 4:
                displayMarks(students, count);
                break;
            case 5:
                // Save marks to file before exiting
                saveMarksToFile(students, count);
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while(choice != 5);

    return 0;
}

void addMarks(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students. Database full.\n");
        return;
    }

    printf("\nEnter student details:\n");
    printf("Name: ");
    scanf("%s", students[*count].name);
    getchar(); // Clearing newline character from input buffer
    printf("Enter marks for Physics (ISA1, ISA2, ESA): ");
    scanf("%f %f %f", &students[*count].marks_physics[0], &students[*count].marks_physics[1], &students[*count].marks_physics[2]);
    getchar(); // Clearing newline character from input buffer
    printf("Enter marks for Chemistry (ISA1, ISA2, ESA): ");
    scanf("%f %f %f", &students[*count].marks_chemistry[0], &students[*count].marks_chemistry[1], &students[*count].marks_chemistry[2]);
    getchar(); // Clearing newline character from input buffer
    printf("Enter marks for Maths (ISA1, ISA2, ESA): ");
    scanf("%f %f %f", &students[*count].marks_maths[0], &students[*count].marks_maths[1], &students[*count].marks_maths[2]);
    getchar(); // Clearing newline character from input buffer

    (*count)++;

    // Save marks to file after adding
    saveMarksToFile(students, *count);
}

void updateMarks(Student students[], int count) {
    char name[50];
    int i;
    printf("\nEnter name of student whose marks you want to update: ");
    scanf("%s", name);
    getchar(); // Clearing newline character from input buffer
    for (i = 0; i < count; i++) {
        if (strcmp(name, students[i].name) == 0) {
            printf("Enter new marks for Physics (ISA1, ISA2, ESA): ");
            scanf("%f %f %f", &students[i].marks_physics[0], &students[i].marks_physics[1], &students[i].marks_physics[2]);
            getchar(); // Clearing newline character from input buffer
            printf("Enter new marks for Chemistry (ISA1, ISA2, ESA): ");
            scanf("%f %f %f", &students[i].marks_chemistry[0], &students[i].marks_chemistry[1], &students[i].marks_chemistry[2]);
            getchar(); // Clearing newline character from input buffer
            printf("Enter new marks for Maths (ISA1, ISA2, ESA): ");
            scanf("%f %f %f", &students[i].marks_maths[0], &students[i].marks_maths[1], &students[i].marks_maths[2]);
            getchar(); // Clearing newline character from input buffer
            printf("Marks updated successfully.\n");
            // Save marks to file after updating
            saveMarksToFile(students, count);
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteMarks(Student students[], int *count) {
    char name[50];
    int i, j;
    printf("\nEnter name of student whose marks you want to delete: ");
    scanf("%s", name);
    getchar(); // Clearing newline character from input buffer
    for (i = 0; i < *count; i++) {
        if (strcmp(name, students[i].name) == 0) {
            for (j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Marks deleted successfully.\n");
            // Save marks to file after deleting
            saveMarksToFile(students, *count);
            return;
        }
    }
    printf("Student not found.\n");
}

void displayMarks(Student students[], int count) {
    int i, j;
    printf("\nStudent Details:\n");
    for (i = 0; i < count; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Physics Marks: ");
        for (j = 0; j < 3; j++) {
            printf("%.2f ", students[i].marks_physics[j]);
        }
        printf("\nChemistry Marks: ");
        for (j = 0; j < 3; j++) {
            printf("%.2f ", students[i].marks_chemistry[j]);
        }
        printf("\nMaths Marks: ");
        for (j = 0; j < 3; j++) {
            printf("%.2f ", students[i].marks_maths[j]);
        }
        printf("\nGrade: ");
        
        // Calculate percentage for each subject and average
        float total_percentage = 0;
        for (j = 0; j < 3; j++) {
            float total_marks_subject = students[i].marks_physics[j] + students[i].marks_chemistry[j] + students[i].marks_maths[j];
            float percentage = (total_marks_subject / 180) * 100; // Total marks in each subject: 40 + 40 + 100 = 180
            total_percentage += percentage;
        }
        float average_percentage = total_percentage / 3;

        // Calculate grade based on average percentage
        printf("%c\n", calculateGrade(average_percentage));
        printf("\n");
    }
}

char calculateGrade(float percentage) {
    if (percentage >= 91) return 'S';
    else if (percentage >= 81) return 'A';
    else if (percentage >= 71) return 'B';
    else if (percentage >= 61) return 'C';
    else if (percentage >= 51) return 'D';
    else if (percentage >= 41) return 'E';
    else return 'F';
}

void saveMarksToFile(Student students[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write each student's details to the file
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n", students[i].name,
                students[i].marks_physics[0], students[i].marks_physics[1], students[i].marks_physics[2],
                students[i].marks_chemistry[0], students[i].marks_chemistry[1], students[i].marks_chemistry[2],
                students[i].marks_maths[0], students[i].marks_maths[1], students[i].marks_maths[2]);
    }

    fclose(file);
}

void loadMarksFromFile(Student students[], int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }

    // Read each student's details from the file
    while (fscanf(file, "%s %f %f %f %f %f %f %f %f %f", students[*count].name,
            &students[*count].marks_physics[0], &students[*count].marks_physics[1], &students[*count].marks_physics[2],
            &students[*count].marks_chemistry[0], &students[*count].marks_chemistry[1], &students[*count].marks_chemistry[2],
            &students[*count].marks_maths[0], &students[*count].marks_maths[1], &students[*count].marks_maths[2]) != EOF) {
        (*count)++;
    }

    fclose(file);
}