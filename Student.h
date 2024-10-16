#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
using namespace std;

class Student {
private:
    string id;
    double courseworkMarks;
    double finalExamMarks;
    double totalMarks;

public:
    Student(string id, double coursework, double finalExam)
        : id(id), courseworkMarks(coursework), finalExamMarks(finalExam) {
        totalMarks = courseworkMarks + finalExamMarks;
    }

    string getId() const {
        return id;
    }

    double getTotalMarks() const {
        return totalMarks;
    }

    char getGrade() const {
        if (totalMarks >= 80) 
        {
            return 'A';
        }
        else if (totalMarks >= 65)
        {
            return 'B';
        }
        else if (totalMarks >= 50)
        {
            return 'C';
        } 
        else 
        {
        return 'F';
        }
    }

    void updateMarks(double coursework, double finalExam) {
        courseworkMarks = coursework;
        finalExamMarks = finalExam;
        totalMarks = courseworkMarks + finalExamMarks;
    }

    void print() const {
        cout << left << setw(10) << id
             << setw(10) << courseworkMarks
             << setw(10) << finalExamMarks
             << setw(10) << totalMarks
             << setw(5) << getGrade() << endl;
    }
};

#endif
