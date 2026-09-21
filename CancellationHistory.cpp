#include "CancellationHistory.h"
#include <iostream>

using namespace std;

CancellationHistory::CancellationHistory() {
    topNode = nullptr;
    count = 0;
}

CancellationHistory::~CancellationHistory() {
    Node* current = topNode;
    while (current != nullptr) {
        Node* below = current->next;
        delete current;
        current = below;
    }
}

void CancellationHistory::push(const Reservation& reservation) {
    Node* newNode = new Node(reservation);
    newNode->next = topNode;
    topNode = newNode;
    count = count + 1;
}

bool CancellationHistory::pop(Reservation& out) {
    if (topNode == nullptr) {
        return false;
    }
    out = topNode->data;
    Node* oldTop = topNode;
    topNode = topNode->next;
    delete oldTop;
    count = count - 1;
    return true;
}

bool CancellationHistory::isEmpty() const {
    return topNode == nullptr;
}

void CancellationHistory::display() const {
    if (topNode == nullptr) {
        cout << "No cancelled reservations.\n";
        return;
    }
    Reservation::displayHeader();
    for (Node* current = topNode; current != nullptr; current = current->next) {
        current->data.displayRow();
    }
}
