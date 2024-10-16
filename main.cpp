#include <iostream>
#include "LinkedList.h"
#include "Student.h"
#include "Utilities.h"
#include "Messages.h"

using namespace std;

int main() {
    LinkedList<Student> studentList;

    printWelcomeMessage();

    int choice;
    bool continueExecuting = true;

    programStartQuit(continueExecuting);

    // Read student data from file
    readFileAndStoreData(studentList, "studentData.txt");
	
	while (continueExecuting)
	{
		displayMenu();
        choice = ValidateUpdateMarks<int>(1, 6);

        switch (choice) {
            case 1:
                studentList.printAll();
                break;

            case 2: {
                string id;
                double coursework, finalExam;

                cout << "Enter student ID to update: ";
                cin >> id;
                while(cin.fail())
                {
                    cin.clear();
                    string dummy;
                    cin >> dummy;
                    cout << "ERROR! Invalid Input Detected." << endl;
                    cout << "Please enter letter \"S\" in uppercase followed by numbers only." << endl;
                    cin >> id;
                }

                Student* student = studentList.findById(id);
                if (student)
                {
                    updateMarkMenu();
                    int updateChoice; 
                    updateChoice = ValidateUpdateMarks<int>(1, 3);

                    switch(updateChoice){
                        case 1:
                            cout << "Enter new coursework marks (0 - 50): ";
                            coursework = ValidateUpdateMarks<double>(0.0, 50.0);
                            break;

                        case 2:
                            cout << "Enter new final exam marks (0 - 50): ";
                            finalExam = ValidateUpdateMarks<double>(0.0, 50.0);
                            break;

                        case 3:
                            cout << "Enter new coursework marks (0 - 50): ";
                            coursework = ValidateUpdateMarks<double>(0.0, 50.0);

                            cout << "Enter new final exam marks (0 - 50): ";
                            finalExam = ValidateUpdateMarks<double>(0.0, 50.0);
                            break;
                    }

                    student->updateMarks(coursework, finalExam);
                    cout << "Marks updated!\n";             } 
                else 
                {
                    cout << "Student not found.\n";
                }
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
                double average = calculateAverageMarks(studentList);
                cout << "Average Marks: " << average << endl;
                break;
            }
            
            case 6: {
                cout << "Exiting program.\n";
                endProgram(continueExecuting);
            }
        }
	}

    return 0;
}