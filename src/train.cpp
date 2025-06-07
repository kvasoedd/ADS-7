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
        delete first;
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

    bool originalState = first->light;
    bool needRestore = false;

    if (!originalState) {
        first->light = true;
        needRestore = true;
    }

    Car* cur = first->next;
    while (cur != first) {
        if (cur->light) {
            cur->light = false;
            countOp++;
        }
        cur = cur->next;
    }

    int steps = 0;
    cur = first;
    do {
        cur = cur->next;
        countOp++;
        steps++;
    } while (cur->light != true);

    if (needRestore) {
        first->light = originalState;
    }

    countOp = 2 * steps;
    return steps;
}

int Train::getOpCount() {
    return countOp;
}
