// Reservation.h
// Declares the Reservation class: ONE booking of one resource by one student on one date. 
// Basically just a printable data record. ReservationManager does all of the actual lifting.


#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

class Reservation {
public:
    // Default constructor
    Reservation();

    // filled out constructor.
    Reservation(int newId, const std::string& newStudentId, const std::string& newStudentName, const std::string& newResourceId, const std::string& newDate);

    // Get
    int getId() const;
    const std::string& getStudentId() const;
    const std::string& getStudentName() const;
    const std::string& getResourceId() const;
    const std::string& getDate() const;

    // Prints reservation
    void displayRow() const;

    // prints headers for reservation display
    static void displayHeader();

private:
    int id;
    std::string studentId;
    std::string studentName;
    std::string resourceId;
    std::string date;
};

#endif