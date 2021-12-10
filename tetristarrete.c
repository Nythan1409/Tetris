#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "tetris.h"

int main(){
  jeu J;
  tetrimino t, suivant, poche;
  int fini=0;
  int pieceposee=0;
  FILE* scores;
  int tick, timer=0;
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
      copier_piece(&t, &suivant);
      suivant=generer_piece();
      afficher_next(&suivant);
      afficher_poche(&poche);
      while(fini==0){
	pieceposee=0;
	J.droitstock=1;
	while (!pieceposee){
	  do{
	    pieceposee=0;
	    tick=MLV_get_time();
	    nouvelle_image(tick, &t, &J);
	    if (!evenement(&t, &poche, &J, tick)||J.piecevide){
	      new_tick(&J, tick);
	      J.piecevide=0;
	      inclure_piece(&t, &J);
	      augmenter_score(&J);
	      afficher_score(&J);
	      afficher_niveau(&J);
	      fini=fin_partie(J);
	      if (!fini){
		copier_piece(&t, &suivant);
		suivant=generer_piece();
		afficher_next(&suivant);
		afficher_poche(&poche);
	      }
	      pieceposee=1;
	      break;
	    }
	  }while (!test_tick(&J, tick));
	  if (J.pause)
	    break;
	  if (est_en_bas(&t, &J)){
	    if (tick-timer==J.timeallowed) {
	      inclure_piece(&t, &J);
	      augmenter_score(&J);
	      afficher_score(&J);
	      afficher_niveau(&J);
	      fini=fin_partie(J);
	      if (!fini){
		copier_piece(&t, &suivant);
		suivant=generer_piece();
		afficher_next(&suivant);
		afficher_poche(&poche);
	      }
	      pieceposee=1;
	    }
	    else{
	      timer=tick;
	    }
	  }
	  else{
	    chute(&t);
	  }
	  new_tick(&J,tick);
	}
	while (J.pause){
	  MLV_draw_filled_rectangle(0,0,500,500, MLV_COLOR_BLACK);
	  MLV_actualise_window();
	}
      }
      scores=fopen("./Scores", "a+");
      enregistrer_score(J, scores);
      fclose(scores);
      fini=0;
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
