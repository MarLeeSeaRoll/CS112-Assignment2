#include <iostream>
#include "LinkedList.h"
#include "Student.h"
#include "Utilities.h"

using namespace std;

int main() {
    LinkedList<Student> studentList;

    // Read student data from file
    readFileAndStoreData(studentList, "studentData.txt");

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Print All Students\n";
        cout << "2. Update Student Marks\n";
        cout << "3. Show Highest Scorer\n";
        cout << "4. Calculate Average Marks\n";
        cout << "5. Calculate Pass Rate\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                studentList.printAll();
                break;

            case 2: {
                string id;
                double coursework, finalExam;
                cout << "Enter student ID to update: ";
                cin >> id;

                Student* student = studentList.findById(id);
                if (student) {
                    cout << "Enter new coursework and final exam marks: ";
                    cin >> coursework >> finalExam;
                    student->updateMarks(coursework, finalExam);
                    cout << "Marks updated!\n";
                } else {
                    cout << "Student not found.\n";
                }
                break;
            }

            case 3: {
                Student* topStudent = getHighestScorer(studentList);
                if (topStudent) {
                    cout << "Highest Scorer:\n";
                    topStudent->print();
                } else {
                    cout << "No students found.\n";
                }
                break;
            }

            case 4: {
                double average = calculateAverageMarks(studentList);
                cout << "Average Marks: " << average << endl;
                break;
            }

            case 5: {

            }

            case 6:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid option!\n";
        }

    } while (choice != 0);

    return 0;
}
