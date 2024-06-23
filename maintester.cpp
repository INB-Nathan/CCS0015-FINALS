#include <iostream>
#include <cctype>
#include "StudentMenu.h"

using namespace std;

int main(){
    StudentDetails sNode;
    string firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, birthday;
    int idNumber, yearLevel, counter = 0;

    while (counter < 3)
    {  
        while (true)
        {
            cout << "Enter First Name: ";
            getline(cin, firstName);

            if (sNode.IsValidName(firstName)) break;
        }
        
        while (true)
        {
            cout << "Enter Middle Name: ";
            getline(cin, middleName);

            if (sNode.IsValidName(lastName)) break;
        }
        
        while (true)
        {
            cout << "Enter Last Name: ";
            getline(cin, lastName);

            if (sNode.IsValidName(lastName)) break;
        }
        
        cout << "Enter Birthday (MM/DD/YYYY): ";
        getline(cin, birthday);
        cout << "Enter Gender (Male or Female): ";
        cin >> studentGender;
        cin.ignore();
        cout << "Enter City Address (ex. Manila City): ";
        getline(cin, studentAddress);
        cout << "Enter ID Number (9-digit ID Number): ";
        cin >> idNumber;
        cout << "Enter Degree Program (ex. BSITCST): ";
        cin >> degreeProgram;
        cout << "Enter Year Level (1-4): ";
        cin >> yearLevel;
        cin.ignore();

        // Insert he new value to the tree
        sNode.AddStudent(firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, birthday, idNumber, yearLevel);
        counter++;
    }

    cout << "\n\nTraversing the tree inorder:\n";
    cout << "Student Number\t\tName"<< endl; 
    sNode.ViewStudent(sNode.root);
}