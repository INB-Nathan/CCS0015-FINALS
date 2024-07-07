#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>
#include <list>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Course {
public:
    string courseCode;
    string courseTitle;
    int units;
    int yearLevel;

    Course(string code = "", string title = "", int unit = 0, int year = 0) 
        : courseCode(code), courseTitle(title), units(unit), yearLevel(year) {}

    void display() const {
        cout << "| " << setw(11) << courseCode << " | " << setw(50) << courseTitle << " | "
             << setw(5) << units << " | " << setw(10) << yearLevel << " |\n";
        cout << "|" << "---------------------------------------------------------------------------------------" << "|\n";
    }

    string getFileName() const {
        return "CourseRecords/" + courseCode + "_" + courseTitle + ".txt";
    }

    void saveToFile() const {
        ofstream file(getFileName());
        if (file.is_open()) {
            file << courseCode << "," << courseTitle << "," << units << "," << yearLevel << "\n";
            file.close();
        } else {
            cerr << "Unable to open file for writing: " << getFileName() << endl;
        }
    }

    void loadFromFile(const string& fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            getline(file, line);
            stringstream ss(line);
            getline(ss, courseCode, ',');
            getline(ss, courseTitle, ',');
            ss >> units;
            ss.ignore();
            ss >> yearLevel;
            file.close();
        } else {
            cerr << "Unable to open file for reading: " << fileName << endl;
        }
    }
};

class Node {
public:
    Course course;
    Node* left;
    Node* right;

    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() : root(nullptr) {}

    void insert(const Course& course) {
        root = insert(root, course);
    }

    void viewCourses() const {
        if (root == nullptr) {
            cout << "No courses available." << endl;
            return;
        }

        cout << "|=======================================================================================|\n";
        cout << "|                                    COURSE RECORDS                                     |\n";
        cout << "|=======================================================================================|\n";
        cout << "| Course Code |                      Course Title                  | Units | Year Level |\n";
        cout << "|=======================================================================================|\n";

        inOrder(root);

        cout << "|=======================================================================================|\n";
    }

    Node* find(const string& courseCode) const {
        return find(root, courseCode);
    }

    void remove(const string& courseCode) {
        root = remove(root, courseCode);
    }

private:
    Node* insert(Node* node, const Course& course) {
        if (node == nullptr) return new Node(course);
        if (course.courseCode < node->course.courseCode)
            node->left = insert(node->left, course);
        else
            node->right = insert(node->right, course);
        return node;
    }

    void inOrder(Node* node) const {
        if (node == nullptr) return;
        inOrder(node->left);
        node->course.display();
        inOrder(node->right);
    }

    Node* find(Node* node, const string& courseCode) const {
        if (node == nullptr || node->course.courseCode == courseCode)
            return node;
        if (courseCode < node->course.courseCode)
            return find(node->left, courseCode);
        return find(node->right, courseCode);
    }

    Node* remove(Node* node, const string& courseCode) {
        if (node == nullptr) return node;

        if (courseCode < node->course.courseCode) {
            node->left = remove(node->left, courseCode);
        } else if (courseCode > node->course.courseCode) {
            node->right = remove(node->right, courseCode);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                fs::remove(node->course.getFileName());
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                fs::remove(node->course.getFileName());
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->course = temp->course;
            node->right = remove(node->right, temp->course.courseCode);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
};

bool isAlphaString(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

void addCourse(BinaryTree& tree) {
    string code, title, input;
    int units, year;

     while (true) {
        cout << "Enter course code: ";
        cin >> code;
        cin.ignore();
        if (tree.find(code) == nullptr) {
            break;
        }
        cout << "Course code already exists! Please enter a different course code." << endl;
    }


    cout << "Enter course title: ";
    getline(cin, title);

    while (true) {
        cout << "Enter number of units (0 to 9): ";
        cin >> input;

        if (input.length() == 1 && isdigit(input[0])) {
            units = input[0] - '0';
            if (units >= 0 && units <= 9) {
                break;
            }
        }
        cout << "Invalid input! Please enter a number between 0 and 9." << endl;
    }

    while (true) {
        cout << "Enter year level (1 to 4): ";
        cin >> input;

        if (input.length() == 1 && isdigit(input[0])) {
            year = input[0] - '0';
            if (year >= 1 && year <= 4) {
                break;
            }
        }
        cout << "Invalid input! Please enter a year level between 1 and 4." << endl;
    }

    Course course(code, title, units, year);
    tree.insert(course);
    course.saveToFile();
}

void editCourse(BinaryTree& tree) {
    string code, input;
    cout << "Enter course code to edit: ";
    cin >> code;
    cin.ignore();
    Node* node = tree.find(code);
    if (node == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    string title;
    int units, year;

    cout << "Enter new course title: ";
    getline(cin, title);


    while (true) {
        cout << "Enter new number of units (0 to 9): ";
        cin >> input;

        if (input.length() == 1 && isdigit(input[0])) {
            units = input[0] - '0';
            if (units >= 0 && units <= 9) {
                break;
            }
        }
        cout << "Invalid input! Please enter a number between 0 and 9." << endl;
    }

    while (true) {
        cout << "Enter new year level (1 to 4): ";
        cin >> input;

        if (input.length() == 1 && isdigit(input[0])) {
            year = input[0] - '0';
            if (year >= 1 && year <= 4) {
                break;
            }
        }
        cout << "Invalid input! Please enter a year level between 1 and 4." << endl;
    }

    node->course.courseTitle = title;
    node->course.units = units;
    node->course.yearLevel = year;
    node->course.saveToFile();
}

void deleteCourse(BinaryTree& tree) {
    string code;
    cout << "Enter course code to delete: ";
    cin >> code;
    Node* node = tree.find(code);
    if (node == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    tree.remove(code);
    fs::remove(node->course.getFileName());
}

void loadCourses(BinaryTree& tree) {
    if (!fs::exists("CourseRecords")) {
        fs::create_directory("CourseRecords");
    }

    for (const auto& entry : fs::directory_iterator("CourseRecords")) {
        Course course;
        course.loadFromFile(entry.path().string());
        tree.insert(course);
    }
}
