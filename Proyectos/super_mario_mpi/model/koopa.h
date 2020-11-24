#ifndef GOOMBA_H
#define GOOMBA_H
#include <element.h>


class KoopaTroopa : public Element {
    public:
        void action(Mario &) override {};
};

#endif