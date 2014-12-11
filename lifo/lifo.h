/*
* LIFO Stack Implementation
* Author: Darrel Weng
*
*/

#ifndef LIFO
#define LIFO
class LifoStack {
    typedef struct Node {
        Node *prev;
        int item;
    } Node;
    typedef struct Stack {
        Node *head;
        Node *tail;
    } Stack;
    Stack bigMomma;
    int size;
public:
    LifoStack();
    LifoStack(const int item);
    int peek();
    int pop();
    void push(const int item);
    bool isEmpty();
};
#endif
