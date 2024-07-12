#include <iostream>
#include "EnrollMenu.h"
using namespace std;

int main(){
    EnrollMenu eMenu;
    string studentID;
    int choice;
    while (true){
    cout << "1. Enroll Student\n";
    cout << "2. View Enrollees\n";
    cout << "0. Exit\n";
    cin >> choice;
    switch (choice){
        case 1:
            cout << "Enroll Student\n";
            while (true){
            cout << "Enter student ID: ";
            cin >> studentID;
            if (eMenu.isExisting(studentID)){
            eMenu.EnrollStudent(studentID);
            break;
            }
            }
        case 2:
            eMenu.ViewEnrollees();
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid choice.\n";
            break;
    } 
    } 
}