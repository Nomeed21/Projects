#include <iostream>
#include <string>
#include <iomanip>

#define MAX_STUDENTS 100
#define COURSES_PER_STUDENT 5
using namespace std;

typedef struct {
    string name;
    int age;
    struct Course {
        string course;
        int grade;
        int Units;
    };
} Records;

class StudentRecords {
private:    
    Records students[MAX_STUDENTS];
    int studentCount;
    int locateStudent(string name) {
        for (int i = 0; i < studentCount; i++) {
            if (students[i].name == name) {
                return i;
            }
        }
        return -1; // Student not found
    }
    bool isDuplicate(string name) {
        return locateStudent(name) != -1;
    }
    bool isEmpty() {
        return studentCount == 0;
    }
    bool isFull() {
        return studentCount >= MAX_STUDENTS;
    }
public:
    StudentRecords() {
        studentCount = 0;
    }

    void addStudent(Records newStudent) {
        if (!isFull()) {
            students[studentCount] = newStudent;
            studentCount++;
        } else {
            cout << "Maximum student limit reached." << endl;
        }
    }

    void deleteStudent(string name) {
        if (isEmpty()) {
            cout << "No students to delete." << endl;
            return;
        }
        int index = locateStudent(name);
        if (index != -1) {
            for (int j = index; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Student " << name << " deleted." << endl;
            return;
        }
        cout << "Student " << name << " not found." << endl;
    }

    void displayStudents() {
        for (int i = 0; i < studentCount; i++) {
            cout << "Name: " << students[i].name << ", Age: " << students[i].age << endl;
            for (int j = 0; j < COURSES_PER_STUDENT; j++) {
                cout << "Course: " << students[i].courses[j].course 
                     << ", Grade: " << students[i].courses[j].grade 
                     << ", Units: " << students[i].courses[j].Units << endl;
            }
            cout << endl;
        }
    }

    int menu(){
        int choice;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Students" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }
};

int main(){
    StudentRecords records;
    switch (records.menu()) {
        case 1: {
            Records newStudent;
            cout << "Enter student name: ";
            cin >> newStudent.name;
            cout << "Enter student age: ";
            cin >> newStudent.age;
            for (int i = 0; i < COURSES_PER_STUDENT; i++) {
                cout << "Enter course name: ";
                cin >> newStudent.courses[i].course;
                cout << "Enter grade: ";
                cin >> newStudent.courses[i].grade;
                cout << "Enter units: ";
                cin >> newStudent.courses[i].Units;
            }
            records.addStudent(newStudent);
            break;
        }
        case 2: {
            string name;
            cout << "Enter student name to delete: ";
            cin >> name;
            records.deleteStudent(name);
            break;
        }
        case 3:
            records.displayStudents();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}