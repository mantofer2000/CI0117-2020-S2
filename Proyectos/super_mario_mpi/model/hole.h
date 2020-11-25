#ifndef HOLE_H
#define HOLE_H
#include "element.h"


class Hole : public Element {
    public:
        Hole();
        void action(Mario &) override;
};

#endif