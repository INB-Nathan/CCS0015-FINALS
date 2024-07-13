#include <iostream>
#include "EnrollMenu.h"
using namespace std;

int main(){
    EnrollMenu eMenu;
    string studentID;
    int choice;
    while (true){
    eMenu.EnrollmentMenu();

    system("cls");
    switch (choice){
        case 1:
            cout << "Enroll Student\n";
            while (true){
            cout << "Enter student ID: ";
            cin >> studentID;
            if (eMenu.isExisting(studentID)){
            eMenu.EnrollStudent(studentID);
            system("cls");
            break;
            }
            }
        case 2:
            eMenu.ViewEnrollees();
            system("pause");
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid choice.\n";
            break;
    } 
    } 
}