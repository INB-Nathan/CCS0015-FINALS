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
    void Pause();
    int EnrollmentMenu();
    int EnrollFunctionalities();

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
    // DESIGN
    void HeaderDesign();
};

void EnrollMenu::HeaderDesign() {
    cout << "                        .|                                          _" << endl;
    cout << "                       | |                                         | |" << endl;
    cout << "                       |'|            ._____                       |'|            ._____" << endl;
    cout << "               ___    |  |            |.   |' .---" << "-|       ___    |  |            |.   |' .---" << ".  " << endl;
    cout << "       _    .-'   '-. |  |     .--'|  ||   | _|    |    .-'   '-. |  |     .--'|  ||   | _|    |" << endl;
    cout << "    .-'|  _.|  |    ||   '-__  |   |  |    ||      |  _.|  |    ||   '-__  |   |  |    ||      |  " << endl;
    cout << "    |' | |.    |    ||       | |   |  |    ||      | |.    |    ||       | |   |  |    ||      |" << endl;
    cout << " ___|  '-'     '      \"       '-'   '-.'    '`      |-'     '      \"       '-'   '-.'    '`      |___" << endl;
    cout << " ___      _        _             _   ___     _ _            _   _      _                _ _                  " << endl;
    cout << "|_ _|__ _| |___ __(_)__ _   _ _ (_) | _ )_ _(_) |_ ___ ___ | | | |_ _ (_)_ _____ _ _ __(_) |_ _  _ " << endl;
    cout << " | |/ _` | / -_|_-< / _` | | ' \\| | | _ \\ '_| |  _/ _ (_-< | |_| | ' \\| \\ V / -_) '_(_-< |  _| || | " << endl;
    cout << "|___\\__, |_\\___/__/_\\__,_| |_||_|_| |___/_| |_|\\__\\___/__/  \\___/|_||_|_|\\_/\\___|_| /__/_|\\__|\\_, |" << endl;
    cout << "    |___/                                                                                     |__/           " << endl;
}


void EnrollMenu::Pause() // Function to replace "system("pause")"
{
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get(); // Wait for the user to press Enter
}

int EnrollMenu::EnrollmentMenu() {
    int choice;
    do {
        HeaderDesign();
        cout << "-- Enrollment Menu --\n\n";
        cout << "[1] Enroll Students\n";
        cout << "[2] View Enrollee\n";
        cout << "[0] Return To Main Menu\n\n";
        cout << ":: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 2);
    system("clear");
    return choice;
}

int EnrollMenu::EnrollFunctionalities() {
    string studentID;
    while (true) {
        switch (EnrollmentMenu()) {
            case 1:
            while (true){
            HeaderDesign();
            cout << "Enter student ID: ";
            cin >> studentID;
            if (isExisting(studentID)){
            EnrollStudent(studentID);
            }
            }
            break;
            case 2:
            ViewEnrollees();
            break;
            case 0:
            return 0;
            break;
            default:
            return 0;
            break;
        }
    }
    return 0;
}

int EnrollMenu::ViewSchedules(string courseCode, int identifier) {
    string schedFile;
    ifstream ifile;
    string scheduleData[7];
    ifstream schedIfile("output/Schedules/SCHEDULES.txt");
    if (schedIfile.is_open()) {
        string line;
        while (getline(schedIfile, line)) {
            HeaderDesign();
            if(line.find(courseCode) != string::npos) {
                identifier = identifier + 1;
            schedFile = "output/Schedules/" + line + ".txt";
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
    ifstream file("output/Schedules/SCHEDULES.txt");
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
    ifstream file("output/Students/idlist.txt");
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
    ifstream file("output/Students/Enrolled Courses" + blockSection + "-" + courseCode + "-" + courseSchedule + "list.txt");
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
        HeaderDesign();
        cout << "Student is already enrolled in the course.\n";
        return;
    }
    do
    {
        do
        {
            do
            {
                system("clear");
                HeaderDesign();
                tree.ViewCourses();
                cout << "Enter course code: ";
                cin >> courseCode;
                if (courseCodeExists(courseCode) == false)
                {
                    cout << "Course not found.\n";
                    Pause();
                }
            } while (courseCodeExists(courseCode) == false);
            cout << "Are you sure you want to enroll in this course? (1 for yes, 0 for no): ";
            cin >> sure;
        } while (sure == 0);
        system("clear");
        HeaderDesign();
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

    ifstream studfile("output/Students/" + studentID + ".txt");
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
    ofstream file("output/Students/Enrolled Courses/" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt", ios::app);
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
    HeaderDesign();
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
    ifstream file("output/Students/Enrolled Courses/" + blockSection + "_" + courseCode + "_" + courseSchedule + "_LIST.txt");
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
    Pause();
}
