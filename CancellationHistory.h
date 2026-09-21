#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

#include "Reservation.h"

class CancellationHistory {
public:
    CancellationHistory();
    ~CancellationHistory();

    void push(const Reservation& reservation);

    bool pop(Reservation& out);

    bool isEmpty() const;

    void display() const;

private:
    struct Node {
        Reservation data;
        Node* next;

        Node(const Reservation& reservation) {
            data = reservation;
            next = nullptr;
        }
    };

    Node* topNode;
    int count;
};

#endif
