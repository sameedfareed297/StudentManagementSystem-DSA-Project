#include <iostream>
#include <string>// getline
#include <algorithm> // For sorting
#include <iomanip> // Include for set width
#include <fstream>// Include for text.file working
// -------------------------------------FUNCTION PROTOTYPES----------------------------------------------------------------
using namespace std;
void registerTeacher();
bool authenticateTeacher(int TEACHER, const string& password);
void enterStudentMarks(int rollno, int TEACHER, const std::string& teacherPassword, const std::string& subject);
void markAttendance(int rollno);
char calculateGrade(float marks);
void viewPersonalDetails(int rollno);
void showAllStudents();
void checkGradesAndAttendance(int rollno);
void ViewTeacherDetails(int TEACHER, const std::string& password);
void viewStudentDetails(int rollno);
void modifyAttendanceAndMarks(int rollno, int TEACHER, const std::string& teacherPassword, const std::string& subject);
void sortByRollNumberQuickSort();
void modifyStudent(int rollno);
void deleteStudent(int rollno);
void bubbleSort();
void deleteTeacher(int teacherID);
void modifyTeacher(int teacherID);
void ViewteacherDetails(int teacherID);
// --------------------------------------STRUCTURES---------------------------------------------------------------
struct SubjectNode {
    string subject;
    float marks;
    SubjectNode* next;
    float attendance;
    SubjectNode(const string& subj, float marksVal, float attendanceVal) {
        subject = subj;
        marks = marksVal;
        attendance = attendanceVal;
        next = nullptr;
    }
};
struct Student {
    int rollno;
    string name;
    string fname;
    string cell;
    string dob;
    string address;
    string department;
    float grades;
    float attendance;
    float marks = 0.0;

    Student* next; // Pointer to the next node in the linked list
    SubjectNode* subjectsHead;
};
struct Teacher {
    int teacherID;
    string name;
    string department;
    string subject;
    string qual;
    int age;
    string password;

    Teacher* next; // Pointer to the next node in the linked list
};

struct StudentCredentials {
    int rollno;
    string password;
    StudentCredentials* next; // Pointer to the next node in the linked list
};
struct TeacherCredentials {
    int TEACHER;
    string password;
    TeacherCredentials* next;
    // Add more details if needed
};
// -----------------------------------------------------------------------------------------------------
TeacherCredentials* teacherCredentialsHead = nullptr;
StudentCredentials* studentCredentialsHead = nullptr; // Head of the linked list for student credentials
Student* studentsHead = nullptr;
Teacher* teachersHead = nullptr;
// -----------------------------STUDENT FUNCTION------------------------------------------------------------------------
void registerStudent() {
    int rollno;
    string password;
    string name;
    string fname;
    string cell;
    string dob;
    string address;
    string department;

    cout << "Enter your Roll Number in the Format (1XXX): ";
    cin >> rollno;

    // Check if the student is already registered
    StudentCredentials* credNode = studentCredentialsHead;
    while (credNode != nullptr) {
        if (credNode->rollno == rollno) {
            cout << "You are already registered. Please log in with your password." << endl;
            return;
        }
        credNode = credNode->next;
    }

    cin.ignore(); // Ignore newline character left in the buffer

    cout << "Enter Student Name: ";
    getline(cin, name);

    cout << "Enter Student's Father Name: ";
    getline(cin, fname);

    cout << "Enter Student's CellPhone Number: ";
    getline(cin, cell);

    cout << "Enter Student's Date of Birth (dd/mm/yyyy): ";
    getline(cin, dob);

    cout << "Enter Student's Address: ";
    getline(cin, address);

    cout << "Enter Student's Department: ";
    getline(cin, department);

    cout << "Set Student's password: ";
    getline(cin, password);

    // Create a new node for student credentials
    StudentCredentials* newCredNode = new StudentCredentials{ rollno, password, nullptr };
    if (studentCredentialsHead == nullptr) {
        studentCredentialsHead = newCredNode;
    }
    else {
        newCredNode->next = studentCredentialsHead;
        studentCredentialsHead = newCredNode;
    }

    // Create a new node for the student
    Student* newStudentNode = new Student{ rollno, name, fname, cell, dob, address, department, 0.0, 0.0, 0.0, nullptr };
    if (studentsHead == nullptr) {
        studentsHead = newStudentNode;
    }
    else {
        newStudentNode->next = studentsHead;
        studentsHead = newStudentNode;
    }

    cout << "Registration successful. Your password is set." << endl;
}

