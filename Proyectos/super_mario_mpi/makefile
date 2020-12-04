all: super_mario_mpi

super_mario_mpi: controller/main.cpp controller/coin.cpp controller/goomba.cpp controller/hole.cpp controller/koopa.cpp controller/mario.cpp controller/world.cpp
	mpic++ -std=gnu++11 controller/main.cpp controller/coin.cpp controller/goomba.cpp controller/hole.cpp controller/koopa.cpp controller/mario.cpp controller/world.cpp -o super_mario_mpi


.PHONY: gitignore
gitignore:
	echo super_mario_mpi > .gitignore

.PHONY: clean
clean:
	rm -f super_mario_mpi