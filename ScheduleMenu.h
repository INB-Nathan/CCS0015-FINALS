#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
#include "CourseCode.h"
using namespace std;

class Schedule {
    private:
    struct SchedNode {
        int numUnits, yearLevel;
        string courseTitle, courseCode, section, weekDay, startTime, endTime, roomNumber, time;
        int schedHour, schedMinute, schedSecond, amountMinute;

        SchedNode *left;
        SchedNode *right;
    } *holder, *current;

    public:
    SchedNode *root;
    Schedule();
    int ScheduleMenu();
    int EditMenu();
    void Pause();
    char EndTrail();
    int ScheduleFunctionalities();

    void AddScheduleData();
    void AddScheduleRecord(string, string, string, string, int, int, int, int);
    void TimeFormat();
    void ViewSchedule();
    void EditSchedule();
    void DeleteSchedule();
    void UpperString(string&);
    void LoadFiles();
    void AddFileNameRecord();
    bool IsValidHour(int);
    bool IsValidMinute(int);
    bool IsValidSecond(int);
    bool IsValidAmountMinute(int);
    bool IsValidDay(string);
    bool IsValidRoomNumber(string);
    bool IsValidSection(string);
    bool IsValidCourseCode(string);
};

Schedule::Schedule() {
    root = NULL;
    LoadFiles();
}

