#include "animal.h"

Animal::Animal() {
    
}

Animal::Animal(int numberOfLegs, int age) {
    this->numberOfLegs = numberOfLegs;
    this->age = age;
}

int Animal::getNumberOfLegs() {
    return this->numberOfLegs;
}

void Animal::setNumberOfLegs(int numberOfLegs) {
    this->numberOfLegs = numberOfLegs;
}

int Animal::getAge() {
    return this->age;
}

void Animal::setAge(int age) {
    this->age = age;
}