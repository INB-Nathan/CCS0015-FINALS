#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

class Course {
public:
    string CourseCode;
    string CourseTitle;
    int Units;
    int YearLevel;

    Course(string code = "", string title = "", int unit = 0, int year = 0)
        : CourseCode(code), CourseTitle(title), Units(unit), YearLevel(year) {}

    void Display() const;
    string GetFileName() const;
    void SaveToFile() const;
    void LoadFromFile(const string& fileName);
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

    void Insert(const Course& course);
    void ViewCourses() const;
    Node* Find(const string& CourseCode) const;
    void Remove(const string& CourseCode);

private:
    Node* Insert(Node* node, const Course& course);
    void InOrder(Node* node) const;
    Node* Find(Node* node, const string& CourseCode) const;
    Node* Remove(Node* node, const string& CourseCode);
    Node* MinValueNode(Node* node);
};

bool IsAlphaString(const string& str);
void AddCourse(BinaryTree& tree);
void EditCourse(BinaryTree& tree);
void DeleteCourse(BinaryTree& tree);
void LoadCourses(BinaryTree& tree);
void CourseCodeMenu();



// Function definitions

void Course::Display() const {
    cout << "| " << setw(11) << CourseCode << " | " << setw(50) << CourseTitle << " | "
         << setw(5) << Units << " | " << setw(10) << YearLevel << " |\n";
    cout << "+" << setw(87) << setfill('-') << "" << setfill(' ') << "+" << endl;
}

string Course::GetFileName() const {
    return "CourseRecords/" + CourseCode + "_" + CourseTitle + ".txt";
}

void Course::SaveToFile() const {
    ofstream file(GetFileName());
    if (file.is_open()) {
        file << CourseCode << "," << CourseTitle << "," << Units << "," << YearLevel << "\n";
        file.close();
    } else {
        cerr << "Unable to open file for writing: " << GetFileName() << endl;
    }
}

void Course::LoadFromFile(const string& fileName) {
    string line;
    ifstream file(fileName);
    if (file.is_open()) {
        getline(file, line);
        stringstream ss(line);
        getline(ss, CourseCode, ',');
        getline(ss, CourseTitle, ',');
        ss >> Units;
        ss.ignore();
        ss >> YearLevel;
        file.close();
    } else {
        cerr << "Unable to open file for reading: " << fileName << endl;
    }
}

void BinaryTree::Insert(const Course& course) {
    root = Insert(root, course);
}

void BinaryTree::ViewCourses() const {
    if (root == nullptr) {
        cout << "No courses available." << endl;
        return;
    }
    cout << endl;
    cout << "+" << setw(87) << setfill('=') << "" << setfill(' ') << "+\n";
    cout << "|                                    COURSE RECORDS                                     |\n";
    cout << "+" << setw(87) << setfill('=') << "" << setfill(' ') << "+\n";
    cout << "| Course Code |                      Course Title                  | Units | Year Level |\n";
    cout << "|" << setw(87) << setfill('=') << "" << setfill(' ') << "+\n";

    InOrder(root);
    cout << endl;
}

Node* BinaryTree::Find(const string& CourseCode) const {
    return Find(root, CourseCode);
}

void BinaryTree::Remove(const string& CourseCode) {
    root = Remove(root, CourseCode);
}

Node* BinaryTree::Insert(Node* node, const Course& course) {
    if (node == nullptr) return new Node(course);
    if (course.CourseCode < node->course.CourseCode)
        node->left = Insert(node->left, course);
    else
        node->right = Insert(node->right, course);
    return node;
}

void BinaryTree::InOrder(Node* node) const {
    if (node == nullptr) return;
    InOrder(node->left);
    node->course.Display();
    InOrder(node->right);
}

Node* BinaryTree::Find(Node* node, const string& CourseCode) const {
    if (node == nullptr || node->course.CourseCode == CourseCode)
        return node;
    if (CourseCode < node->course.CourseCode)
        return Find(node->left, CourseCode);
    return Find(node->right, CourseCode);
}

