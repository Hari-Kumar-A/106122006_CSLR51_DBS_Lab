#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Golab Variables
#define MAX_COURSES 4
#define MAX_STUDENTS 150 
#define FILE_NAME "studentData.txt"


typedef struct{
    char courseName[10];
    int credits;
    char grade;
} Course;

typedef struct
{
    int rollno; 
    char name[50];
    char dept[10];
    Course courses[MAX_COURSES];
    int courseCount;
    float cgpa;
} Student;

Student students[MAX_STUDENTS];                                                                                 
int studentCount = 0;

int gradeConverter(char grade)
{
    switch (grade)
    {
    case 'S':
        return 10;
    case 'A':
        return 9;
    case 'B':
        return 8;
    case 'C':
        return 7;
    case 'D':
        return 6;
    case 'E':
        return 5;
    case 'F':
        return 0;
    default:
        return 0;
    }
}

void gpaCalculator(Student *student)
{
    int totalPoints = 0;
    int totalCredits = 0;
    int n = student->courseCount;
    for (int i = 0; i<n ; i++)
    {
        totalPoints += gradeConverter(student->courses[i].grade) * student->courses[i].credits;
        totalCredits += student->courses[i].credits;
    }
    if (totalCredits!=0) student->cgpa = (float)totalPoints / totalCredits; 
    else student->cgpa = 0.0; 
}

void addStudent()
{
    if (studentCount >= MAX_STUDENTS)
    {
        printf("Sorry, The capacity is full. We cannot add anymore students!\n");
        return;
    }
    Student *student = &students[studentCount];
    
    printf("Enter roll number: ");
    scanf("%d", &student->rollno);
    printf("Enter name: ");
    scanf("%s", student->name);
    printf("Enter department: ");
    scanf("%s", student->dept);
    printf("Enter number of courses (3 to 4): ");
    scanf("%d", &student->courseCount);

    //Courses Count
    for (int i = 0; i < student->courseCount; i++)
    {
        printf("Enter name of Course %d ", i + 1);
        scanf("%s", student->courses[i].courseName);
        printf("Enter credits of Course %d ", i + 1);
        scanf("%d", &student->courses[i].credits);
        printf("Enter grade of Course %d ", i + 1);
        scanf(" %c", &student->courses[i].grade);
    }
    gpaCalculator(student);//cgpa calculate and store..
    studentCount++;
}

void createGPAColumn()
{
    for (int i = 0; i < studentCount; i++)  gpaCalculator(&students[i]); 
    printf("GPA column created successfully for all students!\n");
}

void deleteCourse(int rollno, char *courseName)
{ 
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollno == rollno)
        {
            for (int j = 0; j < students[i].courseCount; j++)
            {
                if (strcmp(students[i].courses[j].courseName, courseName) == 0)//if courseName matches
                {
                    for (int k = j; k < students[i].courseCount - 1; k++)
                    {
                        students[i].courses[k] = students[i].courses[k + 1];
                    }
                    students[i].courseCount--;
                    gpaCalculator(&students[i]);
                    printf("Course %s deleted for student %d.\n", courseName, rollno);
                    return;
                }
            }
        }
    }
    printf("Course not found for the student.\n");
}

void insertCourse(int rollno, const char *courseName, int credit, char grade)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollno == rollno)
        {
            if (students[i].courseCount >= MAX_COURSES)
            {
                printf("Cannot add more courses for this student.\n");
                return;
            }
            Course *course = &students[i].courses[students[i].courseCount];
            strcpy(course->courseName, courseName);
            course->credits = credit;
            course->grade = grade;
            gpaCalculator(&students[i]);
            printf("Course %s inserted for student %d.\n", courseName, rollno);
            return;
        }
    }
    printf("Oops! Student not found.\n");
}

void updateCourse(int rollno, const char *oldName, const char *newName)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollno == rollno)
        {
            for (int j = 0; j < students[i].courseCount; j++)
            {
                if (strcmp(students[i].courses[j].courseName, oldName) == 0)
                {
                    strcpy(students[i].courses[j].courseName, newName);
                    printf("Course name updated from %s to %s for student %d.\n", oldName, newName, rollno);
                    return;
                }
            }
        }
    }
    printf("Course not found for the student.\n");
}

void calculateAllGPA()
{
    createGPAColumn();
}

void updateGrade(char grade, int new_points)
{
    for (int i = 0; i < studentCount; i++)
    {
        for (int j = 0; j < students[i].courseCount; j++)
        {
            if (students[i].courses[j].grade == grade)
            {
                students[i].courses[j].grade = new_points;
            }
        }
        gpaCalculator(&students[i]);
    }
    printf("Grades upgraded for all students.\n");
}

void upgradeGPA(int rollno)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollno == rollno)
        {
            gpaCalculator(&students[i]);
            printf("GPA upgraded for student bearing roll number %d.\n", rollno);
            return;
        }
    }
    printf("Student not found.\n");
}

void generateGradeReport(int rollno)
{
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].rollno == rollno)
        {
            printf("Report Card %d:\n", rollno);
            printf("+------------+-----------+\n");
            printf("|    Course  |   Grade   |\n");
            printf("+------------+-----------+\n");

            for (int j = 0; j < students[i].courseCount; j++)
            {
                printf("| %-10s |   %c   |\n", students[i].courses[j].courseName, students[i].courses[j].grade);
            }
            printf("+------------+-----------+\n");
            printf("|    CGPA    |    %.2f   |\n", students[i].cgpa);
            printf("+------------+-----------+\n");
            return;
        }
    }
    printf("Sorry, Student bearing %d not found.\n", rollno);
}