// Function to authenticate a student
bool authenticateStudent(int rollno, const string& password) {
    StudentCredentials* credNode = studentCredentialsHead;
    while (credNode != nullptr) {
        if (credNode->rollno == rollno && credNode->password == password) {
            return true;
        }
        credNode = credNode->next;
    }

    return false;
}


void updateStudentInfo(int rollno) {
    Student* current = studentsHead;

    while (current != nullptr) {
        if (current->rollno == rollno) {
            int updateChoice;

            cout << "\n\t\tUpdate Student Information" << endl;
            cout << "\t\t-------------------------" << endl;
            cout << "\t\t1-Update Name" << endl;
            cout << "\t\t2-Update Roll Number" << endl;
            cout << "\t\t3-Update Department" << endl;
            cout << "\t\t4-Update Address" << endl;
            cout << "\t\t5-Update Cell Phone Number" << endl;
            cout << "\t\t6-Update Date of Birth" << endl;
            cout << "\t\t7-Return to Student Menu" << endl;
            cout << "Enter your choice: ";
            cin >> updateChoice;

            cin.ignore(); // Ignore newline character left in the buffer

            switch (updateChoice) {
            case 1: // Update Name
                cout << "Enter new Name: ";
                getline(cin, current->name);
                break;
            case 2: // Update Roll Number
                cout << "Enter new Roll Number: ";
                cin >> current->rollno;
                break;
            case 3: // Update Department
                cout << "Enter new Department: ";
                getline(cin, current->department);
                break;
            case 4: // Update Address
                cout << "Enter new Address: ";
                getline(cin, current->address);
                break;
            case 5: // Update Cell Phone Number
                cout << "Enter new Cell Phone Number: ";
                getline(cin, current->cell);
                break;
            case 6: // Update Date of Birth
                cout << "Enter new Date of Birth (dd/mm/yyyy): ";
                getline(cin, current->dob);
                break;
            case 7: // Return to Student Menu
                return;
            default:
                cout << "Invalid choice for Update Student Information." << endl;
            }
        }
        current = current->next;
    }

    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
}

void studentFunctions() {
    int choice;
    int rollno;
    string password;

    do {
        cout << "\n\t\tStudent Functions" << endl;
        cout << "\t\t----------------" << endl;
        cout << "\t\t1-Log In" << endl;
        cout << "\t\t2-Return to Main Menu" << endl;  // New option to return to the main menu
        cout << "\t\t----------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: // Log In
            cout << "Enter Your Roll No: ";
            cin >> rollno;
            cout << "Enter Your Password: ";
            cin >> password;

            if (authenticateStudent(rollno, password)) {
                cout << "Log in successful." << endl;
                // Continue with other student functions (view personal details, check grades, etc.)
                do {
                    cout << "\n\t\t----------------";
                    cout << "\n\t\t1-View Personal Details" << endl;
                    cout << "\t\t2-Check Grades and Attendance" << endl;
                    cout << "\t\t3-Update Information" << endl;
                    cout << "\t\t4-Log Out" << endl;
                    cout << "\t\t----------------" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1: // View Personal Details
                        viewPersonalDetails(rollno);
                        break;
                    case 2: // Check Grades and Attendance
                        checkGradesAndAttendance(rollno);
                        break;
                    case 3: // Update Information
                        updateStudentInfo(rollno);
                        break;
                    case 4: // Return to Student Menu
                        break;
                    default:
                        cout << "Invalid choice for Student Menu." << endl;
                    }
                } while (choice != 4);
            }
            else {
                cout << "Incorrect Roll Number or Password. Log in failed." << endl;
            }
            break;
        case 2: // Return to Main Menu
            return;
        default:
            cout << "Invalid choice for Student Functions." << endl;
        }

    } while (true);
}


