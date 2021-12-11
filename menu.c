#include "tetris.h"

int menu(){/*Renverra 1 pour un joueur, 2 pour Scores, 0 pour options*/
  int selection=-1;
  int curseur=1;
  char bout[20];
  MLV_Keyboard_button bouton;
  while(selection==-1){
    switch(curseur){
    case 1:
      MLV_draw_image(menu1, 0, 0);
      break;
    case 2:
      MLV_draw_image(menu2, 0, 0);
      break;
    case 3:
      MLV_draw_image(menu0, 0, 0);
      break;
    case 0:
      MLV_clear_window(MLV_COLOR_BLACK);
      MLV_draw_text(50,50, "Quiter", MLV_COLOR_WHITE);
      break;
    }
    MLV_actualise_window();
    MLV_wait_keyboard(&bouton, NULL, NULL);
    strcpy(bout,MLV_convert_keyboard_button_to_string(bouton));
    if(strcmp(bout,"MLV_KEYBOARD_UP")==0){
      curseur=(curseur-1)%4;
      if(curseur==-1){
	curseur=3;
      }
    }
    else{
      if(strcmp(bout,"MLV_KEYBOARD_DOWN")==0){
	curseur=(curseur+1)%4;
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

int menu_pause(){
  int selection=-1;
  int curseur=1;
  char bout[20];
  MLV_Keyboard_button bouton;
  while(selection==-1){
    switch(curseur){
    case 1:
      MLV_clear_window(MLV_COLOR_BLACK);
      MLV_draw_text(50,50, "Commandes", MLV_COLOR_WHITE);
      break;
    case 2:
      MLV_clear_window(MLV_COLOR_BLACK);
      MLV_draw_text(50,50, "Sauvegarder", MLV_COLOR_WHITE);
      break;
    case 0:
      MLV_clear_window(MLV_COLOR_BLACK);
      MLV_draw_text(50,50, "Reprendre", MLV_COLOR_WHITE);
      break;
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

int sous_menu_jouer(){
  int selection=-1;
  int curseur=0;
  char bout[20];
  MLV_Keyboard_button bouton;
  while(selection==-1){
    switch(curseur){
    case 0:
      MLV_clear_window(MLV_COLOR_BLACK);
      MLV_draw_text(50,50, "Nouvelle Partie", MLV_COLOR_WHITE);
      break;
    case 1:
      MLV_clear_window(MLV_COLOR_BLACK);
      MLV_draw_text(50,50, "Reprendre", MLV_COLOR_WHITE);
      break;
    }
    MLV_actualise_window();
    MLV_wait_keyboard(&bouton, NULL, NULL);
    strcpy(bout,MLV_convert_keyboard_button_to_string(bouton));
    if(strcmp(bout,"MLV_KEYBOARD_UP")==0){
      curseur=(curseur-1)%2;
      if(curseur==-1){
	curseur=1;
      }
    }
    else{
      if(strcmp(bout,"MLV_KEYBOARD_DOWN")==0){
	curseur=(curseur+1)%2;
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
