compile: controller/*.c view/pthreadmon_ui.c
	gcc `pkg-config --cflags gtk+-3.0` controller/*.c view/pthreadmon_ui.c -lm -pthread -std=gnu99 -o test_ui `pkg-config --libs gtk+-3.0`

