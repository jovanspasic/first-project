#include "dogAgeCalculator.h"

DogAgeCalculator::DogAgeCalculator() {

}

int DogAgeCalculator::calculateAgeInAnimalYears(Animal *animal) {
    return animal->getAge() * 7;
}