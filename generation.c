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
  J.droitstock=1;
  J.palier=100;
  J.score=0;
  J.vitesse=1;
  J.timeallowed=1000;
  J.lasttick=MLV_get_time();
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
  case 8:
    ;
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

tetrimino piece_vide(){
  tetrimino t;
  t.type=8; /*Le type 8 est réservé à une pièce vide*/
  t.posx=0;
  t.posy=0;
  matricetetrimino(t.type, t.mat);
  return t;
}

void copier_piece(tetrimino* dest, tetrimino* source){
  int x,y;
  dest->posx=source->posx;
  dest->posy=source->posy;
  dest->type=source->type;
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      dest->mat[x][y]=source->mat[x][y];
    }
  }
}
