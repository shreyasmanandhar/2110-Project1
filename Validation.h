
// Validation.h
// A resource loader and some helpers


#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

namespace Validation {

// strips text of whitespace
std::string trim(const std::string& text);

// makes sure what you entered makes sense (no letters, only numbers)
bool isValidStudentId(const std::string& studentId);

// Verifies that you entered something other than whitespace after stripping
bool isValidStudentName(const std::string& studentName);

// Checks date format integrity
bool isValidDate(const std::string& date);

// slightly more sophisticated than usual "make sure it's a number" reasoning
bool readInt(int& out);

}

#endif