/*
Shreyas Manandhar (sm4305)
CSCE 2110 Project 1
Waitinglist cpp file
Description: This defines the queue that holds students waiting for resource to be available.
*/

#include "WaitingList.h"
#include <iostream>
#include <iomanip>

using namespace std;

//dimensions for printing
const int StudentID_width = 12;
const int StudentName_width = 22;
const int ResourceID_width = 12;
const int Date_width=10;

//constructor
WaitingList::WaitingList(){
    front = nullptr;
    rear = nullptr;
    count = 0;
}
//destructor
WaitingList::~WaitingList(){
    Node* current = front;
    while (current !=nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
}

//adding new node at the end fo the quwue
void WaitingList::addRequest(const string& resourceID, const WaitRequest& request){
    Node* newNode = new Node(request);
    if (rear == nullptr){
        front = newNode;
        rear = newNode;
    }
    else{
        rear->next = newNode;
        rear = newNode;
    }
    count = count+1;
}

//searching the queue starting from the front to look for the 1st match
bool WaitingList::popNext(const string& resourceID, WaitRequest& nextOut){
    Node* current = front;
    Node* previous = nullptr;
    while (current!=nullptr && current->data.resourceID!=resourceID){
        previous = current;
        current = current->next;
    }
    if (current == nullptr){
        return false;
    }
    nextOut = current->data;

    if (previous==nullptr){
        front = current->next;
    }
    else{
        previous->next=current->next;
    }

    if (current == rear){
        rear = previous;
    }

    delete current;
    count = count - 1;
    return true;
}

//checks if the wailist is empty
bool WaitingList::isEmpty() const{
    return front == nullptr;
}

//Printing the waitlist
void WaitingList::display() const{
    if (front==nullptr){
        cout << "No students are waiting.\n";
        return;
    }
    cout << left << setw(StudentID_width) << "Student ID"
         << setw(StudentName_width) << "Student Name"
         << setw(ResourceID_width) << "Resource"
         << "Request Date" << '\n';
    cout << string(58,'-') << '\n'; //12+22+12+12=58, the value of widths

    for (Node* current=front; current!= nullptr; current = current->next){
        cout << left << setw(StudentID_width) << current->data.studentID
        << setw(StudentName_width) << current->data.studentName
        << setw(ResourceID_width) << current->data.resourceID
        << current->data.requestDate << '\n';
    }
}