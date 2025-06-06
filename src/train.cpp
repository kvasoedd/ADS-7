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
  Car* curr = first;

  curr->light = true;
  countOp++;

  Car* walker = curr->next;
  countOp++;

  while (!walker->light) {
    walker = walker->next;
    countOp++;
  }

  walker->light = false;
  countOp++;

  int length = 1;
  Car* temp = walker->next;
  countOp++;

  while (temp != walker) {
    length++;
    temp = temp->next;
    countOp++;
  }

  return length;
}

int Train::getOpCount() {
  return countOp;
}
