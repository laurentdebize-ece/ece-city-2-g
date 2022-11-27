#include "ececity.h"

int main() {
    initAllegro();
    t_infosJeu InfosJeu;
    InfosJeu=recupererInfosJeu(InfosJeu);
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT_QUEUE *temps = NULL;
    ALLEGRO_EVENT event;
    al_reserve_samples(10);
    ALLEGRO_BITMAP *imageMenu = al_load_bitmap("../etape1.png");// images
    ALLEGRO_BITMAP *imageCabane = al_load_bitmap("../CABANE.png");
    ALLEGRO_BITMAP *imageMaison = al_load_bitmap("../house1.png");
    ALLEGRO_BITMAP *imageTerrain = al_load_bitmap("../grass.png");
    ALLEGRO_BITMAP *imageImmeuble = al_load_bitmap("../immeuble.png");
    ALLEGRO_BITMAP *imageUsine = al_load_bitmap("../Nuclear.png");
    ALLEGRO_BITMAP *imageGratteCiel = al_load_bitmap("../Skyscraper.png");
    ALLEGRO_BITMAP *imageCiterne = al_load_bitmap("../watertower.png");
    ALLEGRO_SAMPLE *son = al_load_sample("../The-Sims-Soundtrack_-Buy-Mode-1.ogg");
    ALLEGRO_SAMPLE_INSTANCE *instanceSon = al_create_sample_instance(son);//musique
    al_set_sample_instance_playmode(instanceSon,ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(instanceSon,al_get_default_mixer());
    al_set_audio_stream_gain(instanceSon, 0.5f);
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_TIMER *timer = NULL;
    queue = al_create_event_queue();
    display = al_create_display(LARGEURFENETRE, HAUTEURFENETRE);
    timer = al_create_timer(0.1);
    al_set_window_position(display, 0, 0);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_start_timer(timer);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(255, 255, 255));
    ALLEGRO_MOUSE_STATE sourisState;
    ALLEGRO_KEYBOARD_STATE clavierState;
    short taillePolice = 14;
    short etape = 0;
    short mode = 0;
    short boite = 0;

    InfoGeneral* infoGeneral=malloc(sizeof (InfoGeneral));
    infoGeneral->argent = 500000;
    infoGeneral->habitant = 0;
    infoGeneral->capeau = 0;
    infoGeneral->capelec = 0;
    infoGeneral->nombreMaison = -1;
    infoGeneral->nombreCiterne = -1;
    infoGeneral->nbConstruction=-1;
    infoGeneral->nombreUsine = -1;
    infoGeneral->graphe= CreerGraphe(50); // creer le graphe vide d'ordre sommets
    double tempsRestant = 0.0;
    short mois = 0;
    short niveau = 0;
    short destruction = 0;
    short terrain = 0;
    short usinec = 0;
    short citernec = 0;
    short route = 0;
    short pause = 0;
    Maison maison;
    Usine usine;
    Citerne citerne;
    souris souris1;
    ALLEGRO_FONT *policeTexte = initialiserPoliceTexte(taillePolice);
    ALLEGRO_FONT *policeTexte2 = initialiserPoliceTexte2(TAILLEPOLICEBOUTTONNORMALE);
    ALLEGRO_FONT *policeTexteGrande = initialiserPoliceTexteGrande(TAILLEPOLICEBOUTTONGRANDE);
    ALLEGRO_FONT *policeTexteTitre = initialiserPoliceTexteTitre(TAILLEPOLICETITRE);
    initDonneesJeu();
    initialiserCasesGrille();
    bool end = false;
    al_flip_display();
    do {
        chercherCaseDeLaSourie(sourisState.x, sourisState.y, &souris1.Casex, &souris1.Casey, &souris1.interieurPlateau);
        al_wait_for_event(queue, &event);
        ALLEGRO_KEYBOARD_STATE clavierState;
        al_get_keyboard_state(&clavierState);
        al_get_mouse_state(&sourisState);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE : { //fermeture de la fenêtre si croix en haut à droite
                end = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : { //si on appuis je bouton de la souris
                if (checkSourisDansBouton(sourisState.x, sourisState.y, BOUTTONX1, BOUTTONY1, BOUTTONX2, BOUTTONY2) &&
                    etape <= 3) {
                    etape = 0; //etape 0 : menu      1 : regle      2 : crédits     3 : modes       4 : interface de jeu
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 10 + 100, SCREEN_HEIGHT - 100,
                                          SCREEN_WIDTH / 3 - 50, SCREEN_HEIGHT - 50) && etape == 0) {
                    etape = 1;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 2 + 190, SCREEN_HEIGHT - 100,
                                          SCREEN_WIDTH - 300, SCREEN_HEIGHT - 50) && etape == 0) {
                    etape = 2;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 60,
                                          SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 + 20) && etape == 0) {
                    etape = 3;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 12, SCREEN_HEIGHT - 500,
                                          SCREEN_WIDTH / 3 - 50, SCREEN_HEIGHT - 420) && etape == 3) {
                    etape = 4;
                    al_play_sample_instance(instanceSon);
                    mode = 1;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 12, SCREEN_HEIGHT - 300,
                                          SCREEN_WIDTH / 3 - 50, SCREEN_HEIGHT - 220) && etape == 3) {
                    etape = 4;
                    al_play_sample_instance(instanceSon);
                    mode = 2;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1OUTIL, Y1OUTIL, X2OUTIL, Y2OUTIL) &&
                    etape == 4) {
                    if (boite) {
                        boite = 0;
                    } else {
                        boite += 1;
                    }
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1NIVEAU0, Y1NIVEAU0, X2NIVEAU0, Y2NIVEAU0) &&
                    etape == 4 && boite) {
                    niveau = 0;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1NIVEAU1, Y1NIVEAU1, X2NIVEAU1, Y2NIVEAU1) &&
                    etape == 4 && boite) {
                    niveau = 1;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1NIVEAU2, Y1NIVEAU2, X2NIVEAU2, Y2NIVEAU2) &&
                    etape == 4 && boite) {
                    niveau = 2;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1DESTRUCTION, Y1DESTRUCTION, X2DESTRUCTION,
                                          Y2DESTRUCTION) && etape == 4 && boite) {
                    terrain = 0, citernec = 0, usinec = 0, route = 0;
                    if (destruction) {
                        destruction = 0;
                    } else {
                        destruction += 1;
                    }
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1TERRAIN, Y1TERRAIN, X2TERRAIN, Y2TERRAIN) &&
                    etape == 4 && boite) {
                    destruction = 0, citernec = 0, usinec = 0, route = 0;
                    if (terrain) {
                        terrain = 0;
                    } else {
                        terrain += 1;
                    }
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1CAPELEC, Y1CITERNE, X2CITERNE, Y2CITERNE) &&
                    etape == 4 && boite) {
                    destruction = 0, terrain = 0, usinec = 0, route = 0;
                    if (citernec) {
                        citernec = 0;
                    } else {
                        citernec += 1;
                    }
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1USINE, Y1USINE, X2USINE, Y2USINE) &&
                    etape == 4 && boite) {
                    destruction = 0, terrain = 0, citernec = 0, route = 0;
                    if (usinec) {
                        usinec = 0;
                    } else {
                        usinec += 1;
                    }
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1ROUTE, Y1ROUTE, X2ROUTE, Y2ROUTE) &&
                    etape == 4 && boite) {
                    destruction = 0, terrain = 0, citernec = 0, usinec = 0;
                    if (route) {
                        route = 0;
                    } else {
                        route += 1;
                    }
                }
                if (etape == 4 && route) {
                    infoGeneral=construireroute(sourisState.x, sourisState.y, souris1.Casex, souris1.Casey,infoGeneral);
                }
                if (etape == 4 && terrain) {
                    infoGeneral=construireterrain(sourisState.x, sourisState.y, souris1.Casex, souris1.Casey, infoGeneral);
                }
                if (etape == 4 && citernec) {
                    infoGeneral=construireciterne(sourisState.x, sourisState.y, souris1.Casex, souris1.Casey, infoGeneral,
                                                  imageCiterne);
                }
                if (etape == 4 && usinec) {
                    infoGeneral=construireusine(sourisState.x, sourisState.y, souris1.Casex, souris1.Casey, infoGeneral);
                }
                if (etape == 4 && destruction) {
                    infoGeneral=destructionConstruction(sourisState.x,sourisState.y,souris1.Casex,souris1.Casey,infoGeneral);
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1PAUSE, Y1PAUSE,X2PAUSE, Y2PAUSE) && etape == 4) {
                    if(pause){
                        pause = 0;
                    }
                    else{
                        pause = 1;
                    }
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1SAUVEGARDE, Y1SAUVEGARDE,X2SAUVEGARDE, Y2SAUVEGARDE) && pause == 1) {
                    etape = 0;
                    sauvegarde();
                }
            }
            case ALLEGRO_EVENT_KEY_DOWN : { //si on appuie sur une touche du clavier
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_SPACE : {
                        if (pause){
                            pause = 0;
                        }
                        else{
                            pause = 1;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_ENTER : {
                        if (etape == 0){
                            etape = 3;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_0 : {
                        if (etape == 4){
                            niveau = 0;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_1 : {
                        if (etape == 4){
                            niveau = 1;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_2 : {
                        if (etape == 4){
                            niveau = 2;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_O : {
                        if (etape == 4){
                            if (boite){
                                boite = 0;
                            }
                            else{
                                boite = 1;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_KEY_C : {
                        if (etape == 4){
                            if (citernec){
                                citernec = 0;
                            }
                            else{
                                usinec = 0; route = 0;terrain = 0;destruction = 0;citernec = 1;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_KEY_U : {
                        if (etape == 4){
                            if (usinec){
                                usinec = 0;
                            }
                            else{
                                route = 0;terrain = 0;destruction = 0;citernec = 0;usinec = 1;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_KEY_R : {
                        if (etape == 4){
                            if (route){
                                route = 0;
                            }
                            else{
                                terrain = 0;destruction = 0;citernec = 0;usinec = 0;route = 1;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_KEY_T : {
                        if (etape == 4){
                            if (terrain){
                                terrain = 0;
                            }
                            else{
                                destruction = 0;citernec = 0;usinec = 0;route = 0;terrain = 1;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_KEY_D : {
                        if (etape == 4){
                            if (destruction){
                                destruction = 0;
                            }
                            else{
                                citernec = 0;usinec = 0;route = 0;terrain = 0;destruction = 1;
                            }
                        }
                        break;
                    }
                    case ALLEGRO_KEY_LEFT : {
                        if (etape < 4){
                            etape = 0;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_A : {
                        if (etape == 3){
                            mode = 1;
                            etape = 4;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_Z : {
                        if (etape == 3){
                            mode = 2;
                            etape = 4;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_Q : {
                        if (etape == 0){
                            etape = 1;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_W : {
                        if (etape == 0){
                            etape = 2;
                        }
                        break;
                    }
                    case ALLEGRO_KEY_S : {
                        if (pause == 1){
                            etape = 0;
                            sauvegarde();
                        }
                        break;
                    }
                }
            }
        }
        if (etape == 0) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //dessinerArrierePlanMenu(imageMenu);
            dessinerBoutonMenu(policeTexte, policeTexteGrande, policeTexteTitre);
        }
        if (etape == 1) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            dessinerRegleDuJeu(policeTexte2, policeTexteGrande);
            dessinerCadre(SCREEN_WIDTH - SCREEN_WIDTH + 40, SCREEN_HEIGHT / 3, SCREEN_WIDTH - 40, SCREEN_HEIGHT - 100,
                          al_map_rgb(50, 50, 50));
            dessinerTexteRegleDuJeu(policeTexte2);
        }
        if (etape == 2) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            dessinerInformationsGenerales(policeTexte2, policeTexteGrande);
        }
        if (etape == 3) {//interface mode
            al_clear_to_color(al_map_rgb(0, 0, 0));
            dessinerBoutonSelectionMode(policeTexte2, policeTexteGrande);
        }
        if (etape == 4) {//interface de jeu
            if (event.type == ALLEGRO_EVENT_TIMER) {
                al_clear_to_color(al_map_rgb(255, 255, 255));
                //dessinneGrille(X1GRILLE, Y1GRILLE, X2GRILLE, Y2GRILLE, 1, al_map_rgb(0, 0, 0), policeTexte);
                al_get_mouse_state(&sourisState);
                colorierCaseSouris(sourisState.x, sourisState.y, niveau, policeTexte, imageCiterne,imageCabane,imageMaison,imageImmeuble,imageGratteCiel,imageTerrain,imageUsine);
                dessinnerTouteCasesColorie();
                afficherTempsRestant(tempsRestant, mois, policeTexte);
                dessinerBoutonOutil(policeTexte, policeTexte);
                dessinerInfosJeu(policeTexte, souris1.Casex,souris1.Casey,infoGeneral);
                if (boite) {
                    dessinerBoiteOutil(policeTexte, policeTexte);
                }
                if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
                    al_flip_display();
                }
                if (pause){
                    dessinerSauvegarde(policeTexte, policeTexte);
                }
                else if (tempsRestant >= 15.0) {
                    tempsRestant = 0.0;
                    mois++;
                    infoGeneral=evolutionTerrain(infoGeneral, &mode);
                    infoGeneral->argent = infoGeneral->argent+ 10 * infoGeneral->habitant;
                } else {
                    tempsRestant += 0.1;
                }
            }
        }
        al_flip_display();
    } while (!end);

    //destruction
    al_destroy_display(display);
    display = NULL;
    al_destroy_timer(timer);
    al_destroy_event_queue(temps);
    al_destroy_bitmap(imageMenu);
    al_destroy_bitmap(imageTerrain);
    al_destroy_bitmap(imageCabane);
    al_destroy_bitmap(imageMaison);
    al_destroy_bitmap(imageImmeuble);
    al_destroy_bitmap(imageUsine);
    al_destroy_bitmap(imageCiterne);
    al_destroy_bitmap(imageGratteCiel);
    return 0;
}