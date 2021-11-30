#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h>
#define TAILLE_MAX 1024

typedef struct {
  int posx;
  int posy;
  int type; /*Contient un int en fonction de la pièce*/
  int mat[4][4]; /*Contient un int pour la couleur du carré, 0 si vide*/
}tetrimino;


typedef struct {
  int mat[10][20];
  int score;
  int niveau;
  int palier; /*Palier de points pour atteindre le prochain niveau*/
  double vitesse;
  int lasttick;
  int timeallowed;
  int droitstock;
}jeu;

MLV_Image *grille, *next, *rouge, *orange, *jaune, *vert, *cyan, *bleu, *violet, *blanc, *menu1, *menu2, *menu0, *fondrouge, *fondvert, *fondbleu, *score, *ombrerouge, *ombreorange, *ombrejaune, *ombrevert, *ombrecyan, *ombrebleu, *ombreviolet;

int menu();

void loadimage();

jeu generer_jeu();

void matricetetrimino(int a, int M[4][4]); /*Génère la matrice correspondant au type a et la place dans M*/

tetrimino generer_piece();

void afficher_fond();

void afficher_grille(jeu* J);

void afficher_piece(tetrimino* t);

void afficher_next(tetrimino* t);

void afficher_score(jeu* J);

void inclure_piece(tetrimino* t, jeu* J);/*Adresse pour pouvoir modifier la matrice. On doit mettre des adresses à chaque fois qu'un jeu est en paramètre dans une fonction pour pouvoir les appeler entre elles*/
/*Pareil pour les tetriminos en fait*/

int position_impossible(tetrimino* t, jeu* J);

int est_a_gauche(tetrimino* t, jeu* J);

int est_a_droite(tetrimino* t, jeu* J);

int est_en_bas(tetrimino* t, jeu* J);

void chute(tetrimino* t, jeu* J, tetrimino* poche);

int chute_rapide(tetrimino* t, jeu *J);

void rotation_d(tetrimino* t, jeu* J);

void rotation_g(tetrimino* t, jeu* J);

int lignes_completes(jeu* J);

void copier_piece(tetrimino* dest, tetrimino* source);

void augmenter_score(jeu* J);

void augmenter_niveau(jeu* J);

void afficher_niveau(jeu* J);

void preshot(tetrimino* t, jeu* J);

void stocker(tetrimino* t, tetrimino* poche);

void afficher_poche(tetrimino* t);

void new_tick(jeu* J, int tick);

int test_tick(jeu* J, int tick);

void nouvelle_image(int tick, tetrimino* t, jeu* J);

tetrimino piece_vide();

/*void rst_mov_tick(jeu* J,time_t tick);*/
