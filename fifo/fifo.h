/*
* FIFO Queue Implementation
* Author: Darrel Weng
*
*/

#ifndef FIFO
#define FIFO
class FifoQueue {
    typedef struct Node {
        Node *next;
        int item;
    } Node;
    typedef struct Queue {
        Node *head;
        Node *tail;
    } Queue;
    Queue bigMomma;
    int size;
public:
    FifoQueue();
    FifoQueue(const int item);
    int peek();
    int pop();
    void push(const int item);
    bool isEmpty();
};
#endif