// -----------------------------ADMIN FUNCTIONS------------------------------------------------------------------------

void adminFunctions() {
    int choice, rollno, teacherID;

    do {
        cout << "\n\t\tAdmin Functions" << endl;
        cout << "\t\t----------------" << endl;
        cout << "\t\t1-Register Student" << endl;
        cout << "\t\t2-Register Teacher" << endl;
        cout << "\t\t3-Delete Teacher" << endl;  // Moved the option to delete teacher to position 3
        cout << "\t\t4-Modify Student" << endl;  // Moved the option to modify student to position 4
        cout << "\t\t5-Delete Student" << endl;  // Added option to delete student at position 5
        cout << "\t\t6-View Student Details" << endl;
        cout << "\t\t7-View Teacher Details" << endl;
        cout << "\t\t8-Check Grades and Attendance" << endl;
        cout << "\t\t9-Show All Students" << endl;
        cout << "\t\t10-Sort Students by Roll Number (Bubble Sort)" << endl;
        cout << "\t\t11-Sort Students by Roll Number (Quick Sort)" << endl;
        cout << "\t\t12-Modify Teacher" << endl;  // Added option to modify teacher at position 12
        cout << "\t\t0-Return to Main Menu" << endl;
        cout << "\t\t----------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            // Existing cases remain unchanged
        case 1:
            registerStudent();
            break;
        case 2:
            registerTeacher();
            break;
        case 3: // Delete Teacher
            cout << "Enter the Teacher ID you want to delete: ";
            cin >> teacherID;
            deleteTeacher(teacherID);
            break;
        case 4: // Modify Student
            cout << "Enter the Roll Number of the Student you want to modify: ";
            cin >> rollno;
            modifyStudent(rollno);
            break;
        case 5: // Delete Student
            cout << "Enter the Roll Number of the Student you want to delete: ";
            cin >> rollno;
            deleteStudent(rollno);
            break;
        case 6: // View Student Details
            cout << "Enter the Roll Number of the Student whose details you want to view: ";
            cin >> rollno;
            viewStudentDetails(rollno);
            break;
        case 7: // View Teacher Details
            cout << "Enter the Teacher ID whose details you want to view: ";
            cin >> teacherID;
            ViewteacherDetails(teacherID);
            break;
        case 8: // Check Grades and Attendance
            cout << "Enter the Roll Number of the student whose grades and attendance you want to check: ";
            cin >> rollno;
            checkGradesAndAttendance(rollno);
            break;
        case 9: // Show All Students
            showAllStudents();
            break;
        case 10: // Sort Students by Roll Number (Bubble Sort)
            bubbleSort();
            break;
        case 11: // Sort Students by Roll Number (Quick Sort)
            sortByRollNumberQuickSort();
            break;
        case 12: // Modify Teacher
            cout << "Enter the Teacher ID you want to modify: ";
            cin >> teacherID;
            modifyTeacher(teacherID);
            break;
        case 0: // Return to Main Menu
            return;
        default:
            cout << "Invalid choice for Admin Functions." << endl;
        }
    } while (true);
}

void ViewteacherDetails(int teacherID) {
    Teacher* currentTeacher = teachersHead;
    while (currentTeacher != nullptr) {
        if (currentTeacher->teacherID == teacherID) {
            // Display teacher details
            cout << "Teacher ID: " << currentTeacher->teacherID << endl;
            cout << "Name: " << currentTeacher->name << endl;
            cout << "Subject: " << currentTeacher->subject << endl;
            // Add more details if needed

            return;
        }
        currentTeacher = currentTeacher->next;
    }

    cout << "Teacher with ID " << teacherID << " Not Found." << endl;
}

