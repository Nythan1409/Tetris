tetris : tetristarrete.c menu.o affichage.o generation.o jeu.o
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` tetristarrete.c menu.o affichage.o generation.o jeu.o `pkg-config --libs-only-l MLV` -o tetris

menu.o : menu.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` menu.c `pkg-config --libs-only-l MLV` -c menu.c

affichage.o : affichage.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` affichage.c `pkg-config --libs-only-l MLV` -c affichage.c

generation.o : generation.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` generation.c `pkg-config --libs-only-l MLV` -c generation.c

jeu.o : jeu.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` jeu.c `pkg-config --libs-only-l MLV` -c jeu.c
