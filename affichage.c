#include "tetris.h"

void loadimage(){
  grille=MLV_load_image("./Images/grille.png");
  next=MLV_load_image("./Images/next.png");
  rouge=MLV_load_image("./Images/rouge.png");
  orange=MLV_load_image("./Images/orange.png");
  jaune=MLV_load_image("./Images/jaune.png");
  vert=MLV_load_image("./Images/vert.png");
  cyan=MLV_load_image("./Images/cyan.png");
  bleu=MLV_load_image("./Images/bleu.png");
  violet=MLV_load_image("./Images/violet.png");
  blanc=MLV_load_image("./Images/blanc.png");
  fondrouge=MLV_load_image("./Images/fondrouge.png");
  fondvert=MLV_load_image("./Images/fondvert.png");
  fondbleu=MLV_load_image("./Images/fondbleu.png");
  menu1=MLV_load_image("./Images/menu1.png");
  menu2=MLV_load_image("./Images/menu2.png");
  menu3=MLV_load_image("./Images/menu3.png");
  menu0=MLV_load_image("./Images/menu0.png");
  menuo1=MLV_load_image("./Images/menuoptions1.png");
  menuo2=MLV_load_image("./Images/menuoptions2.png");
  menuo0=MLV_load_image("./Images/menuoptions0.png");
  pause1=MLV_load_image("./Images/pause1.png");
  pause2=MLV_load_image("./Images/pause2.png");
  pause0=MLV_load_image("./Images/pause0.png");
  sousmenu1=MLV_load_image("./Images/sousmenu1.png");
  sousmenu0=MLV_load_image("./Images/sousmenu0.png");
  score=MLV_load_image("./Images/score.png");
  ombrerouge=MLV_load_image("./Images/ombrerouge.png");
  ombreorange=MLV_load_image("./Images/ombreorange.png");
  ombrejaune=MLV_load_image("./Images/ombrejaune.png");
  ombrevert=MLV_load_image("./Images/ombrevert.png");
  ombrecyan=MLV_load_image("./Images/ombrecyan.png");
  ombrebleu=MLV_load_image("./Images/ombrebleu.png");
  ombreviolet=MLV_load_image("./Images/ombreviolet.png");
}

void afficher_fond(int fond){
  switch(fond){
  case 1:
    MLV_draw_image(fondbleu, 0, 0);
    break;
  case 2:
    MLV_draw_image(fondrouge, 0, 0);
    break;
  case 0:
    MLV_draw_image(fondvert, 0, 0);
    break;
  }
}

void afficher_grille(jeu* J){ /* Nécessite d'avoir fait 8 MLV_load_image*/
  int x,y;
  MLV_draw_image(grille, 72, 72); /*grille est la première image*/
  for(x=0;x<10;x++){
    for(y=0;y<20;y++){
      switch(J->mat[x][y]){ /*Les autres sont les couleurs*/
      case 0:
	;
	break;
      case 1:
	MLV_draw_image(rouge, 72+(x+1)*24, 72+y*24);
	break;
      case 2:
	MLV_draw_image(orange, 72+(x+1)*24, 72+y*24);
	break;
      case 3:
	MLV_draw_image(jaune, 72+(x+1)*24, 72+y*24);
	break;
      case 4:
	MLV_draw_image(vert, 72+(x+1)*24, 72+y*24);
	break;
      case 5:
	MLV_draw_image(cyan, 72+(x+1)*24, 72+y*24);
	break;
      case 6:
	MLV_draw_image(bleu, 72+(x+1)*24, 72+y*24);
	break;
      case 7:
	MLV_draw_image(violet, 72+(x+1)*24, 72+y*24);
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
	MLV_draw_image(rouge, 72+24*(t->posx+x+1), 72+24*(t->posy+y));
	break;
      case 2:
	MLV_draw_image(orange, 72+24*(t->posx+x+1), 72+24*(t->posy+y));
	break;
      case 3:
	MLV_draw_image(jaune, 72+24*(t->posx+x+1), 72+24*(t->posy+y));
	break;
      case 4:
	MLV_draw_image(vert, 72+24*(t->posx+x+1), 72+24*(t->posy+y));
	break;
      case 5:
	MLV_draw_image(cyan, 72+24*(t->posx+x+1), 72+24*(t->posy+y));
	break;
      case 6:
	MLV_draw_image(bleu, 72+24*(t->posx+x+1), 72+24*(t->posy+y));
	break;
      case 7:
	MLV_draw_image(violet, 72+24*(t->posx+x+1), 72+24*(t->posy+y));
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
    a=1;/*On sépare les cas pour un plus bel affichage*/
  }
  MLV_draw_image(next, 384, 120);
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      switch(t->mat[x][y]){
      case 0:
	break;
      case 1:
	MLV_draw_image(rouge, 384+24*(x+1), 120+24*(y+a));
	break;
      case 2:
	MLV_draw_image(orange, 384+24*(x+1), 120+24*(y+a));
	break;
      case 3:
	MLV_draw_image(jaune, 384+24*(x+1), 120+24*(y+a));
	break;
      case 4:
	MLV_draw_image(vert, 384+24*(x+1), 120+24*(y+a));
	break;
      case 5:
	MLV_draw_image(cyan, 384+24*(x+1), 120+24*(y+a));
	break;
      case 6:
	MLV_draw_image(bleu, 384+24*(x+1), 120+24*(y+a));
	break;
      case 7:
	MLV_draw_image(violet, 384+24*(x+1), 120+24*(y+a));
	break;
      }
    }
  }
  MLV_actualise_window();
}

