#include "tetris.h"

int position_impossible(tetrimino* t, jeu* J){ /*Fonction pour savoir si la position que le tetrimino a est impossible dans la matrice du jeu*/
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

int est_a_gauche(tetrimino* t, jeu* J){ /*Sert à savoir si la pièce ne peut plus se déplacer à gauche */
  int a;
  t->posx--;
  a=position_impossible(t, J);
  t->posx++;
  return a;
}

int est_a_droite(tetrimino* t, jeu* J){ /*Sert à savoir si la pièce ne peut plus se déplacer à droite */
  int a;
  t->posx++;
  a=position_impossible(t, J);
  t->posx--;
  return a;
}

int est_en_bas(tetrimino* t, jeu* J){ /*Sert à savoir si la pièce ne peut plus se déplacer en bas */
  int a;
  t->posy++;
  a=position_impossible(t, J);
  t->posy--;
  return a;
}

void inclure_piece(tetrimino* t, jeu* J){ /*Inclut la pièce dans la matrice du jeu*/
  int x,y;
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      if(t->mat[x][y]!=0){
	J->mat[x+t->posx][y+t->posy]=t->mat[x][y];
      }
    }
  }
}

void chute(tetrimino* t){ /*Fais descendre le tetrimino*/
  t->posy++;
}

int chute_rapide(tetrimino* t, jeu *J){ /*Fais descendre le tetrimino à la position la plus basse qu'il peut avoir*/
  while(!est_en_bas(t, J)){
    t->posy++;
  }
  return 1;
}

void rotation_d(tetrimino* t, jeu* J){ /*Fais une rotation pas la droite*/
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

void rotation_g(tetrimino* t, jeu* J){ /*Fais une rotation par la gauche*/
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

int lignes_completes(jeu* J){/*Renvoie le nombre de lignes complètes dans la grille et les supprime (à utiliser après la chute d'une pièce)*/
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

void augmenter_score(jeu* J){ /*Augmente le score suivant le nombre de lignes complétées*/
  int a;
  switch(lignes_completes(J)){
  case 0:
    a=1; /*1 point pas pièce posée*/
    break;
  case 1:
    a=100*J->niveau; /*100 points* le niveau pour une ligne complétée*/
    break;
  case 2:
    a=300*J->niveau; /*300 points* le niveau pour deux lignes complétées*/
    break;
  case 3:
    a=500*J->niveau; /*500 points* le niveau pour trois lignes complétées*/
    break;
  default:
    a=800*J->niveau; /*800 points* le niveau pour un tetris (=4 lignes complétées)*/
    break;
  }
  J->score+=a;
  augmenter_niveau(J);
}

void augmenter_niveau(jeu* J){ /*Fonction qui augmente le niveau*/
  while(J->score>=J->palier){
    J->niveau++;
    J->vitesse*=1.1; /*La vitesse du jeu est augmentée par les niveaux*/
    J->palier=50*(J->niveau)*(J->niveau+1);
  }
}

void stocker(tetrimino* t, tetrimino* poche){ /*Stock du tetrimino actif dans le jeu*/
  tetrimino transition;
  t->posx=3;
  t->posy=0;
  copier_piece(&transition, poche);
  copier_piece(poche, t);
  copier_piece(t, &transition);
  afficher_poche(poche);
}

int test_tick(jeu* J, int tick){ /*Teste si le temps passé depuis le dernier tick est passé ou non*/ 
  int diff;
  diff=tick-(J->lasttick);
  if (diff>=J->timeallowed){
    return 1;
  }
  return 0;
}

void new_tick(jeu* J, int tick){ /*Stocke un nouveau tick dans la variable jeu, le tick est le temps de la dernière action (ici la chute), il stocke aussi le temps autorisé au tick*/
  J->timeallowed=1000/J->vitesse; /*Le temps autorisé dépend de la vitesse du jeu*/
  J->lasttick=tick;
}


int fin_partie(jeu J){ /*Détermine si la partie est finie ou non*/
  int x;
  for(x=0;x<10;x++){
    if(J.mat[x][0]!=0){
      return 1;
    }
  }
  return 0;
}


int evenement(tetrimino* t, tetrimino* poche, jeu* J, int tick){ /*Execute les différents évenements qui occurent durant le jeu grâce à la fonction MLV_get_event(), renvoie 1 si la fonction doit continuer, 0 si elle doit s'arrêter */
  MLV_Event event;
  MLV_Keyboard_button sym;
  MLV_Keyboard_modifier mod;
  MLV_Button_state state;
  int continuer=1;
  event=MLV_get_event(&sym, &mod, NULL, NULL, NULL, NULL, NULL, NULL, &state);
  if (event== MLV_KEY){
    if (state==MLV_PRESSED){
      if (!(J->pause)){
	if (sym==MLV_KEYBOARD_DOWN){ /*Si la touche bas est pressée, la chute rapide est enclenchée*/
	  chute_rapide(t, J);
	  continuer=0;
	}
	if (sym==MLV_KEYBOARD_LEFT){ /*Si la touche gauche est pressée, le tetrimino va à gauche*/
	  if(!est_a_gauche(t, J)){
	    t->posx--;
	  }
	}
	if (sym==MLV_KEYBOARD_RIGHT){ /*Si la touche droite est pressée, le tetrimino va à droite*/
	  if(!est_a_droite(t, J)){
	    t->posx++;
	  }
	}
	if (sym==MLV_KEYBOARD_z){ /*Si la touche z est pressée, la rotation droite est faite*/
	  rotation_d(t, J);
	}
	if (sym==MLV_KEYBOARD_a){ /*Si la touche a est pressée, la rotation gauche est faite*/
	  rotation_g(t, J);
	}
	if (sym==MLV_KEYBOARD_SPACE){ /*Si la touche Escpace est pressée, le tetrimino est stocké*/
	  if(J->droitstock){
	    stocker(t, poche);
	    J->droitstock=0;
	    if (t->type==8){
	      J->piecevide=1;
	    }
	  }
	}
	if (sym==MLV_KEYBOARD_ESCAPE){ /*Si la touche Echap est pressée, la pause est enclenchée*/
	  set_pause(J);
	}
      }
    }
  }
  return continuer;
}

void set_pause(jeu* J){ /*Met le jeu en pause*/
  J->pause=1; 
}

void resume(jeu* J, int tick){ /*Reprend l'execution du jeu*/
  J->pause=0;
  new_tick(J, tick);
}
