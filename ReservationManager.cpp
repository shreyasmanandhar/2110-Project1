// ReservationManager.cpp
// PURPOSE: Implements ReservationManager


#include "ReservationManager.h"
#include "Validation.h"
#include <iostream>
#include <algorithm> //ss
#include <iomanip> //ss
#include <vector> //debug-sm

using namespace std;

const int FIRST_RESERVATION_ID = 301;

// constructor

ReservationManager::ReservationManager(ResourceManager& resourceManager, ReservationList& reservationList, WaitingList& waitList, CancellationHistory& history) : 
    inventory(resourceManager), activeReservations(reservationList), waitingList(waitList), cancelHistory(history), nextReservationId(FIRST_RESERVATION_ID) {
}

// create reservation, 

ReservationStatus ReservationManager::createReservation(const string& studentId, const string& studentName, const string& resourceId, const string& date) {
    // validate typed input. Return the FIRST problem found
    if (!Validation::isValidStudentId(studentId)) {
        return ReservationStatus::InvalidStudentId;
    }
    if (!Validation::isValidStudentName(studentName)) {
        return ReservationStatus::InvalidStudentName;
    }
    if (!Validation::isValidDate(date)) {
        return ReservationStatus::InvalidDate;
    }

    // ensure the resource exists
    Resource* resource = inventory.findById(resourceId);
    if (resource == nullptr) {
        return ReservationStatus::InvalidResourceId;
    }

    // checks before availability so nobody has the same reservation twice. (currently linear search)
    if (activeReservations.hasReservation(studentId, resourceId)) {
        return ReservationStatus::DuplicateReservation;
    }

    // identifies if a resource is taken and gives it to the queue if it is
    if (!resource->isAvailable()) {
        WaitRequest request;
        request.studentID = studentId;
        request.studentName = studentName;
        request.resourceID = resourceId;
        request.requestDate = date;
        waitingList.addRequest(resourceId, request);
        return ReservationStatus::AddedToWaitingList;
    }

    // creates reservation, skips active ids
    while (activeReservations.find(nextReservationId) != nullptr) {
        ++nextReservationId;
    }
    Reservation reservation(nextReservationId, studentId, studentName, resourceId, date);
    ++nextReservationId;

    activeReservations.insert(reservation);
    resource->setAvailable(false);
    resource->updateResCnt(); //call function on resource to update count when reserved
    return ReservationStatus::Success;
}

// Cancel reservation
// SHREYAS ---- linked list section

ReservationStatus ReservationManager::cancelReservation(int reservationId) {
    // makes sure there is a reservation to cancel
    if (activeReservations.isEmpty()) {
        return ReservationStatus::NoActiveReservations;
    }

    // try to remove reservation
    Reservation removed;
    if (!activeReservations.remove(reservationId, removed)) {
        return ReservationStatus::NotFound;
    }

    // when removed, saves history and frees resource
    cancelHistory.push(removed);
    const string resourceId = removed.getResourceId();  // Copy, used below.
    inventory.setAvailable(resourceId, true);

    // checks the line for more waiting people
    // PLEASE use the variable nextRequest because next is a c++ keyword and that sounds annoying to debug
    WaitRequest nextRequest;
    if (waitingList.popNext(resourceId, nextRequest)) {
        ReservationStatus result = createReservation(nextRequest.studentID, nextRequest.studentName, nextRequest.resourceID, nextRequest.requestDate);
        if (result == ReservationStatus::Success) {
            return ReservationStatus::CancelledAndReassigned;
        }
        // If it failed, it's dropped and the resource stays free
    }

    return ReservationStatus::Success;
}

// displayActiveReservations
// SHREYAS ---- ReservationList::display (linked list)


void ReservationManager::displayActiveReservations() const {
    if (activeReservations.isEmpty()) {
        cout << "No active reservations.\n";
        return;
    }
    Reservation::displayHeader();
    activeReservations.display();
}


// restoreReservation (undo hook)
// SHREYAS ---- ReservationList::find (linked list)


ReservationStatus ReservationManager::restoreReservation(const Reservation& reservation) {
    // Checks if there is already a reservation with that id
    if (activeReservations.find(reservation.getId()) != nullptr) {
        return ReservationStatus::DuplicateReservation;
    }

    // checks if the resource no longer exists in the inventory
    Resource* resource = inventory.findById(reservation.getResourceId());
    if (resource == nullptr) {
        return ReservationStatus::InvalidResourceId;
    }

    // checks if someone else holds the resource
    if (!resource->isAvailable()) {
        return ReservationStatus::ResourceUnavailable;
    }

    // puts the original reservation back and mark the resource taken.
    activeReservations.insert(reservation);
    resource->setAvailable(false);
    resource->updateResCnt();
    return ReservationStatus::Success;
}

//add function to display the resources in the waiting list and how many of each , Samuel
// function to remove duplicates from copy vector
vector<string> uniqueStrings(vector<string> input) 
{
    sort(input.begin(), input.end());
    input.erase(unique(input.begin(), input.end()), input.end());
    return input;
}
 
//function for handling the sorted and simmed vector
void ReservationManager::WaitingListReport()
{
    vector<string> waitlistRec = waitingList.getWaitingResourceIds(); //collect waitinglist resources
    if (waitlistRec.empty()){
        cout << "No students are currently on the waiting list." << endl;
        return;
    }
    vector<string> resourceFinal = uniqueStrings(waitlistRec);
    vector<int> countArr(resourceFinal.size(),0);

    int i,j;

    for(i = 0; i < resourceFinal.size(); ++i)
    {
        countArr[i]=0;
        for( j = 0; j < waitlistRec.size(); ++j)
        {
            if(resourceFinal.at(i) == waitlistRec.at(j))
            {
                countArr[i] += 1;
            }
        }
    }

    
    cout << "Resource Id and Number of students waiting"<<endl;
    cout << setw(40)<<setfill('-')<<'-'<<endl;

    for(i =0; i < resourceFinal.size(); ++i)
    {
        cout<< setw(40)<<setfill(' ')<< left<< resourceFinal.at(i)<< right << "#" <<countArr[i]<<endl;
    }

}
