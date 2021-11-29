#include "tetris.h"

int position_impossible(tetrimino* t, jeu* J){
  int x,y;
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      if(t->mat[x][y]!=0 && (x+t->posx<0 || x+t->posx>=10 || y+t->posy>=20 || J->mat[x+t->posx][y+t->posy]!=0)){
	return 1;
      }
    }
  }
  return 0;
}

int est_a_gauche(tetrimino* t, jeu* J){
  int a;
  t->posx--;
  a=position_impossible(t, J);
  t->posx++;
  return a;
}

int est_a_droite(tetrimino* t, jeu* J){
  int a;
  t->posx++;
  a=position_impossible(t, J);
  t->posx--;
  return a;
}

int est_en_bas(tetrimino* t, jeu* J){
  int a;
  t->posy++;
  a=position_impossible(t, J);
  t->posy--;
  return a;
}

void inclure_piece(tetrimino* t, jeu* J){
  int x,y;
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      if(t->mat[x][y]!=0){
	J->mat[x+t->posx][y+t->posy]=t->mat[x][y];
      }
    }
  }
}

void chute(tetrimino* t, jeu* J){
  int bouton;
  afficher_grille(J);
  preshot(t,J);
  afficher_piece(t);
  while(!est_en_bas(t,J)){
    switch(MLV_wait_keyboard_or_seconds(NULL, NULL, &bouton, 1)){
    case 1:
      t->posy++;
      afficher_grille(J);
      preshot(t,J);
      afficher_piece(t);
      break;
    case 0:
      switch(bouton){
      case 's':
        chute_rapide(t, J);
	break;
      case 'q':
	if(!est_a_gauche(t, J)){
	  t->posx--;
	}
	break;
      case 'd':
	if(!est_a_droite(t, J)){
	  t->posx++;
	}
	break;
      case 'z':
	rotation_d(t, J);
	break;
      case 'a':
	rotation_g(t, J);
	break;
      }
      afficher_grille(J);
      preshot(t,J);
      afficher_piece(t);
      break;
    }
    bouton=0;
  }
  inclure_piece(t, J);
}

void chute_rapide(tetrimino* t, jeu *J){
  while(!est_en_bas(t, J)){
    t->posy++;
  }
}

void rotation_d(tetrimino* t, jeu* J){
  int x,y;
  int M[4][4];
  int save[4][4];
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      M[x][y]=0;
    }
  }
  if(t->type==3 || t->type==5){
    for(x=0;x<4;x++){
      for(y=0;y<4;y++){
	M[x][y]=t->mat[y][3-x];
      }
    }
  }
  else{
    for(x=0;x<3;x++){
      for(y=0;y<3;y++){
	M[x][y]=t->mat[y][2-x];
      }
    }
  }
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      save[x][y]=t->mat[x][y];
      t->mat[x][y]=M[x][y];
    }
  }
  if(position_impossible(t, J)){
    for(x=0;x<4;x++){
      for(y=0;y<4;y++){
	t->mat[x][y]=save[x][y];
      }
    }
  }
}

void rotation_g(tetrimino* t, jeu* J){
  int x,y;
  int M[4][4];
  int save[4][4];
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      M[x][y]=0;
    }
  }
  if(t->type==3 || t->type==5){
    for(x=0;x<4;x++){
      for(y=0;y<4;y++){
	M[x][y]=t->mat[3-y][x];
      }
    }
  }
  else{
    for(x=0;x<3;x++){
      for(y=0;y<3;y++){
	M[x][y]=t->mat[2-y][x];
      }
    }
  }
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      save[x][y]=t->mat[x][y];
      t->mat[x][y]=M[x][y];
    }
  }
  if(position_impossible(t, J)){
    for(x=0;x<4;x++){
      for(y=0;y<4;y++){
	t->mat[x][y]=save[x][y];
      }
    }
  }
}

int lignes_completes(jeu* J){
  int lignes=0;
  int complete=1;
  int x,y;
  int x2,y2;
  for(y=19;y>=0;y--){
    for(x=0;x<10;x++){
      if(J->mat[x][y]==0){
	complete=0;
      }
    }
    if(complete==1){
      lignes++;
      for(x2=0;x2<10;x2++){
	for(y2=y;y2>0;y2--){
	  J->mat[x2][y2]=J->mat[x2][y2-1];
	}
	J->mat[x2][0]=0;
      }
      y++;/*Pour réétudier la ligne de même numéro au prochain tour de boucle*/
    }
    complete=1;
  }
  afficher_grille(J);
  return lignes;
}

void augmenter_score(jeu* J){
  int a;
  switch(lignes_completes(J)){
  case 0:
    a=1;
    break;
  case 1:
    a=100*J->niveau;
    break;
  case 2:
    a=300*J->niveau;
    break;
  case 3:
    a=500*J->niveau;
    break;
  default:
    a=800*J->niveau;
    break;
  }
  J->score+=a;
  augmenter_niveau(J);
}

void augmenter_niveau(jeu* J){
  while(J->score>=J->palier){
    J->niveau++;
    J->palier=50*(J->niveau)*(J->niveau+1);
  }
}
