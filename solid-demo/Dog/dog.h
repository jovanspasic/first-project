#pragma once
#include "..\Animal\Domestic_Animal\domesticAnimal.h"

class Dog : public DomesticAnimal{

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
        void playWithOwner(void);
        void chaseTail(void);

};