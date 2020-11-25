#ifndef GOOMBA_H
#define GOOMBA_H
#include "element.h"


class Little_Goomba : public Element {
    public:
        Little_Goomba();
        void action(Mario &) override {};
};

#endif