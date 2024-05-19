#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

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

void searchStudent(Student students[], int count, char name[]) {
    int i;
    for (i = 0; i < count; i++) {
        float total_percentage = 0;
        if (strcmp(name, students[i].name) == 0) {
            printf("\nStudent Details:\n");
            printf("Name: %s\n", students[i].name);
            printf("Physics Marks: %.2f %.2f %.2f\n", students[i].marks_physics[0], students[i].marks_physics[1], students[i].marks_physics[2]);
            printf("Chemistry Marks: %.2f %.2f %.2f\n", students[i].marks_chemistry[0], students[i].marks_chemistry[1], students[i].marks_chemistry[2]);
            printf("Maths Marks: %.2f %.2f %.2f\n", students[i].marks_maths[0], students[i].marks_maths[1], students[i].marks_maths[2]);
            for (int j = 0; j < 3; j++) {
                float total_marks_subject = students[i].marks_physics[j] + students[i].marks_chemistry[j] + students[i].marks_maths[j];
                float percentage = (total_marks_subject / 180) * 100;
                total_percentage += percentage;
            }
            float average_percentage = total_percentage / 3;
            printf("Average Percentage: %.2f\n", average_percentage);
            printf("Grade: %c\n", calculateGrade(average_percentage));
            return;
        }
    }
    printf("Student not found.\n");
}
