#ifndef B_
#define B_

#include <iostream>

class B {
    friend class A;
    public:
        void print();
        B();
    private:
        int value;
};

#endif