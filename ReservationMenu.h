// ReservationMenu.h
// prompts the user, calls ResourceManager or ReservationManager, and prints the result
// main.cpp's menu loop only has to call these, so your features need no logic inside main.cpp


#ifndef RESERVATION_MENU_H
#define RESERVATION_MENU_H

#include "ReservationManager.h"
#include "ResourceManager.h"

// Shows every resource in a table
void handleViewResources(const ResourceManager& resourceManager);

// Shows per-type counts and the list of available resources
void handleViewAvailability(const ResourceManager& resourceManager);

// Asks for student ID, name, resource ID, and date, then tries to reserve
void handleCreateReservation(ReservationManager& reservationManager);

// Asks for a reservation ID, then tries to cancel it
void handleCancelReservation(ReservationManager& reservationManager);

// Shows all active reservations
void handleViewActiveReservations(const ReservationManager& reservationManager);

// Asks for a resource ID, linear searches it, and shows the result
void handleSearchResourceById(ResourceManager& resourceManager);

#endif