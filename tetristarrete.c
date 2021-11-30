#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "tetris.h"

int main(){
  jeu J;
  tetrimino t, suivant, poche;
  int fini=0;
  FILE* scores;
  srand(time(NULL));
  MLV_create_window("Tetris", "rectangle", 600, 648);
  loadimage();
  while(1){
    switch(menu()){
    case 1:
      afficher_fond();
      J=generer_jeu();
      afficher_score(&J);
      afficher_niveau(&J);
      suivant=generer_piece();
      poche=piece_vide();
      while(fini==0){
	copier_piece(&t, &suivant);
	suivant=generer_piece();
	afficher_next(&suivant);
	afficher_poche(&poche);
	chute(&t,&J,&poche);
	augmenter_score(&J);
	afficher_score(&J);
	afficher_niveau(&J);
	fini=fin_partie(J);
      }
      scores=fopen("./Scores", "a+");
      enregistrer_score(J, scores);
      fclose(scores);
      break;
    case 2:
      scores=fopen("./Scores", "r+");
      top_10(scores);
      fclose(scores);
      MLV_wait_seconds(5);
      break;
    case 0:
      exit(EXIT_SUCCESS);
      break;
    }
  }
}