void MENU()
{
    printf("1. Insert student record\n");
    printf("2. Create GPA column\n");
    printf("3. Delete course\n");
    printf("4. Insert course\n");
    printf("5. Update course name\n");
    printf("6. Calculate GPA for all students\n");
    printf("7. Upgrade grade\n");
    printf("8. Upgrade GPA for a student\n");
    printf("9. Generate grade report\n");
    printf("10. Exit\n");
}

void readDataFromFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return;
    }
    studentCount = 0;
    while (fscanf(fp, "%d %s %s %d", &students[studentCount].rollno, students[studentCount].name,
                  students[studentCount].dept, &students[studentCount].courseCount) == 4)
    {
        for (int i = 0; i < students[studentCount].courseCount; i++)
        {
            fscanf(fp, "%s %d %c", students[studentCount].courses[i].courseName,
                   &students[studentCount].courses[i].credits, &students[studentCount].courses[i].grade);
        }
        gpaCalculator(&students[studentCount]);
        studentCount++;
        if (studentCount >= MAX_STUDENTS)
        {
            printf("Maximum student limit reached.\n");
            break;
        }
    }
    fclose(fp);
}

void writeDataToFile(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }
    for (int i = 0; i < studentCount; i++)
    {
        fprintf(fp, "+------------+-------+\n");
        fprintf(fp, "| Student: %d (%s)\n", students[i].rollno, students[i].name);
        fprintf(fp, "+------------+-------+\n");
        for (int j = 0; j < students[i].courseCount; j++)
        {
            fprintf(fp, "| %-10s |   %c   |\n", students[i].courses[j].courseName, students[i].courses[j].grade);
        }
        fprintf(fp, "+------------+-------+\n");
        fprintf(fp, "|   CGPA     | %.2f |\n", students[i].cgpa);
        fprintf(fp, "+------------+-------+\n");
    }
    fclose(fp);
    printf("Student data saved to file %s.\n", filename);
}

void addStudenToFile(const char *filename, Student *student)
{
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("Error opening file %s for appending.\n", filename);
        return;
    }
    fprintf(fp, "+------------+-------+\n");
    fprintf(fp, "| Student: %d (%s)\n", student->rollno, student->name);
    fprintf(fp, "+------------+-------+\n");
    for (int i = 0; i < student->courseCount; i++)
    {
        fprintf(fp, "| %-10s |   %c   |\n", student->courses[i].courseName, student->courses[i].grade);
    }
    fprintf(fp, "+------------+-------+\n");
    fprintf(fp, "| GPA        | %.2f |\n", student->cgpa);
    fprintf(fp, "+------------+-------+\n");
    fclose(fp);
    printf("Student data added to file %s.\n", filename);
}

void deleteStudentFromFile(const char *filename, int rollno)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return;
    }
 
    FILE *tempFp = fopen("temp.txt", "w");
    if (tempFp == NULL)
    {
        fclose(fp);
        printf("Error creating temporary file.\n");
        return;
    }

    int found = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp))
    {
        int current_rollno;
        sscanf(line, "%d", &current_rollno);
        if (current_rollno == rollno)
        {
            found = 1;
            continue; // skip this line
        }
        fputs(line, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    if (found)
    {
        remove(filename);
        rename("temp.txt", filename);
        printf("Student with roll number %d deleted from file.\n", rollno);
    }
    else
    {
        remove("temp.txt");
        printf("Student with roll number %d not found in file.\n", rollno);
    }
}

int main()
{
    int choice;
    const char *filename = "studentData.txt";  

    readDataFromFile(filename);   
    do
    {
        MENU();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addStudent();
            int index = studentCount - 1;
            addStudenToFile(filename, &students[index]);  
            break;

        case 2:
            createGPAColumn();
            break;

        case 3:
        {
            int rollno;
            char courseName[10];
            printf("Enter roll number: ");
            scanf("%d", &rollno);
            printf("Enter course name: ");
            scanf("%s", courseName);
            deleteCourse(rollno, courseName);
            writeDataToFile(filename);  
            break;
        }

        case 4:
        {
            int rollno;
            char courseName[10];
            int credit;
            char grade;
            printf("Enter roll number: ");
            scanf("%d", &rollno);
            printf("Enter course name: ");
            scanf("%s", courseName);
            printf("Enter credit: ");
            scanf("%d", &credit);
            printf("Enter grade: ");
            scanf(" %c", &grade);
            insertCourse(rollno, courseName, credit, grade);
            writeDataToFile(filename); 
            break;
        }

        case 5:
        {
            int rollno;
            char oldName[10], newName[10];
            printf("Enter roll number: ");
            scanf("%d", &rollno);
            printf("Enter old course name: ");
            scanf("%s", oldName);
            printf("Enter new course name: ");
            scanf("%s", newName);
            updateCourse(rollno, oldName, newName);
            writeDataToFile(filename);  
            break;
        }

        case 6:
            calculateAllGPA();
            break;

        case 7:
        {
            char grade;
            int new_points;
            printf("Enter grade to upgrade: ");
            scanf(" %c", &grade);
            printf("Enter new points: ");
            scanf("%d", &new_points);
            updateGrade(grade, new_points);
            writeDataToFile(filename);  
            break;
        }

        case 8:
        {
            int rollno;
            printf("Enter roll number: ");
            scanf("%d", &rollno);
            upgradeGPA(rollno);
            writeDataToFile(filename);  
            break;
        }

        case 9:
        {
            int rollno;
            printf("Enter roll number: ");
            scanf("%d", &rollno);
            generateGradeReport(rollno);
            break;
        }

        case 10:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 10);

    return 0;
}
