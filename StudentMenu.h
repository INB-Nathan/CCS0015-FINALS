#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

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

public:
    StudentNode *root;
    // Add input validation functions.
    bool IsValidName(string);
    bool IsValidGender(string);
    int MonthNameToNumber(string &);
    bool IsValidBirthMonth(string &);
    bool IsValidBirthDate(int, string &, int);
    // Constructor
    StudentDetails();
    // Add main functions
    void AddStudent(string, string, string, string, string, string, string, int, int);
    void SaveIDToList();
    void EditStudent();
    void DeleteStudent();
    void RestoreStudentInfo(int, string, string, string, string, string, string, string, int);
    void FetchEachStudentFile(string);
    void FetchStudentInfo();
    void ViewStudent(StudentNode *);
};

bool StudentDetails::IsValidName(string str)
{
    // Convert the string to lowercase manually
    for (int i = 0; i < str.length(); i++)
    {
        if (!isalpha(str[i]) && !isspace(str[i])) // Check if alpha or a space
        {
            cout << "Please Enter a Valid Name (a-z)" << endl;
            return false;
        }
    }

    return true;
}

bool StudentDetails::IsValidGender(string str)
{
    // Convert the string to lowercase manually
    for (int i = 0; i < str.length(); ++i)
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

int StudentDetails::MonthNameToNumber(string &monthName)
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

bool StudentDetails::IsValidBirthMonth(string &month)
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

bool StudentDetails::IsValidBirthDate(int birthday, string &month, int year)
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

StudentDetails::StudentDetails()
{
    root = NULL;
}

void StudentDetails::AddStudent(string fName, string lName, string mName, string dProgram, string sGender, string sAddress, string bDay, int idNum, int yrLvl)
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
                cout << "Duplicate values are not allowed in trees.";
                return;
            }
        }
    }

    // Generate a filename from the input id, use to_string function to convert int to string
    filename = to_string(idNum) + ".txt";
    // Create the file object and open the file
    ofstream ofile(filename);

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

    SaveIDToList();
}

void StudentDetails::SaveIDToList() // Saves the Stud num to a list for reading purposes
{
    // Create another file to store all of the student numbers
    ofstream ofile("idlist.txt", ios::app);

    // Store the idNumber
    ofile << node->idNumber << endl;

    // Close the file
    ofile.close();
}

// This shows ID Number and full names of all students in the program. The list must be sorted.
void StudentDetails::ViewStudent(StudentNode *tempNode)
{
    // Left -> Root -> Right

    if (tempNode == NULL)
    { // Base case of the recursion
        return;
    }

    ViewStudent(tempNode->left);
    cout << tempNode->idNumber << "\t\t" << tempNode->firstName << " " << tempNode->middleName << " " << tempNode->lastName << endl;
    ViewStudent(tempNode->right);
}

void StudentDetails::FetchStudentInfo() // Reads the idlist file to traverse through the student files
{
    string filename;
    // Open a ifstream object and open the idlist file
    ifstream ifile("idlist.txt");

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

    ifstream ifile(idOfFile + ".txt"); // Opens the student file given by the FetchStudentInfo func
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

    RestoreStudentInfo(idNum, fName, mName, lName, bDay, sGender, sAddress, dProgram, yrLvl); 
}

void StudentDetails::RestoreStudentInfo(int idNum, string fName, string mName, string lName, string bDay, string sGender, string sAddress, string dProgram, int yrLvl)
{ // Restores the data into the tree
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
        cout << "Student Info Restored\n";
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
                    cout << "Student Info Restored\n";
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
                    cout << "Student Info Restored\n";
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