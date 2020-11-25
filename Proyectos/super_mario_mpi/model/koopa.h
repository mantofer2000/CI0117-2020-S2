#ifndef GOOMBA_H
#define GOOMBA_H
#include "element.h"


class Koopa_Troopa : public Element {
    public:
        Koopa_Troopa();
        void action(Mario &) override {};
};

#endif