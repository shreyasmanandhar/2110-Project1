// ResourceManager.h
// Owns the resource inventory as vectors
// Loads resources from a text file, displays them, reports availability, and makes data available for other classes


#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <vector>
#include "Resource.h"

class ResourceManager {
public:
    // Reads resources from a pipe-delimited file (ID,Name,Type,Status), gives status for data and prints good data
    bool loadFromFile(const std::string& path);

    // Prints every resource as an aligned table, or an error if none loaded
    void displayAll() const;

    // Prints available/total counts per type, then lists all currently available resources
    void displayAvailability() const;

    // Helper lookup (linear search for right now)
    // Returns a pointer to the matching Resource so the caller can read or change it, or nullptr if no resource has that ID
    // The actual search algorithm comes in the second half of our project
    Resource* findById(const std::string& id);

    // Marks resource "id" available or unavailable
    // Returns false if there isn't a resource with that id
    bool setAvailable(const std::string& id, bool newAvailable);

private:
    std::vector<Resource> resources;
};

#endif