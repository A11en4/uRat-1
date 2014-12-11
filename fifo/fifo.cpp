/*
* FIFO Queue Implementation
* Author: Darrel Weng
*/

#include "fifo.h"
#include <stdlib.h>

FifoQueue::FifoQueue() {
    bigMomma.head = (Node*)malloc(sizeof(Node));
    bigMomma.tail = (Node*)malloc(sizeof(Node));
    size = 0;
}
FifoQueue::FifoQueue(const int item) {
    bigMomma.head = (Node*)malloc(sizeof(Node));
    bigMomma.tail = (Node*)malloc(sizeof(Node));
    size = 0;
    push(item);
}
int FifoQueue::peek() {
    return bigMomma.head->item;
}
int FifoQueue::pop() {
    if (!isEmpty()) {
        int val = bigMomma.head->item;
        bigMomma.head = bigMomma.head->next;
        size--;
        return val;
    } else {
        return NULL;
    }
}
void FifoQueue::push(const int item) {
    Node *dum = (Node*)malloc(sizeof(Node));
    dum->item = item;
    if (isEmpty()) {
        bigMomma.head = dum;
        bigMomma.tail = dum;
    } else {
        bigMomma.tail->next = dum;
        bigMomma.tail = bigMomma.tail->next;
    }
    size++;
}
bool FifoQueue::isEmpty() {
    if (size == 0) {
        return true;
    } else {
        return false;
    }
}
// Testing
#include <iostream>
int main() {
    FifoQueue test;
    test.push(1);
    test.push(5);
    test.push(2);
    test.push(10);
    test.push(3234);
    test.push(7);
    std::cout << "Test 1" << std::endl;
    while(!test.isEmpty()) {
        std::cout << test.pop() << std::endl;
    }
    test.push(1);
    test.push(5);
    test.push(2);
    test.push(10);
    test.push(3234);
    test.push(7);
    std::cout << "Test 1" << std::endl;
    while(!test.isEmpty()) {
        std::cout << test.pop() << std::endl;
    }
    FifoQueue check(3);
    check.push(5);
    check.push(2);
    check.push(4);
    int foo;
    std::cout << "Test 2" << std::endl;
    while(!check.isEmpty()) {
        std::cout << check.peek() << std::endl;
        foo = check.pop();
    }
}
