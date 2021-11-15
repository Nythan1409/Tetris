tetris : tetristarrete.c menu.o
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` tetristarrete.c menu.o `pkg-config --libs-only-l MLV` -o tetris

menu.o : menu.c header.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` menu.c `pkg-config --libs-only-l MLV` -c menu.c
