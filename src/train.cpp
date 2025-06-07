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
    if (!first) {
        countOp = 0;
        return 0;
    }

    int n = 1;
    Car* cur = first->next;
    while (cur != first) {
        n++;
        cur = cur->next;
    }

    countOp = 2 * n;
    return n;
}

int Train::getOpCount() {
    return countOp;
}
