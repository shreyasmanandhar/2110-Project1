
// ResourceManager.cpp
// Implements ResourceManager.h


#include "ResourceManager.h"
#include "Validation.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;


// constants and private helper functions


const size_t EXPECTED_FIELD_COUNT = 4;
const char FIELD_DELIMITER = '|';
const char COMMENT_MARKER = '#';
const int TYPE_LABEL_WIDTH = 22;
const vector<string> ALLOWED_TYPES = {"Study Room", "Laptop", "Calculator", "Lab Equipment", "Tutoring Appointment"
};


// checks types for validity
static bool isAllowedType(const string& type) {
    for (const string& allowed : ALLOWED_TYPES) {
        if (type == allowed) {
            return true;
        }
    }
    return false;
}

// Splits and trims input
static vector<string> splitLine(const string& line, char delimiter) {
    vector<string> fields;
    stringstream lineStream(line);
    string piece;

    while (getline(lineStream, piece, delimiter)) {
        fields.push_back(Validation::trim(piece));
    }
    return fields;
}

// skipped line error message
static void warnSkip(int lineNumber, const string& reason) {
    cout << "Warning (line " << lineNumber << "): " << reason
         << ". Line skipped.\n";
}

// loadFromFile
bool ResourceManager::loadFromFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error: could not open resource file \"" << path << "\".\n";
        return false;
    }

    string line;
    int lineNumber = 0;
    int skippedLines = 0;

    while (getline(file, line)) { 
        ++lineNumber;
        string cleanLine = Validation::trim(line);

        if (cleanLine.empty() || cleanLine[0] == COMMENT_MARKER) {
            continue;
        }

        vector<string> fields = splitLine(cleanLine, FIELD_DELIMITER);
        if (fields.size() != EXPECTED_FIELD_COUNT) {
            warnSkip(lineNumber, "expected " + to_string(EXPECTED_FIELD_COUNT) +
                                 " fields but found " + to_string(fields.size()));
            ++skippedLines;
            continue;
        }


        const string& id = fields[0];
        const string& name = fields[1];
        const string& type = fields[2];
        const string& statusText = fields[3];

        if (id.empty() || name.empty()) {
            warnSkip(lineNumber, "missing ID or name");
            ++skippedLines;
            continue;
        }
        if (findById(id) != nullptr) {
            warnSkip(lineNumber, "duplicate resource ID " + id);
            ++skippedLines;
            continue;
        }
        if (!isAllowedType(type)) {
            warnSkip(lineNumber, "unknown type \"" + type + "\"");
            ++skippedLines;
            continue;
        }

        bool isAvailableNow = false; 
        if (statusText == "Available") {
            isAvailableNow = true;
        } else if (statusText != "Unavailable") {
            warnSkip(lineNumber, "unknown status \"" + statusText + "\"");
            ++skippedLines;
            continue;
        }

        resources.push_back(Resource(id, name, type, isAvailableNow));
    }

    cout << "Loaded " << resources.size() << " resources ("
         << skippedLines << " lines skipped).\n";
    return true;
}


// displayAll and displayAvailability


void ResourceManager::displayAll() const {
    if (resources.empty()) {
        cout << "No resources loaded.\n";
        return;
    }
    Resource::displayHeader();
    for (const Resource& resource : resources) {
        resource.displayRow();
    }
}

void ResourceManager::displayAvailability() const {
    if (resources.empty()) {
        cout << "No resources loaded.\n";
        return;
    }

    // checks how many items exist
    cout << "Availability by type (available / total):\n";
    for (const string& type : ALLOWED_TYPES) {
        int total = 0;
        int availableCount = 0;
        for (const Resource& resource : resources) {
            if (resource.getType() == type) {
                ++total;
                if (resource.isAvailable()) {
                    ++availableCount;
                }
            }
        }
        cout << "  " << left << setw(TYPE_LABEL_WIDTH) << type
             << availableCount << " / " << total << '\n';
    }

    // lists all reservable resources
    cout << "\nCurrently available resources:\n";
    Resource::displayHeader();
    for (const Resource& resource : resources) {
        if (resource.isAvailable()) {
            resource.displayRow();
        }
    }
}


// findById and setAvailable

Resource* ResourceManager::findById(const string& id) {
    for (Resource& resource : resources) {
        if (resource.getId() == id) {
            return &resource;
        }
    }
    return nullptr;
}

bool ResourceManager::setAvailable(const string& id, bool newAvailable) {
    Resource* resource = findById(id);
    if (resource == nullptr) {
        return false;
    }
    resource->setAvailable(newAvailable);
    return true;
}