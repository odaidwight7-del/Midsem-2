
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/* ================= STUDENT CLASS ================= */
class Student {
public:
    string indexNumber;
    string name;

    Student(string i, string n) {
        indexNumber = i;
        name = n;
    }
};

/* ================= GLOBAL STORAGE ================= */
vector<Student> students;

/* ================= FUNCTION PROTOTYPES ================= */
void loadStudents();
void saveStudents();
void registerStudent();
void viewStudents();
void searchStudent();
void createSession();
void mainMenu();

/* ================= FILE HANDLING ================= */
void loadStudents() {
    ifstream file("students.txt");
    if (!file) return;

    string index, name;
    while (file >> index) {
        file.ignore();
        getline(file, name);
        students.push_back(Student(index, name));
    }
    file.close();
}

void saveStudents() {
    ofstream file("students.txt");
    for (auto &s : students) {
        file << s.indexNumber << " " << s.name << endl;
    }
    file.close();
}

/* ================= STUDENT MANAGEMENT ================= */
void registerStudent() {
    string index, name;
    cout << "Enter Index Number: ";
    cin >> index;
    cin.ignore();
    cout << "Enter Full Name: ";
    getline(cin, name);

    students.push_back(Student(index, name));
    saveStudents();

    cout << "Student Registered Successfully!\n";
}

void viewStudents() {
    cout << "\n--- REGISTERED STUDENTS ---\n";
    for (auto &s : students) {
        cout << s.indexNumber << " - " << s.name << endl;
    }
}

void searchStudent() {
    string index;
    cout << "Enter Index Number to Search: ";
    cin >> index;

    for (auto &s : students) {
        if (s.indexNumber == index) {
            cout << "Found: " << s.name << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

/* ================= ATTENDANCE SESSION ================= */
void createSession() {
    string courseCode, date;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;

    string filename = "session_" + courseCode + "_" + date + ".txt";
    ofstream file(filename);

    if (!file) {
        cout << "Error creating session file.\n";
        return;
    }

    int present = 0, absent = 0, late = 0;

    for (auto &s : students) {
        char status;
        cout << "Mark attendance for " << s.name
             << " (P = Present, A = Absent, L = Late): ";
        cin >> status;

        if (status == 'P' || status == 'p') present++;
        else if (status == 'L' || status == 'l') late++;
        else absent++;

        file << s.indexNumber << " "
             << s.name << " "
             << status << endl;
    }

    file << "\nSUMMARY\n";
    file << "Present: " << present << endl;
    file << "Absent: " << absent << endl;
    file << "Late: " << late << endl;

    file.close();
    cout << "Attendance session saved successfully!\n";
}

/* ================= MAIN MENU ================= */
void mainMenu() {
    int choice;
    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Create Attendance Session\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            createSession();
            break;
        case 5:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

/* ================= MAIN FUNCTION ================= */
int main() {
    loadStudents();
    mainMenu();
    return 0;
}