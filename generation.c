#include "tetris.h"

jeu generer_jeu(){
  jeu J;
  int x,y;
  for(x=0;x<10;x++){
    for(y=0;y<20;y++){
      J.mat[x][y]=0;
    }
  }
  J.niveau=1;
  J.palier=100;
  J.score=0;
  J.vitesse=1;
  return J;
}

void matricetetrimino(int a, int M[4][4]){
  int x,y;
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      M[x][y]=0;
    }
  }
  switch(a){
  case 1:
    for(x=0;x<2;x++){
      M[x][0]=a;
      M[x+1][1]=a;
    }
    break;
  case 2:
    M[2][0]=a;
    for(x=0;x<3;x++){
      M[x][1]=a;
    }
    break;
  case 3:
    for(x=1;x<3;x++){
      for(y=1;y<3;y++){
	M[x][y]=a;
      }
    }
    break;
  case 4:
    for(x=0;x<2;x++){
      M[x][1]=a;
      M[x+1][0]=a;
    }
    break;
  case 5:
    for(x=0;x<4;x++){
      M[x][1]=a;
    }
    break;
  case 6:
    M[0][0]=a;
    for(x=0;x<3;x++){
      M[x][1]=a;
    }
    break;
  case 7:
    M[1][0]=a;
    for(x=0;x<3;x++){
      M[x][1]=a;
    }
    break;
  }
}

tetrimino generer_piece(){
  tetrimino t;
  t.type=rand()%7+1;
  t.posx=3;
  t.posy=0;
  matricetetrimino(t.type, t.mat);
  return t;
}

void copier_piece(tetrimino* t, tetrimino* t2){
  int x,y;
  t->posx=t2->posx;
  t->posy=t2->posy;
  t->type=t2->type;
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      t->mat[x][y]=t2->mat[x][y];
    }
  }
}
