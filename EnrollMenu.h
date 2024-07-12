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

bool EnrollMenu::isExisting(string studentID)
{
    ifstream file("Students\\StudentList.txt");
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
    cout<< "Student ID not found.\n";
    return false;
}

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
    string courseCode, courseSchedule, blockSection, studentFirstName, studentLastName, studentMiddlename;
    if (isEnrolled(studentID, blockSection, courseCode, courseSchedule))
    {
        cout << "Student is already enrolled in the course.\n";
        return;
    }
    cout << "Enter course code to enroll: ";
    cin >> courseCode;
    cout << "Enter block section: ";
    cin >> blockSection;
    cout << "Enter course schedule: ";
    cin >> courseSchedule;

    ifstream file ("Students\\" + studentID + ".txt");
    if (file.is_open())
    {
        getline(file, studentID); // Read the student ID
        getline(file, studentFirstName);
        getline(file, studentLastName);
        getline(file, studentMiddlename);
        file.close();
    }
    else
    {
        cerr << "Unable to open file for reading.\n";
    }
    ofstream file("Students\\Enrolled Courses\\" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt", ios::app);
    if (file.is_open()){
        file << studentID << "-" << studentLastName << "-" << studentFirstName << "-" << studentMiddlename << "\n;
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
    string studentID, studentFirstName, studentLastName, studentMiddlename;
    cout << "Enter the course code: ";
    cin >> courseCode;
    cout << "Enter the block section: ";
    cin >> blockSection;
    cout << "Enter the course schedule: ";
    cin >> courseSchedule;
    ifstream file("Students\\Enrolled Courses\\" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt");
    string line;
    if (!file.is_open())
    {
        cerr << "File is not existing.\n";
        return;
    }
    tolower(courseCode, blockSection, courseSchedule);
    cout << "Enrolled Students in " << courseCode << " " << blockSection << " " << courseSchedule << ":\n";
    while (getline(file, line))
    {
        studentID = line.substr(0, line.find("-"));
        line.erase(0, line.find("-") + 1);
        studentLastName = line.substr(0, line.find("-"));
        line.erase(0, line.find("-") + 1);
        studentFirstName = line.substr(0, line.find("-"));
        line.erase(0, line.find("-") + 1);
        studentMiddlename = line;
        cout << studentID << " " << studentLastName << ", " << studentFirstName << " " << studentMiddlename << "\n";
    }
    file.close();
}