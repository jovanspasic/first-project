#pragma once
#include <iostream>

using namespace std;

class Animal {

    protected:
        int numberOfLegs;
        int age;

    public:
        Animal();
        Animal(int numberOfLegs, int age);

        int getNumberOfLegs(void);
        void setNumberOfLegs(int numberOfLegs);
        int getAge(void);
        void setAge(int age);

        virtual void makeSound(void) = 0;

};