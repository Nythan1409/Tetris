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
}


void afficher_grille(jeu* J){ /* Nécessite d'avoir fait 8 MLV_load_image*/
  int x,y;
  MLV_draw_image(grille, 0, 0); /*grille est la première image*/
  for(x=0;x<10;x++){
    for(y=0;y<20;y++){
      switch(J->mat[x][y]){ /*Les autres sont les couleurs*/
      case 0:
	;
	break;
      case 1:
	MLV_draw_image(rouge, (x+1)*12, y*12);
	break;
      case 2:
	MLV_draw_image(orange, (x+1)*12, y*12);
	break;
      case 3:
	MLV_draw_image(jaune, (x+1)*12, y*12);
	break;
      case 4:
	MLV_draw_image(vert, (x+1)*12, y*12);
	break;
      case 5:
	MLV_draw_image(cyan, (x+1)*12, y*12);
	break;
      case 6:
	MLV_draw_image(bleu, (x+1)*12, y*12);
	break;
      case 7:
	MLV_draw_image(violet, (x+1)*12, y*12);
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
	MLV_draw_image(rouge, 12*(t->posx+x+1), 12*(t->posy+y));
	break;
      case 2:
	MLV_draw_image(orange, 12*(t->posx+x+1), 12*(t->posy+y));
	break;
      case 3:
	MLV_draw_image(jaune, 12*(t->posx+x+1), 12*(t->posy+y));
	break;
      case 4:
	MLV_draw_image(vert, 12*(t->posx+x+1), 12*(t->posy+y));
	break;
      case 5:
	MLV_draw_image(cyan, 12*(t->posx+x+1), 12*(t->posy+y));
	break;
      case 6:
	MLV_draw_image(bleu, 12*(t->posx+x+1), 12*(t->posy+y));
	break;
      case 7:
	MLV_draw_image(violet, 12*(t->posx+x+1), 12*(t->posy+y));
	break;
      }
    }
  }
  MLV_actualise_window();
}
