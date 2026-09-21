/*
Shreyas Manandhar (sm4305)
CSCE 2110 Project 1
Waitinglist header file
Description: This declares the queue that holds students waiting for resource to be available.
*/

#ifndef WAITING_LIST_H
#define WAITING_LIST_H

#include<string>

struct WaitRequest{
    std::string studentID;
    std::string studentName;
    std::string resourceID;
    std::string requestDate;
};

class WaitingList{
    public:
        WaitingList(); //constructor
        ~WaitingList(); //desctructor

        //adds request at the end of the queue
        void addRequest(const std::string& resourceID, const WaitRequest& request);

        //gets the oldest request for resource, removes and copies it to nextOut
        bool popNext(const std::string& resourceID, WaitRequest& nextOut);

        //checking is anyone is on the waitlsit
        bool isEmpty() const;

        //printing the waitlist
        void display() const;

    private:
        struct Node{
            WaitRequest data;
            Node* next;
            Node(const WaitRequest& req){
                data = req;
                next = nullptr;
            }
        };
        Node* front;
        Node* rear;
        int count;
};
#endif
