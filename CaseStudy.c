#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functions.h>

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
