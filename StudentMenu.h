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
    // Constructor
    StudentDetails();
    // Add main functions : Add student, view student, edit student, delete student.
    void AddStudent(string, string, string, string, string, string, string, int, int);
    void ViewStudent(StudentNode *);
    void EditStudent();
    void DeleteStudent();
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

StudentDetails::StudentDetails()
{
    root = NULL;
}

void StudentDetails::AddStudent(string fName, string lName, string mName, string dProgram, string sGender, string sAddress, string bDay, int idNum, int yrLvl)
{
    // Create and instantiate the node
    string filename;

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