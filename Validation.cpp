// Validation.cpp
// PURPOSE: Implements Validation.h


#include "Validation.h"
#include <cctype>
#include <iostream>
#include <limits>
using namespace std; 

namespace Validation { 

// constants
const string WHITESPACE = " \t\r\n";
const size_t DATE_LENGTH = 10;
const size_t FIRST_SLASH = 2;
const size_t SECOND_SLASH = 5;
const size_t MONTH_START = 0;
const size_t DAY_START = 3;
const size_t YEAR_START = 6;
const size_t TWO_DIGITS = 2;
const size_t FOUR_DIGITS = 4;

const int MONTHS_IN_YEAR = 12;
const int FEBRUARY = 2;
const int FEBRUARY_LEAP_DAYS = 29;
const int DAYS_IN_MONTH[MONTHS_IN_YEAR] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


// trim, student ID, student name


string trim(const string& text) {
    size_t first = text.find_first_not_of(WHITESPACE);
    if (first == string::npos) {
        return "";
    }
    size_t last = text.find_last_not_of(WHITESPACE); 
    return text.substr(first, last - first + 1);
}

bool isValidStudentId(const string& studentId) {
    if (studentId.empty()) {
        return false;
    }
    for (char c : studentId) { 
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool isValidStudentName(const string& studentName) {
    string name = trim(studentName);
    if (name.empty()) {
        return false;
    }
    for (char c : name) {
        bool isLetter = isalpha(static_cast<unsigned char>(c)) != 0;
        bool isAllowedSymbol = (c == ' ' || c == '-' || c == '\'');
        if (!isLetter && !isAllowedSymbol) {
            return false;
        }
    }
    return true;
}

// Section 3: dates

bool isValidDate(const string& date) {
    // checks date formatting
    if (date.size() != DATE_LENGTH) {
        return false;
    }
    for (size_t i = 0; i < date.size(); ++i) {
        if (i == FIRST_SLASH || i == SECOND_SLASH) {
            if (date[i] != '/') {
                return false;
            }
        } else if (!isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }

    // turn the digit groups into numbers
    int month = stoi(date.substr(MONTH_START, TWO_DIGITS));
    int day = stoi(date.substr(DAY_START, TWO_DIGITS));
    int year = stoi(date.substr(YEAR_START, FOUR_DIGITS));

    // rechecks date format integrity
    if (month < 1 || month > MONTHS_IN_YEAR) {
        return false;
    }
    int daysAllowed = DAYS_IN_MONTH[month - 1];

    // Leap year rule (I know this is a weird exception, it caused a really weird bug in a code I made once and I refuse to fight with that again)
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == FEBRUARY && isLeapYear) {
        daysAllowed = FEBRUARY_LEAP_DAYS;
    }
    return day >= 1 && day <= daysAllowed;
}

// safe number user input
bool readInt(int& out) {
    int value = 0;
    cin >> value;

    if (cin.fail()) {
        if (cin.eof()) {
            return false;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    out = value;
    return true;
}

}