#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_STUDENTS 100
#define FILENAME "marks.txt" // File name to store marks

typedef struct {
    char name[50];
    float marks_physics[3];
    float marks_chemistry[3];
    float marks_maths[3];
} Student;

void addMarks(Student students[], int *count);
void updateMarks(Student students[], int count);
void deleteMarks(Student students[], int *count);
void displayMarks(Student students[], int count);
char calculateGrade(float percentage);
void saveMarksToFile(Student students[], int count);

#endif
