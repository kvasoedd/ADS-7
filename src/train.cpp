// Copyright 2021 NNTU-CS
#include <iostream>
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (first) {
        Car* current = first->next;
        first->prev->next = nullptr;
        while (current) {
            Car* next = current->next;
            delete current;
            current = next;
        }
    }
}

void Train::addCar(bool light) {
    Car* newCar = new Car();
    newCar->light = light;
    
    if (!first) {
        newCar->next = newCar;
        newCar->prev = newCar;
        first = newCar;
    } else {
        newCar->prev = first->prev;
        newCar->next = first;
        first->prev->next = newCar;
        first->prev = newCar;
    }
    
    countOp = 0;
}

int Train::getLength() {
    if (!first) return 0;
    countOp = 0;
    
    Car* current = first;
    bool originalState = current->light;
    bool needRestore = false;
    
    if (!originalState) {
        current->light = true;
        needRestore = true;
        countOp++;
    }
    
    current = current->next;
    while (current != first) {
        if (current->light) {
            current->light = false;
            countOp++;
        }
        current = current->next;
        countOp++;
    }
    
    int steps = 1;
    current = first->next;
    countOp++;
    
    while (current->light != true) {
        steps++;
        current = current->next;
        countOp++;
    }
    
    if (needRestore) {
        first->light = originalState;
        countOp++;
    }
    
    return steps;
}

int Train::getOpCount() {
    return countOp;
}
