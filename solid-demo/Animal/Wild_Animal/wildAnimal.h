#pragma once
#include "..\animal.h"

class WildAnimal : public Animal{

    public:
        WildAnimal();
        WildAnimal(int numberOfLegs, int age);

        virtual void huntPrey(void) = 0;

};