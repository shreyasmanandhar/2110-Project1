
// Reservation.cpp
// Reservation.h function implementations.


#include "Reservation.h"
#include <iomanip>
#include <iostream>

using namespace std;

// Column widths for the reservation table.
const int RES_ID_WIDTH = 8;
const int STUDENT_ID_WIDTH = 12;
const int STUDENT_NAME_WIDTH = 22;
const int RESOURCE_ID_WIDTH = 12;
const int DATE_WIDTH = 10;

// Default constructor
Reservation::Reservation() : id(0) {
}
// filled constructor
Reservation::Reservation(int newId, const string& newStudentId, const string& newStudentName, const string& newResourceId, const string& newDate) :
     id(newId), studentId(newStudentId), studentName(newStudentName), resourceId(newResourceId), date(newDate) {
}

// Get
int Reservation::getId() const { return id; }
const string& Reservation::getStudentId() const { return studentId; }
const string& Reservation::getStudentName() const { return studentName; }
const string& Reservation::getResourceId() const { return resourceId; }
const string& Reservation::getDate() const { return date; }

// Displays table row 
void Reservation::displayRow() const {
    cout << left
         << setw(RES_ID_WIDTH) << id
         << setw(STUDENT_ID_WIDTH) << studentId
         << setw(STUDENT_NAME_WIDTH) << studentName
         << setw(RESOURCE_ID_WIDTH) << resourceId
         << date << '\n';
}

// header display
void Reservation::displayHeader() {
    cout << left
         << setw(RES_ID_WIDTH) << "Res ID"
         << setw(STUDENT_ID_WIDTH) << "Student ID"
         << setw(STUDENT_NAME_WIDTH) << "Student Name"
         << setw(RESOURCE_ID_WIDTH) << "Resource"
         << "Date" << '\n';
    cout << string(RES_ID_WIDTH + STUDENT_ID_WIDTH + STUDENT_NAME_WIDTH +
                   RESOURCE_ID_WIDTH + DATE_WIDTH, '-')
         << '\n';
}