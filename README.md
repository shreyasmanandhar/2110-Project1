# Overview
**Foundations of Data Structures CSCE 2110 - Project 1, <ins>Final Submission</ins>**

This project is intended to provide a Campus Resource Reservation Management System to allow users to; make reservations of campus resources, create and cancel reservations, track history of reservations, generate reports, search and sort resources, and manage wait lists.

The project applies data structures, algorithms, including linked lists, queues, stacks, linear search, and merge sort, to manage operations.

## Functionality Description

The program will interface with the user from the main.cpp file using a loop to present the user with options to chose from a menu.

- **Resource Management:** `Resource` and `ResourceManager` store resource information loaded from data files and support viewing, searching, and sorting resources.
- **Reservation Management:** `Reservation` and `ReservationManager` handle reservation data, validation, creation, and cancellation. A linked list allows dynamic insertion and deletion of reservations.
- **Waiting List:** `WaitingList` uses a first-in, first-out (FIFO) queue to maintain the order of students waiting for resources.
- **Cancellation History:** `CancellationHistory` uses a last-in, first-out (LIFO) stack to store cancelled reservations and support restoring the most recent cancellation.
- **Input Validation:** The validation files check user inputs and data formats to ensure that the information entered is valid.
- **Searching and Sorting:** Linear search is used to find resources by ID, while merge sort displays resources alphabetically by name.
- **System Reports:** The reporting functions either display the number of reservations for each resource or the number of students currently waiting for each resource.

### Project Structure

* data/ : stores resources and reservation data files
* include/ : contains the C++ header files
* src/ : contains the C++ source files (it also includes main.cpp that provides the main menu and integrates the system's operations)

### Requirements & Dependencies

* Linux Environment with terminal
* C++ compiler (g++ was used during development adn testing)
* Project source files and required data files
* <ins>Note</ins>: This program is designed for and debugged in the UNT CELL machine environment and is recommended that the user runs the program there.

## Setup and Execution

### Compiling the Program
* Navigate to the main project directory and execute the following command (not required but preferred for efficiency, and the user may rename the output file based on their preference): `g++ -std=c++11 -Wall -Wextra -Iinclude src/*.cpp -o test_output`
* If the compilation is successful, an executable file named `text_output` will be created in the prohect directory.

### Running the Program
* After successful compilation, to execute the program, run the following command in the terminal: `./test_output`

## Data File Format
* The system uses two text files, resources.txt and reservations.txt, stored in the data/ directory. Each record is stored on a separate line, with fields separated by a vertical bar (|).

* Resource Data (resources.txt): `ResourceID | ResourceName | ResourceType | AvailabilityStatus`
* Reservation Data (reservations.txt): `ReservationID | StudentID | StudentName | ResourceID | Date`
* Dates follow the MM/DD/YYYY format. Resource IDs must match existing resources in the system. Data files should follow the specified format to ensure they are loaded correctly.

## Help

Common problems
* Having the header files or code files in an inaccessible repository or folder.
   - if you are in the cell machine run the command ls and make sure all the files are listed
   - if you are in an editor like Visual Studio make sure you can view all files in the explorer
* Not being in a UNT CELL machine with proper access.
   - UNT CELL machines have a firewall that has geographical access so make sure you are logged into a computer on the engineering campus or have logged into the CELL with two factor authentification on the DOU mobile app.


## Authors

* Team Leader: Shreyas Manadhar
* Email: ShreyasManandhar@my.unt.edu
----------
* Member: Tucker Williamson
* Email: JakeWilliamson@my.unt.edu
----------
* Member: Samuel Smethers
* Email: SamuelSmethers@my.unt.edu


## Version History

* 0.1 – Milestone 1
    * This version is the Initial Release and is the core functionality of the full system.
* 0.2 – Final Submission
    * Added resource seraching using linear search.
    * Added resource sorthing using merge sort (alphabetical sorting of names).
    * Added system reporting functionality.
    * Completed system integration and documentation.

## THANK YOU
