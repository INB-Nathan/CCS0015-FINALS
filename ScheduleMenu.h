#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
#include "CourseMenu.h"
using namespace std;

class Schedule {
    private:
    struct SchedNode {
        int numUnits, yearLevel;
        string courseTitle, courseCode, section, weekDay, startTime, endTime, roomNumber;
        int schedHour, schedMinute, schedSecond;
        double amountMinute;

        SchedNode *left;
        SchedNode *right;
    } *holder, *current;

    public:
    SchedNode *root;
    Schedule();
    int ScheduleMenu();
    void AddScheduleData();
    void AddScheduleRecord(string, string, string, string, string, int, int, int, int, int, double);
    void TimeFormat();
    void ViewSchedule();
    void EditSchedule();
    void DeleteSchedule();
    void UpperString(string&);
};

Schedule::Schedule() {
    root = NULL;
}

int Schedule::ScheduleMenu() {
    int choice;

    do {
        cout << "-- Schedule Management --\n\n";
        cout << "[1] Add a Schedule\n";
        cout << "[2] View Schedules\n";
        cout << "[3] Edit a Schedule\n";
        cout << "[4] Delete a Schedule\n";
        cout << "[0] Return to Main Menu\n";
        cout << ":: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 4);
    return choice;
}

void Schedule::AddScheduleData() {
    int schedHour, schedMinute, schedSecond, amountMinute, numUnits, yearLevel;
    string courseTitle, courseCode, section, weekDay, roomNumber;

    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    cout << "Enter Course Name: ";
    getline(cin, courseTitle);
    cout << "Enter Section for the Course: ";
    getline(cin, section);
    cout << "Enter Day the Course to be scheduled for: ";
    getline(cin, weekDay);
    cout << "Enter Room Number: ";
    getline(cin, roomNumber);
    cout << "Enter Number of Units: ";
    cin >> numUnits;
    cin.ignore();
    cout << "Enter Year Level: ";
    cin >> yearLevel;
    cin.ignore();
    cout << "Enter Start Hour of the schedule: ";
    cin >> schedHour;
    cin.ignore();
    cout << "Enter Start Minute of the schedule: ";
    cin >> schedMinute;
    cin.ignore();
    cout << "Enter Start Second of the schedule: ";
    cin >> schedSecond;
    cin.ignore();
    cout << "Enter Amount of Minute for the Course: ";
    cin >> amountMinute;
    cin.ignore();

    UpperString(courseCode);
    UpperString(courseTitle);
    UpperString(section);
    UpperString(roomNumber);
    UpperString(weekDay);

    AddScheduleRecord(courseTitle, section, weekDay, courseCode, roomNumber, numUnits, yearLevel, schedHour, schedMinute, schedSecond, amountMinute);
}

void Schedule::AddScheduleRecord(string courseName, string block, string day, string courseId, string rNumber, int units, int yLevel, int sHour, int sMin, int sSec, double amountMinute) {
    string schedFile, time, sectionChecker; 
    SchedNode* parent = NULL;
    holder = new SchedNode;
    holder -> courseTitle = courseName;
    holder -> section = block;
    holder -> weekDay = day;
    holder -> courseCode = courseId;
    holder -> numUnits = units;
    holder -> yearLevel = yLevel;
    holder -> roomNumber = rNumber;
    holder -> schedHour = sHour;
    holder -> schedMinute = sMin;
    holder -> schedSecond = sSec;
    holder -> amountMinute = amountMinute;
    holder->left = NULL;
    holder->right = NULL;

    schedFile = "Schedules\\" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        cout << "Schedule Already Exists!\n";
        ifile.close();
        return;
    }
            
    if (root == NULL) {
        root = holder;
        cout << "Schedule successfully added!\n";
    }

    else {
        current = root;
        while (current != NULL) {
            parent = current;
            if (block < current->section || day < current->weekDay) {
                current = current->left;
            }
            else if (block > current->section || day > current -> weekDay) {
                current = current->right;
            }
            else {
                cout << "Schedule Already Exists!\n";
                return;
            }
        }
        if (block < parent->section) {
            parent->left = holder;
        }
        else {
            parent->right = holder;
        }
        cout << "Schedule successfully added!\n";
    }

    TimeFormat();
    ofstream ofile(schedFile);
    ofile << holder->courseCode << "\n";
    ofile << holder->courseTitle << "\n";
    ofile << holder->section << "\n";
    ofile << holder->numUnits << "\n";
    ofile << holder->weekDay << "\n";
    ofile << holder->startTime << " - " << holder->endTime << "\n";
    ofile << holder->roomNumber << "\n";
    ofile.close();
}

void Schedule::ViewSchedule() {
    string schedFile;
    ifstream ifile;
    current = root;
    string scheduleData[7];

    cout << "|" <<"-------------------------------------------------------------------------------------------------------------------------"<< "|\n";
    while (current != NULL) {
        schedFile = "Schedules\\" + current->section + "_" + current->courseCode + "_" + current->weekDay + ".txt";
        ifile.open(schedFile);
        if (ifile.is_open()) {
            for (int i = 0; i < 7; i++) {
                getline(ifile, scheduleData[i]);
            }
            ifile.close();

            cout << "| " << setw(11) << scheduleData[0] << " | " << setw(10) << scheduleData[1] << " | " << setw(5) << scheduleData[2] << " | " << setw(10) << scheduleData[3] << " | " << setw(10) << scheduleData[4] << " | " << setw(10) << scheduleData[5] << " | " << setw(10) << scheduleData[6] << " |\n";
            cout <<"|" <<"-------------------------------------------------------------------------------------------------------------------------"<< "|\n";
        }

        if (current->left != NULL && current->right != NULL) {
            if (current->left->section < current->right->section) {
                current = current->left;
            } else {
                current = current->right;
            }
        } else if (current->left != NULL) {
            current = current->left;
        } else if (current->right != NULL) {
            current = current->right;
        } else {
            break;
        }
    }
}

void Schedule::TimeFormat() {
    const int SIZE = 100;
    struct tm time;
    char schedTime[SIZE];
    string startTime, endTime;
    int totalMinutes, amountMinutes;

    time.tm_hour = holder->schedHour;
    time.tm_min = holder->schedMinute;
    time.tm_sec = holder->schedSecond;

    time.tm_isdst = 0;
    mktime(&time);

    strftime(schedTime, SIZE, "%H:%M:%S", &time);
    holder->startTime = string(schedTime);

    totalMinutes = holder->schedHour * 60 + holder->schedMinute;
    amountMinutes = holder->amountMinute;
    totalMinutes += amountMinutes;

    time.tm_hour = totalMinutes / 60;
    time.tm_min = totalMinutes % 60;
    mktime(&time);

    strftime(schedTime, SIZE, "%H:%M:%S", &time);
    holder->endTime = string(schedTime);
}

void Schedule::UpperString(string &str) {
     for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
}




