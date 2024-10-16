#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;
    
    Node(T val) : data(val), next(NULL) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(NULL) {}

    // Insert a new node at the end of the linked list
    void insert(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Accessor method to get the head of the linked list
    Node<T>* getHead() const {
        return head;
    }

    // Find a student by ID
    T* findById(const string& id) {
        Node<T>* temp = head;
        while (temp) {
            if (temp->data.getId() == id) {
                return &(temp->data);
            }
            temp = temp->next;
        }
            return NULL;
    }

    // Print all student data
    void printAll() const {
        Node<T>* temp = head;
        cout << "ID        CW Marks   FE Marks   Total      Grade\n";
        cout << "----------------------------------------------\n";
        while (temp) {
            temp->data.print();
            temp = temp->next;
        }
    }

    // Destructor to clean up memory
    ~LinkedList() {
        Node<T>* temp = head;
        while (temp) {
            Node<T>* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

#endif
