/* INITIAL VERSION
Shreyas Manandhar (sm4305)
CSCE 2110 Project 1
Linked-list Header file
Description: I am declaring ReservationList, a singly linked-list that holds reservation records that are active currently.


#ifndef RESERVATION_LIST_H
#define RESERVATION_LIST_H

#include <string>
#include "Reservation.h"

class ReservationList{
	public:
		ReservationList(); //constructor
		~ReservationList(); //destructor
		
		//checking if student already had reservation for the resource
		bool hasReservation(const std::string& studentId, const std::string& resourceId) const;
		
		//finding reservation by ID -- gives nullptr if not found in the list
		Reservation* find(int id);

		//adding reservation to the end of the list
		void insert(const Reservation& reservation);

		//removing reservation based on id, copies in removedout before deleting, false if id not found
		bool remove(int id, Reservation& removedOut);

		//gives true is list is empty
		bool isEmpty() const;

		//prints resources from the lits
		void display() const;

	private:
		struct Node{
			Reservation data;
			Node* next;
			Node(const Reservation& res){
				data=res;
				next=nullptr;
			}
		};
		Node* head;
		Node* tail;
		int count;
};
#endif

*/
