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
  Car* current = first;
  current->light = true;

  Car* probe = current->next;
  countOp++;

  while (!probe->light) {
    probe = probe->next;
    countOp++;
  }

  probe->light = false;

  int len = 1;
  Car* walker = probe->next;
  countOp++;

  while (walker != probe) {
    len++;
    walker = walker->next;
    countOp++;
  }

  return len;
}

int Train::getOpCount() {
  return countOp;
}
