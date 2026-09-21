// ReservationManager.h
// The rules for reservations are validate a request, create it, cancel it, display active ones, and restore a cancelled one for undo
// No prompts, each output is returned as a ReservationStatus, and ReservationMenu turns that output into text
// It does not own the data structures


#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <string>

// TEAMMATE ---- CancellationHistory.h not created yet.
// void push(const Reservation&) ---- used in cancelReservation()
// bool pop(Reservation&) ----needed for undo -> restoreReservation() (unwired)
#include "CancellationHistory.h"

#include "Reservation.h"

// TEAMMATE ---- ReservationList.h not created yet.
// bool hasReservation(const std::string& studentId, const std::string& resourceId) const;
// Reservation* find(int id);
// void insert(const Reservation&);
// bool remove(int id, Reservation& removedOut);
// bool isEmpty() const;
// void display() const;
#include "ReservationList.h"

#include "ResourceManager.h"

// TEAMMATE ---- WaitingList.h not created yet.
// struct WaitRequest { std::string studentId, studentName, resourceId, requestDate; };
// void addRequest(const std::string& resourceId, const WaitRequest&);
// bool popNext(const std::string& resourceId, WaitRequest& nextOut);
#include "WaitingList.h"

// most possible outcomes of the program
enum class ReservationStatus {
    Success,
    CancelledAndReassigned,
    InvalidStudentId,
    InvalidStudentName,
    InvalidDate,
    InvalidResourceId,
    DuplicateReservation,
    AddedToWaitingList,
    NotFound,
    NoActiveReservations,
    ResourceUnavailable
};

class ReservationManager {
public:
    // Stores REFERENCES to objects that already exist
    ReservationManager(ResourceManager& resourceManager, ReservationList& reservationList, WaitingList& waitList, CancellationHistory& history);

    // Validates and creates a reservation
    ReservationStatus createReservation(const std::string& studentId, const std::string& studentName, const std::string& resourceId, const std::string& date);

    // Cancels by reservation ID: removes it from the list, pushes it onto the cancellation history, frees the resource, and gives it to the next waiting student if any
    // Returns Success, CancelledAndReassigned, NoActiveReservations, or NotFound
    ReservationStatus cancelReservation(int reservationId);

    // Prints either all active reservations, or "No active reservations."
    void displayActiveReservations() const;

    // Redoes a cancelled reservation ONLY if its ID isn't already active and its resource is free
    // puts out Success, DuplicateReservation, InvalidResourceId, or ResourceUnavailable
    // Never overrides another reservation
    ReservationStatus restoreReservation(const Reservation& reservation);

private:
    // Members are initialized in this order, so the constructor's initializer list uses the same order (-Wall warns if they don't match)
    ResourceManager& inventory;
    ReservationList& activeReservations;
    WaitingList& waitingList;
    CancellationHistory& cancelHistory;
    int nextReservationId;
};

#endif