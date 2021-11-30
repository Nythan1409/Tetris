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

void chute(tetrimino* t, jeu* J, tetrimino* poche){
  int bouton;
  int droitstock=1;
  int tick, timer;
  int chuterapide=0, pieceposee=0, piecevide=0;
  MLV_Event event;
  MLV_Keyboard_button sym;
  MLV_Keyboard_modifier mod;
  MLV_Button_state state;
  afficher_grille(J);
  preshot(t,J);
  afficher_piece(t);
  tick=MLV_get_time();
  while(!pieceposee){
    do{
      tick=MLV_get_time();
      nouvelle_image(tick, t, J);
      event=MLV_get_event(&sym, &mod, &bouton, NULL, NULL, NULL, NULL, NULL, &state);
      if (event== MLV_KEY){
	if (state==MLV_PRESSED){
	  if (sym==MLV_KEYBOARD_s){
	    chuterapide=chute_rapide(t, J);
	    break;
	  }
	  if (sym==MLV_KEYBOARD_q){
	    if(!est_a_gauche(t, J)){
	      t->posx--;
	    }
	  }
	  if (sym==MLV_KEYBOARD_d){
	    if(!est_a_droite(t, J)){
	      t->posx++;
	    }
	  }
	  if (sym==MLV_KEYBOARD_e){
	    rotation_d(t, J);
	  }
	  if (sym==MLV_KEYBOARD_a){
	    rotation_g(t, J);
	  }
	  if (sym==MLV_KEYBOARD_z){
	    if(droitstock==1){
	      stocker(t, poche);
	      droitstock=0;
	      if (t->type==8){
		piecevide=1;
		break;
	      }
	    }
	  }
	}
      }
    } while((!test_tick(J, tick)));
    if (chuterapide||piecevide){
      new_tick(J, tick);
      chuterapide=0;
      piecevide=0;
      inclure_piece(t, J);
      break;
    }
    bouton=0;
    if (est_en_bas(t, J)){
      if (tick-timer==J->timeallowed) {
	inclure_piece(t, J);
	pieceposee=1;
      }
      else{
	timer=tick;
      }
    }
    else{
      t->posy++;
    }
    new_tick(J,tick);
  }
}
int chute_rapide(tetrimino* t, jeu *J){
  while(!est_en_bas(t, J)){
    t->posy++;
  }
  return 1;
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
    J->vitesse*=1.2;
    J->palier=50*(J->niveau)*(J->niveau+1);
  }
}

void stocker(tetrimino* t, tetrimino* poche){
  tetrimino transition;
  t->posx=3;
  t->posy=0;
  copier_piece(&transition, poche);
  copier_piece(poche, t);
  copier_piece(t, &transition);
  afficher_poche(poche);
}

int test_tick(jeu* J, int tick){ 
  int diff;
  diff=tick-(J->lasttick);
  if (diff>=J->timeallowed){
    return 1;
  }
  return 0;
}

void new_tick(jeu* J, int tick){
  J->timeallowed=1000/J->vitesse;
  J->lasttick=tick;
}


/*void rst_mov_tick(jeu* J,time_t tick){
  if (difftime(J->lasttick, tick)<((J->timeallowed)/(J->vitesse*2))){
    J->timeallowed+=0.1;
  }
  }*/

int fin_partie(jeu J){
  int x;
  for(x=0;x<10;x++){
    if(J.mat[x][0]!=0){
      return 1;
    }
  }
  return 0;
}

void enregistrer_score(jeu J, FILE* fichier){
  int c1, c2, c3;
  MLV_clear_window(MLV_COLOR_BLACK);
  MLV_draw_text(100, 100, "Entrez votre nom (3 lettres)", MLV_COLOR_WHITE);
  MLV_actualise_window();
  while(c1<65 || (c1>90 && c1<97) || c1>122){
    MLV_wait_keyboard(NULL, NULL, &c1);
    if(c1>=97){
      c1-=32;
    }
  }
  MLV_draw_text(50, 150, &c1, MLV_COLOR_WHITE);
  MLV_actualise_window();
  while(c2<65 || (c2>90 && c2<97) || c2>122){
    MLV_wait_keyboard(NULL, NULL, &c2);
    if(c2>=97){
      c2-=32;
    }
  }
  MLV_draw_text(100, 150, &c2, MLV_COLOR_WHITE);
  MLV_actualise_window();
  while(c3<65 || (c3>90 && c3<97) || c3>122){
    MLV_wait_keyboard(NULL, NULL, &c3);
    if(c3>=97){
      c3-=32;
    }
  }
  MLV_draw_text(150, 150, &c3, MLV_COLOR_WHITE);
  MLV_actualise_window();
  fprintf(fichier, "%c%c%c %d\n", c1, c2, c3, J.score);
}
