#pragma once
#include "animalAgeCalculator.h"

class DogAgeCalculator : AnimalAgeCalculator {

    public:
        DogAgeCalculator();
        
        int calculateAgeInAnimalYears(Animal &animal);

};