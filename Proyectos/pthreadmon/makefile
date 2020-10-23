all: pthreadmon


pthreadmon: controller/game_master.c controller/mapper.c controller/player.c controller/pokemon.c view/pthreadmon_ui.c
	gcc `pkg-config --cflags gtk+-3.0` controller/game_master.c controller/mapper.c controller/player.c controller/pokemon.c view/pthreadmon_ui.c -lm -pthread -std=gnu99 -o pthreadmon `pkg-config --libs gtk+-3.0`


.PHONY: clean
clean:
	rm -f  pthreadmon



