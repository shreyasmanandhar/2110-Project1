/* INITIAL VERSION
Shreyas Manandhar (sm4305)
CSCE 2110 Project 1
Linked-list cpp file
Description: This defines the reservation list header file's functions.


#include "ReservationList.h"
using namespace std;

//constructor
ReservationList::ReservationList(){
    head = nullptr;
    tail = nullptr;
    count = 0;
}

//destructor
ReservationList::~ReservationList(){
    Node* current = head;
    while (current!=nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
}

//checking each node to find if student has reservation
bool ReservationList::hasReservation(const string& studentId, const string& resourceId) const{
    for (Node* current = head; current!=nullptr; current = current->next){
        if (current->data.getStudentId() == studentId && current->data.getResourceId()==resourceId){
            return true;
        }
    }
    return false;
}

//checking for a matching ID
Reservation* ReservationList::find(int id){
    for (Node* current = head; current!= nullptr; current = current->next){
        if (current->data.getId() == id){
            return &current->data;
        }
    }
    return nullptr;
}

//adding new node at the end
void ReservationList::insert(const Reservation& reservation){
    Node* newNode = new Node(reservation);
    if (head==nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    count = count+1;
}

//finding node and removing it from linkedlist
bool ReservationList::remove(int id, Reservation& removedOut){
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr && current->data.getId()!= id){
        previous = current;
        current = current->next;
    }
    if  (current==nullptr){
        return false;
    }
    removedOut = current->data;
    if (previous==nullptr){
        head = current->next;
    }
    else{
        previous->next=current->next;
    }
    if(current == tail){
        tail = previous;
    }
    delete current;
    count = count - 1;
    return true;
}

//checking if list is empty
bool ReservationList::isEmpty() const{
    return head == nullptr;
}

//printing each reservation
void ReservationList::display() const{
    for (Node* current = head; current!=nullptr; current=current->next){
        current->data.displayRow();
    }
}

*/
