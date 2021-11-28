#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "tetris.h"

int main(){
  jeu J;
  tetrimino t, suivant;
  srand(time(NULL));
  MLV_create_window("Tetris", "rectangle", 250, 500);
  loadimage();
  if(menu()==1){
    MLV_clear_window(MLV_COLOR_BLACK);
    J=generer_jeu();
    suivant=generer_piece();
    while(1<2){
      copier_piece(&t, &suivant);
      suivant=generer_piece();
      chute(&t,&J);
      lignes_completes(&J);
    }
  }
  exit(EXIT_SUCCESS);
}
