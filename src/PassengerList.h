#ifndef PASSENGERLIST_H
#define PASSENGERLIST_H

#include <iostream>
#include <string>
using namespace std;

struct Passenger {
    int ticketID;
    string name;
    string destination;
    Passenger* next;
};

class PassengerList {
private:
    Passenger* head;
    Passenger* tail;
    int count;
    int nextTicketID;
public:
    PassengerList();
    ~PassengerList();
    void boardPassenger(string name, string destination);
    void alightPassenger(int ticketID);
    void displayAll();
    int  getCount();
    bool isEmpty();
};

#endif