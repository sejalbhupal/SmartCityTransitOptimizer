#include "JourneyTracker.h"

JourneyStack::JourneyStack():top(nullptr),size(0){}
JourneyStack::~JourneyStack(){while(!isEmpty())pop();}

void JourneyStack::push(string stop){
    StackNode* n=new StackNode(); n->stopName=stop; n->next=top; top=n; size++;
    cout<<"  [+] Stop added: "<<stop<<"\n";
}
void JourneyStack::pop(){
    if(isEmpty()){cout<<"  [!] Journey empty.\n";return;}
    StackNode* t=top; top=top->next;
    cout<<"  [-] Undone: "<<t->stopName<<"\n"; delete t; size--;
}
void JourneyStack::peek(){
    if(isEmpty()) cout<<"  [i] Journey not started.\n";
    else          cout<<"  [i] Current stop: "<<top->stopName<<"\n";
}
void JourneyStack::displayAll(){
    if(isEmpty()){cout<<"  [i] Journey log empty.\n";return;}
    cout<<"\n  === Journey Log ===\n";
    StackNode* c=top; int s=size;
    while(c){cout<<"    Stop "<<s--<<": "<<c->stopName<<"\n";c=c->next;}
}
bool JourneyStack::isEmpty(){return top==nullptr;}
int  JourneyStack::getSize() {return size;}

BoardingQueue::BoardingQueue():front(nullptr),rear(nullptr),size(0){}
BoardingQueue::~BoardingQueue(){while(!isEmpty())dequeue();}

void BoardingQueue::enqueue(string name){
    QueueNode* n=new QueueNode(); n->passengerName=name; n->next=nullptr;
    if(!rear) front=rear=n;
    else{rear->next=n;rear=n;}
    size++;
    cout<<"  [+] "<<name<<" joined line. Position: "<<size<<"\n";
}
void BoardingQueue::dequeue(){
    if(isEmpty()){cout<<"  [!] Line empty.\n";return;}
    QueueNode* t=front; front=front->next;
    if(!front)rear=nullptr;
    cout<<"  [>] "<<t->passengerName<<" boarded.\n"; delete t; size--;
}
void BoardingQueue::displayLine(){
    if(isEmpty()){cout<<"  [i] Boarding line empty.\n";return;}
    cout<<"\n  === Boarding Line ("<<size<<" waiting) ===\n";
    QueueNode* c=front; int p=1;
    while(c){cout<<"    "<<p++<<". "<<c->passengerName<<"\n";c=c->next;}
}
bool BoardingQueue::isEmpty(){return front==nullptr;}
int  BoardingQueue::getSize() {return size;}