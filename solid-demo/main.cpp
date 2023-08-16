#include "Dog\dog.h"

int main(void) {
    Animal *dog = new Dog("asd", "asd", 4, 4);
    dog->makeSound();
}