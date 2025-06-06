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

int Train::countAllOff() {
  if (!first) return 0;
  const Car* start = first;
  const Car* walker = first->next;
  int ops = 1;
  while (walker != start) {
    walker = walker->next;
    ops++;
  }
  return ops;
}

int Train::countAllOn() {
  if (!first) return 0;
  Car* curr = first;
  int ops = 0;
  do {
    curr = curr->next;
    ops++;
    curr->light = false;
  } while (curr != first);

  first->light = true;

  Car* walker = first->next;
  ops++;
  while (!walker->light) {
    walker = walker->next;
    ops++;
  }
  walker->light = false;

  int len = 1;
  Car* temp = walker->next;
  ops++;
  while (temp != walker) {
    len++;
    temp = temp->next;
    ops++;
  }

  return ops;
}

int Train::countRandom() {
  if (!first) return 0;
  Car* curr = first;
  int ops = 0;
  do {
    curr = curr->next;
    ops++;
    curr->light = false;
  } while (curr != first);

  first->light = true;
  Car* walker = first->next;
  ops++;
  int len = 1;
  while (walker != first) {
    len++;
    walker = walker->next;
    ops++;
  }
  return ops;
}

int Train::getLength() {
  if (!first) return 0;

  bool anyOn = false, allOn = true;
  Car* cursor = first;
  do {
    if (cursor->light) anyOn = true;
    else allOn = false;
    cursor = cursor->next;
  } while (cursor != first && !(anyOn && !allOn));

  if (!anyOn) {
    countOp = countAllOff();
    return 1 + countOp;
  }
  if (allOn) {
    countOp = countAllOn();
    return countOp / 3 + 1;
  }
  countOp = countRandom();
  return countOp / 2 + 1;
}

int Train::getOpCount() {
  return countOp;
}
