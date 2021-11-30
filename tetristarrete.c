#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "tetris.h"

int main(){
  jeu J;
  tetrimino t, suivant, poche;
  srand(time(NULL));
  MLV_create_window("Tetris", "rectangle", 600, 648);
  loadimage();
  switch(menu()){
  case 1:
    afficher_fond();
    J=generer_jeu();
    afficher_score(&J);
    afficher_niveau(&J);
    suivant=generer_piece();
    poche=generer_piece();
    while(1){
      copier_piece(&t, &suivant);
      suivant=generer_piece();
      afficher_next(&suivant);
      afficher_poche(&poche);
      chute(&t,&J,&poche);
      augmenter_score(&J);
      afficher_score(&J);
      afficher_niveau(&J);
    }
    break;
  case 2:
    exit(EXIT_SUCCESS);
    break;
  case 0:
    exit(EXIT_SUCCESS);
    break;
  }
  exit(EXIT_SUCCESS);
}
