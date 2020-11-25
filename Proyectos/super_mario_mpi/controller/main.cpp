#include "../model/coin.h"
#include "../model/goomba.h"

int main() {

    Little_Goomba myGoomba;
    Coin myCoin;

    if (myCoin != myGoomba) {
        std::cout << "Diferrent Elements" << std::endl;
    }


    return 0;

}