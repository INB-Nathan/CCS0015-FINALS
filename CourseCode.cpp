#include <iostream>
#include <iomanip>
#include "CourseCode.h"

using namespace std;

int main() {
    string input;
    BinaryTree tree;
    LoadCourses(tree);

    int choice;
    do {
        while (true) {
            
            CourseCodeMenu();
            cout << "Enter choice: ";
            cin >> input;

            if (input.length() == 1 && isdigit(input[0])) {
                choice = input[0] - '0';
                if (choice >= 0 && choice <= 4) {
                    break;
                }
            }
            system("cls");
            cout << "Invalid input! \nPlease enter a number between 0 and 4." << endl;
            cin.clear(); 
        }

        switch (choice) {
            case 1:
                AddCourse(tree);
                break;
            case 2:
                tree.ViewCourses();
                break;
            case 3:
                EditCourse(tree);
                break;
            case 4:
                DeleteCourse(tree);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
