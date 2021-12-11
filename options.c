#include "tetris.h"

int options(){
  int selection=-1;
  int curseur=1;
  char bout[20];
  MLV_Keyboard_button bouton;
  while(selection==-1){
    MLV_clear_window(MLV_COLOR_BLACK);
    MLV_draw_text(50, 50, "Couleur du fond :", MLV_COLOR_WHITE);
    switch(curseur){
    case 1:
      MLV_draw_text(100, 100, "BLEU", MLV_COLOR_BLUE);
      break;
    case 2:
      MLV_draw_text(100, 100, "ROUGE", MLV_COLOR_RED);
      break;
    case 0:
      MLV_draw_text(100, 100, "VERT", MLV_COLOR_GREEN);
      break;
    }
    MLV_actualise_window();
    MLV_wait_keyboard(&bouton, NULL, NULL);
    strcpy(bout,MLV_convert_keyboard_button_to_string(bouton));
    if(strcmp(bout,"MLV_KEYBOARD_LEFT")==0){
      curseur=(curseur-1)%3;
      if(curseur==-1){
	curseur=2;
      }
    }
    else{
      if(strcmp(bout,"MLV_KEYBOARD_RIGHT")==0){
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
