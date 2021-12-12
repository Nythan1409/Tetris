#include "tetris.h"

int menu(){/*Affiche le menu principal, puis retourne l'entier correspondant à la sélection du joueur*/
  int selection=-1;/*Reste à -1 tant que l'utilisateur ne fait pas de choix*/
  int curseur=1;/*Montre à l'utilsateur quel choix il fera s'il appuie sur Entrée*/
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
      MLV_draw_image(menu3, 0, 0);
      break;
    case 0:
      MLV_draw_image(menu0, 0, 0);
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

int menu_pause(){/*Affiche le menu de pause et renvoie la sélection du joueur, sur le même principe que le menu principal*/
  int selection=-1;
  int curseur=1;
  char bout[20];
  MLV_Keyboard_button bouton;
  while(selection==-1){
    switch(curseur){
    case 1:
      MLV_draw_image(pause1, 0, 0);
      break;
    case 2:
      MLV_draw_image(pause2, 0, 0);
      break;
    case 0:
      MLV_draw_image(pause0, 0, 0);
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

int sous_menu_jouer(){/*Affiche le sous-menu de jeu et renvoie la sélection du joueur, sur le même principe que le menu principal*/
  int selection=-1;
  int curseur=0;
  char bout[20];
  MLV_Keyboard_button bouton;
  while(selection==-1){
    switch(curseur){
    case 0:
      MLV_draw_image(sousmenu1, 0, 0);
      break;
    case 1:
      MLV_draw_image(sousmenu0, 0, 0);
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

int options(int fond){/*Affiche le menu des options et renvoie la sélection du joueur, sur le même principe que le menu principal, prend la valeur du fond en paramètre pour commencer sur la sélection actuelle du joueur*/
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
