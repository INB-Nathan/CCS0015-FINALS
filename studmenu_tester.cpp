#include <iostream>
#include <cctype>
#include <string>
#include "StudentMenu.h"

using namespace std;

int main()
{
    StudentDetails sNode;
    int choice;
    sNode.FetchStudentInfo();

    while (true)
    {
        cout << "1. Add Student" << endl;
        cout << "2. View Student List" << endl;
        cout << "3. View Student's Record" << endl;
        cout << "4. Edit Student Info" << endl;
        cout << "5. Delete Student" << endl
             << endl;
        cout << "0. Exit" << endl;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 0:
        {
            return 0;
        }
        case 1:
        {
            sNode.AddStudentInput();
            break;
        }
        case 2:
        {
            sNode.ViewStudents();
            break;
        }
        case 3:
        {
            sNode.ViewStudentsForInputFunctions();
            cout << endl;
            sNode.ViewDetailsInput();
            break;
        }
        case 4:
        {
            sNode.ViewStudentsForInputFunctions();
            cout << endl;
            sNode.EditStudentInput();
            break;
        }
        case 5:
        {
            sNode.ViewStudentsForInputFunctions();
            cout << endl;
            sNode.DeleteStudentInput();
            break;
        }
        }
    }
}
