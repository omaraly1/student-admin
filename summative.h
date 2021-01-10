#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

typedef struct {
    char courseCode[100], courseName[100];
    int period, courseID, numStudents, studentID[400], mark[400];

} Course;

typedef struct {
    char firstName[50], lastName[50];
    int studentID;
} Student;

typedef struct {
    int teacherID, numCourses, courseID[4];
    char firstName[50], lastName[50];
} Teacher;


int loadStudents(Student *);
int loadCourses(Course *);
int loadTeachers(Teacher *);
int saveStudents(Student *, int);
int saveCourses(Course *, int);
int saveTeachers(Teacher *, int);
void sortStudentsByFirstName(Student *, int);
void sortStudentsByLastName(Student *, int);
int findNextStudent (Student *, char*, int, int);
int addStudent(Student *, Student *, int);
int deleteStudent (Student *, Course *, int, int*, int);
int displayStudents(Student *, Course *, int *, int);
int displayItems(char *, char *, char **, char **, char **, int, int, int, int);
int displayOneStudent(Student *, Course *, int, int);
int mainMenu();
int displayCourses(Course *, int, int);
int displayAllCourses(Teacher *, Course *, Student *, int, int, int);
void sortTeachersByLastName(Teacher *, int);
void sortCoursesByName(Course *, int);
int displayTeachers(Teacher *, Course *, int*, int);
int displayOneCourse(Teacher *, Course *, Student *, int, int, int);
