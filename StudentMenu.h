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
            string firstName, lastName, middleName, degreeProgram, studentGender, studentAddress;
            
            int idNumber, yearLevel;

            StudentNode *head, *next, *current;
        };

    public:
        // Add input validation functions.
            
        // Constructor
        StudentDetails();
        // Add main functions : Add student, view student, edit student, delete student.
        void AddStudent();
        void ViewStudent();
        void EditStudent();
        void DeleteStudent();
};

void StudentDetails::AddStudent()
{
    
}


