#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <sstream>
#include <string>
#include "LinkedList.h"
#include "Student.h"

// Function Prototypes
void readFileAndStoreData(LinkedList<Student>& studentList, const string& filename);

double calculateAverageMarks(const LinkedList<Student>& studentList);

Student* getHighestScorer(LinkedList<Student>& studentList);

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
    while (current != nullptr) {
        totalMarks += current->data.getTotalMarks();
        count++;
        current = current->next;
    }

    return (count == 0) ? 0 : totalMarks / count;
}

Student* getHighestScorer(LinkedList<Student>& studentList) {
    if (!studentList.getHead()) return nullptr;

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

#endif
