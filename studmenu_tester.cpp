#include <iostream>
#include <cctype>
#include <string>
#include "SRC/StudentMenu.h"

using namespace std;

int main()
{
    StudentDetails sNode;
    string firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, birthMonthName, fullBirthday;
    int idNumber, yearLevel, choice, birthDay, birthYear, birthMonthNum, idToView, idToEdit, idToDelete;
    char conChoice = ' ';
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
            while (true)
            {
                cout << "Enter First Name: ";
                getline(cin, firstName);

                if (sNode.IsValidName(firstName))
                    break;
            }

            while (true)
            {
                cout << "Enter Middle Name: ";
                getline(cin, middleName);

                if (sNode.IsValidName(middleName))
                    break;
            }

            while (true)
            {
                cout << "Enter Last Name: ";
                getline(cin, lastName);

                if (sNode.IsValidName(lastName))
                    break;
            }

            cout << "Enter Birth Month: ";
            cin >> birthMonthName;
            while (!sNode.IsValidBirthMonth(birthMonthName))
            {
                cout << "Invalid Month! Please enter a valid birth month." << endl;
                cout << "Enter Birth Month: ";
                cin >> birthMonthName;
            }

            cout << "Enter Birth Day: ";
            cin >> birthDay;

            cout << "Enter Birth Year: ";
            cin >> birthYear;
            while (!sNode.IsValidBirthDate(birthDay, birthMonthName, birthYear))
            {
                cout << "Invalid Birth Date! Please enter a valid Birth Date." << endl;
                cout << "Enter Birth Month: ";
                cin >> birthMonthName;
                cout << "Enter Birth Day: ";
                cin >> birthDay;
                cout << "Enter Birth Year: ";
                cin >> birthYear;
            }

            while (true)
            {
                cout << "Enter Gender (Male or Female): ";
                cin >> studentGender;
                cin.ignore();

                if (sNode.IsValidGender(studentGender))
                    break;
            }

            while (true)
            {
                cout << "Enter City Address (ex. Manila City): ";
                getline(cin, studentAddress);

                if (sNode.IsValidName(studentAddress))
                    break;
            }

            while (true)
            {
                cout << "Enter ID Number (9-digit ID Number): ";
                cin >> idNumber;

                if (sNode.IsValidStudentNum(idNumber))
                    break;
            }

            while (true)
            {
                cout << "Enter Degree Program (ex. BSITCST): ";
                cin >> degreeProgram;

                if (sNode.IsValidName(degreeProgram))
                    break;
            }

            while (true)
            {
                cout << "Enter Year Level (1-4): ";
                cin >> yearLevel;
                cin.ignore();

                if (yearLevel >= 1 && yearLevel <= 4)
                    break;
                else
                    cout << "Enter a Valid Year Level." << endl;
            }

            birthMonthNum = sNode.MonthNameToNumber(birthMonthName);                                          // Convert month name to number(int)
            fullBirthday = to_string(birthMonthNum) + "/" + to_string(birthDay) + "/" + to_string(birthYear); // Convert into the full birthday format (string)

            while (true)
            {
                cout << "Confirm Add Student? [Y/N]" << endl;
                cin >> conChoice;

                if (toupper(conChoice) == 'Y')
                {
                    sNode.AddStudent(firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, fullBirthday, idNumber, yearLevel);
                    break; // Exit loop after adding student
                }
                else if (toupper(conChoice) == 'N')
                {
                    cout << "Add Student Cancelled" << endl;
                    break; // Exit loop without adding student
                }
                else
                {
                    cout << "Invalid Input. Y or N only." << endl;
                }
            }

            sNode.Pause();
            system("clear");
            break;
        }
        case 2:
        {
            sNode.ViewStudents();
            sNode.Pause();
            system("clear");
            break;
        }
        case 3:
        {
            sNode.ViewStudents();
            cout << endl;

            while (true) // to edit
            {
                cout << "Enter Student Number to View: ";
                cin >> idToView;

                if (sNode.IsValidStudentNum(idToView))
                    break;
            }
            system("clear");
            sNode.ViewDetails(to_string(idToView));

            sNode.Pause();
            system("clear");

            break;
        }
        case 4:
        {
            sNode.ViewStudents();
            cout << endl;

            while (true) // to edit
            {
                cout << "Enter Student Number to Edit: ";
                cin >> idToEdit;

                if (sNode.IsValidStudentNum(idToEdit))
                    break;
            }

            while (true)
            {
                cout << "Confirm Edit Student? [Y/N]" << endl;
                cin >> conChoice;

                if (toupper(conChoice) == 'Y')
                {
                    sNode.EditStudent(to_string(idToEdit));

                    cout << endl
                         << "Successfully Edited" << endl
                         << endl;
                    break; // Exit loop after editing student
                }
                else if (toupper(conChoice) == 'N')
                {
                    cout << "Edit Student Cancelled" << endl;
                    break; // Exit loop without editing student
                }
                else
                {
                    cout << "Invalid Input. Y or N only." << endl;
                }
            }

            sNode.Pause();
            system("clear");

            break;
        }
        case 5:
        {
            sNode.ViewStudents();
            cout << endl;

            while (true) // to edit
            {
                cout << "Enter Student Number to Delete: ";
                cin >> idToDelete;

                if (sNode.IsValidStudentNum(idToDelete))
                    break;
            }

            while (true)
            {
                cout << "Confirm Delete Student? [Y/N]" << endl;
                cin >> conChoice;

                if (toupper(conChoice) == 'Y')
                {
                    sNode.DeleteStudent(to_string(idToDelete));

                    cout << endl
                         << "Successfully Deleted" << endl
                         << endl;
                    break; // Exit loop after deleting student
                }
                else if (toupper(conChoice) == 'N')
                {
                    cout << "Delete Student Cancelled" << endl;
                    break; // Exit loop without deleting student
                }
                else
                {
                    cout << "Invalid Input. Y or N only." << endl;
                }
            }

            sNode.Pause();
            system("clear");

            break;
        }
        }
    }
}
