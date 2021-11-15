#include "header.h"

int menu(){/*Renverra 1 pour un joueur, 2 pour 2 joueurs, 0 pour options*/
  int selection=-1;
  int curseur=1;
  char bout[20];
  MLV_Keyboard_button bouton;
  MLV_create_window("Tetris", "rectangle", 640, 480);
  while(selection==-1){
    MLV_clear_window(MLV_COLOR_BLACK);
    if(curseur==1){
      MLV_draw_text(100,150,"1 Joueur", MLV_COLOR_YELLOW);
      MLV_draw_text(100,250,"2 Joueurs", MLV_COLOR_WHITE);
      MLV_draw_text(100,350,"Options", MLV_COLOR_WHITE);
    }
    else{
      if(curseur==2){
	MLV_draw_text(100,150,"1 Joueur", MLV_COLOR_WHITE);
	MLV_draw_text(100,250,"2 Joueurs", MLV_COLOR_YELLOW);
	MLV_draw_text(100,350,"Options", MLV_COLOR_WHITE);
      }
      else{
	if(curseur==0){
	  MLV_draw_text(100,150,"1 Joueur", MLV_COLOR_WHITE);
	  MLV_draw_text(100,250,"2 Joueurs", MLV_COLOR_WHITE);
	  MLV_draw_text(100,350,"Options", MLV_COLOR_YELLOW);
	}
      }
    }
    MLV_actualise_window();
    MLV_wait_keyboard(&bouton, NULL, NULL);
    strcpy(bout,MLV_convert_keyboard_button_to_string(bouton));
    if(strcmp(bout,"MLV_KEYBOARD_UP")==0){
      curseur=(curseur-1)%3;
      if(curseur==-1){
	curseur=2;
      }
    }
    else{
      if(strcmp(bout,"MLV_KEYBOARD_DOWN")==0){
	curseur=(curseur+1)%3;
      }
      else{
	if(strcmp(bout,"MLV_KEYBOARD_RETURN")==0){
	  selection=curseur;
	}
      }
    }
  }
  return selection;
}
