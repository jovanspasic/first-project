#include "wolf.h"

Wolf::Wolf() {

}

Wolf::Wolf(bool isInAPack, int numberOfLegs, int age) : WildAnimal(numberOfLegs, age) {
    this->isInAPack = isInAPack;
}

bool Wolf::getIsInAPack() {
    return this->isInAPack;
}

void Wolf::setIsInAPack(bool isInAPack) {
    this->isInAPack = isInAPack;
}

void Wolf::makeSound() {
    cout << "Awooo" << endl;
}

void Wolf::huntPrey() {
    cout << "Track the prey" << endl;

    if(this->isInAPack) {
        cout << "Spread to surround the prey" << endl;
    }

    cout << "Attack!" << endl;
}