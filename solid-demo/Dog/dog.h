#pragma once
#include "..\Animal\animal.h"

class Dog : public Animal{

    private:
        string breed;
        string furColor;

    public:
        Dog();
        Dog(string breed, string furColor, int numberOfLegs, int age);

        string getBreed(void);
        void setBreed(string breed);
        string getFurColor(void);
        void setFurColor(string furColor);

        void makeSound(void);
        void chaseTail(void);

};