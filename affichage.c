#include "tetris.h"

void loadimage(){
  grille=MLV_load_image("./Images/grille.png");
  next=MLV_load_image("./Images/next.png");
  rouge=MLV_load_image("./Images/Rouge.png");
  orange=MLV_load_image("./Images/Orange.png");
  jaune=MLV_load_image("./Images/Jaune.png");
  vert=MLV_load_image("./Images/Vert.png");
  cyan=MLV_load_image("./Images/Cyan.png");
  bleu=MLV_load_image("./Images/Bleu.png");
  violet=MLV_load_image("./Images/Violet.png");
  blanc=MLV_load_image("./Images/Blanc.png");
  fondrouge=MLV_load_image("./Images/fondrouge.png");
  fondvert=MLV_load_image("./Images/fondvert.png");
  fondbleu=MLV_load_image("./Images/fondbleu.png");
  menu1=MLV_load_image("./Images/menu1.png");
  menu2=MLV_load_image("./Images/menu2.png");
  menu0=MLV_load_image("./Images/menu0.png");
  score=MLV_load_image("./Images/score.png");
}

void afficher_fond(){
  MLV_draw_image(fondvert, 0, 0);
}

void afficher_grille(jeu* J){ /* Nécessite d'avoir fait 8 MLV_load_image*/
  int x,y;
  MLV_draw_image(grille, 36, 36); /*grille est la première image*/
  for(x=0;x<10;x++){
    for(y=0;y<20;y++){
      switch(J->mat[x][y]){ /*Les autres sont les couleurs*/
      case 0:
	;
	break;
      case 1:
	MLV_draw_image(rouge, 36+(x+1)*12, 36+y*12);
	break;
      case 2:
	MLV_draw_image(orange, 36+(x+1)*12, 36+y*12);
	break;
      case 3:
	MLV_draw_image(jaune, 36+(x+1)*12, 36+y*12);
	break;
      case 4:
	MLV_draw_image(vert, 36+(x+1)*12, 36+y*12);
	break;
      case 5:
	MLV_draw_image(cyan, 36+(x+1)*12, 36+y*12);
	break;
      case 6:
	MLV_draw_image(bleu, 36+(x+1)*12, 36+y*12);
	break;
      case 7:
	MLV_draw_image(violet, 36+(x+1)*12, 36+y*12);
	break;
      }
    }
  }
  MLV_actualise_window();
}

void afficher_piece(tetrimino* t){
  int x,y;
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      switch(t->mat[x][y]){
      case 0:
	break;
      case 1:
	MLV_draw_image(rouge, 36+12*(t->posx+x+1), 36+12*(t->posy+y));
	break;
      case 2:
	MLV_draw_image(orange, 36+12*(t->posx+x+1), 36+12*(t->posy+y));
	break;
      case 3:
	MLV_draw_image(jaune, 36+12*(t->posx+x+1), 36+12*(t->posy+y));
	break;
      case 4:
	MLV_draw_image(vert, 36+12*(t->posx+x+1), 36+12*(t->posy+y));
	break;
      case 5:
	MLV_draw_image(cyan, 36+12*(t->posx+x+1), 36+12*(t->posy+y));
	break;
      case 6:
	MLV_draw_image(bleu, 36+12*(t->posx+x+1), 36+12*(t->posy+y));
	break;
      case 7:
	MLV_draw_image(violet, 36+12*(t->posx+x+1), 36+12*(t->posy+y));
	break;
      }
    }
  }
  MLV_actualise_window();
}

void afficher_next(tetrimino* t){
  int x,y;
  int a=2;
  if(t->type==3 || t->type==5){
    a=1;/*On sépare les cs pour un plus bel affichage*/
  }
  MLV_draw_image(next, 192, 60);
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      switch(t->mat[x][y]){
      case 0:
	break;
      case 1:
	MLV_draw_image(rouge, 192+12*(x+1), 60+12*(y+a));
	break;
      case 2:
	MLV_draw_image(orange, 192+12*(x+1), 60+12*(y+a));
	break;
      case 3:
	MLV_draw_image(jaune, 192+12*(x+1), 60+12*(y+a));
	break;
      case 4:
	MLV_draw_image(vert, 192+12*(x+1), 60+12*(y+a));
	break;
      case 5:
	MLV_draw_image(cyan, 192+12*(x+1), 60+12*(y+a));
	break;
      case 6:
	MLV_draw_image(bleu, 192+12*(x+1), 60+12*(y+a));
	break;
      case 7:
	MLV_draw_image(violet, 192+12*(x+1), 60+12*(y+a));
	break;
      }
    }
  }
  MLV_actualise_window();
}

void afficher_score(jeu* J){
  char n[20];
  sprintf(n, "%d", J->score);
  MLV_draw_image(score, 192, 144);
  MLV_draw_text(205, 154, n, MLV_COLOR_WHITE);
  MLV_actualise_window();
}

void afficher_niveau(jeu* J){
  char n[20];
  sprintf(n, "%d", J->niveau);
  MLV_draw_image(score, 192, 192);
  MLV_draw_text(205, 202, n, MLV_COLOR_WHITE);
  MLV_actualise_window();
}
