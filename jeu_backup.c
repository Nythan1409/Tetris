void chute(tetrimino* t, jeu* J, tetrimino* poche){
  int bouton;
  int droitstock=1;
  int tick;
  int chuterapide=0;
  MLV_Event event;
  MLV_Keyboard_button sym;
  MLV_Keyboard_modifier mod;
  MLV_Button_state state;
  afficher_grille(J);
  preshot(t,J);
  afficher_piece(t);
  while(!est_en_bas(t,J)){
    do{
      tick=MLV_get_time();
      nouvelle_image(tick, t, J);
      event=MLV_get_event(&sym, &mod, &bouton, NULL, NULL, NULL, NULL, NULL, &state);
      if (event== MLV_KEY){
	if (state==MLV_PRESSED){
	  if (sym==MLV_KEYBOARD_s){
	    chuterapide=chute_rapide(t, J);
	    break;
	  }
	  if (sym==MLV_KEYBOARD_q){
	    if(!est_a_gauche(t, J)){
	      t->posx--;
	    }
	  }
	  if (sym==MLV_KEYBOARD_d){
	    if(!est_a_droite(t, J)){
	      t->posx++;
	    }
	  }
	  if (sym==MLV_KEYBOARD_e){
	    rotation_d(t, J);
	  }
	  if (sym==MLV_KEYBOARD_a){
	    rotation_g(t, J);
	  }
	  if (sym==MLV_KEYBOARD_z){
	    if(droitstock==1){
	      stocker(t, poche);
	      droitstock=0;
	    }
	  }
	}
      }
    }while((!test_tick(J, tick)));
    if (!chuterapide){
      t->posy++;
    }
    new_tick(J,tick);
    bouton=0;
  }
  do{
    if (chuterapide)
      break;
    tick=MLV_get_time();
    nouvelle_image(tick, t, J);
    event=MLV_get_event(&sym, &mod, &bouton, NULL, NULL, NULL, NULL, NULL, &state);
    if (event== MLV_KEY){
      if (state==MLV_PRESSED){
	if (sym==MLV_KEYBOARD_s){
	  chuterapide=chute_rapide(t, J);
	  break;
	}
	if (sym==MLV_KEYBOARD_q){
	  if(!est_a_gauche(t, J)){
	    t->posx--;
	  }
	}
	if (sym==MLV_KEYBOARD_d){
	  if(!est_a_droite(t, J)){
	    t->posx++;
	  }
	}
	if (sym==MLV_KEYBOARD_e){
	  rotation_d(t, J);
	}
	if (sym==MLV_KEYBOARD_a){
	  rotation_g(t, J);
	}
	if (sym==MLV_KEYBOARD_z){
	  if(droitstock==1){
	    stocker(t, poche);
	    droitstock=0;
	  }
	}
      }
    }
  }while((!test_tick(J, tick)));
  chuterapide=0;
  inclure_piece(t, J);
}
