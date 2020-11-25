all: super_mario_mpi

super_mario_mpi: controller/*.cpp
	g++ -std=gnu++11 controller/*.cpp -o super_mario_mpi

.PHONY: clean
clean:
	rm -f  pthreadmon