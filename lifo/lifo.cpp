/*
* Lifo Stack Implementation
* Author: Darrel Weng
*/

#include "lifo.h"
#include <stdlib.h>

LifoStack::LifoStack() {
    bigMomma.head = (Node*)malloc(sizeof(Node));
    bigMomma.tail = (Node*)malloc(sizeof(Node));
    size = 0;
}
LifoStack::LifoStack(const int item) {
    bigMomma.head = (Node*)malloc(sizeof(Node));
    bigMomma.tail = (Node*)malloc(sizeof(Node));
    size = 0;
    push(item);
}
int LifoStack::peek() {
    return bigMomma.tail->item;
}
int LifoStack::pop() {
    if (!isEmpty()) {
        int val = bigMomma.tail->item;
        bigMomma.tail = bigMomma.tail->prev;
        size--;
        return val;
    } else {
        return NULL;
    }
}
void LifoStack::push(const int item) {
    Node *dum = (Node*)malloc(sizeof(Node));
    dum->item = item;
    if (isEmpty()) {
        bigMomma.head = dum;
        bigMomma.tail = dum;
    } else {
        dum->prev = bigMomma.tail;
        bigMomma.tail = dum;
    }
    size++;
}
bool LifoStack::isEmpty() {
    if (size == 0) {
        return true;
    } else {
        return false;
    }
}
// Testing
// #include <iostream>
// int main() {
//     LifoStack test;
//     test.push(1);
//     test.push(5);
//     test.push(2);
//     test.push(10);
//     test.push(3234);
//     test.push(7);
//     std::cout << "Test 1" << std::endl;
//     while(!test.isEmpty()) {
//         std::cout << test.pop() << std::endl;
//     }
//     test.push(1);
//     test.push(5);
//     test.push(2);
//     test.push(10);
//     test.push(3234);
//     test.push(7);
//     std::cout << "Test 1" << std::endl;
//     while(!test.isEmpty()) {
//         std::cout << test.pop() << std::endl;
//     }
//     LifoStack check(3);
//     check.push(5);
//     check.push(2);
//     check.push(4);
//     int foo;
//     std::cout << "Test 2" << std::endl;
//     while(!check.isEmpty()) {
//         std::cout << check.peek() << std::endl;
//         foo = check.pop();
//     }
// }