int Schedule::ScheduleFunctionalities() {
    while (true) {
        switch(ScheduleMenu()){
            case 1:
            AddScheduleData();
            break;
            case 2:
            ViewSchedule();
            break;
            case 3:
            EditSchedule();
            break;
            case 4:
            DeleteSchedule();
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

int Schedule::ScheduleMenu() {
    int choice;

    do {
        cout << "-- Schedule Management --\n\n";
        cout << "[1] Add a Schedule\n";
        cout << "[2] View Schedules\n";
        cout << "[3] Edit a Schedule\n";
        cout << "[4] Delete a Schedule\n";
        cout << "[0] Return to Main Menu\n\n";
        cout << ":: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 4);
    system("cls");
    return choice;
}

int Schedule::EditMenu() {
    int choice;
    do {
        cout << "\n\n-- Edit Schedule Menu --\n\n";
        cout << "[1] Edit Day\n";
        cout << "[2] Edit Time\n";
        cout << "[3] Edit Section\n";
        cout << "[4] Edit Room\n";
        cout << "[0] Return to Schedule Menu\n\n";
        cout << ":: ";
        cin >> choice;
        cin.ignore();
    } while (choice < 0 || choice > 4);
    system("cls");
    return choice;
}

void Schedule::AddScheduleData() {
    int schedHour, schedMinute, schedSecond, amountMinute;
    string courseCode, section, weekDay, roomNumber;

    while (true) {
        cout << "Enter Course Code: ";
        getline(cin, courseCode);
        UpperString(courseCode);
        if(IsValidCourseCode(courseCode)) {
            break;
        }
        else {
            cout << "Please Enter a Valid Course Code.\n";
        }
    }
    

    while(true){
        cout << "Enter Section: ";
        getline(cin, section);
        UpperString(section);
        if(IsValidSection(section)){
            break;
        }
        else {
            cout << "Please Enter a Valid Section.\n";
        }
    }

    while (true) {
        cout << "Enter Day the Course to be scheduled for: ";
        getline(cin, weekDay);
        UpperString(weekDay);
        if(IsValidDay(weekDay)) {
            break;
        }
        else {
            cout << "Please enter a valid Week Day.\n";
        }
    }

    while (true) {
        cout << "Enter Room Number: ";
        getline(cin, roomNumber);
        UpperString(roomNumber);
        if(IsValidRoomNumber(roomNumber)) {
            break;
        }
        else {
            cout << "Please enter a valid Room Number (up to 5 alphanumeric characters or 'ONLINE').\n";
        }
    }

    while (true) {
        cout << "Enter Start Hour of the schedule: ";
        cin >> schedHour;
        cin.ignore();
        if (IsValidHour(schedHour)) {
            break;
        } else {
            cout << "Invalid hour. Please enter a value between 1 and 24.\n";
        }
    }

    while (true) {
        cout << "Enter Start Minute of the schedule: ";
        cin >> schedMinute;
        cin.ignore();
        if (IsValidMinute(schedMinute)) {
            break;
        } else {
            cout << "Invalid minute. Please enter a value between 0 and 59.\n";
        }
    }

    while (true) {
        cout << "Enter Start Second of the schedule: ";
        cin >> schedSecond;
        cin.ignore();
        if (IsValidSecond(schedSecond)) {
            break;
        } else {
            cout << "Invalid second. Please enter a value between 0 and 59.\n";
        }
    }

    while (true) {
        cout << "Enter Amount of Minute for the Course: ";
        cin >> amountMinute;
        cin.ignore();
        if (IsValidAmountMinute(amountMinute)) {
            break;
        } else {
            cout << "Invalid amount of minute. Please enter a positive value.\n";
        }
    }

    AddScheduleRecord(section, weekDay, courseCode, roomNumber, schedHour, schedMinute, schedSecond, amountMinute);
}
void Schedule::AddScheduleRecord(string block, string day, string courseId, string rNumber, int sHour, int sMin, int sSec, int amountMinute) {
    string schedFile, time, sectionChecker, fileName, line; 
    SchedNode* parent = NULL;
    fileName = "CourseRecords\\" + courseId + ".txt";
    ifstream courseFile(fileName);
    if (courseFile.is_open()) {
        holder = new SchedNode;
        getline(courseFile, holder->courseCode);
        getline(courseFile, holder->courseTitle);
        getline(courseFile, line);
        holder->numUnits = stoi(line);
        getline(courseFile, line);
        holder->yearLevel = stoi(line);
        courseFile.close();
    } else {
        cout << "Course file not found.\n";
        return;
    }
    
    holder->section = block;
    holder->weekDay = day;
    holder->roomNumber = rNumber;
    holder->schedHour = sHour;
    holder->schedMinute = sMin;
    holder->schedSecond = sSec;
    holder->amountMinute = amountMinute;
    holder->left = NULL;
    holder->right = NULL;

    schedFile = "Schedules\\" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        cout << "Schedule Already Exists!\n";
        ifile.close();
        return;
    }

    // Check if a schedule with the same room number already exists
    ifstream schedIfile("Schedules\\SCHEDULES.txt");
    bool roomExists = false;
    while (getline(schedIfile, line)) {
        string schedRoomNumber;
        ifstream schedRoomFile("Schedules\\" + line + ".txt");
        getline(schedRoomFile, line);
        getline(schedRoomFile, line);
        getline(schedRoomFile, line);
        getline(schedRoomFile, line);
        getline(schedRoomFile, line);
        getline(schedRoomFile, schedRoomNumber);
        schedRoomFile.close();
        if (schedRoomNumber == holder->roomNumber) {
            roomExists = true;
            break;
        }
    }
    schedIfile.close();
    if (roomExists) {
        cout << "A schedule with the same room number already exists!\n";
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
            if (holder->section < current->section || holder->weekDay < current->weekDay || holder->courseCode < current->courseCode || holder->roomNumber < current->roomNumber) {
                if (holder->schedHour < current->schedHour || holder->schedMinute < current->schedMinute || holder->schedSecond < current->schedSecond)
                current = current->left;
            }
            else if (holder->section > current->section || holder->weekDay > current->weekDay || holder->courseCode > current->courseCode || holder->roomNumber > current->roomNumber) {
                if (holder->schedHour > current->schedHour || holder->schedMinute > current->schedMinute || holder->schedSecond > current->schedSecond)
                current = current->right;
            }
            else {
                cout << "Schedule Already Exists!\n";
                return;
            }
        }
        if (holder->section < parent->section) {
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
    AddFileNameRecord();
}


void Schedule::ViewSchedule() {
    string schedFile;
    ifstream ifile;
    string scheduleData[7];

    ifstream schedIfile("Schedules\\SCHEDULES.txt");
    if (schedIfile.is_open()) {
        string line;
        while (getline(schedIfile, line)) {
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
        schedIfile.close();
    } else {
        cout << "Failed to open SCHEDULES.txt file." << endl;
    }
    Pause();

}

void Schedule::EditSchedule() {
    string section, courseCode, weekDay, schedFile, newSchedFile, newDay, newSection, newRoom;
    int schedHour, schedMinute, schedSecond, amountMinute;

    while (true) {
        cout << "Enter Section: ";
        getline(cin, section);
        UpperString(section);
        if (IsValidSection(section)) {
            break;
        } else {
            cout << "Please enter a valid Section (up to 5 alphanumeric characters).\n";
        }
    }

    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    UpperString(courseCode);
    
    while (true) {
        cout << "Enter Day: ";
        getline(cin, weekDay);
        UpperString(weekDay);
        if (IsValidDay(weekDay)) {
            break;
        } else {
            cout << "Please enter a valid Week Day.\n";
        }
    }

    schedFile = "Schedules\\" + section + "_" + courseCode + "_" + weekDay + ".txt";

    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        ifile.close();

        SchedNode* temp = root;
        while (temp != NULL) {
            if (temp->section == section && temp->courseCode == courseCode && temp->weekDay == weekDay) {
                break;
            } else if (temp->section < section || temp->weekDay < weekDay || temp->courseCode < courseCode) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }

        if (temp == NULL) {
            cout << "Schedule not found!\n";
            return;
        }

        while (true) {        
            switch (EditMenu()) {
                case 1: {
                    while (true) {
                        cout << "Enter new Day: ";
                        getline(cin, newDay);
                        UpperString(newDay);
                        if (IsValidDay(newDay)) {
                            holder->weekDay = newDay;
                            newSchedFile = "Schedules\\" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
                            rename(schedFile.c_str(), newSchedFile.c_str());
                            schedFile = newSchedFile;
                            break;
                        } else {
                            cout << "Please enter a valid Week Day.\n";
                        }
                    }
                    break;
                }
                case 2: {
                    while (true) {
                        cout << "Enter new Start Hour: ";
                        cin >> schedHour;
                        cin.ignore();
                        if (IsValidHour(schedHour)) {
                            break;
                        } else {
                            cout << "Invalid hour. Please enter a value between 1 and 24.\n";
                        }
                    }
                    while (true) {
                        cout << "Enter new Start Minute: ";
                        cin >> schedMinute;
                        cin.ignore();
                        if (IsValidMinute(schedMinute)) {
                            break;
                        } else {
                            cout << "Invalid minute. Please enter a value between 0 and 59.\n";
                        }
                    }
                    while (true) {
                        cout << "Enter new Start Second: ";
                        cin >> schedSecond;
                        cin.ignore();
                        if (IsValidSecond(schedSecond)) {
                            break;
                        } else {
                            cout << "Invalid second. Please enter a value between 0 and 59.\n";
                        }
                    }
                    while (true) {
                        cout << "Enter Amount of Minute for the Course: ";
                        cin >> amountMinute;
                        cin.ignore();
                        if (IsValidAmountMinute(amountMinute)) {
                            break;
                        } else {
                            cout << "Invalid amount of minute. Please enter a positive value.\n";
                        }
                    }

                    holder->schedHour = schedHour;
                    holder->schedMinute = schedMinute;
                    holder->schedSecond = schedSecond;
                    holder->amountMinute = amountMinute;
                    TimeFormat();
                    break;
                }
                case 3: {
                    while (true) {
                        cout << "Enter new Section: ";
                        getline(cin, newSection);
                        UpperString(newSection);
                        if (IsValidSection(newSection)) {
                            holder->section = newSection;

                            newSchedFile = "Schedules\\" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
                            rename(schedFile.c_str(), newSchedFile.c_str());
                            schedFile = newSchedFile;
                            break;
                        } else {
                            cout << "Please enter a valid Section (up to 5 alphanumeric characters).\n";
                        }
                    }
                    break;
                }
                case 4: {
                    while (true) {
                        cout << "Enter new Room: ";
                        getline(cin, newRoom);
                        UpperString(newRoom);
                        if (IsValidRoomNumber(newRoom)) {
                            holder->roomNumber = newRoom;
                            break;
                        } else {
                            cout << "Please enter a valid Room Number (up to 5 alphanumeric characters or 'ONLINE').\n";
                        }
                    }
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }

           ofstream ofile(schedFile);
            ofile << holder->courseCode << "\n";
            ofile << holder->courseTitle << "\n";
            ofile << holder->section << "\n";
            ofile << holder->numUnits << "\n";
            ofile << holder->weekDay << "\n";
            ofile << holder->startTime << " - " << holder->endTime << "\n";
            ofile << holder->roomNumber << "\n";
            ofile.close();
            cout << "Schedule successfully edited!\n";
            return;
        }
    } else {
        cout << "Schedule not found!\n";
    }
}

void Schedule::DeleteSchedule() {
    string section, courseCode, weekDay, schedFile;

    cout << "Enter Section: ";
    getline(cin, section);
    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    cout << "Enter Day: ";
    getline(cin, weekDay);

    UpperString(section);
    UpperString(courseCode);
    UpperString(weekDay);
    schedFile = "Schedules\\" + section + "_" + courseCode + "_" + weekDay + ".txt";

    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        ifile.close();
        remove(schedFile.c_str());
        ifstream schedIfile("Schedules\\SCHEDULES.txt");
        ofstream tempFile("Schedules\\temp.txt");
        string line;
        while (getline(schedIfile, line)) {
            if (line != section + "_" + courseCode + "_" + weekDay) {
                tempFile << line << "\n";
            }
        }
        schedIfile.close();
        tempFile.close();
        remove("Schedules\\SCHEDULES.txt"); 
        rename("Schedules\\temp.txt", "Schedules\\SCHEDULES.txt");
        cout << "Schedule successfully deleted!\n";
    } else {
        cout << "Schedule not found!\n";
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

void Schedule::LoadFiles() {
    ifstream ifile("Schedules\\SCHEDULES.txt"); // Opens the txt file where all file names existing gets stored
    string schedFile, startTime, endTime;

    if (ifile.is_open()) {
        while (getline(ifile, schedFile)) { // Iterates over file names inside the text file // Iterates over file names inside the text file 
            ifstream schedIfile("Schedules\\" + schedFile + ".txt");
            if (schedIfile.is_open()) {
                string scheduleData[7];
                for (int i = 0; i < 7; i++) {
                    getline(schedIfile, scheduleData[i]); // Iterates over the data of the open schedule file
                }
                schedIfile.close();

                holder = new SchedNode;
                holder->courseCode = scheduleData[0];
                holder->courseTitle = scheduleData[1];
                holder->section = scheduleData[2];
                holder->numUnits = stoi(scheduleData[3]);
                holder->weekDay = scheduleData[4];
                startTime = scheduleData[5].substr(0, 5);
                endTime = scheduleData[5].substr(7);
                holder->startTime = startTime;
                holder->endTime = endTime;
                holder->roomNumber = scheduleData[6];

                holder->schedHour = stoi(startTime.substr(0, 2));
                holder->schedMinute = stoi(startTime.substr(3, 2));
                holder->schedHour = stoi(endTime.substr(0, 2));
                holder->schedMinute = stoi(endTime.substr(3, 2));

                // Reset left and right pointers to NULL
                holder->left = NULL;
                holder->right = NULL;

                // Puts all the data from the found files to the record again
                if (root == NULL) {
                    root = holder; 
                } else {
                    current = root;
                    while (true) {
                        if (holder->section < current->section) {
                            if (current->left == NULL) {
                                current->left = holder;
                                break;
                            }
                            current = current->left;
                        } else {
                            if (current->right == NULL) {
                                current->right = holder;
                                break;
                            }
                            current = current->right;
                        }
                    }
                }
            } else {
                cout << "Failed to open file: " << schedFile << ".txt" << endl;
            }
        }
        ifile.close(); // Closes the schedules txt file either from the error catcher or the function has completely loaded all
                       // schedule files
    } else {
        cout << "Failed to open SCHEDULES.txt file." << endl;
    }

}
void Schedule::AddFileNameRecord() {
    ofstream ofile("Schedules\\SCHEDULES.txt", ios::app);
    ofile << holder->section + "_" + holder->courseCode + "_" + holder->weekDay + "\n";
    ofile.close();
}

bool Schedule::IsValidHour(int hour) {
    if (hour > 0 && hour <= 24) 
        return true;
    else 
        return false;
}
bool Schedule::IsValidMinute(int minute) {
    if (minute >= 0 && minute <= 59) 
        return true;
    else 
        return false;
}
bool Schedule::IsValidSecond(int second) {
    if (second >= 0 && second <= 59) 
        return true;
    else 
        return false;
}
bool Schedule::IsValidAmountMinute(int amountMinute) {
    if (amountMinute > 0 && amountMinute <= 999) 
        return true;
    else 
        return false;
}

bool Schedule::IsValidDay(string day) {
    if (day == "MONDAY" || day == "TUESDAY" || day == "WEDNESDAY" || day == "THURSDAY" || day == "FRIDAY" || day == "SATURDAY" || day == "SUNDAY") {
        return true;
    }
    else
    return false;
}
bool Schedule::IsValidRoomNumber(string roomNumber) {
    if (roomNumber == "ONLINE") {
        return true;
    } else if (roomNumber.length() <= 5) {
        for (int i = 0; i < roomNumber.length(); i++) {
            if (!isalnum(roomNumber[i])) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool Schedule::IsValidSection(string section) {
    if (section.length() <= 5) {
        for (int i = 0; i < section.length(); i++) {
            if (!isalnum(section[i])) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
bool Schedule::IsValidCourseCode(string courseCode) {
    if (courseCode.length() == 7) {
        for (int i = 0; i < courseCode.length(); i++) {
            if (!isalnum(courseCode[i])) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

char Schedule::EndTrail() {
    char continueChoice ='Y';

    cout << "Do you want to Continue [Y/N]: ";
    cin >> continueChoice;
    continueChoice = toupper(continueChoice);
    system("cls");

    return continueChoice;
}

void Schedule::Pause() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    system("cls");
}



