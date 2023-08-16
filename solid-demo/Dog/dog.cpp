#include "dog.h"

Dog::Dog() {

}

Dog::Dog(string breed, string furColor, int numberOfLegs, int age) : DomesticAnimal(numberOfLegs, age) {
    this->breed = breed;
    this->furColor = furColor;
}

string Dog::getBreed() {
    return this->breed;
}

void Dog::setBreed(string breed) {
    this->breed = breed;
}

string Dog::getFurColor() {
    return this->furColor;
}

void Dog::setFurColor(string furColor) {
    this->furColor = furColor;
}

void Dog::makeSound() {
    cout << "woof woof" << endl;
}

void Dog::playWithOwner() {
    cout << "Owner throws a stick\nRun for the stick\nGet the stick for the owner" << endl;
}

void Dog::chaseTail() {
    cout << "running in circles uncontrollably..." << endl;
}