#include <iostream>
#include "StudentMenu.h"

using namespace std;

int main(){
    StudentDetails sNode;
    string firstName, lastName, middleName, degreeProgram, studentGender, studentAddress;
    int idNumber, yearLevel, counter = 0;

    while (counter < 6)
    {  
        cout << "Enter First Name: ";
        getline(cin, firstName);
        cout << "Enter Middle Name: ";
        getline(cin, middleName);
        cout << "Enter Last Name: ";
        getline(cin, lastName);
        cout << "Enter Degree Program (ex. BSITCST): ";
        cin >> degreeProgram;
        cout << "Enter Gender (Male or Female): ";
        cin >> studentGender;
        cin.ignore();
        cout << "Enter City Address (ex. Manila City): ";
        getline(cin, studentAddress);
        cout << "Enter ID Number (9-digit ID Number): ";
        cin >> idNumber;
        cout << "Enter Year Level (1-4): ";
        cin >> yearLevel;
        cin.ignore();

        // Insert he new value to the tree
        sNode.AddStudent(firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, idNumber, yearLevel);
        counter++;
    }

    cout << "\n\nTraversing the tree inorder:\n";
    sNode.ViewStudent(sNode.root);
}