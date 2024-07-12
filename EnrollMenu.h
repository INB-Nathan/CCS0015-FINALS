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
    bool blockSectionExists(string);
    bool courseCodeExists(string);
    bool scheduleExists(string);
    // Function Prototypes
    void EnrollStudent(string);
    void ViewEnrollees();
    int ViewSchedules(string,int);
};

int EnrollMenu::ViewSchedules(string courseCode, int identifier) {
    string schedFile;
    ifstream ifile;
    string scheduleData[7];
    ifstream schedIfile("Schedules\\SCHEDULES.txt");
    if (schedIfile.is_open()) {
        string line;
        while (getline(schedIfile, line)) {
            if(line.find(courseCode) != string::npos) {
                identifier = identifier + 1;
            schedFile = "Schedules\\" + line + ".txt";
            ifile.open(schedFile);
            if (ifile.is_open()) {
                for (int i = 0; i < 7; i++) {
                    getline(ifile, scheduleData[i]);
                }
                ifile.close();
                cout <<"|" <<"----------------------------------------------------------------------------------------------------------------------"<< "|\n";
                cout << "|" << setw(11) << scheduleData[0] << " | " << setw(10) << scheduleData[1] << " | " << setw(5) << scheduleData[2] << " | " << setw(10) << scheduleData[3] << " | " << setw(10) << scheduleData[4] << " | " << setw(10) << scheduleData[5] << " | " << setw(10) << scheduleData[6] << " |\n";
                cout <<"|" <<"----------------------------------------------------------------------------------------------------------------------"<< "|\n";
            } else {
                cout << "Failed to open file: " << schedFile << endl;
            }
            }
        }
        schedIfile.close();
        return identifier;
    } else {
        cout << "Failed to open SCHEDULES.txt file." << endl;
        return identifier;
    }
}

bool EnrollMenu::courseCodeExists(string courseCode) {
    ifstream file("CourseRecords/recordlist.txt");
    string line;
    while (getline(file, line)) {
        if (line.find(courseCode) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}


bool EnrollMenu::scheduleExists(string courseSchedule)
{
    ifstream file("schedules\\SCHEDULES.txt");
    string line;
    while (getline(file, line))
    {
        if (line.find(courseSchedule) != string::npos)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool EnrollMenu::blockSectionExists(string blockSection)
{
    ifstream file("Schedules/SCHEDULES.txt");
    string line;
    while (getline(file, line))
    {
        if (line.find(blockSection) != string::npos)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool EnrollMenu::isExisting(string studentID)
{
    ifstream file("Students\\idlist.txt");
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
    cout << "Student ID not found.\n";
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
    LoadCourses(tree);
    int sure = 0, identifier = 0;
    string line;
    string courseCode, courseSchedule, blockSection, studentFirstName, studentLastName, studentMiddlename;
    if (isEnrolled(studentID, blockSection, courseCode, courseSchedule))
    {
        cout << "Student is already enrolled in the course.\n";
        return;
    }
    do
    {
        do
        {
            do
            {
                system("cls");
                tree.ViewCourses();
                cout << "Enter course code: ";
                cin >> courseCode;
                if (courseCodeExists(courseCode) == false)
                {
                    cout << "Course not found.\n";
                    system("pause");
                }
            } while (courseCodeExists(courseCode) == false);
            cout << "Are you sure you want to enroll in this course? (1 for yes, 0 for no): ";
            cin >> sure;
        } while (sure == 0);
        system("cls");
        ViewSchedules(courseCode, identifier);
        if (identifier == 0)
        {
            cout << "No schedules found.\n";
            return;
        }
    } while (identifier == 0);
    do
    {
        cout << "\nEnter block section: ";
        cin >> blockSection;
        if (blockSectionExists(blockSection) == false)
        {
            cout << "Block section not found, Please try again.\n";
        }
    } while (blockSectionExists(blockSection) == false);
    do
    {
        cout << "\nEnter course schedule: ";
        cin >> courseSchedule;
        if (scheduleExists(courseSchedule) == false)
        {
            cout << "Schedule not found, Please try again.\n";
        }
    } while (scheduleExists(courseSchedule) == false);

    ifstream studfile("Students\\" + studentID + ".txt");
    if (studfile.is_open())
    {
        getline(studfile, studentID); // Read the student ID
        getline(studfile, studentFirstName);
        getline(studfile, studentLastName);
        getline(studfile, studentMiddlename);
        studfile.close();
    }
    else
    {
        cerr << "Unable to open file for reading.\n";
    }
    ofstream file("Students\\Enrolled Courses\\" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt", ios::app);
    if (file.is_open())
    {
        file << studentID << "-" << studentLastName << "-" << studentFirstName << "-" << studentMiddlename << "\n";
        file.close();
    }
    else
    {
        cout << "Unable to open file for writing.\n";
    }
    cout << "Student enrolled successfully.\n";
}

void EnrollMenu::ViewEnrollees()
{
    string courseCode, courseSchedule, blockSection;
    string studentID, studentFirstName, studentLastName, studentMiddlename;
    do
    {
        cout << "Enter course code: ";
        cin >> courseCode;
        if (courseCodeExists(courseCode) == false)
        {
            cout << "Course not found.\n";
        }
    } while (courseCodeExists(courseCode) == false);
    do
    {
        cout << "Enter block section: ";
        cin >> blockSection;
        if (blockSectionExists(blockSection) == false)
        {
            cout << "Block section not found, Please try again.\n";
        }
    } while (blockSectionExists(blockSection) == false);
    do
    {
        cout << "Enter course schedule: ";
        cin >> courseSchedule;
        if (scheduleExists(courseSchedule) == false)
        {
            cout << "Schedule not found, Please try again.\n";
        }
    } while (scheduleExists(courseSchedule) == false);
    ifstream file("Students\\Enrolled Courses\\" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt");
    string line;
    if (!file.is_open())
    {
        cout << "File is not existing.\n";
        return;
    }
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
