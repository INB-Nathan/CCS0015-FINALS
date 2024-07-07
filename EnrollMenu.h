#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class EnrollMenu
{
    private:
        string studentID, studentName;
    public:
    // Validation Functions
        bool isEnrolled(string);
    // Function Prototypes
        void EnrollStudent(string);
        void ViewEnrollees();
};