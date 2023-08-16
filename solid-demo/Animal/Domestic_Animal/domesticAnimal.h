#pragma once
#include "..\animal.h"

class DomesticAnimal : public Animal {

    public:
        DomesticAnimal();
        DomesticAnimal(int numberOfLegs, int age);

        virtual void playWithOwner(void) = 0;

};