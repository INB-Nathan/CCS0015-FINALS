#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include "Design.h"

using namespace std;
class StudentDetails
{
private:
    // Declare Student Information variables.
    struct StudentNode
    {
        string firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, birthday;
        int idNumber, yearLevel;
        StudentNode *left;
        StudentNode *right;
    } *node, *current;

    struct ListNode
    {
        StudentNode *student;
        ListNode *next;
    } *head;

public:
    StudentNode *root;
    int StudMenu();
    void Pause();
    int StudentFunctionalities();
    // Add input validation functions.
    bool ConfirmScreen(char);
    bool IsValidStudentNum(int);
    bool IsValidName(string);
    bool IsValidGender(string);
    int MonthNameToNumber(string &);
    bool IsValidBirthMonth(string &);
    bool IsValidBirthDate(int, string &, int);
    bool IsValidDegreeProgram(string);
    bool HasStudentsWithYear(StudentNode *, int);
    bool HasStudentsWithLastNameInitial(StudentNode *, char);
    // Constructor
    StudentDetails();
    // Add main functions
    void AddStudentInput();
    void AddStudent(string, string, string, string, string, string, string, int, int);
    void SaveIDToList();
    void ViewDetailsInput();
    void ViewDetails(string);
    void EditStudentInput();
    void EditStudent(string);
    void DeleteStudentInput();
    void DeleteStudent(string);
    void RestoreStudentInfo(int, string, string, string, string, string, string, string, int);
    void FetchEachStudentFile(string);
    void RemoveAll(StudentNode *&);
    void FetchStudentInfo();
    void ViewStudentsSortedByIDNumber(StudentNode *);
    void ViewStudentsSortedByLastName();
    void InOrderTraversal(StudentNode *);
    void InsertSorted(StudentNode *);
    void ViewStudents();
    void ViewStudentsForInputFunctions();
    void FilterByYear(StudentNode *, int);
    void FilterByLastNameInitial(StudentNode *, char);
};

int StudentDetails::StudMenu()
{
    int choice;
    
    HeaderDesign();
    do {
    cout << endl;
    cout << "1. Add Student" << endl;
    cout << "2. View Student List" << endl;
    cout << "3. View Student's Record" << endl;
    cout << "4. Edit Student Info" << endl;
    cout << "5. Delete Student" << endl
         << endl;
    cout << "0. Return to Main Menu" << endl << endl;
    cout << ":: ";
    cin >> choice;
    cin.ignore();
    } while (choice < 0 || choice > 5);
    system("clear");
    return choice;
}

