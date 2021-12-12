#include "tetris.h"

int options(int fond){
  int selection=-1;
  int curseur=fond;
  char bout[20];
  MLV_Keyboard_button bouton;
  while(selection==-1){
    afficher_fond(curseur);
    switch(curseur){
    case 1:
      MLV_draw_image(menuo1, 0, 0);
      break;
    case 2:
      MLV_draw_image(menuo2, 0, 0);
      break;
    case 0:
      MLV_draw_image(menuo0, 0, 0);
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
