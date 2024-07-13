#include <iostream>
#include "ScheduleMenu.h"
#include "StudentMenu.h"
#include "EnrollMenu.h"

using namespace std;

int StudentManagementMenu();

int main() {
    Schedule sched;
    StudentDetails student;
    EnrollMenu enroll;
    
    while (true) {
        Front();
        switch (StudentManagementMenu()){
            case 1:
            enroll.EnrollFunctionalities();
            break;
            case 2:
            student.StudentFunctionalities();
            break;
            case 3:
            CourseFunctionalities();
            break;
            case 4:
            sched.ScheduleFunctionalities();
            break;
            case 0:
            exit(0);
            break;
            default:
            cout << "Enter a valid choice.\n";
            return 0;
            break;
        }
    }
}

int StudentManagementMenu() {
    int choice;

    do {
        cout << "-- Student Management --\n\n";
        cout << "[1] Enroll Students\n";
        cout << "[2] Manage Students\n";
        cout << "[3] Manage Course\n";
        cout << "[4] Manage Schedules\n";
        cout << "[0] Exit\n\n";
        cout << ":: ";
        cin >> choice;
    } while (choice < 0 || choice > 4);
    system("clear");
    return choice;
}