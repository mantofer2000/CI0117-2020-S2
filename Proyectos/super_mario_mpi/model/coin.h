#ifndef COIN_H
#define COIN_H
#include "element.h"


class Coin : public Element {
    public:
        Coin();
        int action(Mario &) override;
};

#endif