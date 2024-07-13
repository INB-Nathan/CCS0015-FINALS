#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <iomanip>
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
    void HeaderDesignCopy();

    void AddScheduleData();
    void AddScheduleRecord(string, string, string, string, int, int, int, int);
    void TimeFormat();
    void ViewSchedule();
    void EditSchedule();
    void DeleteSchedule();
    void UpperString(string&);
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
    HeaderDesignCopy();
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
    system("clear");
    return choice;
}

int Schedule::EditMenu() {
    int choice;
    HeaderDesignCopy();
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
    system("clear");
    return choice;
}

void Schedule::AddScheduleData() {
    int schedHour, schedMinute, schedSecond, amountMinute;
    string courseCode, section, weekDay, roomNumber;
    HeaderDesignCopy();

    while (true) { // loops until the course code is valid
        cout << "Enter Course Code: ";
        getline(cin, courseCode);
        UpperString(courseCode);
        if(IsValidCourseCode(courseCode)) { // uses the validation to check if the course code inputted is valid
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
        if(IsValidSection(section)){ // uses the validation to check if the section inputted is valid
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
        if(IsValidDay(weekDay)) { // uses the validation to check if the week day inputted is valid
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
        if(IsValidRoomNumber(roomNumber)) { // uses the validation to check if the room number inputted is valid
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
        if (IsValidHour(schedHour)) { // uses the validation to check if the hour inputted is valid
            break;
        } else {
            cout << "Invalid hour. Please enter a value between 1 and 24.\n";
        }
    }

    while (true) {
        cout << "Enter Start Minute of the schedule: ";
        cin >> schedMinute;
        cin.ignore();
        if (IsValidMinute(schedMinute)) { // uses the validation to check if the minute inputted is valid
            break;
        } else {
            cout << "Invalid minute. Please enter a value between 0 and 59.\n";
        }
    }

    while (true) {
        cout << "Enter Start Second of the schedule: ";
        cin >> schedSecond;
        cin.ignore();
        if (IsValidSecond(schedSecond)) { // uses the validation to check if the second inputted is valid
            break;
        } else {
            cout << "Invalid second. Please enter a value between 0 and 59.\n";
        }
    }

    while (true) {
        cout << "Enter Amount of Minute for the Course: ";
        cin >> amountMinute;
        cin.ignore();
        if (IsValidAmountMinute(amountMinute)) { // uses the validation to check if the amount of minutes inputted is valid
            break;
        } else {
            cout << "Invalid amount of minute. Please enter a positive value.\n";
        }
    }
    // calls for add schedule record function to add the record of the data in a file
    AddScheduleRecord(section, weekDay, courseCode, roomNumber, schedHour, schedMinute, schedSecond, amountMinute);
}
void Schedule::AddScheduleRecord(string block, string day, string courseId, string rNumber, int sHour, int sMin, int sSec, int amountMinute) {
    string schedFile, time, sectionChecker, fileName, line; 
    SchedNode* parent = NULL;
    fileName = "output/CourseRecords/" + courseId + ".txt"; // calls for the files from the course records
    ifstream courseFile(fileName);
    if (courseFile.is_open()) { // gets the details from the course file with the course id entered by the user
        holder = new SchedNode;
        getline(courseFile, holder->courseCode);
        getline(courseFile, holder->courseTitle);
        getline(courseFile, line);
        holder->numUnits = stoi(line);
        getline(courseFile, line);
        holder->yearLevel = stoi(line);
        courseFile.close();
    } else { // checks if there is no such file
        cout << "Course file not found.\n";
        return;
    }
    // puts details for the schedule from add schedule data to the file
    holder->section = block;
    holder->weekDay = day;
    holder->roomNumber = rNumber;
    holder->schedHour = sHour;
    holder->schedMinute = sMin;
    holder->schedSecond = sSec;
    holder->amountMinute = amountMinute;
    holder->left = NULL;
    holder->right = NULL;
    // creates a file name with the information some information for the file name of the file
    schedFile = "output/Schedules/" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
    ifstream ifile(schedFile); // checks if there is already an existing file name 
    if (ifile.is_open()) {
        cout << "Schedule Already Exists!\n"; // prints out an existing message if it does
        ifile.close();
        return; // returns to the menu if a file exists
    }

    // check if a schedule with the same room number and same file name already exists
    ifstream schedIfile("output/Schedules/SCHEDULES.txt");
    bool roomExists = false;
    while (getline(schedIfile, line)) {
        string schedRoomNumber;
        ifstream schedRoomFile("output/Schedules/" + line + ".txt");
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
        cout << "A schedule with the same room number already exists!\n"; // prints out a message if the same schedule
                                                                          // with same room number already exists
        return;
    }

    if (root == NULL) {
        root = holder;
        cout << "Schedule successfully added!\n"; // adds as the root if its the first addition of schedule
    }

    else {
        current = root;
        while (current != NULL) {
            parent = current;
            // checks the details to put into the tree whethere to put the new schedule to the left or right
            // allows the some details to be the same but still maintains to have just schedules not duplicate for a section or block
            if (holder->section < current->section || holder->weekDay < current->weekDay || holder->courseCode < current->courseCode || holder->roomNumber < current->roomNumber) {
                if (holder->schedHour < current->schedHour || holder->schedMinute < current->schedMinute || holder->schedSecond < current->schedSecond)
                current = current->left;
            }
            else if (holder->section > current->section || holder->weekDay > current->weekDay || holder->courseCode > current->courseCode || holder->roomNumber > current->roomNumber) {
                if (holder->schedHour > current->schedHour || holder->schedMinute > current->schedMinute || holder->schedSecond > current->schedSecond)
                current = current->right;
            }
            else {
                cout << "Schedule Already Exists!\n"; // prints a message when most of the details are the same
                return;
            }
        }
        // another layer of checking the section as the sections is included with the file name
        if (holder->section < parent->section) {
            parent->left = holder;
        }
        else {
            parent->right = holder;
        }
        cout << "Schedule successfully added!\n";
    }

    TimeFormat(); // formats the time to make the individual details of time is formatted for an actual time
                  // calculates the end time automatically as well based on the time details inputted
    // formats the details to be entered into the file
    ofstream ofile(schedFile);
    ofile << holder->courseCode << "\n";
    ofile << holder->courseTitle << "\n";
    ofile << holder->section << "\n";
    ofile << holder->numUnits << "\n";
    ofile << holder->weekDay << "\n";
    ofile << holder->startTime << " - " << holder->endTime << "\n";
    ofile << holder->roomNumber << "\n";
    ofile.close();
    // after adding the details to the file the file name is also added to a single file to record
    AddFileNameRecord();
    return;
}


void Schedule::ViewSchedule() {
    string schedFile;
    ifstream ifile;
    string scheduleData[7];
    HeaderDesignCopy();
    ifstream schedIfile("output/Schedules/SCHEDULES.txt"); // opens the schedules text file containing all the file names to traverse
    if (schedIfile.is_open()) {
        string line;
        while (getline(schedIfile, line)) {
            schedFile = "output/Schedules/" + line + ".txt"; // opens the files using the file name gathered from the master file
            ifile.open(schedFile);
            if (ifile.is_open()) {
                for (int i = 0; i < 7; i++) {
                    getline(ifile, scheduleData[i]); // iterates over all the lines of the specifically opened files
                }
                ifile.close();
                // displays the gathered lines of data in a formatted way
                cout <<"|" <<"----------------------------------------------------------------------------------------------------------------------"<< "|\n";
                cout << "|" << setw(11) << scheduleData[0] << " | " << setw(10) << scheduleData[1] << " | " << setw(5) << scheduleData[2] << " | " << setw(10) << scheduleData[3] << " | " << setw(10) << scheduleData[4] << " | " << setw(10) << scheduleData[5] << " | " << setw(10) << scheduleData[6] << " |\n";
                cout <<"|" <<"----------------------------------------------------------------------------------------------------------------------"<< "|\n";
            } else {
                cout << "Failed to open file: " << schedFile << endl; // displays an error message if the specfic schedule file had problems to open or does not exist
            }
        }
        schedIfile.close();
    } else {
        cout << "Failed to open SCHEDULES.txt file." << endl; // error message if the materlist file had issues opening
    }
    Pause(); // pause function to wait the user for a bit before clearing the screen display

}

void Schedule::EditSchedule() {
    string section, courseCode, weekDay, schedFile, newSchedFile, newDay, newSection, newRoom;
    int schedHour, schedMinute, schedSecond, amountMinute;
    HeaderDesignCopy();
    // asks the user with details of the schedule that is part of the file name
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
    // opens the file that the user wants to edit
    schedFile = "output/Schedules/" + section + "_" + courseCode + "_" + weekDay + ".txt";

    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        ifile.close();
        // looks for the schedule file in the folder
        SchedNode* temp = root;
        while (temp != NULL) {
            if (temp->section == section && temp->courseCode == courseCode && temp->weekDay == weekDay) {
                holder=temp;
                break;
            } else if (temp->section < section || temp->weekDay < weekDay || temp->courseCode < courseCode) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        // prints an error message if the file is not found
        if (holder == NULL) {
            cout << "Schedule not found!\n";
            return;
        }
        system("clear");
        // displays a menu of what operations the user can do in edit
        while (true) {        
            switch (EditMenu()) {
                case 1: {
                    while (true) {
                        HeaderDesignCopy();
                        cout << "Enter new Day: "; // asks for a new day from the user
                        getline(cin, newDay);
                        UpperString(newDay);
                        if (IsValidDay(newDay)) {
                            holder->weekDay = newDay; // sets the new day to the struct variable and edits the file name with the new day as well
                            newSchedFile = "output/Schedules/" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
                            rename(schedFile.c_str(), newSchedFile.c_str()); // renames to the new file name
                            schedFile = newSchedFile;
                            break;
                        } else {
                            cout << "Please enter a valid Week Day.\n"; // error message to display when the week day entered is invalid
                        }
                    }
                    break;
                }
                case 2: { // when the user want to edit the hour
                    while (true) {
                        // asks the user to input the new starting time separately from hour, minute and second and amount of time too
                        HeaderDesignCopy();
                        cout << "Enter new Start Hour: "; // asks for the new starting hour
                        cin >> schedHour; 
                        cin.ignore();
                        if (IsValidHour(schedHour)) {
                            break;
                        } else {
                            cout << "Invalid hour. Please enter a value between 1 and 24.\n";
                        }
                    }
                    while (true) {
                        cout << "Enter new Start Minute: "; // asks for the new starting minute
                        cin >> schedMinute;
                        cin.ignore();
                        if (IsValidMinute(schedMinute)) {
                            break;
                        } else {
                            cout << "Invalid minute. Please enter a value between 0 and 59.\n";
                        }
                    }
                    while (true) {
                        cout << "Enter new Start Second: "; // asks for the new starting second
                        cin >> schedSecond;
                        cin.ignore();
                        if (IsValidSecond(schedSecond)) {
                            break;
                        } else {
                            cout << "Invalid second. Please enter a value between 0 and 59.\n";
                        }
                    }
                    while (true) {
                        cout << "Enter Amount of Minute for the Course: "; // asks for the new amount of minutes
                        cin >> amountMinute;
                        cin.ignore();
                        if (IsValidAmountMinute(amountMinute)) {
                            break;
                        } else {
                            cout << "Invalid amount of minute. Please enter a positive value.\n";
                        }
                    }
                    // puts the new time date into the struct variables
                    holder->schedHour = schedHour;
                    holder->schedMinute = schedMinute;
                    holder->schedSecond = schedSecond;
                    holder->amountMinute = amountMinute;
                    // formats the new starting time and calculating for the new end time
                    TimeFormat();
                    break;
                }
                case 3: {
                    while (true) {
                        HeaderDesignCopy();
                        cout << "Enter new Section: "; // asks the user for the new section of the schedule
                        getline(cin, newSection);
                        UpperString(newSection);
                        if (IsValidSection(newSection)) {
                            holder->section = newSection; // puts into the struct the new section
                            // creates a file name with the new section
                            newSchedFile = "output/Schedules/" + holder->section + "_" + holder->courseCode + "_" + holder->weekDay + ".txt";
                            rename(schedFile.c_str(), newSchedFile.c_str()); // renames the file into the new file name
                            schedFile = newSchedFile;
                            break;
                        } else {
                            cout << "Please enter a valid Section (up to 5 alphanumeric characters).\n"; // error message for invalid section input
                        }
                    }
                    break;
                }
                case 4: {
                    while (true) {
                        HeaderDesignCopy();
                        cout << "Enter new Room: "; // asks the user for a new room for the schedule
                        getline(cin, newRoom);
                        UpperString(newRoom);
                        if (IsValidRoomNumber(newRoom)) {
                            holder->roomNumber = newRoom; // puts the new room data into the struct
                            break;
                        } else {
                            cout << "Please enter a valid Room Number (up to 5 alphanumeric characters or 'ONLINE').\n"; // error message if the new room is invalid
                        }
                    }
                    break;
                }
                case 0:
                    return; // returns to the menu 
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            system("clear");
            // edits the file with the current and new details for the course
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
        cout << "Schedule not found!\n"; // error message if schedule is not found or does not exist
    }
}

void Schedule::DeleteSchedule() {
    string section, courseCode, weekDay, schedFile;
    HeaderDesignCopy();
    // enters the details of the schedule relating to the file name to be deleted
    cout << "Enter Section: ";
    getline(cin, section);
    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    cout << "Enter Day: ";
    getline(cin, weekDay);

    UpperString(section);
    UpperString(courseCode);
    UpperString(weekDay);
    schedFile = "output/Schedules/" + section + "_" + courseCode + "_" + weekDay + ".txt"; // opens the file of the schedule

    ifstream ifile(schedFile);
    if (ifile.is_open()) {
        ifile.close();
        remove(schedFile.c_str()); // delete the file from the folder
        ifstream schedIfile("output/Schedules/SCHEDULES.txt"); // opens the master file of the schedule
        ofstream tempFile("output/Schedules/temp.txt"); // creates a temp file
        string line;
        while (getline(schedIfile, line)) {
            if (line != section + "_" + courseCode + "_" + weekDay) {
                tempFile << line << "\n"; // traverses the master file to find the file name
                                          // and if it's not the file name to be deleted, it copies the line into the temp file
            }
        }
        schedIfile.close();
        tempFile.close();
        remove("output/Schedules/SCHEDULES.txt");  // removes the master file after finding the correct file name
        rename("output/Schedules/temp.txt", "output/Schedules/SCHEDULES.txt"); // renames the temp file into the file name of the master file
        cout << "Schedule successfully deleted!\n";
    } else {
        cout << "Schedule not found!\n"; // error message if the schedule file is not found
    }
    system("clear");
}

void Schedule::TimeFormat() {
    const int SIZE = 100;
    struct tm time;
    char schedTime[SIZE];
    string startTime, endTime;
    int totalMinutes, amountMinutes;
    // sets the tm struct variables to the inputted datas from the user in the struct
    time.tm_hour = holder->schedHour;
    time.tm_min = holder->schedMinute;
    time.tm_sec = holder->schedSecond;

    time.tm_isdst = 0;
    mktime(&time); 
    // formats the collection of strings into a time formatted string
    // puts the given time formatted into starting time
    strftime(schedTime, SIZE, "%H:%M:%S", &time);
    holder->startTime = string(schedTime);
    // calculates the end time by adding the amount of minutes to the starting time
    totalMinutes = holder->schedHour * 60 + holder->schedMinute;
    amountMinutes = holder->amountMinute;
    totalMinutes += amountMinutes;
    // sets the hours and minutes based on the calculation made
    time.tm_hour = totalMinutes / 60;
    time.tm_min = totalMinutes % 60;
    mktime(&time);
    // formats the calculated time details into end time
    strftime(schedTime, SIZE, "%H:%M:%S", &time);
    holder->endTime = string(schedTime);
}

void Schedule::UpperString(string &str) {
    // coverts per character of the string into uppercases
     for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
}

void Schedule::AddFileNameRecord() {
    // adds the new file name record into the master file of the schedule
    ofstream ofile("output/Schedules/SCHEDULES.txt", ios::app);
    ofile << holder->section + "_" + holder->courseCode + "_" + holder->weekDay + "\n";
    ofile.close();
}

bool Schedule::IsValidHour(int hour) {
    // only allows the hour to be 1 - 24
    if (hour > 0 && hour <= 24) 
        return true;
    else 
        return false;
}
bool Schedule::IsValidMinute(int minute) {
    // lets the user enter 0 to 59 for minutes
    if (minute >= 0 && minute <= 59) 
        return true;
    else 
        return false;
}
bool Schedule::IsValidSecond(int second) {
    // lets the user enter 0 to 59 for seconds
    if (second >= 0 && second <= 59) 
        return true;
    else 
        return false;
}
bool Schedule::IsValidAmountMinute(int amountMinute) {
    // allows the user to enter 0 to 999 for the amount of minutes the schedule is alloted for
    if (amountMinute > 0 && amountMinute <= 999) 
        return true;
    else 
        return false;
}

bool Schedule::IsValidDay(string day) {
    // allows the user to enter one of the 7 days of the week for the schedule
    if (day == "MONDAY" || day == "TUESDAY" || day == "WEDNESDAY" || day == "THURSDAY" || day == "FRIDAY" || day == "SATURDAY" || day == "SUNDAY") {
        return true;
    }
    else
    return false;
}
bool Schedule::IsValidRoomNumber(string roomNumber) {
    // allows 5 alphanumeric string characters and online to be accepted as valid
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
    // allows 5 aplhanumeric string as valid for section
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
    // allows 7 alphanumeric string as valid for course code
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

void Schedule::Pause() {
    // own defined function of pause to make it easier for other devices
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    system("clear");
}

void Schedule::HeaderDesignCopy() {
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