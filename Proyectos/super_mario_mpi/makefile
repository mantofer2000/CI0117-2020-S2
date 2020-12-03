all: prueba

prueba: controller/main.cpp controller/coin.cpp controller/goomba.cpp controller/hole.cpp controller/koopa.cpp controller/mario.cpp controller/world.cpp
	mpic++ controller/main.cpp controller/coin.cpp controller/goomba.cpp controller/hole.cpp controller/koopa.cpp controller/mario.cpp controller/world.cpp -o prueba


.PHONY: gitignore
gitignore:
	echo prueba > .gitignore

.PHONY: clean
clean:
	rm -f  pthreadmon