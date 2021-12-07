tetris : tetristarrete.c menu.o affichage.o generation.o jeu.o sauvegarde.o options.o
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` tetristarrete.c menu.o affichage.o generation.o jeu.o sauvegarde.o options.o `pkg-config --libs-only-l MLV` -o tetris

menu.o : menu.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` menu.c `pkg-config --libs-only-l MLV` -c menu.c

affichage.o : affichage.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` affichage.c `pkg-config --libs-only-l MLV` -c affichage.c

generation.o : generation.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` generation.c `pkg-config --libs-only-l MLV` -c generation.c

jeu.o : jeu.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` jeu.c `pkg-config --libs-only-l MLV` -c jeu.c

sauvegarde.o: sauvegarde.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` sauvegarde.c `pkg-config --libs-only-l MLV` -c sauvegarde.c

options.o : options.c tetris.h
	gcc -Wall `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` options.c `pkg-config --libs-only-l MLV` -c options.c
