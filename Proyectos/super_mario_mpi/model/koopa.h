#ifndef KOOPA_H
#define KOOPA_H
#include "element.h"


class Koopa_Troopa : public Element {
    public:
        Koopa_Troopa();
        int action(Mario &, int probability) override;
};

#endif