// Resource.h
// Declares the Resource class, which represents one reservable item
// A Resource only stores its own data and knows how to print itself


#ifndef RESOURCE_H
#define RESOURCE_H


#include <string>


class Resource {
public:

    // Constructor
    Resource(const std::string& newId, const std::string& newName,
             const std::string& newType, bool newAvailable);


    // Get
    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getType() const;
    bool isAvailable() const;

    // Returns the word used in resources.txt as either "Available" or "Unavailable"
    std::string getStatusText() const;

    // Setter
    void setAvailable(bool newAvailable);

    // Prints this resource as one table row
    void displayRow() const;

    // Prints column titles for a resource table
    static void displayHeader();

private:
    std::string id;
    std::string name;
    std::string type;
    bool available;
};

#endif