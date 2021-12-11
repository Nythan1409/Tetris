#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "tetris.h"

int main(){
  jeu J;
  tetrimino t, suivant, poche;
  int fini;
  int pieceposee=0;
  FILE* scores;
  FILE* partie;
  int tick, timer=0;
  int fond=1;
  int reprendre;
  srand(time(NULL));
  MLV_create_window("Tetris", "rectangle", 600, 648);
  loadimage();
  while(1){
    switch(menu()){
    case 1:
      partie=fopen("./Partie", "r+");
      if(sauvegarde_existe(partie)){
	reprendre=sous_menu_jouer();
      }
      fini=0;
      switch(reprendre){
      case 0:
	J=generer_jeu();
	suivant=generer_piece();
	poche=piece_vide();
	copier_piece(&t, &suivant);
	suivant=generer_piece();
	break;
      case 1:
	charger_partie(&J, partie, &t, &suivant, &poche);
	break;
      }
      fclose(partie);
      afficher_fond(fond);
      afficher_score(&J);
      afficher_niveau(&J);
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
	  switch(menu_pause()){
	  case 1:
	    ;
	    break;
	  case 2:
	    partie=fopen("./Partie", "w");
	    enregistrer_partie(J, partie, t, suivant, poche);
	    fclose(partie);
	    fini=2;/*Finir la partie sans enregistrer le score*/
	    resume(&J, tick);
	    break;
	  case 0:
	    afficher_fond(fond);
	    afficher_score(&J);
	    afficher_niveau(&J);
	    afficher_next(&suivant);
	    afficher_poche(&poche);
	    resume(&J, tick);
	    break;
	  }
	}
      }
      if(fini==1){
	scores=fopen("./Scores", "a+");
	enregistrer_score(J, scores);
	fclose(scores);
      }
      break;
    case 2:
      scores=fopen("./Scores", "r+");
      top_10(scores);
      fclose(scores);
      MLV_wait_seconds(5);
      break;
    case 3:
      fond=options();
      break;
    case 0:
      exit(EXIT_SUCCESS);
      break;
    }
  }
}
