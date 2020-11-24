#ifndef GOOMBA_H
#define GOOMBA_H
#include <element.h>


class LittleGoomba : public Element {
    public:
        void action(Mario &) override {};
};

#endif