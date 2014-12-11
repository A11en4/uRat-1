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
    /* Initializes Empty Stack */
    LifoStack();
    /* Initializes Stack with One Item */
    LifoStack(const int item);
    /* Look at most recently added item w/o removal */
    int peek();
    /* Look at most recently added item w/ removal */
    int pop();
    /* Add item to stack */
    void push(const int item);
    /* pls no */
    bool isEmpty();
};
#endif
