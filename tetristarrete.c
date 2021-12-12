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
  int reprendre=0;
  srand(time(NULL));
  MLV_create_window("Tetris", "rectangle", 600, 648);
  loadimage();
  while(1){
    afficher_fond(fond);
    switch(menu()){
    case 1:
      partie=fopen("./Partie", "r+");
      if(sauvegarde_existe(partie)){
	afficher_fond(fond);
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
	new_tick(&J, tick);
	break;
      }
      fclose(partie);
      afficher_fond(fond); /*On affiche les graphismes du jeu*/
      afficher_score(&J);
      afficher_niveau(&J);
      afficher_next(&suivant);
      afficher_poche(&poche);
      while(fini==0){ /**/
	pieceposee=0;
	J.droitstock=1;
	while (!pieceposee){
	  do{
	    pieceposee=0;
	    tick=MLV_get_time();
	    nouvelle_image(tick, &t, &J);
	    if (!evenement(&t, &poche, &J, tick)||J.piecevide){ /*On observe les evenements, si un evenement stoppe l'execution d'un tick, on rentre dans le if*/
	      new_tick(&J, tick); /*On inclut la pièce dans le jeu est on reinitialise le tick*/
	      J.piecevide=0;
	      inclure_piece(&t, &J);
	      augmenter_score(&J);
	      afficher_score(&J);
	      afficher_niveau(&J);
	      fini=fin_partie(J);
	      if (!fini){ /*Si le jeu n'est pas fini on recharge les tetriminos*/
		copier_piece(&t, &suivant);
		suivant=generer_piece();
		afficher_next(&suivant);
		afficher_poche(&poche);
	      }
	      pieceposee=1;
	      break;
	    }
	  }while (!test_tick(&J, tick));
	  if (J.pause) /*Si le jeu est mis en pause on quitte l'execution de la boucle*/
	    break;
	  if (est_en_bas(&t, &J)){
	    if (tick-timer==J.timeallowed) { /*Si la pièce est en bas et qu'un tick entier c'est écoulé, on inclut la pièce dans le jeu*//
	      inclure_piece(&t, &J);
	      augmenter_score(&J);
	      afficher_score(&J);
	      afficher_niveau(&J);
	      fini=fin_partie(J);
	      if (!fini){ /*Si la partie n'est pas finie, on recharge des nouveaux tetriminos*/
		copier_piece(&t, &suivant);
		suivant=generer_piece();
		afficher_next(&suivant);
		afficher_poche(&poche);
	      }
	      pieceposee=1;
	    }
	    else{
	      timer=tick; /*Si le temps depuis le dernier tick ne s'est pas écoulé, on stocke le temps dans le timer*/
	    }
	  }
	  else{
	    chute(&t); /*On fait chuter la pièce si la pièce n'est pas en bas*/
	  }
	  new_tick(&J,tick); /*Stocke un nouveau tick à la fin de l'exécution du dernier*/
	}
	while (J.pause){
	  afficher_fond(fond);
	  switch(menu_pause()){
	  case 1:
	    afficher_fond(fond); /*Réaffiche le jeu si on sort du menu*/
	    afficher_score(&J);
	    afficher_niveau(&J);
	    afficher_next(&suivant);
	    afficher_poche(&poche);
	    resume(&J, tick);
	    break;
	  case 2:
	    partie=fopen("./Partie", "w");
	    enregistrer_partie(J, partie, t, suivant, poche);
	    fclose(partie);
	    MLV_draw_text(50, 50, "Partie Sauvegardée", MLV_COLOR_WHITE);
	    MLV_actualise_window();
	    MLV_wait_seconds(2);
	    break;
	  case 0:
	    fini=2;/*Finir la partie sans enregistrer le score*/
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
      fond=options(fond);
      break;
    case 0:
      exit(EXIT_SUCCESS);
      break;
    }
  }
}
