#DEFINE TAILLE_MAX 1024

typedef struct {
  int posx;
  int posy;
  int type;
  int mat[4][4];
}tetrimino;


typedef struct {
  int mat[10][20];
  int score;
  int vitesse;
}jeu;
