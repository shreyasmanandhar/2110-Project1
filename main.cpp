/*
Shreyas Manandhar, Jake Williamson, Samuel Smethers
CSCE 2110 Project 1
Main cpp file
Description: This right here is our main file
*/

#include<iostream>
#include<string>
#include "ResourceManager.h"
#include "ReservationList.h"
#include "WaitingList.h"
#include "CancellationHistory.h"
#include "ReservationManager.h"
#include "ReservationMenu.h"
#include "Validation.h"

using namespace std;

const string ResourceFile = "data/resources.txt";

//printing menu and reading user's choice
int promptMenuChoice(){
    cout << "\n===== CAMPUS RESOURCE RESERVATION SYSTEM =====\n"
         << "1. View Resources\n"
         << "2. View Resource Availability\n"
         << "3. Create Reservation\n"
         << "4. Cancel Reservation\n"
         << "5. View Active Reservation\n"
         << "6. View Waitlist\n"
         << "7. Undo Last Cancellation\n"
         << "8. Exit\n"
         << "Enter Choice: ";
    
    int choice = -1;
    if (!Validation::readInt(choice)){
        return -1;
    }
    return choice;
}

//for option of waitlist
void handleViewWaitingList(const WaitingList& waitingList){
    waitingList.display();
}

//for option of undo
void handleUndoCancellation(ReservationManager& reservationManager, CancellationHistory& history){
    Reservation lastCancelled;
    if(!history.pop(lastCancelled)){
        cout << "No cancellation to undo.\n";
        return;
    }

    ReservationStatus status = reservationManager.restoreReservation(lastCancelled);
    if (status == ReservationStatus::Success){
        cout << "Reservation restored successfully.\n";
    }
    else if (status == ReservationStatus::DuplicateReservation){
        cout << "Could not restore. Reservation with that ID exists.\n";
    }
    else if (status == ReservationStatus::InvalidResourceId){
        cout << "Could not restore: Resource does not exist.\n";
    }
    else if (status == ReservationStatus::ResourceUnavailable){
        cout << "Could not restore: Resource is currently unavailable.\n";
    }
}

int main(){
    ResourceManager resourceManager;
    ReservationList reservations;
    WaitingList waitList;
    CancellationHistory cancelHistory;

    if (!resourceManager.loadFromFile(ResourceFile)){
        cout << "Setup failed: Could not load resource data.\n";
        return 1;
    }

    ReservationManager reservationManager(resourceManager, reservations, waitList, cancelHistory);
    bool operating = true;
    while (operating){
        int choice = promptMenuChoice();
        switch (choice){
            case 1:
                handleViewResources(resourceManager);
                break;

            case 2:
                handleViewAvailability(resourceManager);
                break;

            case 3:
                handleCreateReservation(reservationManager);
                break;

            case 4:
                handleCancelReservation(reservationManager);
                break;

            case 5:
                handleViewActiveReservations(reservationManager);
                break;

            case 6:
                handleViewWaitingList(waitList);
                break;

            case 7:
                handleUndoCancellation(reservationManager, cancelHistory);
                break;
            
            case 8:
                cout << "Bye. Take Care.\n";
                operating = false;
                break;

            default:
                cout << "Invalid choice. Please choose a number from menu.\n";
                break;
        }
    }
    return 0;
}