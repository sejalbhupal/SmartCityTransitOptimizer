#include "PassengerList.h"

PassengerList::PassengerList() : head(nullptr),tail(nullptr),count(0),nextTicketID(1001){}

PassengerList::~PassengerList() {
    Passenger* c=head;
    while(c){Passenger* t=c;c=c->next;delete t;}
}

void PassengerList::boardPassenger(string name, string dest) {
    Passenger* p = new Passenger();
    p->ticketID=nextTicketID++; p->name=name; p->destination=dest; p->next=nullptr;
    if(!head) head=tail=p;
    else { tail->next=p; tail=p; }
    count++;
    cout << "  [+] " << name << " boarded. Ticket: " << p->ticketID << "\n";
}

void PassengerList::alightPassenger(int id) {
    if(!head){cout<<"  [!] No passengers.\n";return;}
    if(head->ticketID==id){
        Passenger* t=head; head=head->next;
        if(!head)tail=nullptr;
        cout<<"  [-] "<<t->name<<" alighted.\n"; delete t; count--; return;
    }
    Passenger* prev=head; Passenger* curr=head->next;
    while(curr){
        if(curr->ticketID==id){
            prev->next=curr->next;
            if(curr==tail)tail=prev;
            cout<<"  [-] "<<curr->name<<" alighted.\n"; delete curr; count--; return;
        }
        prev=curr; curr=curr->next;
    }
    cout<<"  [!] Ticket "<<id<<" not found.\n";
}

void PassengerList::displayAll() {
    if(!head){cout<<"  [i] No passengers on board.\n";return;}
    cout<<"\n  === Passengers ("<<count<<") ===\n";
    Passenger* c=head; int p=1;
    while(c){cout<<"    "<<p++<<". [#"<<c->ticketID<<"] "<<c->name<<" -> "<<c->destination<<"\n";c=c->next;}
}

int  PassengerList::getCount(){return count;}
bool PassengerList::isEmpty() {return head==nullptr;}