int StudentDetails::StudentFunctionalities() {
    while (true) {
        switch (StudMenu()) {
            case 1:
            AddStudentInput();
            break;
            case 2:
            ViewStudents();
            break;
            case 3:
            ViewStudentsForInputFunctions();
            cout << "\n";
            ViewDetailsInput();
            break;
            case 4:
            ViewStudentsForInputFunctions();
            cout << "\n";
            EditStudentInput();
            break;
            case 5:
            ViewStudentsForInputFunctions();
            cout << "\n";
            DeleteStudentInput();
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

void StudentDetails::Pause() // Function to replace "system("pause")"
{
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get(); // Wait for the user to press Enter
    system("clear");
}

bool StudentDetails::ConfirmScreen(char choice) // Function for confirmation screen
{
    if (toupper(choice) == 'Y') // Returns true, proceeds to do the func to perform
        return true;
    else if (toupper(choice) == 'N') // Returns false, proceeds to do the func to perform
        return false;
    else
        return false; // Handle invalid inputs as false
}

bool StudentDetails::IsValidStudentNum(int idNumber) // Function to check if the id number input is valid
{
    if (idNumber >= 201500000 && idNumber < 202500000) // Only accepts student numbers from 2015 to 2024, returns true if valid, false if not
    {
        return true;
    }
    else
    {
        cout << "Enter a Valid Student Number." << endl;
        return false;
    }
}

bool StudentDetails::IsValidName(string str) // Function for checking if the input is Alpha or a Space mostly used for names and such
{
    // Convert the string to lowercase manually
    int i;
    for (i = 0; i < str.length(); i++)
    {
        if (!isalpha(str[i]) && !isspace(str[i])) // Check if alpha or a space
        {
            cout << "Please Enter a Valid Name (a-z)" << endl;
            return false;
        }
    }

    return true;
}

bool StudentDetails::IsValidGender(string str) // Function to check if the input is either male or female regardless of the case
{
    // Convert the string to lowercase manually
    int i;
    for (i = 0; i < str.length(); ++i)
    {
        str[i] = tolower(str[i]);
    }

    // Check if the string is male or female
    if (str == "male" || str == "female")
    {
        return true;
    }
    else
    {
        cout << "Please Enter a Valid Gender." << endl;
        return false;
    }
}

int StudentDetails::MonthNameToNumber(string &monthName) // Converts the month name input into its corresponding number
{
    if (monthName == "January")
    {
        return 1;
    }
    if (monthName == "February")
    {
        return 2;
    }
    if (monthName == "March")
    {
        return 3;
    }
    if (monthName == "April")
    {
        return 4;
    }
    if (monthName == "May")
    {
        return 5;
    }
    if (monthName == "June")
    {
        return 6;
    }
    if (monthName == "July")
    {
        return 7;
    }
    if (monthName == "August")
    {
        return 8;
    }
    if (monthName == "September")
    {
        return 9;
    }
    if (monthName == "October")
    {
        return 10;
    }
    if (monthName == "November")
    {
        return 11;
    }
    if (monthName == "December")
    {
        return 12;
    }
    return -1;
}

bool StudentDetails::IsValidBirthMonth(string &month) // Function to check if the input is a valid month
{
    string validMonths[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (string &validMonth : validMonths)
    {
        if (month == validMonth)
        {
            return true;
        }
    }
    return false;
}

bool StudentDetails::IsValidBirthDate(int birthday, string &month, int year) // Function to check if the date of birth is valid, checks leap years and such
{
    int monthNumber = MonthNameToNumber(month);

    if (monthNumber == -1)
    {
        return false; // Invalid month
    }

    if (birthday < 1 || birthday > 31)
    {
        return false; // Invalid day
    }

    if (monthNumber == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            return birthday <= 29; // Leap year
        }
        else
        {
            return birthday <= 28; // Non-leap year
        }
    }
    else if (monthNumber == 4 || monthNumber == 6 || monthNumber == 9 || monthNumber == 11)
    {
        return birthday <= 30; // April, June, September, November have 30 days
    }
    else
    {
        return true; // All other months have 31 days
    }
}

bool StudentDetails::IsValidDegreeProgram(string degreeProg)
{
    for (int i = 0; i < degreeProg.length(); ++i)
    {
        degreeProg[i] = toupper(degreeProg[i]);
    }

    if (degreeProg == "BSITCST" || degreeProg == "BSITWMA" || degreeProg == "BSITBA" || degreeProg == "BSITAGD")
    {
        return true;
    }
    else
    {
        cout << "Please Enter a Valid Degree Program. (BSITCST, BSITWMA, BSITBA, BSITAGD)" << endl;
        return false;
    }
}

bool StudentDetails::HasStudentsWithYear(StudentNode *node, int year)
{
    if (node == NULL)
    {
        return false;
    }
    int studentYear = node->idNumber / 100000;
    if (studentYear == year)
    {
        return true;
    }
    return HasStudentsWithYear(node->left, year) || HasStudentsWithYear(node->right, year);
}

bool StudentDetails::HasStudentsWithLastNameInitial(StudentNode *node, char initial)
{
    if (node == NULL)
    {
        return false;
    }
    if (toupper(node->lastName[0]) == toupper(initial))
    {
        return true;
    }
    return HasStudentsWithLastNameInitial(node->left, initial) || HasStudentsWithLastNameInitial(node->right, initial);
}

StudentDetails::StudentDetails() // Constructor
{
    root = NULL;
}

void StudentDetails::AddStudentInput() // Function to take inputs for AddStudent Function
{
    string firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, birthMonthName, fullBirthday;
    int idNumber, yearLevel, birthDay, birthYear, birthMonthNum;
    char conChoice = ' ';

    system("clear");

    HeaderDesign();
    cout << endl;
    while (true)
    {
        cout << "Enter First Name: ";
        getline(cin, firstName);

        if (IsValidName(firstName))
            break;
    }

    while (true)
    {
        cout << "Enter Middle Name: ";
        getline(cin, middleName);

        if (IsValidName(middleName))
            break;
    }

    while (true)
    {
        cout << "Enter Last Name: ";
        getline(cin, lastName);

        if (IsValidName(lastName))
            break;
    }

    cout << "Enter Birth Month: ";
    cin >> birthMonthName;
    while (!IsValidBirthMonth(birthMonthName))
    {
        cout << "Invalid Month! Please enter a valid birth month." << endl;
        cout << "Enter Birth Month: ";
        cin >> birthMonthName;
    }

    cout << "Enter Birth Day: ";
    cin >> birthDay;

    cout << "Enter Birth Year: ";
    cin >> birthYear;
    while (!IsValidBirthDate(birthDay, birthMonthName, birthYear))
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

        if (IsValidGender(studentGender))
            break;
    }

    while (true)
    {
        cout << "Enter City Address (ex. Manila City): ";
        getline(cin, studentAddress);

        if (IsValidName(studentAddress))
            break;
    }

    while (true)
    {
        cout << "Enter ID Number (9-digit ID Number): ";
        cin >> idNumber;

        if (IsValidStudentNum(idNumber))
            break;
    }

    while (true)
    {
        cout << "Enter Degree Program (BSITCST, BSITWMA, BSITBA, BSITAGD): ";
        cin >> degreeProgram;

        if (IsValidDegreeProgram(degreeProgram))
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

    birthMonthNum = MonthNameToNumber(birthMonthName);                                                // Convert month name to number(int)
    fullBirthday = to_string(birthMonthNum) + "/" + to_string(birthDay) + "/" + to_string(birthYear); // Convert into the full birthday format (string)

    while (true)
    {
        cout << "Confirm Add Student? [Y/N]" << endl;
        cin >> conChoice;

        if (toupper(conChoice) == 'Y')
        {
            AddStudent(firstName, lastName, middleName, degreeProgram, studentGender, studentAddress, fullBirthday, idNumber, yearLevel);
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
    Pause();
}

void StudentDetails::AddStudent(string fName, string lName, string mName, string dProgram, string sGender, string sAddress, string bDay, int idNum, int yrLvl) // Function to add student into the tree and creates a file to store their data
{
    string filename;
    // Create and instantiate the node
    node = new StudentNode;
    node->firstName = fName;
    node->lastName = lName;
    node->middleName = mName;
    node->degreeProgram = dProgram;
    node->studentGender = sGender;
    node->studentAddress = sAddress;
    node->birthday = bDay;
    node->idNumber = idNum;
    node->yearLevel = yrLvl;
    node->left = NULL;
    node->right = NULL;

    // Check if the tree is empty
    if (root == NULL)
    {
        // Set the new node as the root
        root = node;
        cout << "New Student is Successfully Added\n";
    }
    else
    {                   // If the tree has nodes already
        current = root; // Get the root node
        while (current != NULL)
        {
            // If the value of the new node is lesser than the current, go left
            if (idNum < current->idNumber)
            {
                if (current->left == NULL)
                {
                    // If the left pointer of the currrent node is empty
                    //   insert the new node to the left of the current node
                    current->left = node;
                    cout << "New Student is Successfully Added\n";
                    break;
                }
                else
                {
                    // Go to the next node if the left pointer has a child already
                    current = current->left;
                }
                // If the value of the new node is greater than the current, go right
            }
            else if (idNum > current->idNumber)
            {
                if (current->right == NULL)
                {
                    // If the right pointer of the currrent node is empty
                    //   insert the new node to the right of the current node
                    current->right = node;
                    cout << "New Student is Successfully Added\n";
                    break;
                }
                else
                {
                    // Go to the next node if the right pointer has a child already
                    current = current->right;
                }
            }
            else
            {
                cout << "Duplicate students are not allowed.\n";
                return;
            }
        }
    }

    // Generate a filename from the input id, use to_string function to convert int to string
    filename = "output/Students/" + to_string(idNum) + ".txt";
    // Create the file object and open the file
    ofstream ofile(filename);
    if (!ofile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    // Store data to file
    ofile << node->idNumber << endl;
    ofile << node->firstName << endl;
    ofile << node->middleName << endl;
    ofile << node->lastName << endl;
    ofile << node->birthday << endl;
    ofile << node->studentGender << endl;
    ofile << node->studentAddress << endl;
    ofile << node->degreeProgram << endl;
    ofile << node->yearLevel << endl;
    // Close the ofstream object, always close the object after using it to avoid problems
    ofile.close();

    SaveIDToList(); // Save the student id to the idlist file
}

void StudentDetails::SaveIDToList() // Saves the Stud num to a list for reading purposes
{
    // Create another file to store all of the student numbers
    ofstream ofile("output/Students/idlist.txt", ios::app);
    if (!ofile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    // Store the idNumber
    ofile << node->idNumber << endl;

    // Close the file
    ofile.close();
}

void StudentDetails::ViewStudentsSortedByIDNumber(StudentNode *tempNode) // This shows ID Number and full names of all students in the program. The list is sorted by id number
{
    if (tempNode == NULL)
    { // Base case of the recursion
        return;
    }
    // Left -> Root -> Right
    ViewStudentsSortedByIDNumber(tempNode->left);
    cout << tempNode->idNumber << "\t\t" << tempNode->firstName << " " << tempNode->middleName << " " << tempNode->lastName << endl;
    ViewStudentsSortedByIDNumber(tempNode->right);
}

void StudentDetails::RemoveAll(StudentNode *&node)
{
    if (!node) return;
                     
    RemoveAll(node->left);
    RemoveAll(node->right);
    
    delete node;
    node = NULL;
}

void StudentDetails::FetchStudentInfo() // Reads the idlist file to traverse through the student files
{
    string filename;
    RemoveAll(root);
    // Open a ifstream object and open the idlist file
    ifstream ifile("output/Students/idlist.txt");
    if (!ifile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    while (getline(ifile, filename))
    { // Fetch data stored in the file one line at a time
        FetchEachStudentFile(filename);
    }

    ifile.close();
}

void StudentDetails::FetchEachStudentFile(string idOfFile) // Reads each student file to restore it to the tree upon start of program
{
    int idNum, yrLvl, i = 0;
    string fName, mName, lName, bDay, sGender, sAddress, dProgram;
    string *s = new string[9];

    ifstream ifile("output/Students/" + idOfFile + ".txt"); // Opens the student file given by the FetchStudentInfo func
    if (!ifile)                                             // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    while (getline(ifile, s[i]))
    { // Fetch data stored in the file one line at a time
        i++;
    }

    idNum = stoi(s[0]);
    fName = s[1];
    mName = s[2];
    lName = s[3];
    bDay = s[4];
    sGender = s[5];
    sAddress = s[6];
    dProgram = s[7];
    yrLvl = stoi(s[8]);

    ifile.close();

    RestoreStudentInfo(idNum, fName, mName, lName, bDay, sGender, sAddress, dProgram, yrLvl); // Passes the information to the RestoreStudentInfo function to insert the info into the tree again
}

void StudentDetails::RestoreStudentInfo(int idNum, string fName, string mName, string lName, string bDay, string sGender, string sAddress, string dProgram, int yrLvl) // Restores the data into the tree
{
    // Create and instantiate the node
    node = new StudentNode;
    node->firstName = fName;
    node->lastName = lName;
    node->middleName = mName;
    node->degreeProgram = dProgram;
    node->studentGender = sGender;
    node->studentAddress = sAddress;
    node->birthday = bDay;
    node->idNumber = idNum;
    node->yearLevel = yrLvl;
    node->left = NULL;
    node->right = NULL;

    // Check if the tree is empty
    if (root == NULL)
    {
        // Set the new node as the root
        root = node;
    }
    else
    {                   // If the tree has nodes already
        current = root; // Get the root node
        while (current != NULL)
        {
            // If the value of the new node is lesser than the current, go left
            if (idNum < current->idNumber)
            {
                if (current->left == NULL)
                {
                    // If the left pointer of the currrent node is empty
                    //   insert the new node to the left of the current node
                    current->left = node;
                    break;
                }
                else
                {
                    // Go to the next node if the left pointer has a child already
                    current = current->left;
                }
                // If the value of the new node is greater than the current, go right
            }
            else if (idNum > current->idNumber)
            {
                if (current->right == NULL)
                {
                    // If the right pointer of the currrent node is empty
                    //   insert the new node to the right of the current node
                    current->right = node;
                    break;
                }
                else
                {
                    // Go to the next node if the right pointer has a child already
                    current = current->right;
                }
            }
            else
            {
                cout << "Duplicate values are not allowed in trees.";
                return;
            }
        }
    }
}

void StudentDetails::ViewDetailsInput() // Function to take inputs for ViewDetails Function
{
    int idToView;
    while (true) // to edit
    {
        cout << "Enter Student Number to View: ";
        cin >> idToView;

        if (IsValidStudentNum(idToView))
            break;
    }
    system("clear");
    HeaderDesign();
    cout << endl;
    ViewDetails(to_string(idToView));
    Pause();
}

void StudentDetails::ViewDetails(string idNum) // Preview details inside the student's record
{
    int i = 0;
    string *s = new string[9];
    ifstream ifile("output/Students/" + idNum + ".txt");
    if (!ifile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    while (getline(ifile, s[i]))
    { // Fetch data stored in the file one line at a time and saves it in the string array
        i++;
    }
    // Prints the details stored in the string array
    cout << "Student Number: " << s[0] << endl;
    cout << "First Name: " << s[1] << endl;
    cout << "Middle Name: " << s[2] << endl;
    cout << "Last Name: " << s[3] << endl;
    cout << "Birthday: " << s[4] << endl;
    cout << "Gender: " << s[5] << endl;
    cout << "Address: " << s[6] << endl;
    cout << "Degree Program: " << s[7] << endl;
    cout << "Year Level: " << s[8] << endl
         << endl;

    ifile.close();
}

void StudentDetails::EditStudentInput() // Function to take inputs for EditStudent Function
{
    int idToEdit;
    char conChoice = ' ';
    
    while (true) // to edit
    {
        cout << "Enter Student Number to Edit: ";
        cin >> idToEdit;

        if (IsValidStudentNum(idToEdit))
            break;
    }

    while (true)
    {
        cout << "Confirm Edit Student? [Y/N]" << endl;
        cin >> conChoice;

        if (toupper(conChoice) == 'Y')
        {
            EditStudent(to_string(idToEdit));

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
    Pause();
}

void StudentDetails::EditStudent(string idToEdit)
{
    string fName, mName, lName, bDay, sGender, sAddress, dProgram, birthMonthName, fullBirthday, filename, temp;
    int idNum, yrLvl, choice, birthDay, birthYear, birthMonthNum, i = 0;
    string *s = new string[9];
    ifstream ifile("output/Students/" + idToEdit + ".txt");
    if (!ifile) // Error display if the file won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }
    while (getline(ifile, s[i]))
    { // Fetch data stored in the file one line at a time
        i++;
    }

    idNum = stoi(s[0]);
    fName = s[1];
    mName = s[2];
    lName = s[3];
    bDay = s[4];
    sGender = s[5];
    sAddress = s[6];
    dProgram = s[7];
    yrLvl = stoi(s[8]);

    ifile.close();
    system("clear");
    HeaderDesign();
    cout << endl;
    // Same with the ViewDetails function, this reprints the information so that the user would know which info they will be editing
    cout << "\n\n1. Student Number: " << idNum << endl;
    cout << "2. First Name: " << fName << endl;
    cout << "3. Middle Name: " << mName << endl;
    cout << "4. Last Name: " << lName << endl;
    cout << "5. Birthday: " << bDay << endl;
    cout << "6. Gender: " << sGender << endl;
    cout << "7. Address: " << sAddress << endl;
    cout << "8. Degree Program: " << dProgram << endl;
    cout << "9. Year Level: " << yrLvl << endl
         << endl;

    cout << "What do you want to edit (1-9): "; // Ask what part to edit
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
    {
        while (true)
        {
            cout << "Enter new ID Number (9-digit ID Number): ";
            cin >> idNum;
            cin.ignore();

            if (IsValidStudentNum(idNum))
                break;
        }

        ifstream ifile("output/Students/idlist.txt");
        ofstream ofile("output/Students/temp.txt");

        if (!ifile || !ofile) // Error display if the file/s won't open
        {
            cerr << "Error opening file" << endl;
            return;
        }

        while (getline(ifile, temp)) // Reads the file and stores strings in temp
        {
            size_t pos = temp.find(idToEdit); // Looks for the id to edit in the list

            while (pos != string::npos) // While everything that has to be replaced isnt replaced yet
            {
                temp.replace(pos, idToEdit.length(), to_string(idNum));     // Replaces the id in the list with the new one starting at the pos
                pos = temp.find(idToEdit, pos + to_string(idNum).length()); // Looks again for other id match
            }

            ofile << temp << "\n"; // Writes the modified line in the temp file
        }

        ifile.close();
        ofile.close();

        // Replace the original idlist.txt with the temporary file
        // Error display if it doesn't go through
        if (remove("output/Students/idlist.txt") != 0)
        {
            cerr << "Error deleting file: idlist.txt" << endl;
        }
        if (rename("output/Students/temp.txt", "output/Students/idlist.txt") != 0)
        {
            cerr << "Error renaming file: temp.txt to idlist.txt" << endl;
        }

        break;
    }
    case 2:
    {
        while (true)
        {
            cout << "Enter new First Name: ";
            getline(cin, fName);

            if (IsValidName(fName))
                break;
        }
        break;
    }
    case 3:
    {
        while (true)
        {
            cout << "Enter new Middle Name: ";
            getline(cin, mName);

            if (IsValidName(mName))
                break;
        }
        break;
    }
    case 4:
    {
        while (true)
        {
            cout << "Enter new Last Name: ";
            getline(cin, lName);

            if (IsValidName(lName))
                break;
        }
        break;
    }
    case 5:
    {
        cout << "Enter new Birth Month: ";
        cin >> birthMonthName;
        while (!IsValidBirthMonth(birthMonthName))
        {
            cout << "Invalid Month! Please enter a valid birth month." << endl;
            cout << "Enter Birth Month: ";
            cin >> birthMonthName;
        }

        cout << "Enter new Birth Day: ";
        cin >> birthDay;

        cout << "Enter new Birth Year: ";
        cin >> birthYear;
        while (!IsValidBirthDate(birthDay, birthMonthName, birthYear))
        {
            cout << "Invalid Birth Date! Please enter a valid Birth Date." << endl;
            cout << "Enter Birth Month: ";
            cin >> birthMonthName;
            cout << "Enter Birth Day: ";
            cin >> birthDay;
            cout << "Enter Birth Year: ";
            cin >> birthYear;
        }

        birthMonthNum = MonthNameToNumber(birthMonthName);                                                // Convert month name to number(int)
        fullBirthday = to_string(birthMonthNum) + "/" + to_string(birthDay) + "/" + to_string(birthYear); // Convert into the full birthday format (string)
        break;
    }
    case 6:
    {
        while (true)
        {
            cout << "Enter new Gender (Male or Female): ";
            cin >> sGender;
            cin.ignore();

            if (IsValidGender(sGender))
                break;
        }
        break;
    }
    case 7:
    {
        while (true)
        {
            cout << "Enter new City Address (ex. Manila City): ";
            getline(cin, sAddress);

            if (IsValidName(sAddress))
                break;
        }
        break;
    }
    case 8:
    {
        while (true)
        {
            cout << "Enter new Degree Program (BSITCST, BSITWMA, BSITBA, BSITAGD): ";
            cin >> dProgram;

            if (IsValidDegreeProgram(dProgram))
                break;
        }
        break;
    }
    case 9:
    {
        while (true)
        {
            cout << "Enter new Year Level (1-4): ";
            cin >> yrLvl;
            cin.ignore();

            if (yrLvl >= 1 && yrLvl <= 4)
                break;
            else
                cout << "Enter a Valid Year Level." << endl;
        }
        break;
    }
    }

    // Generate a filename from the input id, use to_string function to convert int to string
    filename = "output/Students/" + to_string(idNum) + ".txt";
    // Create the file object and open the file
    ofstream ofile(filename);

    // Store data to file, overwrites the existing details
    ofile << idNum << endl;
    ofile << fName << endl;
    ofile << mName << endl;
    ofile << lName << endl;
    ofile << bDay << endl;
    ofile << sGender << endl;
    ofile << sAddress << endl;
    ofile << dProgram << endl;
    ofile << yrLvl << endl;
    // Close the ofstream object, always close the object after using it to avoid problems
    ofile.close();
}

void StudentDetails::DeleteStudentInput() // Function to take inputs for DeleteStudent Function
{
    int idToDelete;
    char conChoice = ' ';
    while (true) // to edit
    {
        cout << "Enter Student Number to Delete: ";
        cin >> idToDelete;

        if (IsValidStudentNum(idToDelete))
            break;
    }

    while (true)
    {
        cout << "Confirm Delete Student? [Y/N]" << endl;
        cin >> conChoice;

        if (toupper(conChoice) == 'Y')
        {
            DeleteStudent(to_string(idToDelete));

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
    Pause();
}

void StudentDetails::DeleteStudent(string idNum)
{
    string temp, line;
    string filename = "output/Students/" + idNum + ".txt";
    remove(filename.c_str());

    ifstream ifile("output/Students/idlist.txt");
    ofstream ofile("output/Students/temp.txt");

    if (!ifile || !ofile) // Error display if the file/s won't open
    {
        cerr << "Error opening file" << endl;
        return;
    }

    // Read each line from idlist.txt
    while (getline(ifile, line))
    {
        // If the line doesn't contain the idNum, write it to the temporary file
        if (line.find(idNum) == string::npos)
        {
            ofile << line << "\n";
        }
    }

    ifile.close();
    ofile.close();

    // Replace the original idlist.txt with the temporary file
    // Error display if it doesn't go through
    if (remove("output/Students/idlist.txt") != 0)
    {
        cerr << "Error deleting file: idlist.txt" << endl;
    }
    if (rename("output/Students/temp.txt", "output/Students/idlist.txt") != 0)
    {
        cerr << "Error renaming file: temp.txt to idlist.txt" << endl;
    }
}

void StudentDetails::InOrderTraversal(StudentNode *node) // Performs an in order traversal in the BST and sends it to the InsertSorted Function
{
    if (node == NULL) // Checks if node is null (base case)
    {
        return;
    }
    InOrderTraversal(node->left); // Left, Root, Right traversal
    InsertSorted(node);           // Inserts the current node to the Linked List
    InOrderTraversal(node->right);
}

void StudentDetails::InsertSorted(StudentNode *student) // Inserts the sorted StudentNodes into the linked list for last name based sorting
{
    ListNode *newNode = new ListNode; // Creates a new node
    newNode->student = student;       // Sets the new node value as the students' data
    newNode->next = NULL;

    if (head == NULL || head->student->lastName > student->lastName) // If the list is empty or if the new student's last name should be on top
    {
        newNode->next = head; // Sets the val of the new node next pointer to the current head
        head = newNode;       // Sets the newNode as the new head
    }
    else // Finds the correct position if not in front
    {
        ListNode *current = head;
        while (current->next != NULL && current->next->student->lastName < student->lastName) // Traversing the list to find the right position
        {
            current = current->next;
        }
        newNode->next = current->next; // Sets the val of the new node next pointer to the current node's next node
        current->next = newNode;       // Sets the current node's next node to the new node value
    }
}

void StudentDetails::ViewStudentsSortedByLastName() // This shows ID Number and full names of all students in the program. The list is sorted by last name
{
    head = NULL;            // Clear the linked list
    InOrderTraversal(root); // Populate the linked list with sorted nodes

    ListNode *current = head;
    while (current != NULL) // Traversing the linked list
    {
        StudentNode *student = current->student; // Fetching student data from current node
        cout << student->idNumber << "\t\t" << student->firstName << " " << student->middleName << " " << student->lastName << endl;
        current = current->next; // Moves to the next node
    }

    // Clean up the linked list
    while (head != NULL)
    {
        ListNode *temp = head; // Stores the current head node in a temp var
        head = head->next;     // Moves from head to the next node
        delete temp;           // Delete to free memory
    }
}

void StudentDetails::ViewStudents() // This function is for viewing student list, giving the user a choice if they want to view sorted by last name or student num
{
    int sortChoice, choice;
    system("clear");
    HeaderDesign();
    cout << endl;
    cout << "View Students Menu" << endl;
    cout << "1. View All Students" << endl;
    cout << "2. Filter by Year" << endl;
    cout << "3. Filter by Last Name Initial" << endl;
    cout << "0. Back to Main Menu" << endl;
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 0:
        system("clear");
        return; // Return to main menu
    case 1:
        system("clear");
        HeaderDesign();
        cout << endl;
        cout << "Sort by: " << endl;
        cout << "1. Student Number" << endl;
        cout << "2. Last Name" << endl;
        cin >> sortChoice;

        system("clear");
        switch (sortChoice)
        {
        case 1:
        {
            HeaderDesign();
            cout << endl;
            cout << "Displaying Students in order of Student Number:\n";
            cout << "Student Number\t\tName" << endl;
            ViewStudentsSortedByIDNumber(root); // Calls function to display student list by id num
            Pause();
            break;
        }

        case 2:
        {
            HeaderDesign();
            cout << endl;
            cout << "Displaying Students in order of Last Name:\n";
            cout << "Student Number\t\tName" << endl;
            ViewStudentsSortedByLastName(); // Calls function to display student list by last name
            Pause();
            break;
        }
        }
        break;
    case 2:
    {
        // Filter by year
        int yearFilter;
        system("clear");
        HeaderDesign();
        cout << endl;
        while (true)
        {
            cout << "Enter Year to Filter (2015-2024): "; // Asks for the year input
            cin >> yearFilter;
            cin.ignore();
            if (yearFilter >= 2015 && yearFilter <= 2024)
            {
                break; // Valid year, exit loop
            }
            else
            {
                cout << "Invalid year. Please enter a year between 2015 and 2024." << endl;
            }
        }
        system("clear");
        HeaderDesign();
        cout << endl;
        cout << "Displaying Students with ID Numbers starting in " << yearFilter << ".\n";
        cout << "Student Number\t\tName" << endl;
        FilterByYear(root, yearFilter); // Calls function to display student list of those that have the input year
        if (!HasStudentsWithYear(root, yearFilter))
        {
            cout << "No students found with ID Numbers starting in " << yearFilter << "." << endl;
            Pause();
            ViewStudents();
        }
        cout << endl;
        break;
    }
    case 3:
    {
        // Filter by last name initial
        char lastNameInitial;
        system("clear");
        HeaderDesign();
        cout << endl;
        while (true)
        {
            cout << "Enter Last Name Initial to Filter: "; // Asks for the initial input
            cin >> lastNameInitial;
            cin.ignore();
            if (isalpha(lastNameInitial))
            {
                break; // Valid letter, exit loop
            }
            else
            {
                cout << "Invalid input. Please enter a single letter." << endl;
            }
        }
        system("clear");
        HeaderDesign();
        cout << endl;
        cout << "Displaying Students with Last Names starting in " << lastNameInitial << ".\n";
        cout << "Student Number\t\tName" << endl;
        FilterByLastNameInitial(root, lastNameInitial); // Calls function to display student list of those that have the input initial
        if (!HasStudentsWithLastNameInitial(root, lastNameInitial))
        {
            cout << "No students found with Last Names starting in " << lastNameInitial << "." << endl;
            Pause();
            ViewStudents();
        }
        cout << endl;
        break;
    }
    default:
        cout << "Invalid choice. Please enter a valid option." << endl;
        break;
    }
}

void StudentDetails::ViewStudentsForInputFunctions() // This version of view students function is for those functions with input like EditStudent and others
{
    int sortChoice, choice;
    system("clear");
    HeaderDesign();
    cout << endl;
    cout << "View Students Menu" << endl;
    cout << "1. View All Students" << endl;
    cout << "2. Filter by Year" << endl;
    cout << "3. Filter by Last Name Initial" << endl;
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
        system("clear");
        HeaderDesign();
        cout << endl;
        cout << "Sort by: " << endl;
        cout << "1. Student Number" << endl;
        cout << "2. Last Name" << endl;
        cin >> sortChoice;

        system("clear");
        switch (sortChoice)
        {
        case 1:
        {
            HeaderDesign();
            cout << endl;
            cout << "Displaying Students in order of Student Number:\n";
            cout << "Student Number\t\tName" << endl;
            ViewStudentsSortedByIDNumber(root); // Calls function to display student list by id num
            cout << endl;
            break;
        }

        case 2:
        {
            HeaderDesign();
            cout << endl;
            cout << "Displaying Students in order of Last Name:\n";
            cout << "Student Number\t\tName" << endl;
            ViewStudentsSortedByLastName(); // Calls function to display student list by last name
            cout << endl;
            break;
        }
        }
        break;
    case 2:
    {
        // Filter by year
        int yearFilter;
        system("clear");
        HeaderDesign();
        cout << endl;
        while (true)
        {
            cout << "Enter Year to Filter (2015-2024): "; // Asks for the year input
            cin >> yearFilter;
            cin.ignore();
            if (yearFilter >= 2015 && yearFilter <= 2024)
            {
                break; // Valid year, exit loop
            }
            else
            {
                cout << "Invalid year. Please enter a year between 2015 and 2024." << endl;
            }
        }
        system("clear");
        HeaderDesign();
        cout << endl;
        cout << "Displaying Students with ID Numbers starting in " << yearFilter << ".\n";
        cout << "Student Number\t\tName" << endl;
        FilterByYear(root, yearFilter); // Calls function to display student list of those that have the input year
        Pause();
        if (!HasStudentsWithYear(root, yearFilter))
        {
            cout << "No students found with ID Numbers starting in " << yearFilter << "." << endl;
            Pause();
            ViewStudentsForInputFunctions();
        }
        cout << endl;
        break;
    }
    case 3:
    {
        // Filter by last name initial
        char lastNameInitial;
        system("clear");
        HeaderDesign();
        cout << endl;
        while (true)
        {
            cout << "Enter Last Name Initial to Filter: "; // Asks for the initial input
            cin >> lastNameInitial;
            cin.ignore();
            if (isalpha(lastNameInitial))
            {
                break; // Valid letter, exit loop
            }
            else
            {
                cout << "Invalid input. Please enter a single letter." << endl;
            }
        }
        system("clear");
        HeaderDesign();
        cout << endl;   
        cout << "Displaying Students with Last Names starting in " << lastNameInitial << ".\n";
        cout << "Student Number\t\tName" << endl;
        FilterByLastNameInitial(root, lastNameInitial); // Calls function to display student list of those that have the input initial
        Pause();
        if (!HasStudentsWithLastNameInitial(root, lastNameInitial))
        {
            cout << "No students found with Last Names starting in " << lastNameInitial << "." << endl;
            Pause();
            ViewStudentsForInputFunctions();
        }
        cout << endl;
        break;
    }
    default:
        cout << "Invalid choice. Please enter a valid option." << endl;
        break;
    }
}

void StudentDetails::FilterByYear(StudentNode *node, int year) // Function to traverse tree and print the students with student num that starts with the given year
{
    int studentYear;
    if (node != NULL) // Checks if current node is not null
    {                 // Traverses inorder-ly
        FilterByYear(node->left, year);
        studentYear = node->idNumber / 100000; // Divides student num that returns an int, so it checks if the first 4 numbers corresponds to the year
        if (studentYear == year)
        {
            cout << node->idNumber << "\t\t" << node->firstName << " " << node->middleName << " " << node->lastName << endl; // Prints those who have that year
        }
        FilterByYear(node->right, year);
    }
}

void StudentDetails::FilterByLastNameInitial(StudentNode *node, char initial) // Function to traverse tree and print the students with last names that starts with the given initial
{
    if (node != NULL) // Checks if current node is not null
    {                 // Traverses inorder-ly
        FilterByLastNameInitial(node->left, initial);
        if (toupper(node->lastName[0]) == toupper(initial)) // Checks if the last name starts with the initial given, uses toupper function to make it case-insensitive
        {
            cout << node->idNumber << "\t\t" << node->firstName << " " << node->middleName << " " << node->lastName << endl;
        }
        FilterByLastNameInitial(node->right, initial);
    }
}
