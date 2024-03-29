#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> /*On a besoin de la bibliothèque time.h pour l'aléatoire*/
#include <MLV/MLV_all.h>
#define TAILLE_MAX 1024

typedef struct {
  int posx;
  int posy;
  int type; /*Contient un int en fonction de la pièce, 8 si tetrimino vide*/
  int mat[4][4]; /*Contient un int pour la couleur du carré, 0 si vide*/
}tetrimino;/*Nom des pièces de Tetris*/


typedef struct {
  int mat[10][20];
  int score;
  int niveau; /*Le niveau du jeu*/
  int palier; /*Palier de points pour atteindre le prochain niveau*/
  double vitesse; /*Le multiplicateur de vitesse du jeu*/
  int lasttick; /*Le temps auquel la dernière action a été faite, fourni grace à MLV_get_time*/
  int timeallowed; /*Le temps autorisé avant le prochain tick*/
  int droitstock; /*Booléen qui détermine si le stock est possiblé*/
  int piecevide; /*Booléen qui détermine si la poche est vide*/
  int pause;
}jeu;

MLV_Image *grille, *next, *rouge, *orange, *jaune, *vert, *cyan, *bleu, *violet, *blanc, *menu1, *menu2, *menu3, *menu0, *menuo1, *menuo2, *menuo0, *pause1, *pause2, *pause0, *sousmenu1, *sousmenu0, *fondrouge, *fondvert, *fondbleu, *score, *ombrerouge, *ombreorange, *ombrejaune, *ombrevert, *ombrecyan, *ombrebleu, *ombreviolet;

/*----------Fonctions----------*/

/*-----menu.c-----*/

int menu();

int menu_pause();

int sous_menu_jouer();

int options(int fond);

/*-----affichage.c-----*/

void loadimage();

void afficher_fond();

void afficher_grille(jeu* J);

void afficher_piece(tetrimino* t);

void afficher_next(tetrimino* t);

void afficher_score(jeu* J);

void afficher_niveau(jeu* J);

void preshot(tetrimino* t, jeu* J);

void afficher_poche(tetrimino* t);

void nouvelle_image(int tick, tetrimino* t, jeu* J);

/*-----generation.c-----*/

jeu generer_jeu();

void matricetetrimino(int a, int M[4][4]);

tetrimino generer_piece();

tetrimino piece_vide();

void copier_piece(tetrimino* dest, tetrimino* source);

/*-----jeu.c-----*/

int position_impossible(tetrimino* t, jeu* J);

int est_a_gauche(tetrimino* t, jeu* J);

int est_a_droite(tetrimino* t, jeu* J);

int est_en_bas(tetrimino* t, jeu* J);

void inclure_piece(tetrimino* t, jeu* J);

void chute(tetrimino* t);

int chute_rapide(tetrimino* t, jeu *J);

void rotation_d(tetrimino* t, jeu* J);

void rotation_g(tetrimino* t, jeu* J);

int lignes_completes(jeu* J);

void augmenter_score(jeu* J);

void augmenter_niveau(jeu* J);

void stocker(tetrimino* t, tetrimino* poche);

int test_tick(jeu* J, int tick);

void new_tick(jeu* J, int tick);

int fin_partie(jeu J);

int evenement(tetrimino* t, tetrimino* poche, jeu* J, int tick);

void set_pause(jeu* J);

void resume(jeu* J, int tick);

/*-----sauvegarde.c-----*/

void enregistrer_score(jeu J, FILE* fichier);

void top_10(FILE* fichier);

void enregistrer_partie(jeu J, FILE* fichier, tetrimino t, tetrimino s, tetrimino p);

void charger_partie(jeu* J, FILE* fichier, tetrimino* t, tetrimino* s, tetrimino* p);

int sauvegarde_existe(FILE* fichier);
