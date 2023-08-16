#include "Dog\dog.h"
#include "Wolf\wolf.h"
#include ".\Calculator\dogAgeCalculator.h"

int main(void) {
    DomesticAnimal *dog = new Dog("corgi", "brown", 4, 4);
    WildAnimal *wolf = new Wolf(true, 4, 7);

    DogAgeCalculator dogAgeCalculator;

    dog->playWithOwner();
    dog->makeSound();
    ((Dog *)dog)->chaseTail();
    cout << endl;
    wolf->makeSound();
    wolf->huntPrey();

    cout << endl << endl << "Age of the dog is: " << dogAgeCalculator.calculateAgeInAnimalYears(dog);
}