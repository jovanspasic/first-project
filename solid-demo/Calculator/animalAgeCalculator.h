#pragma once
#include "..\Animal\animal.h"

class AnimalAgeCalculator {

    public:

        virtual int calculateAgeInAnimalYears(Animal &animal) = 0;

};