Node* BinaryTree::Remove(Node* node, const string& CourseCode) {
    if (node == nullptr) return node;

    if (CourseCode < node->course.CourseCode) {
        node->left = Remove(node->left, CourseCode);
    } else if (CourseCode > node->course.CourseCode) {
        node->right = Remove(node->right, CourseCode);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            fs::remove(node->course.GetFileName());
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            fs::remove(node->course.GetFileName());
            return temp;
        }

        Node* temp = MinValueNode(node->right);
        node->course = temp->course;
        node->right = Remove(node->right, temp->course.CourseCode);
    }
    return node;
}

Node* BinaryTree::MinValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

bool IsAlphaString(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

void AddCourse(BinaryTree& tree) {
    string code, title, input;
    int units, year;
    bool isValid = false;

    while (true) {
        cout << "Enter course code: ";
        cin >> code;
        cin.ignore();
        if (tree.Find(code) == nullptr) {
            break;
        }
        cout << "Course code already exists! Please enter a different course code." << endl;
    }

    while (true) {
        cout << "Enter course title: ";
        getline(cin, title);

        for (char c : title) {
            if (isalnum(c)) {
                isValid = true;
                break;
            }
        }

        if (isValid) {
            break;
        } else {
            system("cls");
            cout << "Invalid input! \nCourse title must contain at least one alphanumeric character." << endl;
        }
    }

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
    tree.Insert(course);
    course.SaveToFile();

    system("cls");
    cout << "Course added successfully!\n" << endl;
}

void EditCourse(BinaryTree& tree) {
    string code, input, title;
    int units, year;

    cout << "Enter course code to edit: ";
    cin >> code;
    cin.ignore();
    Node* node = tree.Find(code);
    if (node == nullptr) {
        cout << "Course not found.\n";
        return;
    }


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

    node->course.CourseTitle = title;
    node->course.Units = units;
    node->course.YearLevel = year;
    node->course.SaveToFile();

    system("cls");
    cout << "Course edited successfully!" << endl;
    cout << endl;
}

void DeleteCourse(BinaryTree& tree) {
    string code;
    cout << "Enter course code to delete: ";
    cin >> code;
    Node* node = tree.Find(code);
    if (node == nullptr) {
        cout << "Course not found.\n";
        return;
    }

    tree.Remove(code);
    fs::remove(node->course.GetFileName());

    system("cls");
    cout << "Course deleted successfully!" << endl;
    cout << endl;
}

void LoadCourses(BinaryTree& tree) {
    if (!fs::exists("CourseRecords")) {
        fs::create_directory("CourseRecords");
    }

    for (const auto& entry : fs::directory_iterator("CourseRecords")) {
        Course course;
        course.LoadFromFile(entry.path().string());
        tree.Insert(course);
    }
}

void CourseCodeMenu() {
    cout << endl;
    cout << "+" << setw(87) << setfill('=') << "" << setfill(' ') << "+\n";
    cout << "|                                     COURSE MENU                                       |\n";
    cout << "+" << setw(87) << setfill('=') << "" << setfill(' ') << "+" << endl;
    cout << "|" << setw(10) << right << "[1] " << setw(77) << left << "Add Course" << "|" << endl;
    cout << "|" << setw(10) << right << "[2] " << setw(77) << left << "View Courses" << "|" << endl;
    cout << "|" << setw(10) << right << "[3] " << setw(77) << left << "Edit Course" << "|" << endl;
    cout << "|" << setw(10) << right << "[4] " << setw(77) << left << "Delete Course" << "|" << endl;
    cout << "|" << setw(10) << right << "[0] " << setw(77) << left << "Exit" << "|\n";
    cout << "+" << setw(87) << setfill('-') << "" << setfill(' ') << "+" << endl;
}
