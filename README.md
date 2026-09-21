# Overview
Foundations of Data Structures CSCE 2110 - Project 1

This project is intended to provide a Campus Resource Reservation Management System to allow users to; make reservations of campus resources, track history of reservations, generate reports and manage wait lists.

## Functionality Description

The program will interface with the user from the main.cpp file using a loop to present the user with options to chose from.

* It will handle Resources in the files Resource.h/Resource.cpp and ResourceManager by creating object data types that will store all the information for a resource such as Study rooms and will accept the input from a file. It will also allow for searching and sorting of the resources.
* The Reservation data is an object created by using Reservation files to hold all of the information and handled by the ReservationManager files to store them in a linked list for dynamic size and insertion and deletion, run validation of reservations, and manage cancellation. The ReservationManager links a lot of the functions of the program together.
* The Students are stored in a queue using first in first out order in the files named WaitList to maintain order for who gets the next resource.
* The Cancelled reservations are removed from the linked lists and stored in a stack for history, which is last in first out order so that the most recent cancellations could be restored first by the ReservationManager. These files are titled CancellationHistory.
* Last but not least is the Validation files that check input and read data to make sure it is valid for the programs storage types and correct for the location the data is to be stored in, such as an ID to actually be an ID.


### Dependencies

* This program is designed for and debugged in the UNT CELL machine environment and requires the user to run the program there.


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

* 0.1
    * The current version is the Initial Release and is the core functionality of the full system.


## Acknowledgments

Credit user Dominique Pizzie for Read me template.
* [DomPizzie Template](https://gist.github.com/DomPizzie/7a5ff55ffa9081f2de27c315f5018afc#file-readme-template-md)
