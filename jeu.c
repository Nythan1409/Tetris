#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "tetris.c"

int init_jeu(jeu* j) /* Permet d'initialiser le jeu */
{
  int i, j;
  for (i=0;i<10;i++){
    for (j=0;j<20;i++){
      j.mat[i][j]=0;
    }
  }
  j.score=0;
  j.p_niveau=0;
  j.niveau=0;
  j.vitesse=1;
}

