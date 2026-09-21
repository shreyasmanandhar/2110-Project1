// Resource.cpp
// Defines Resource.h.


#include "Resource.h"
#include <iomanip>
#include <iostream>
using namespace std;

// Column widths for resource table
const int ID_WIDTH = 8;
const int NAME_WIDTH = 20;
const int TYPE_WIDTH = 22;
const int STATUS_WIDTH = 11;

// constructor
Resource::Resource(const string& newId, const string& newName, const string& newType, bool newAvailable) :
    id(newId), name(newName), type(newType), available(newAvailable) {

}

// getters
const string& Resource::getId() const { return id; }
const string& Resource::getName() const { return name; }
const string& Resource::getType() const { return type; }
bool Resource::isAvailable() const { return available; }

string Resource::getStatusText() const {
    return available ? "Available" : "Unavailable";
}

void Resource::setAvailable(bool newAvailable) {
    available = newAvailable;
}

void Resource::displayRow() const {
    cout << left
         << setw(ID_WIDTH) << id
         << setw(NAME_WIDTH) << name
         << setw(TYPE_WIDTH) << type
         << getStatusText()
         << '\n';
}

void Resource::displayHeader() {
    cout << left
         << setw(ID_WIDTH) << "ID"
         << setw(NAME_WIDTH) << "Name"
         << setw(TYPE_WIDTH) << "Type"
         << "Status" << '\n';

    cout << string(ID_WIDTH + NAME_WIDTH + TYPE_WIDTH + STATUS_WIDTH, '-') << '\n';
}