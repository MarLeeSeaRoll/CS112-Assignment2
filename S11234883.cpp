#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Student{
	string id;
	double coursework;
	double finalExam;
	double totalMark;	
};

struct node {
    Student *studentdata;
    node *pNext;
    node *pPrev;
};

node *pHead = NULL;
node *pTail = NULL;

int validateInput(int lowerLimit, int upperLimit)
{
    int input;
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

void printWelcomeMessage()
{
    cout << "+-------------------------------------------------+\n";
    cout << "|      WELCOME TO THE STUDENT GRADES PROGRAM      |\n";
    cout << "+-------------------------------------------------+\n";
}

void endProgram(bool& continueExecuting)
{
    continueExecuting = false;

    cout << endl;
    cout << "+-------------------------------------+\n";
    cout << "|  Thank you for using this program!  |\n";
    cout << "+-------------------------------------+\n";
}

void displayMenu()
{
	cout << "Menu:" << endl;
	cout << "1. Print Entire List with Grades" << endl;
	cout << "2. Update Student's Marks" << endl;
	cout << "3. Print Average marks" << endl;
	cout << "4. Print Pass Rate" << endl;
	cout << "5. Print the Highest Scorer's Details" << endl;
	cout << "6. Exit Program" << endl;
	cout << "\nEnter the number corresponding to your choice" << endl;
}

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

void AppendNode(node *pNode) {
    if (pHead == NULL) {
        // List is empty
        pHead = pTail = pNode;
        pNode->pNext = pNode->pPrev = NULL;
    } else {
        // Append at the end
        pTail->pNext = pNode;
        pNode->pPrev = pTail;
        pNode->pNext = NULL;
        pTail = pNode;  // Correctly updating the tail
    }
}

void FreeList(node *pHead) {
    node *current = pHead;
    node *next;

    while (current != NULL) {
        next = current->pNext;
        delete current->studentdata;  // Free the Student object
        delete current;               // Free the node
        current = next;
    }
}

void fillArray(string fileName, int& rows, node*& pHead) {
    ifstream readFile(fileName.c_str());

    if (!readFile) {
        cout << "ERROR! File could not be found." << endl;
        exit(1); // Exiting as the file is not found
    } else {
        string id;
        double coursework, finalexam;
		
		string discardLine;
		getline(readFile, discardLine);

        // Read through the file and append to the linked list
        while (!readFile.eof()) {
			readFile >> id >> coursework >> finalexam;
            // Allocate and fill student object
            Student* student = new Student;
            student->id = id;
            student->coursework = coursework;
            student->finalExam = finalexam;

            // Allocate new node
            node* pNode = new node;
            pNode->studentdata = student;

            // Append to linked list
            AppendNode(pNode);
        }
    }
}

string determineGrade(double totalMark)
{
	if (totalMark >= 85)
	{
		return "A+";
	}
	else if (totalMark >= 78)
	{
		return "A";
	}
	else if (totalMark >= 71)
	{
		return "B+";
	}
	else if (totalMark >= 64)
	{
		return "B";
	}
	else if (totalMark >= 57)
	{
		return "C+";
	}
	else if (totalMark >= 50)
	{
		return "C";
	}
	else if (totalMark >= 40)
	{
		return "D";
	}
	else 
	{
		return "E";
	}
}

void printEntireList(node* pHead) {
    if (pHead == NULL) {
        cout << "The student list is empty." << endl;
        return;
    }

    cout << "\nThe Entire List of Students with Grades:" << endl;
    cout << left << setw(20) << "ID" << setw(20) << "Coursework" 
         << setw(20) << "Final Exam" << setw(20) << "Grade" << endl;
    cout << "-----------------------------------------------------------------" << endl;

    node* current = pHead;
    while (current != NULL) {
        Student* student = current->studentdata;
        student->totalMark = student->coursework + student->finalExam;
        string studentGrade = determineGrade(student->totalMark);
        
        cout << left << setw(20) << student->id << setw(20) << student->coursework 
             << setw(20) << student->finalExam << setw(20) << studentGrade << endl;
        cout << "-----------------------------------------------------------------" << endl;

        current = current->pNext;
    }
}

void updateMark(node *phead)
{
    string searchId;
    bool found = false;
    
    cout << "Please enter the ID number you would like to search for (e.g., S00005): ";
    cin >> searchId;

    // Basic input validation: Ensure ID starts with 'S' and followed by numbers
    while (cin.fail() || searchId[0] != 'S' || searchId.length() != 6)
    {
        cin.clear();
        string dummy;
        cin >> dummy;
        cout << "ERROR! Invalid Input Detected." << endl;
        cout << "Please enter ID in the format 'S' followed by 5 digits (e.g., S00005): ";
        cin >> searchId;
    }

    // Traverse the linked list to find the student with the given ID
    while (phead != NULL)
    {
        Student *studentdata = phead->studentdata;  // Initialize studentdata with the current node's student data

        if (studentdata->id == searchId)
        {
            found = true;
            const int MIN_CHOICE = 1;
            const int MAX_CHOICE = 3;
            const int MARK_UPDATE_MAX = 50;
            const int MARK_UPDATE_MIN = 0;

            cout << "\nWhich Mark Would You Like To Update?" << endl;
            cout << "1. Coursework Only" << endl;
            cout << "2. Final Exam Only" << endl;
            cout << "3. Both Coursework and Final Exam" << endl;

            int choice = validateInput(MIN_CHOICE, MAX_CHOICE);

            switch (choice)
            {
                case 1: 
                    cout << "Enter the new coursework mark: ";
                    studentdata->coursework = validateInput(MARK_UPDATE_MIN, MARK_UPDATE_MAX);
                    break;
                case 2: 
                    cout << "Enter the new final exam mark: ";
                    studentdata->finalExam = validateInput(MARK_UPDATE_MIN, MARK_UPDATE_MAX);
                    break;
                case 3: 
                    cout << "Enter the new coursework mark: ";
                    studentdata->coursework = validateInput(MARK_UPDATE_MIN, MARK_UPDATE_MAX);
                    cout << "Enter the new final exam mark: ";
                    studentdata->finalExam = validateInput(MARK_UPDATE_MIN, MARK_UPDATE_MAX);
                    break;
            }

            studentdata->totalMark = studentdata->coursework + studentdata->finalExam;
            string studentGrade = determineGrade(studentdata->totalMark);

            cout << "\nMarks Updated Successfully!" << endl;
            cout << left << setw(20) << "ID" << setw(20) << "Coursework" << setw(20) << "Final Exam" 
                 << setw(20) << "Total" << setw(20) << "Grade" << endl;
            cout << left << setw(20) << studentdata->id << setw(20) << studentdata->coursework 
                 << setw(20) << studentdata->finalExam << setw(20) << studentdata->totalMark 
                 << setw(20) << studentGrade << endl;

            break;  // Exit the loop once the student is found and marks are updated
        }

        phead = phead->pNext;  // Move to the next node
    }

    if (!found)
    {
        cout << "\nNo student was found with the ID# " << searchId << endl;
    }
}

void printAverageMarks(node *pHead)
{
    double totalMarks = 0.0;
    int studentCount = 0;

    node *current = pHead;

    while (current != NULL)
    {
        Student *studentdata = current->studentdata;
        studentdata->totalMark = studentdata->coursework + studentdata->finalExam;
        totalMarks += studentdata->totalMark;
        studentCount++;

        current = current->pNext;  // Move to the next node
    }

    if (studentCount > 0)
    {
        double averageMarks = totalMarks / studentCount;
        cout << "\nThe average mark for the class is: " << fixed << setprecision(2) << averageMarks << endl;
    }
    else
    {
        cout << "\nNo students found in the list." << endl;
    }
}

void printPassRate(node *pHead)
{
    int totalStudents = 0;      // Counter for total number of students
    int passedCounter = 0;      // Counter for students who passed

    node *current = pHead;      // Start at the head of the list

    // Traverse the linked list
    while (current != NULL) {
        Student *studentdata = current->studentdata;  // Access the student data
        studentdata->totalMark = studentdata->coursework + studentdata->finalExam;  // Calculate total mark

        if (studentdata->totalMark >= 50) {
            passedCounter++;    // Increment if the student passed
        }

        totalStudents++;        // Increment total student count
        current = current->pNext;  // Move to the next node
    }

    if (totalStudents > 0) {
        double passRate = (static_cast<double>(passedCounter) / totalStudents) * 100;  // Calculate pass rate
        cout << "\nThe pass rate of the class is " << passRate << "%" << endl;
    } else {
        cout << "\nNo students found in the list." << endl;
    }
}

void printHighestScorerDetails(node *pHead)
{
    if (pHead == NULL) {
        cout << "\nNo students found in the list." << endl;
        return;
    }

    node *current = pHead;
    node *highestScorer = pHead;

    while (current != NULL)
    {
        Student *studentdata = current->studentdata;
        studentdata->totalMark = studentdata->coursework + studentdata->finalExam;

        // Compare with the current highest scorer
        if (studentdata->totalMark > highestScorer->studentdata->totalMark)
        {
            highestScorer = current;
        }

        current = current->pNext;  // Move to the next node
    }

    // Display the highest scorer details
    Student *highestStudent = highestScorer->studentdata;
    string studentGrade = determineGrade(highestStudent->totalMark);
    
    cout << "\nHighest Scorer's Full Details:" << endl;
    cout << left << setw(20) << "ID" << setw(20) << "Coursework" 
         << setw(20) << "Final Exam" << setw(20) << "Total" 
         << setw(20) << "Grade" << endl;
    cout << left << setw(20) << highestStudent->id 
         << setw(20) << highestStudent->coursework 
         << setw(20) << highestStudent->finalExam 
         << setw(20) << highestStudent->totalMark 
         << setw(20) << studentGrade << endl;
}

int main()
{
    bool continueExecuting = true;
    
    cout << fixed << setprecision(2) << endl;
    printWelcomeMessage();
    
    programStartQuit(continueExecuting);
    
    if (continueExecuting) 
    {
        int rows = 0;
        fillArray("studentData.txt", rows, pHead);  // fill linked list once

        while (continueExecuting)
        {
            displayMenu();
            int choice = validateInput(1, 6);

            switch (choice)
            {
                case 1:
                    printEntireList(pHead);  // Print using linked list
                    break;
                case 2:
                    updateMark(pHead);  // Update marks (requires linked list modification)
                    break;
                case 3:
                    printAverageMarks(pHead);  // Calculate average marks
                    break;
                case 4:
                    printPassRate(pHead);  // Calculate pass rate
                    break;
                case 5:
					printHighestScorerDetails(pHead);  // Find highest scorer
                    break;
                case 6:
                    endProgram(continueExecuting);
                    break;
            }
        }

        FreeList(pHead);  // Clean up memory
    }

    return 0;
}
