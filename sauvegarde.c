#include "tetris.h"

void enregistrer_score(jeu J, FILE* fichier){
  int x=0;
  char c1, c2, c3;
  MLV_clear_window(MLV_COLOR_BLACK);
  MLV_draw_text(100, 100, "Entrez votre nom (3 lettres)", MLV_COLOR_WHITE);
  MLV_actualise_window();
  while(x<65 || (x>90 && x<97) || x>122){
    MLV_wait_keyboard(NULL, NULL, &x);
    if(x>=97){
      x-=32;
    }
  }
  c1=x;
  x=0;
  MLV_draw_text(50, 150, &c1, MLV_COLOR_WHITE);
  MLV_actualise_window();
  while(x<65 || (x>90 && x<97) || x>122){
    MLV_wait_keyboard(NULL, NULL, &x);
    if(x>=97){
      x-=32;
    }
  }
  c2=x;
  x=0;
  MLV_draw_text(100, 150, &c2, MLV_COLOR_WHITE);
  MLV_actualise_window();
  while(x<65 || (x>90 && x<97) || x>122){
    MLV_wait_keyboard(NULL, NULL, &x);
    if(x>=97){
      x-=32;
    }
  }
  c3=x;
  x=0;
  MLV_draw_text(150, 150, &c3, MLV_COLOR_WHITE);
  MLV_actualise_window();
  fprintf(fichier, "%c%c%c %d\n", c1, c2, c3, J.score);
  MLV_wait_seconds(1);
}

void top_10(FILE* fichier){
  char noms[100][3];
  int scores[100];
  int i=0;
  int j;
  int k;
  int l;
  int transition[4];
  char texte[100];
  char a,b,c;
  int d;
  for(l=0;l<100;l++){
    scores[l]=0;
  }
  MLV_clear_window(MLV_COLOR_BLACK);
  while(fscanf(fichier, "%c%c%c %d\n", &a, &b, &c, &d)==4 && i<100){
    noms[i][0]=a;
    noms[i][1]=b;
    noms[i][2]=c;
    scores[i]=d;
    j=i;
    while(j!=0 && scores[j]>scores[j-1]){
      transition[0]=noms[j-1][0];
      transition[1]=noms[j-1][1];
      transition[2]=noms[j-1][2];
      transition[3]=scores[j-1];
      noms[j-1][0]=noms[j][0];
      noms[j-1][1]=noms[j][1];
      noms[j-1][2]=noms[j][2];
      scores[j-1]=scores[j];
      noms[j][0]=transition[0];
      noms[j][1]=transition[1];
      noms[j][2]=transition[2];
      scores[j]=transition[3];
      j--;
    }
    i++;
  }
  for(k=0;k<10;k++){
    if(scores[k]==0){
      sprintf(texte, "%d. Aucun score", k+1);
      MLV_draw_text(20, 20*(k+1), texte, MLV_COLOR_WHITE);
    }
    else{
      a=noms[k][0];
      b=noms[k][1];
      c=noms[k][2];
      d=scores[k];
      sprintf(texte, "%d. %c%c%c %d", k+1, a, b, c, d);
      MLV_draw_text(20, 20*(k+1), texte, MLV_COLOR_WHITE);
    }
  }
  MLV_actualise_window();
}

void enregistrer_partie(jeu J, FILE* fichier, tetrimino t, tetrimino s, tetrimino p){
  int i,j;
  fprintf(fichier, "a"); /*Caractère que le main lira s'il y a un fichier*/
  fprintf(fichier, "%d %d %d %d %d %d %d %lf\n", J.score, J.niveau, J.palier, J.lasttick, J.timeallowed, J.droitstock, J.piecevide, J.vitesse);
  for(j=0;j<20;j++){
    for(i=0; i<10; i++){
      fprintf(fichier, "%d\n", J.mat[i][j]);
    }
  }
  fprintf(fichier, "%d %d %d %d %d\n", t.type, t.posx, t.posy, s.type, p.type);
}

void charger_partie(jeu* J, FILE* fichier, tetrimino* t, tetrimino* s, tetrimino* p){
  int i,j;
  fscanf(fichier, "%d %d %d %d %d %d %d %lf\n", &(J->score), &(J->niveau), &(J->palier), &(J->lasttick), &(J->timeallowed), &(J->droitstock), &(J->piecevide), &(J->vitesse));
  J->pause=0;
  for(j=0;j<20;j++){
    for(i=0; i<10; i++){
      fscanf(fichier, "%d\n", &(J->mat[i][j]));
    }
  }
  fscanf(fichier, "%d %d %d %d %d\n", &(t->type), &(t->posx), &(t->posy), &(s->type), &(p->type));
  matricetetrimino(t->type, t->mat);
  matricetetrimino(s->type, s->mat);
  s->posx=3;
  s->posy=0;
  matricetetrimino(p->type, p->mat);
  p->posx=3;
  p->posy=0;
}

int sauvegarde_existe(FILE* fichier){
  if(fgetc(fichier)==EOF){
    return 0;
  }
  return 1;
}
