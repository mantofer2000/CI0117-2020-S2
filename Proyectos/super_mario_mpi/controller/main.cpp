#include "../model/coin.h"
#include "../model/goomba.h"
#include "../model/world.h"

int main() {

    Little_Goomba myGoomba;
    Coin myCoin;

    World w;

    if (myCoin != myGoomba) {
        std::cout << "Diferrent Elements" << std::endl;
    }


    return 0;

}