void modifyStudent(int rollno) {
    Student* current = studentsHead;
    while (current != nullptr) {
        if (current->rollno == rollno) {
            cout << "Enter Modified Student Details:" << endl;
            cout << "Enter Student Name: ";
            cin >> current->name;
            cout << "Enter Student's Father name: ";
            cin >> current->fname;
            cout << "Enter Student's Cell Phone Number: ";
            cin >> current->cell;
            cout << "Enter Student's Date of Birth(dd/mm/yyyy): ";
            cin >> current->dob;
            cout << "Enter Student's Address: ";
            cin.ignore(); // Ignore newline character left in the buffer
            getline(cin, current->address);
            cout << "Enter Student's Department: ";
            cin >> current->department;
            cout << "Student with Roll Number " << rollno << " Modified Successfully." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
}
void modifyTeacher(int teacherID) {
    Teacher* current = teachersHead;

    while (current != nullptr) {
        if (current->teacherID == teacherID) {
            cout << "Enter Modified Teacher Details:" << endl;
            cout << "Enter Teacher Name: ";
            cin >> current->name;
            cout << "Enter Teacher's Department: ";
            cin >> current->department;
            cout << "Enter Teacher's Subject: ";
            cin >> current->subject;
            cout << "Enter Teacher's Qualification: ";
            cin >> current->qual;
            cout << "Enter Teacher's Age: ";
            cin >> current->age;
            cout << "Teacher with ID " << teacherID << " Modified Successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Teacher with ID " << teacherID << " Not Found." << endl;
}

void deleteStudent(int rollno) {
    Student* current = studentsHead;
    Student* prev = nullptr;

    while (current != nullptr) {
        if (current->rollno == rollno) {
            if (prev != nullptr) {
                prev->next = current->next;
            }
            else {
                studentsHead = current->next;
            }

            delete current;
            cout << "Student with Roll Number " << rollno << " Deleted Successfully." << endl;
            return;
        }

        prev = current;
        current = current->next;
    }

    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
}
void deleteTeacher(int teacherID) {
    Teacher* current = teachersHead;
    Teacher* prev = nullptr;

    while (current != nullptr) {
        if (current->teacherID == teacherID) {
            if (prev != nullptr) {
                prev->next = current->next;
            }
            else {
                teachersHead = current->next;
            }

            delete current;
            cout << "Teacher with ID " << teacherID << " Deleted Successfully." << endl;
            return;
        }

        prev = current;
        current = current->next;
    }

    cout << "Teacher with ID " << teacherID << " Not Found." << endl;
}

void viewStudentDetails(int rollno) {
    Student* current = studentsHead;

    while (current != nullptr) {
        if (current->rollno == rollno) {
            // Display student details in a formatted way
            cout << endl;
            cout << "\nStudent Details:\n";
            cout << "----------------------------------------\n";
            cout << setw(20) << left << "Roll Number:" << current->rollno << endl;
            cout << setw(20) << left << "Name:" << current->name << endl;
            cout << setw(20) << left << "Department:" << current->department << endl;

            cout << setw(20) << left << "Grades:";
            if (current->grades > 0) {
                cout << calculateGrade(current->marks);
            }
            else {
                cout << "Not Mentioned Yet";
            }
            cout << endl;

            cout << setw(20) << left << "Overall Attendance:" << current->attendance << "%" << endl;
            cout << setw(20) << left << "Overall Marks:" << current->marks << endl;

            // Display subject-wise details
            SubjectNode* subjectNode = current->subjectsHead;
            int subjectNumber = 1;

            while (subjectNode != nullptr) {
                cout << "\nSubject " << subjectNumber << " Details:\n";
                cout << setw(20) << left << "Subject:" << subjectNode->subject << endl;
                cout << setw(20) << left << "Marks:" << subjectNode->marks << endl;
                cout << setw(20) << left << "Grade:" << calculateGrade(subjectNode->marks) << endl;
                cout << setw(20) << left << "Attendance:" << subjectNode->attendance << "%" << endl;

                subjectNode = subjectNode->next;
                subjectNumber++;
            }

            cout << "----------------------------------------\n";
            return;  // Move the return statement to the end of the function
        }
        current = current->next;
    }

    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
}




void viewPersonalDetails(int rollno) {
    Student* current = studentsHead;

    while (current != nullptr) {
        if (current->rollno == rollno) {
            // Display personal details
            cout << endl;
            cout << "Personal Details:\n";
            cout << "----------------------------------------\n";
            cout << setw(20) << left << "Roll Number:" << current->rollno << endl;
            cout << setw(20) << left << "Name:" << current->name << endl;
            cout << setw(20) << left << "Father's Name:" << current->fname << endl;
            cout << setw(20) << left << "Cell Phone:" << current->cell << endl;
            cout << setw(20) << left << "Date of Birth:" << current->dob << endl;
            cout << setw(20) << left << "Address:" << current->address << endl;

            // Display the subject numbers and corresponding grades
            SubjectNode* subjectNode = current->subjectsHead;
            int subjectNumber = 1;

            while (subjectNode != nullptr) {
                cout << "Subject " << subjectNumber << ": " << subjectNode->subject << " - Grade: " << calculateGrade(subjectNode->marks) << endl;
                subjectNode = subjectNode->next;
                subjectNumber++;
            }

            cout << "----------------------------------------\n";
            return;
        }
        current = current->next;
    }

    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
}

// Function to calculate the grade based on marks
char calculateGrade(float marks) {
    if (marks >= 85) {
        return 'A';
    }
    else if (marks >= 79) {
        return 'B';
    }
    else if (marks >= 70) {
        return 'C';
    }
    else if (marks >= 65) {
        return 'D';
    }
    else if (marks >= 55) {
        return 'E';
    }
    else {
        return 'F';
    }
}
void checkGradesAndAttendance(int rollno) {
    Student* current = studentsHead;

    while (current != nullptr) {
        if (current->rollno == rollno) {
            // Display grades, attendance, and grade
            cout << endl;
            cout << "GRADES & ATTENDANCE:\n";
            cout << "----------------------------------------\n";
            cout << "Roll Number: " << current->rollno << endl;

            // Display subject-wise attendance and grade
            SubjectNode* subjectNode = current->subjectsHead;
            int subjectNumber = 1;

            while (subjectNode != nullptr) {
                cout << "Subject " << subjectNumber << ": " << subjectNode->subject
                    << " - Attendance: " << subjectNode->attendance << "%"
                    << " - Grade: " << calculateGrade(subjectNode->marks) << endl;
                subjectNode = subjectNode->next;
                subjectNumber++;
            }

            cout << "----------------------------------------\n";
            return;
        }
        current = current->next;
    }

    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
}



void showAllStudents() {
    Student* current = studentsHead;
    cout << endl;
    cout << "\t\t\t ALL STUDENT DETAILS\n";
    cout << "--------------------------------------------------------------------------------" << endl;

    while (current != nullptr) {
        cout << "----------------------" << endl;
        cout << "Roll Number: " << current->rollno << endl;
        cout << "Name: " << current->name << endl;
        cout << "Father's Name: " << current->fname << endl;
        cout << "Contact Number: " << current->cell << endl;
        cout << "Date of Birth: " << current->dob << endl;
        cout << "Address: " << current->address << endl;
        // Display individual subject marks, grades, and attendance
        cout << endl;
        SubjectNode* subjectNode = current->subjectsHead;
        while (subjectNode != nullptr) {
            cout << "Subject: " << subjectNode->subject << endl;
            cout << "Marks: " << subjectNode->marks << endl;
            cout << "Grade: " << calculateGrade(subjectNode->marks) << endl;
            cout << "Attendance: " << subjectNode->attendance << "%" << endl;
            cout << "----------------------" << endl;
            subjectNode = subjectNode->next;
        }

        current = current->next;
    }
}
// Sorting algorithms
void bubbleSort() {
    if (studentsHead == nullptr || studentsHead->next == nullptr) {
        cout << "Nothing to sort. List is empty or has only one element." << endl;
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Student* current = studentsHead;
        Student* nextNode = studentsHead->next;

        while (nextNode != nullptr) {
            if (current->rollno > nextNode->rollno) {
                swap(current->rollno, nextNode->rollno);
                swapped = true;
            }

            current = nextNode;
            nextNode = nextNode->next;
        }
    } while (swapped);

    cout << "Students sorted by Roll Number using Bubble Sort." << endl;
}
void quickSort(Student* left, Student* right) {
    if (left == nullptr || right == nullptr || left == right || left->next == right) {
        return;
    }

    int pivot = left->rollno;
    Student* i = left;
    Student* j = left->next;

    while (j != nullptr && j != right->next) {
        if (j->rollno < pivot) {
            i = i->next;
            swap(i->rollno, j->rollno);
        }
        j = j->next;
    }

    swap(left->rollno, i->rollno);

    quickSort(left, i);
    quickSort(i->next, right);
}
void sortByRollNumberQuickSort() {
    Student* tail = studentsHead;
    while (tail != nullptr && tail->next != nullptr) {
        tail = tail->next;
    }

    quickSort(studentsHead, tail);

    cout << "Students sorted by Roll Number using Quick Sort." << endl;
}
// ----------------------------------TEACHER FUNCTIONS-------------------------------------------------------------------
void teacherFunctions() {
    int choice, TEACHER;
    string  password, subject;

    do {
        cout << "\n\t\tTeacher Functions" << endl;
        cout << "\t\t----------------" << endl;
        cout << "\t\t1-Log In" << endl;
        cout << "\t\t2-Return to Main Menu" << endl;  // Updated option to return to the main menu
        cout << "\t\t----------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: // Log In
            cout << "Enter your Teacher ID: ";
            cin >> TEACHER;
            cout << "Enter your Password: ";
            cin >> password;
            cout << "\t\tNote: Enter Correct Subject!" << endl;
            cout << "Enter your Subject: ";
            cin >> subject;
            if (authenticateTeacher(TEACHER, password)) {
                cout << endl;
                cout << "Log In Successful." ;

                // Continue with other teacher functions (enter student marks, mark attendance, etc.)
                do {
                    cout << "\n\t\t----------------";
                    cout << "\n\t\t1-Enter Student Marks" << endl;
                    cout << "\t\t2-Mark Attendance" << endl;
                    cout << "\t\t3-View Personal Details" << endl;
                    cout << "\t\t4-Modify Attendance And Marks" << endl;
                    cout << "\t\t5-Check Student Numbers & Grades" << endl;
                    cout << "\t\t6-Show All Students" << endl;
                    cout << "\t\t7-Log Out" << endl;  // New option to return to the teacher menu
                    cout << "\t\t----------------" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1: // Enter Student Marks
                        int studentRoll;
                        cout << "Enter the Roll Number of the Student: ";
                        cin >> studentRoll;
                        enterStudentMarks(studentRoll, TEACHER, password, subject);
                        break;
                    case 2: // Mark Attendance
                        int studentRollMarkAttendance;
                        cout << "Enter the Roll Number of the Student whose Attendance you want to mark: ";
                        cin >> studentRollMarkAttendance;
                        markAttendance(studentRollMarkAttendance);
                        break;
                    case 3: // View Personal Details
                        ViewTeacherDetails(TEACHER, password);  // Pass the username to view the details
                        break;
                    case 4: // Modify Attendance And Marks
                        int studentRollModify;
                        cout << "Enter the Roll Number of the Student: ";
                        cin >> studentRollModify;
                        modifyAttendanceAndMarks(studentRollModify,TEACHER, password, subject);  // Pass both student roll and teacher username
                        break;
                    case 5:
                        int StudentRoll;
                        cout << "Enter the Roll Number of the Student: ";
                        cin >> StudentRoll;
                        checkGradesAndAttendance(StudentRoll);
                        break;
                    case 6:
                        showAllStudents();
                        break;
                    case 7:
                        return;
                    default:
                        cout << "Invalid choice for Teacher Menu." << endl;
                    }
                } while (choice != 6);
            }
            else {
                cout << "Incorrect UserName or password. Log In Failed." << endl;
            }
            break;
        case 2: // Return to Main Menu
            return;
        default:
            cout << "Invalid choice for Teacher Functions." << endl;
        }

    } while (true);
}
void enterStudentMarks(int rollno, int teacherID, const std::string& teacherPassword, const std::string& subject) {

    // Check if the teacher is registered
    TeacherCredentials* teacherNode = teacherCredentialsHead;
    while (teacherNode != nullptr) {
        if (teacherNode->TEACHER == teacherID && teacherNode->password == teacherPassword) {
            // Teacher is authenticated, proceed to enter marks

            // Check if the subject matches the teacher's assigned subject
            Teacher* currentTeacher = teachersHead;
            while (currentTeacher != nullptr) {
                if (currentTeacher->teacherID == teacherID && currentTeacher->subject == subject) {
                    // Subject matches, proceed to enter marks

                    // Find the student
                    Student* current = studentsHead;

                    while (current != nullptr) {
                        if (current->rollno == rollno) {
                            float marks;
                            cout << "Enter Marks for " << subject << ": ";
                            cin >> marks;

                            // Add a new subject node to the linked list
                            SubjectNode* newSubjectNode = new SubjectNode(subject, marks, 0.0);
                            newSubjectNode->next = current->subjectsHead;
                            current->subjectsHead = newSubjectNode;

                            // Update the total marks for the student
                            current->marks += marks;

                            // Update the grade
                            current->grades = calculateGrade(current->marks);

                            cout << "Marks for Student with Roll Number " << rollno << " in " << subject << " Updated Successfully." << endl;
                            return;
                        }
                        current = current->next;
                    }

                    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
                    return;
                }
                currentTeacher = currentTeacher->next;
            }

            cout << "Subject " << subject << " does not match the Teacher's assigned subject." << endl;
            return;
        }
        teacherNode = teacherNode->next;
    }

    cout << "Authentication failed. You are not entering correct information." << endl;
}
void markAttendance(int rollno) {
    Student* current = studentsHead;

    while (current != nullptr) {
        if (current->rollno == rollno) {
            // Display subject-wise attendance and update only the current subject
            SubjectNode* subjectNode = current->subjectsHead;
            while (subjectNode != nullptr) {
                cout << "Enter Attendance for Subject " << subjectNode->subject << ": ";
                cin >> subjectNode->attendance;

                // Break after updating the attendance for the current subject
                break;
            }

            cout << "Attendance for student with Roll Number " << rollno << " Updated Successfully." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
}
void ViewTeacherDetails(int TEACHER, const std::string& password) {

    // Check if the teacher is registered
    TeacherCredentials* teacherNode = teacherCredentialsHead;
    while (teacherNode != nullptr) {
        if (teacherNode->TEACHER == TEACHER && teacherNode->password == password) {
            // Teacher is authenticated, find and display their details
            Teacher* current = teachersHead;
            while (current != nullptr) {
                if (current->teacherID == TEACHER) {
                    cout << endl;
                    cout << "\t\t\t TEACHER DETAILS\n";
                    cout << "--------------------------------------------------------------------------------" << endl;
                    std::cout << "Teacher ID: " << current->teacherID << endl;
                    std::cout << "Name: " << current->name << endl;
                    std::cout << "Department: " << current->department << endl;
                    std::cout << "Subject: " << current->subject << endl;
                    std::cout << "Qualification: " << current->qual << endl;
                    std::cout << "Age: " << current->age << endl;
                    cout << "--------------------------------------------------------------------------------" << endl;
                    return;
                }
                current = current->next;
            }
            std::cout << "Teacher details not found." << endl;
            return;
        }
        teacherNode = teacherNode->next;
    }
    std::cout << "Authentication failed. Only registered teachers can view their details." << endl;
}
void registerTeacher() {
    int teacherID;
    string name;
    string department;
    string subject;
    string qual;
    int age;
    string password;

    cout << "Enter your Teacher ID in the Format (2XXX): ";
    cin >> teacherID;

    // Check if the teacher is already registered
    TeacherCredentials* credNode = teacherCredentialsHead;
    while (credNode != nullptr) {
        if (credNode->TEACHER == teacherID) {
            cout << "Teacher Already Registered. Please choose a different Teacher ID." << endl;
            return;
        }
        credNode = credNode->next;
    }

    cin.ignore(); // Ignore newline character left in the buffer

    cout << "Enter Teacher Name: ";
    getline(cin, name);

    cout << "Enter Teacher Department: ";
    getline(cin, department);

    cout << "Enter Teacher Subject: ";
    getline(cin, subject);

    cout << "Enter Teacher Qualification: ";
    getline(cin, qual);

    cout << "Enter Teacher Age: ";
    cin >> age;

    cout << "Set Password: ";
    cin >> password;

    // Create a new node for teacher credentials
    TeacherCredentials* newTeacherCredNode = new TeacherCredentials{ teacherID, password, nullptr };
    if (teacherCredentialsHead == nullptr) {
        teacherCredentialsHead = newTeacherCredNode;
    }
    else {
        newTeacherCredNode->next = teacherCredentialsHead;
        teacherCredentialsHead = newTeacherCredNode;
    }

    // Create a new node for the teacher
    Teacher* newTeacherNode = new Teacher{ teacherID, name, department, subject, qual, age, password, nullptr };
    if (teachersHead == nullptr) {
        teachersHead = newTeacherNode;
    }
    else {
        newTeacherNode->next = teachersHead;
        teachersHead = newTeacherNode;
    }

    cout << "Teacher Registration Successful. Teacher Password is Set." << endl;
}
void modifyAttendanceAndMarks(int rollno, int teacherID, const std::string& teacherPassword, const std::string& subject) {
    // Find the student
    Student* current = studentsHead;

    while (current != nullptr) {
        if (current->rollno == rollno) {
            float marks;

            // Check if the subject matches the teacher's assigned subject
            Teacher* currentTeacher = teachersHead;

            while (currentTeacher != nullptr) {
                if (currentTeacher->teacherID == teacherID && currentTeacher->subject == subject) {
                    string subject = currentTeacher->subject;

                    // Update the subject node in the linked list
                    SubjectNode* subjectNode = current->subjectsHead;

                    while (subjectNode != nullptr) {
                        if (subjectNode->subject == subject) {
                            // Modify marks
                            cout << "Enter New Marks for " << subject << ": ";
                            cin >> marks;
                            subjectNode->marks = marks;

                            // Modify attendance
                            cout << "Enter New Attendance: ";
                            cin >> subjectNode->attendance;

                            cout << "Marks and Attendance for Student with Roll Number " << rollno << " in " << subject << " Updated Successfully." << endl;

                            // Break out of loops after updating
                            return;
                        }
                        subjectNode = subjectNode->next;
                    }

                    // Subject not found in the student's record
                    cout << "Subject " << subject << " not found for Student with Roll Number " << rollno << "." << endl;
                    return;
                }
                currentTeacher = currentTeacher->next;
            }

            cout << "Teacher for Student with Roll Number " << rollno << " Not Found." << endl;
            return;
        }
        current = current->next;
    }

    cout << "Student with Roll Number " << rollno << " Not Found." << endl;
}

bool authenticateTeacher(int TEACHER, const string& password) {
    TeacherCredentials* teacherNode = teacherCredentialsHead;
    while (teacherNode != nullptr) {
        if (teacherNode->TEACHER == TEACHER && teacherNode->password == password) {
            return true;
        }
        teacherNode = teacherNode->next;
    }
    return false;
}
int main() {
    int choice;

    cout << "\t\t\tWELCOME TO STUDENT MANAGEMENT SYSTEM (SMS)" << endl;
    cout << "\t\t\t------------------------------------------" << endl;
    while (true) {
        cout << "\n\t\tWhat do you want to do?" << endl;
        cout << "\t\t----------------------" << endl;
        cout << "\t\t1-Admin Functions" << endl;
        cout << "\t\t2-Teacher Functions" << endl;
        cout << "\t\t3-Student Functions" << endl;
        cout << "\t\t4-Quit Program" << endl;
        cout << "\t\t----------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: // Admin Functions
            adminFunctions();
            break;
        case 2:
            teacherFunctions();
            break;
        case 3: // Student Functions
            studentFunctions();
            break;
        case 4: // Quit Program
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
    return 0;
}