// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

void Train::addCar(bool light) {
  Car* car = new Car{light, nullptr, nullptr};
  if (!first) {
    car->next = car;
    car->prev = car;
    first = car;
  } else {
    Car* last = first->prev;
    car->next = first;
    car->prev = last;
    last->next = car;
    first->prev = car;
  }
}

int Train::getLength() {
  if (!first) return 0;

  const Car* start = first;
  const Car* walker = first->next;
  countOp++;

  int len = 1;
  while (walker != start) {
    len++;
    walker = walker->next;
    countOp++;
  }
  return len;
}

int Train::getOpCount() {
  return countOp;
}
