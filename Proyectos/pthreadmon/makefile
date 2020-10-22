all: prueba_consola prueba_gui refactor

prueba_consola: controller/*.c
	gcc controller/*.c -pthread -std=gnu99 -lm -o prueba_consola

prueba_gui: controller/game_master.c controller/mapper.c controller/player.c controller/pokemon.c view/pthreadmon_ui.c
	gcc `pkg-config --cflags gtk+-3.0` controller/game_master.c controller/mapper.c controller/player.c controller/pokemon.c view/pthreadmon_ui.c -lm -pthread -std=gnu99 -o prueba_gui `pkg-config --libs gtk+-3.0`



refactor: controller/main_refactor.c controller/mapper.c controller/player.c controller/pokemon.c controller/game_master2.c 
	gcc controller/main_refactor.c controller/mapper.c controller/player.c controller/pokemon.c controller/game_master2.c  -pthread -std=gnu99 -lm -o refactor


