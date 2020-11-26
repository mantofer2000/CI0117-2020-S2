all: prueba

prueba: controller/main.cpp controller/coin.cpp controller/goomba.cpp controller/hole.cpp controller/koopa.cpp controller/mario.cpp controller/world.cpp
	g++ -std=gnu++11 controller/main.cpp controller/coin.cpp controller/goomba.cpp controller/hole.cpp controller/koopa.cpp controller/mario.cpp controller/world.cpp -o prueba

.PHONY: clean
clean:
	rm -f  pthreadmon