void afficher_score(jeu* J){
  char n[20];
  sprintf(n, "%d", J->score);
  MLV_draw_image(score, 384, 288);
  MLV_draw_text(410, 308, n, MLV_COLOR_WHITE);
  MLV_actualise_window();
}

void afficher_niveau(jeu* J){
  char n[20];
  sprintf(n, "%d", J->niveau);
  MLV_draw_image(score, 384, 384);
  MLV_draw_text(410, 404, n, MLV_COLOR_WHITE);
  MLV_actualise_window();
}

void preshot(tetrimino* t, jeu* J){
  tetrimino ombre;
  int x,y;
  copier_piece(&ombre, t);
  while(!est_en_bas(&ombre, J)){
    ombre.posy++;
  }
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      switch(t->mat[x][y]){
      case 0:
	break;
      case 1:
	MLV_draw_image(ombrerouge, 72+24*(ombre.posx+x+1), 72+24*(ombre.posy+y));
	break;
      case 2:
	MLV_draw_image(ombreorange, 72+24*(ombre.posx+x+1), 72+24*(ombre.posy+y));
	break;
      case 3:
	MLV_draw_image(ombrejaune, 72+24*(ombre.posx+x+1), 72+24*(ombre.posy+y));
	break;
      case 4:
	MLV_draw_image(ombrevert, 72+24*(ombre.posx+x+1), 72+24*(ombre.posy+y));
	break;
      case 5:
	MLV_draw_image(ombrecyan, 72+24*(ombre.posx+x+1), 72+24*(ombre.posy+y));
	break;
      case 6:
	MLV_draw_image(ombrebleu, 72+24*(ombre.posx+x+1), 72+24*(ombre.posy+y));
	break;
      case 7:
	MLV_draw_image(ombreviolet, 72+24*(ombre.posx+x+1), 72+24*(ombre.posy+y));
	break;
      }
    }
  }
  MLV_actualise_window();
}

void afficher_poche(tetrimino* t){
    int x,y;
  int a=2;
  if(t->type==3 || t->type==5){
    a=1;/*On sépare les cas pour un plus bel affichage*/
  }
  MLV_draw_image(next, 384, 480);
  for(x=0;x<4;x++){
    for(y=0;y<4;y++){
      switch(t->mat[x][y]){
      case 0:
	break;
      case 1:
	MLV_draw_image(rouge, 384+24*(x+1), 480+24*(y+a));
	break;
      case 2:
	MLV_draw_image(orange, 384+24*(x+1), 480+24*(y+a));
	break;
      case 3:
	MLV_draw_image(jaune, 384+24*(x+1), 480+24*(y+a));
	break;
      case 4:
	MLV_draw_image(vert, 384+24*(x+1), 480+24*(y+a));
	break;
      case 5:
	MLV_draw_image(cyan, 384+24*(x+1), 480+24*(y+a));
	break;
      case 6:
	MLV_draw_image(bleu, 384+24*(x+1), 480+24*(y+a));
	break;
      case 7:
	MLV_draw_image(violet, 384+24*(x+1), 480+24*(y+a));
	break;
      }
    }
  }
  MLV_actualise_window();
}

void nouvelle_image(int tick, tetrimino* t, jeu* J){
  if (tick%(1000/25)==0){
    afficher_grille(J);
    preshot(t,J);
    afficher_piece(t);
  }
}
