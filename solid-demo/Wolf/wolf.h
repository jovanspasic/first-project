#pragma once 
#include "..\Animal\Wild_Animal\wildAnimal.h"

class Wolf : public WildAnimal {

    private:
        bool isInAPack;

    public:
        Wolf();
        Wolf(bool isInAPack, int numberOfLegs, int age);

        bool getIsInAPack(void);
        void setIsInAPack(bool isInAPack);

        void makeSound(void);
        void huntPrey(void);

};