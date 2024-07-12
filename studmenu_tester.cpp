#include <iostream>
#include <cctype>
#include <string>
#include "StudentMenu.h"

using namespace std;

int main()
{
    StudentDetails sNode;
    sNode.FetchStudentInfo();
    
    while (true)
    {
        switch (sNode.StudMenu())
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
