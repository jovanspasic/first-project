#include "Dog\dog.h"
#include "Wolf\wolf.h"
#include "Calculator\ageCalculatorHelper.h"

int main(void) {
    DomesticAnimal *dog = new Dog("corgi", "brown", 4, 4);
    WildAnimal *wolf = new Wolf(true, 4, 7);

    dog->playWithOwner();
    dog->makeSound();
    
    //casting using static cast
    static_cast<Dog *>(dog)->chaseTail();

    cout << endl;
    wolf->makeSound();
    wolf->huntPrey();

    cout << endl << endl << "Age of the dog is: " << AgeCalculatorHelper::calculateAnimalAge(dog->getAge(), 7);
}