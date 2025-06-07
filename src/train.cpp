// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car *current = first->next;
    while (current != first) {
        Car *next = current->next;
        delete current;
        current = next;
    }
    delete first;
    first = nullptr;
}

void Train::addCar(bool light) {
    if (first == nullptr) {
        first = new Car{light, nullptr, nullptr};
        first->next = first;
        first->prev = first;
        return;
    }
    Car *last = first->prev;
    Car *newCar = new Car{light, first, last};
    last->next = newCar;
    first->prev = newCar;
}

int Train::getOpCount() {
    return countOp;
}

int Train::getLength() {
    countOp = 0;
    if (!first) return 0;
    
    if (!first->light) {
        first->light = true;
    }

    Car* current = first;
    while (true) {
        int steps = 0;
        Car* p = current->next;
        countOp++;

        while (p != current && !p->light) {
            p = p->next;
            steps++;
            countOp++;
        }

        if (p == current) {
            return steps + 1;
        }

        p->light = false;
        countOp += steps;

        for (int i = 0; i < steps; i++) {
            p = p->prev;
        }
        current = p;
        
        countOp++;
    }
}
