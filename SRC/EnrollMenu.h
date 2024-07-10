#include <iostream>
#include <fstream>
#include <string>
#include "CourseCode.h"
using namespace std;

class EnrollMenu
{
    private:
        string studentID, studentName, courseCode, courseTitle, courseUnits, courseYearLevel, courseSchedule, blockSection;
    public:
    // Validation Functions
        bool isEnrolled(string, string, string, string);
        bool isExisting(string);
    // Function Prototypes
        void EnrollStudent(string);
        void ViewEnrollees();
};

bool EnrollMenu::isEnrolled(string studentID, string courseCode, string courseSchedule, string blockSection)
{
    ifstream file("Students\\Enrolled Courses" + blockSection + "-" + courseCode + "-" + courseSchedule + "list.txt");
    string line;
    while (getline(file, line))
    {
        if (line.find(studentID) != string::npos)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void EnrollMenu::EnrollStudent(string studentID)
{
    BinaryTree tree;
    loadCourses(tree);
    string courseCode, courseSchedule, blockSection;
    cout << "Enter block section: ";
    cin >> blockSection;
    cout << "Enter course code to enroll: ";
    cin >> courseCode;
    cout << "Enter course schedule: ";
    cin >> courseSchedule;
    if (isEnrolled(studentID, blockSection, courseCode, courseSchedule))
    {
        cout << "Student is already enrolled in the course.\n";
        return;
    }
    ofstream file("Students\\Enrolled Courses\\" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt", ios::app);
    if (file.is_open())
    {
        file << studentID << "\n";
        file.close();
    }
    else
    {
        cerr << "Unable to open file for writing.\n";
    }
    cout << "Student enrolled successfully.\n";
}

void EnrollMenu::ViewEnrollees()
{
    string courseCode, courseSchedule, blockSection;
    cout << "Enter the course code: ";
    cin >> courseCode;
    cout << "Enter the course schedule: ";
    cin >> courseSchedule;
    cout << "Enter the block section: ";
    cin >> blockSection;
    ifstream file("Students\\Enrolled Courses\\" + blockSection + "_" + courseCode + "_" + courseSchedule + "_list.txt");
    string line;
    if (!file.is_open())
    {
        cerr << "File is not existing.\n";
        return;
    }
    while (getline(file, line))
    {
        cout << line << endl;
    }
    file.close();
}

