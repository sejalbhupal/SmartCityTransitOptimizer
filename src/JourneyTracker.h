#ifndef JOURNEYTRACKER_H
#define JOURNEYTRACKER_H
#include <iostream>
#include <string>
using namespace std;

struct StackNode { string stopName; StackNode* next; };

class JourneyStack {
private:
    StackNode* top; int size;
public:
    JourneyStack();  ~JourneyStack();
    void push(string stop);
    void pop();
    void peek();
    void displayAll();
    bool isEmpty();
    int  getSize();
};

struct QueueNode { string passengerName; QueueNode* next; };

class BoardingQueue {
private:
    QueueNode* front; QueueNode* rear; int size;
public:
    BoardingQueue();  ~BoardingQueue();
    void enqueue(string name);
    void dequeue();
    void displayLine();
    bool isEmpty();
    int  getSize();
};

#endif