#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <sstream>
#include <string>
#include "LinkedList.h"
#include "Student.h"

// Function Prototypes
void programStartQuit(bool& continueExecuting);

void readFileAndStoreData(LinkedList<Student>& studentList, const string& filename);

double calculateAverageMarks(const LinkedList<Student>& studentList);

Student* getHighestScorer(LinkedList<Student>& studentList);

void programStartQuit(bool& continueExecuting)
{
    string userDecision;
    cout << "Enter S to start or Q to quit" << endl;
    cin >> userDecision;
    
    while(userDecision != "S" && userDecision != "s" && userDecision != "Q" && userDecision != "q") {
        cin.clear();
        cout << "ERROR! Invalid input detected." << endl;
        cout << "Please enter either \"S\" or \"Q\" only." << endl;
        cin >> userDecision;
    }
    
    if (userDecision == "S" || userDecision == "s")
	{
		continueExecuting = true;
	}
	else if (userDecision == "Q" || userDecision == "q")
	{
		continueExecuting = false;
	}
}

// Function Definitions
void readFileAndStoreData(LinkedList<Student>& studentList, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file!" << endl;
        return;
    }
    double coursework, finalExam;
    string id;
    string line;
    getline(file, line);
    while (file >> id >> coursework >> finalExam) {
        Student student(id, coursework, finalExam);
        studentList.insert(student);
    }
    file.close();
}

double calculateAverageMarks(const LinkedList<Student>& studentList) {
    double totalMarks = 0.0;
    int count = 0;

    Node<Student>* current = studentList.getHead();
    while (current != NULL) {
        totalMarks += current->data.getTotalMarks();
        count++;
        current = current->next;
    }

    return (count == 0) ? 0 : totalMarks / count;
}

Student* getHighestScorer(LinkedList<Student>& studentList) {
    if (!studentList.getHead())
    {
        return NULL;
    }

    Node<Student>* current = studentList.getHead();
    Student* topStudent = &(current->data);

    while (current) {
        if (current->data.getTotalMarks() > topStudent->getTotalMarks()) {
            topStudent = &(current->data);
        }
        current = current->next;
    }

    return topStudent;
}

// Valid input for updating marks
    template <typename V>
    V ValidateUpdateMarks(V lowerLimit, V upperLimit)
    {
        V input;
        cin >> input;
    
        while(input < lowerLimit || input > upperLimit || cin.fail())
        {
            if (cin.fail())
            {
                cin.clear();
                string dummy;
                cin >> dummy;
                cout << "ERROR! Invalid option detected." << endl;
                cout << "Please enter a number." << endl;
            }
            else if (input < lowerLimit || input > upperLimit)
            {
                cin.clear();
                cout << "ERROR! Your choice is not in range." << endl;
                cout << "Please enter a number between " << lowerLimit << " and " << upperLimit << endl;
            }
            cin >> input;
        }
        return input;
    }

#endif
