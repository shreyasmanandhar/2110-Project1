// ReservationMenu.cpp
// Implements ReservationMenu.h

#include "ReservationMenu.h"
#include "Validation.h"
#include <iostream>
#include <string>

using namespace std;


// private helpers

// trims whitespace and returns input
static string promptLine(const string& label) {
    cout << label;
    string input;
    getline(cin, input);
    return Validation::trim(input);
}

// gives error messages for bad outcomes
// Success it printed by the caller so this doesn't do that
static void printStatusMessage(ReservationStatus status) {
    switch (status) {   // Jump to the case that matches 'status'.
        case ReservationStatus::InvalidStudentId:
            cout << "Invalid student ID. Use digits only (example: 1001).\n";
            break;      // Leave the switch. Without break, the next case runs too.
        case ReservationStatus::InvalidStudentName:
            cout << "Invalid student name. Use letters, spaces, hyphens, or apostrophes.\n";
            break;
        case ReservationStatus::InvalidDate:
            cout << "Invalid date. Enter a real date as MM/DD/YYYY.\n";
            break;
        case ReservationStatus::InvalidResourceId:
            cout << "Invalid resource ID. No resource has that ID.\n";
            break;
        case ReservationStatus::DuplicateReservation:
            cout << "Duplicate reservation. This student already holds this resource.\n";
            break;
        case ReservationStatus::AddedToWaitingList:
            cout << "Resource is unavailable. Added to waiting list.\n";
            break;
        case ReservationStatus::NotFound:
            cout << "Reservation not found.\n";
            break;
        case ReservationStatus::NoActiveReservations:
            cout << "No active reservations.\n";
            break;
        case ReservationStatus::ResourceUnavailable:
            cout << "Resource is currently unavailable.\n";
            break;
        default:
            break;
    }
}


// public handlers


void handleViewResources(const ResourceManager& resourceManager) {
    resourceManager.displayAll();
}

void handleViewAvailability(const ResourceManager& resourceManager) {
    resourceManager.displayAvailability();
}

void handleCreateReservation(ReservationManager& reservationManager) {

    string studentId = promptLine("Student ID: ");
    string studentName = promptLine("Student Name: ");
    string resourceId = promptLine("Resource ID: ");
    string date = promptLine("Reservation Date (MM/DD/YYYY): ");


    ReservationStatus status =
        reservationManager.createReservation(studentId, studentName, resourceId, date);


    if (status == ReservationStatus::Success) {
        cout << "Reservation Created Successfully.\n";
    } else {
        printStatusMessage(status);
    }
}

void handleCancelReservation(ReservationManager& reservationManager) {
    cout << "Reservation ID: ";
    int reservationId = 0;
    if (!Validation::readInt(reservationId)) {
        cout << "Invalid input. Reservation ID must be a number.\n";
        return;
    }

    ReservationStatus status = reservationManager.cancelReservation(reservationId);

    if (status == ReservationStatus::Success ||
        status == ReservationStatus::CancelledAndReassigned) {
        cout << "Reservation Cancelled.\n";
        cout << "Added to cancellation history.\n";
        if (status == ReservationStatus::CancelledAndReassigned) {
            cout << "Resource assigned to the next student on the waiting list.\n";
        }
    } else {
        printStatusMessage(status);
    }
}

void handleViewActiveReservations(const ReservationManager& reservationManager) {
    reservationManager.displayActiveReservations();
}

void handleSearchResourceById(ResourceManager& resourceManager) {
    string resourceId = promptLine("Resource ID: ");

    // linear search, implemented inside of ResourceManager::findById
    Resource* found = resourceManager.findById(resourceId);

    if (found == nullptr) {
        cout << "No resource found with ID \"" << resourceId << "\".\n";
        return;
    }

    Resource::displayHeader();
    found->displayRow();
}

void handleViewResourcesSortedName(const ResourceManager& resourceManager){
    resourceManager.displaySortedName();
}