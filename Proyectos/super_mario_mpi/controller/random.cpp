#include "../model/random.h"

Rand_Gen::Rand_Gen() {
    double seed = time(NULL) * (10000);
    srand (seed);
}

double Rand_Gen::get_rand_double() {
    double number = rand() % (100 + 1);
    return number;
}