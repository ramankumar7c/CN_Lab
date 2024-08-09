#include <stdio.h>
#include <string.h>

struct dob {
    int day;
    int month;
    int year;
};

struct student_info {
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

void printStudentInfoByValue(struct student_info student) {
    printf("By Value:\n");
    printf("Roll No: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("Date of Birth: %02d/%02d/%d\n", student.age.day, student.age.month, student.age.year);
}

void printStudentInfoByAddress(struct student_info *student) {
    printf("By Address:\n");
    printf("Roll No: %d\n", student->roll_no);
    printf("Name: %s\n", student->name);
    printf("CGPA: %.2f\n", student->CGPA);
    printf("Date of Birth: %02d/%02d/%d\n", student->age.day, student->age.month, student->age.year);
}

int main() {
    struct student_info student;

    printf("Enter Roll No: ");
    scanf("%d", &student.roll_no);
    
    printf("Enter Name: ");
    scanf(" %[^\n]%*c", student.name);
    
    printf("Enter CGPA: ");
    scanf("%f", &student.CGPA);

    printf("Enter Date of Birth (dd mm yyyy): ");
    scanf("%d %d %d", &student.age.day, &student.age.month, &student.age.year);

    printStudentInfoByValue(student);

    printStudentInfoByAddress(&student);

    return 0;
}
