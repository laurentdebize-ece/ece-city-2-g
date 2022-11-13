#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

#define LARGEURFENETRE 1250
#define HAUTEURFENETRE 660
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TAILLEPOLICEBOUTTONNORMALE 20
#define TAILLEPOLICEBOUTTONGRANDE 40
#define TAILLEPOLICETITRE 90
#define BOUTTONX1 SCREEN_WIDTH -130
#define BOUTTONY1 SCREEN_HEIGHT - 700
#define BOUTTONX2 SCREEN_WIDTH -30
#define BOUTTONY2 SCREEN_HEIGHT - 650
#define NOMBREBOUTTONJEU1 4
#define NOMBREBOUTTONJEU 6

#define NOMBRECOLONNE 45
#define NOMBRELIGNE 35
#define XCHRONO 1100
#define YCHRONO 45
#define X1GRILLE 20
#define X2GRILLE 740
#define Y1GRILLE 20
#define Y2GRILLE 580

#define X1OUTIL 830
#define X2OUTIL 1200
#define Y1OUTIL 240
#define Y2OUTIL 300

#define X1NIVEAU0 830
#define X2NIVEAU0 970
#define Y1NIVEAU0 320
#define Y2NIVEAU0 360
#define X1NIVEAU1 830
#define X2NIVEAU1 970
#define Y1NIVEAU1 380
#define Y2NIVEAU1 420
#define X1NIVEAU2 830
#define X2NIVEAU2 970
#define Y1NIVEAU2 440
#define Y2NIVEAU2 480
#define X1DESTRUCTION 830
#define X2DESTRUCTION 970
#define Y1DESTRUCTION 500
#define Y2DESTRUCTION 540

#define X1TERRAIN 1050
#define X2TERRAIN 1200
#define Y1TERRAIN 320
#define Y2TERRAIN 360
#define X1CITERNE 1050
#define X2CITERNE 1200
#define Y1CITERNE 380
#define Y2CITERNE 420
#define X1USINE 1050
#define X2USINE 1200
#define Y1USINE 440
#define Y2USINE 480
#define X1ROUTE 1050
#define X2ROUTE 1200
#define Y1ROUTE 500
#define Y2ROUTE 540

#define X1ARGENT 830
#define X2ARGENT 970
#define Y1ARGENT 140
#define Y2ARGENT 180
#define X1HABITANT 830
#define X2HABITANT 970
#define Y1HABITANT 180
#define Y2HABITANT 220

#define X1CAPEAU 1050
#define X2CAPEAU 1200
#define Y1CAPEAU 140
#define Y2CAPEAU 180
#define X1CAPELEC 1050
#define X2CAPELEC 1200
#define Y1CAPELEC 180
#define Y2CAPELEC 220




#define MONTER  1
#define DESCENDRE 3
#define DROITE 2
#define GAUCHE 4
#define NOMBREOBSTACLESDIFFERENT 9

#define CONSTRUCTION1 3
#define CONSTRUCTION2 3
#define CONSTRUCTION3 3

typedef struct Bouton{
    short  x1Bouton, y1Bouton, x2Bouton, y2Bouton, taillePolice, action;
    char nomBouton[20];
    ALLEGRO_COLOR couleurBouton, couleurTexte, couleurPassageBouton;
    struct Bouton * bouton;
}Bouton;


typedef struct Case{
    short x1Case, x2Case, y1Case, y2Case, obstacle;
    ALLEGRO_COLOR couleurCase;
}Case;

Case matriceCase[NOMBRELIGNE][NOMBRECOLONNE];


typedef struct Joueur{
    int numJoueur,  ligne, colonne;
} Joueur;

Bouton tabBoutonPause[3];


void initAllegro(){
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    //al_install_keyboard();
    al_install_mouse();
    //al_install_audio();
    //al_init_acodec_addon();
}

/*void initialiserObstacle(){
    tabObstacle[CONSTRUCTION1] = al_load_bitmap("");
    tabObstacle[CONSTRUCTION2] = al_load_bitmap("");
    tabObstacle[CONSTRUCTION3] = al_load_bitmap("");
}
 */


float largeurCaseGrille(short x1, short x2){
    return (x2 - x1)/NOMBRECOLONNE;
}
float hauteurCaseGrille(short y1, short y2){
    return (y2 - y1)/NOMBRELIGNE;
}
float coordonneX1CaseGrille(short x1, short x2,short noCollonne) {
    return x1 + largeurCaseGrille(x1, x2) * (noCollonne - 1);
}
float coordonneX2CaseGrille(short x1, short x2,short noCollonne) {
    return x1 + largeurCaseGrille(x1, x2) * noCollonne;
}
float coordonneY1CaseGrille( short y1,  short y2,short noLigne) {
    return y1 + hauteurCaseGrille(y1,y2) * (noLigne- 1);
}
float coordonneY2CaseGrille( short y1,  short y2,short noLigne) {
    return y1 + hauteurCaseGrille(y1,y2) * (noLigne);
}
void initialiserCasesGrille(){
    for(short i = 0; i<NOMBRELIGNE; i++){
        for(short j = 0; j < NOMBRECOLONNE; j++){
            matriceCase[i][j].x1Case = coordonneX1CaseGrille(X1GRILLE, X2GRILLE, j+1);
            matriceCase[i][j].y1Case = coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, i+1);
            matriceCase[i][j].x2Case = coordonneX2CaseGrille(X1GRILLE, X2GRILLE, j+1);
            matriceCase[i][j].y2Case = coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, i+1);
            matriceCase[i][j].obstacle = 0;
            matriceCase[i][j].couleurCase = al_map_rgba(0,0,0,0);
        }
    }
}

/*
Bouton * initialiserTabBouton(){
    strcpy(tabBouton[3].nomBouton, "boite à outil");
    tabBouton[3].couleurBouton = al_map_rgb(180,180,180);
    tabBouton[3].couleurTexte = al_map_rgb(0,0,0);
    tabBouton[3].couleurPassageBouton = al_map_rgb(200,0,0);
    tabBouton[3].x1Bouton = 740 ;
    tabBouton[3].x2Bouton = 830;
    tabBouton[3].y1Bouton = 620;
    tabBouton[3].y2Bouton = 655;
    tabBouton[3].taillePolice =15 ;
    return &tabBouton[0];
}
*/

void initDonneesJeu(){
    //initialiserTabBouton();
    initialiserCasesGrille();
    //initialiserObstacle();
}


void dessinerArrierePlanMenu(ALLEGRO_BITMAP *imageMenu){
    al_draw_scaled_bitmap(imageMenu, 0, 0, 1280, 738, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
}

void dessinerBouton(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexte,short taillePolice ){
    al_draw_filled_rectangle(x1, y1, x2, y2,couleur);
    al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(50,50,50), 2);
    al_draw_text(policeTexte, al_map_rgb(0,0,0),(x1 +x2)/2-10 - strlen(texte)*taillePolice/5, (y2+y1)/2-taillePolice/2,0,texte );
}


void dessinerCadre(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur ){
    al_draw_filled_rectangle(x1, y1, x2, y2,couleur);
    al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(50,50,50), 2);
}


ALLEGRO_FONT* initialiserPoliceTexte2(short taillePolice){
    ALLEGRO_FONT* policeTexte = NULL ;
    policeTexte = al_load_ttf_font("../Bangers-Regular.ttf", taillePolice,0);
    return policeTexte;
}

ALLEGRO_FONT* initialiserPoliceTexteGrande(short taillePoliceGrande){
    ALLEGRO_FONT* policeTexteGrande = NULL ;
    policeTexteGrande = al_load_ttf_font("../Bangers-Regular.ttf", taillePoliceGrande,0);
    return policeTexteGrande;
}

ALLEGRO_FONT* initialiserPoliceTexteTitre(short taillePoliceTitre){
    ALLEGRO_FONT* policeTexteTitre = NULL ;
    policeTexteTitre = al_load_ttf_font("../Bangers-Regular.ttf", taillePoliceTitre,0);
    return policeTexteTitre;
}

void dessinerBoutonGrand(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexteGrande,short taillePoliceGrande ){
    al_draw_filled_rectangle(x1, y1, x2, y2,couleur);
    al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(50,50,50), 2);
    al_draw_text(policeTexteGrande, al_map_rgb(0,0,0),(x1 +x2)/2-15 - strlen(texte)*taillePoliceGrande/5, (y2+y1)/2-taillePoliceGrande/2,0,texte );
}

void dessinerInformationsGenerales(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(BOUTTONX1, BOUTTONY1, BOUTTONX2, BOUTTONY2, al_map_rgb(100,100,100), "retour", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBoutonGrand(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 3, al_map_rgb(100,100,100), "SIMS", policeTexte, TAILLEPOLICEBOUTTONGRANDE);
    dessinerBoutonGrand(SCREEN_WIDTH / 20, SCREEN_HEIGHT / 2 - 30, SCREEN_WIDTH / 3,SCREEN_HEIGHT /2+30, al_map_rgb(100,100,100), "Realise par :", policeTexte, TAILLEPOLICEBOUTTONGRANDE);
    dessinerBouton(SCREEN_WIDTH / 20, SCREEN_HEIGHT - 300, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 250, al_map_rgb(100,100,100), "Emilien", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(SCREEN_WIDTH / 20, SCREEN_HEIGHT - 240, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 190, al_map_rgb(100,100,100), "Lucie", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(SCREEN_WIDTH / 20, SCREEN_HEIGHT - 180, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 130, al_map_rgb(100,100,100), "Rémi", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(SCREEN_WIDTH / 20, SCREEN_HEIGHT - 120, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 70, al_map_rgb(100,100,100), "Amaury", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
}
void dessinerTitre(ALLEGRO_FONT* policeTexteTitre){
    al_draw_text(policeTexteTitre, al_map_rgb(0,0,0), SCREEN_WIDTH / 4 -20, SCREEN_HEIGHT / 8, 0, "ECE CITY");
}
void dessinerBoutonMenu(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande, ALLEGRO_FONT* policeTexteTitre){
    dessinerTitre(policeTexteTitre);
    dessinerBoutonGrand(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 -60, SCREEN_WIDTH / 2 + 100,SCREEN_HEIGHT / 2+20, al_map_rgb(254, 177, 43), "Jouer", policeTexteGrande, TAILLEPOLICEBOUTTONGRANDE);
    dessinerBouton(SCREEN_WIDTH / 10 + 100, SCREEN_HEIGHT - 100, SCREEN_WIDTH / 3-50, SCREEN_HEIGHT - 50, al_map_rgb(226, 177, 107), "regles", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(SCREEN_WIDTH / 2 + 190, SCREEN_HEIGHT - 100, SCREEN_WIDTH - 300, SCREEN_HEIGHT - 50, al_map_rgb(226, 177, 107), "credit", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
}
void dessinerRegleDuJeu(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(BOUTTONX1, BOUTTONY1, BOUTTONX2, BOUTTONY2, al_map_rgb(100,100,100), "retour", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(SCREEN_WIDTH /20+100,50 , SCREEN_WIDTH/2 + 100 , 120, al_map_rgb(100,100,100), "Regle du Jeu", policeTexteGrande, TAILLEPOLICEBOUTTONGRANDE);
}

void dessinerTexteRegleDuJeu(ALLEGRO_FONT* policeTexte){
    al_draw_text(policeTexte, al_map_rgb(0,0,0), SCREEN_WIDTH - SCREEN_WIDTH + 50, SCREEN_HEIGHT-450,0,"L'objectif de ce jeu est de developper sa ville" );
    al_draw_text(policeTexte, al_map_rgb(0,0,0), SCREEN_WIDTH - SCREEN_WIDTH + 50, SCREEN_HEIGHT-400,0,"Differents modes de jeu vous serons propose afin de vous amuser au maximum" );
    al_draw_text(policeTexte, al_map_rgb(0,0,0), SCREEN_WIDTH - SCREEN_WIDTH + 50, SCREEN_HEIGHT-350,0,"Construiser des batiments toujours plus grands et plus nombreux afin d'augmenter le nombre d'habitants" );
    al_draw_text(policeTexte, al_map_rgb(0,0,0), SCREEN_WIDTH - SCREEN_WIDTH + 50, SCREEN_HEIGHT-300,0,"Gerer votre budget afin de pouvoir alimenter en eau et en electricite chaque habitation" );
    al_draw_text(policeTexte, al_map_rgb(0,0,0), SCREEN_WIDTH - SCREEN_WIDTH + 50, SCREEN_HEIGHT-250,0,"Arriverez-vous a être maire de cette ville et a la diriger ?" );
    al_draw_text(policeTexte, al_map_rgb(0,0,0), SCREEN_WIDTH - SCREEN_WIDTH + 50, SCREEN_HEIGHT-200,0,"A vous d’etre strategique pour y parvenir " );
}

void dessinerBoutonSelectionMode(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(SCREEN_WIDTH /20+100,50 , SCREEN_WIDTH/2 + 100 , 120, al_map_rgb(100,100,100), "MODES DE JEU", policeTexteGrande, TAILLEPOLICEBOUTTONGRANDE);
    dessinerBouton(SCREEN_WIDTH / 12, SCREEN_HEIGHT - 500, SCREEN_WIDTH / 3 - 50, SCREEN_HEIGHT - 420, al_map_rgb(243,134,124), "Communisme", policeTexteGrande, TAILLEPOLICEBOUTTONGRANDE);
    dessinerBouton(SCREEN_WIDTH / 12, SCREEN_HEIGHT - 300, SCREEN_WIDTH / 3 - 50, SCREEN_HEIGHT - 220, al_map_rgb(243,134,124), "Capitalisme", policeTexteGrande, TAILLEPOLICEBOUTTONGRANDE);
    dessinerBouton(SCREEN_WIDTH -130, SCREEN_HEIGHT - 700, SCREEN_WIDTH -30, SCREEN_HEIGHT - 650, al_map_rgb(183, 42, 81), "retour", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
}

void afficherChrono(double angle, ALLEGRO_COLOR couleur){
    al_draw_circle(XCHRONO, YCHRONO, 30,couleur, 5 );
    al_draw_filled_circle(XCHRONO, YCHRONO, 5, couleur);
    al_draw_line(XCHRONO, YCHRONO - 30, XCHRONO, YCHRONO - 36, couleur, 4);
    al_draw_line(XCHRONO -3, YCHRONO - 35, XCHRONO +3, YCHRONO - 35, couleur, 4);
    al_draw_filled_triangle(XCHRONO-cos(angle)*2, YCHRONO +sin(angle)*2, XCHRONO +cos(angle)*2, YCHRONO - sin(angle)*2, XCHRONO - sin(angle)*25, YCHRONO - cos(angle)*25, couleur);
}





void afficherTempsRestant(float tempsRestant,float mois, ALLEGRO_FONT* policeTexte){
    al_draw_textf(policeTexte, al_map_rgb(0,0,0), XCHRONO + 60, YCHRONO - 20,0,"%.1f secondes", tempsRestant);
    al_draw_textf(policeTexte, al_map_rgb(0,0,0), XCHRONO + 60, YCHRONO ,0,"%.0f mois", mois);
    double angle = (tempsRestant)*(-0.42);
    if(tempsRestant <= 3){
        afficherChrono(angle, al_map_rgb(190,0,0));
    }
    else{afficherChrono(angle, al_map_rgb(0,0,0));}
}


void dessinnerTouteCasesColorie() {
    for (short i = 0; i < NOMBRELIGNE; i++) {
        for (short j = 0; j < NOMBRECOLONNE; j++) {
            al_draw_filled_rectangle(matriceCase[i][j].x1Case, matriceCase[i][j].y1Case, matriceCase[i][j].x2Case,matriceCase[i][j].y2Case, matriceCase[i][j].couleurCase);
            }
        }
    }

ALLEGRO_FONT* initialiserPoliceTexte(short taillePolice){
    ALLEGRO_FONT* policeTexte = NULL ;
    policeTexte = al_load_ttf_font("../Bangers-Regular.ttf", taillePolice,0);
    return policeTexte;
}



bool checkSourisDansBouton(short xSouris, short ySouris, short x1, short y1,short x2, short y2 ){
    if(xSouris >= x1 && xSouris <= x2 && ySouris >= y1 && ySouris <= y2){
        return true;
    }
    else{return false;}
}

void dessinneGrille( int x1, int y1, int x2, int y2, int epaisseur, ALLEGRO_COLOR couleurGrille, ALLEGRO_FONT* policeTexte){
    float largeurCase = largeurCaseGrille(x1, x2);
    float hauteurCase = hauteurCaseGrille(y1, y2);
    for(int i = 0; i <= NOMBRECOLONNE; i++){
        al_draw_line( x1 + i*largeurCase, y1,x1 +i* largeurCase , y2, couleurGrille, epaisseur);
        if(i<NOMBRECOLONNE){
            al_draw_textf(policeTexte,couleurGrille, x1 + i*largeurCase +3, y1 - 13,0,"%d", i+1);}
    }
    for(int j = 0; j <= NOMBRELIGNE; j++){
        al_draw_line(x1, y1+ j*hauteurCase, x2, y1 + j*hauteurCase, couleurGrille, epaisseur);
        if(j<NOMBRELIGNE){
            al_draw_textf(policeTexte, couleurGrille,x1 -22, y1 + j*hauteurCase +2,0,"  %d", j+1 );}
    }
}




void colorierCaseGrille(short xSouris, short ySouris){
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),
                                      coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),
                                      coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),
                                      coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                matriceCase[j][i].couleurCase = al_map_rgba(80, 80, 80, 0.4);
            }
            /*
            else if(matriceCase[j][i].obstacle != -1){matriceCase[j][i].couleurCase = al_map_rgba(0,0,0, 0);}
            else if(matriceCase[j][i].obstacle == -1 ){matriceCase[j][i].couleurCase  = al_map_rgba(0,0,130,100);}
             */
        }
    }
}

void dessinerBoutonOutil(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(X1OUTIL, Y1OUTIL , X2OUTIL ,Y2OUTIL , al_map_rgb(150,150,150), "OUTILS", policeTexteGrande, TAILLEPOLICEBOUTTONGRANDE);
}

void dessinerBoiteOutil(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(X1NIVEAU0, Y1NIVEAU0 , X2NIVEAU0 ,Y2NIVEAU0 , al_map_rgb(150,150,150), "niveau 0", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1NIVEAU1, Y1NIVEAU1 , X2NIVEAU1 ,Y2NIVEAU1 , al_map_rgb(150,150,150), "iveau -1", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1NIVEAU2, Y1NIVEAU2 , X2NIVEAU2 ,Y2NIVEAU2 , al_map_rgb(150,150,150), "niveau -2", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1TERRAIN, Y1TERRAIN , X2TERRAIN ,Y2TERRAIN , al_map_rgb(150,150,150), "terrain", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1CITERNE, Y1CITERNE , X2CITERNE ,Y2CITERNE , al_map_rgb(150,150,150), "citerne", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1USINE, Y1USINE , X2USINE,Y2USINE , al_map_rgb(150,150,150), "usine", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1DESTRUCTION, Y1DESTRUCTION , X2DESTRUCTION ,Y2DESTRUCTION , al_map_rgb(150,150,150), "detruire", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1ROUTE, Y1ROUTE , X2ROUTE,Y2ROUTE , al_map_rgb(150,150,150), "route", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
}

void dessinerInfosJeu(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande,float argent , float habitant, float  capelec, float capeau) {
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X1ARGENT, Y1ARGENT,0,"argent : %.0f",argent );
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X1HABITANT,Y1HABITANT,0,"habitant : %.0f",habitant);
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X1CAPEAU, Y1CAPEAU,0,"cap eau : %.0f",capeau);
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X1CAPELEC, Y1CAPELEC,0,"cap elec : %.0f",capelec);
}

int main() {
    initAllegro();
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT_QUEUE *temps = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP *imageMenu = al_load_bitmap("../etape1.png");
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
    //al_register_event_source(queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(255, 255, 255));
    ALLEGRO_MOUSE_STATE sourisState;
    //ALLEGRO_KEYBOARD_STATE clavierState;
    short taillePolice = 14;
    short etape= 0;
    short mode = 0;
    short boite = 0;
    int argent = 500000;
    int habitant = 0;
    int capeau = 0;
    int capelec = 0;
    float tempsRestant = 0.0;
    short mois = 0;
    short niveau =0;
    ALLEGRO_FONT  * policeTexte = initialiserPoliceTexte(taillePolice);
    //ALLEGRO_FONT * policeTexte50 = initialiserPoliceTexte(50);
    ALLEGRO_FONT  * policeTexte2 = initialiserPoliceTexte2(TAILLEPOLICEBOUTTONNORMALE);
    ALLEGRO_FONT * policeTexteGrande = initialiserPoliceTexteGrande(TAILLEPOLICEBOUTTONGRANDE);
    ALLEGRO_FONT * policeTexteTitre = initialiserPoliceTexteTitre(TAILLEPOLICETITRE);
    initDonneesJeu();
    initialiserCasesGrille();
    bool fin = false;
    al_flip_display();
    do {
        al_wait_for_event(queue, &event);
        //ALLEGRO_KEYBOARD_STATE clavierState;
        //al_get_keyboard_state(&clavierState);
        al_get_mouse_state(&sourisState);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                fin = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                if (checkSourisDansBouton(sourisState.x, sourisState.y, BOUTTONX1, BOUTTONY1, BOUTTONX2, BOUTTONY2 )&& etape <=3) {
                    etape = 0;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 10 + 100, SCREEN_HEIGHT - 100, SCREEN_WIDTH / 3-50, SCREEN_HEIGHT - 50) && etape == 0) {
                    etape = 1;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 2 + 190, SCREEN_HEIGHT - 100, SCREEN_WIDTH - 300, SCREEN_HEIGHT - 50) && etape == 0) {
                    etape = 2;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 -60, SCREEN_WIDTH / 2 + 100,SCREEN_HEIGHT / 2+20) &&etape == 0) {
                    etape = 3;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 12, SCREEN_HEIGHT - 500, SCREEN_WIDTH / 3 - 50, SCREEN_HEIGHT - 420) && etape == 3) {
                    etape = 4;
                    mode = 1;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, SCREEN_WIDTH / 12, SCREEN_HEIGHT - 300, SCREEN_WIDTH / 3 - 50, SCREEN_HEIGHT - 220) && etape == 1) {
                    etape = 4;
                    mode = 2;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1OUTIL, Y1OUTIL, X2OUTIL, Y2OUTIL) && etape == 4 ) {
                    if(boite){
                        boite = 0;
                    }
                    else{
                        boite +=1;
                    }
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1NIVEAU0, Y1NIVEAU0, X2NIVEAU0, Y2NIVEAU0) && etape == 4 && boite) {
                    niveau =0;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1NIVEAU1, Y1NIVEAU1, X2NIVEAU1, Y2NIVEAU1) && etape == 4 && boite) {
                    niveau = 1;
                }
                if (checkSourisDansBouton(sourisState.x, sourisState.y, X1NIVEAU2, Y1NIVEAU2, X2NIVEAU2, Y2NIVEAU2) && etape == 4 && boite) {
                    niveau = 2;
                }
            }
        }
        if (etape == 0) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            //dessinerArrierePlanMenu(imageMenu);
            dessinerBoutonMenu(policeTexte,policeTexteGrande, policeTexteTitre);
        }
        if (etape==1){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            dessinerRegleDuJeu(policeTexte2,policeTexteGrande);
            dessinerCadre(SCREEN_WIDTH - SCREEN_WIDTH + 40,SCREEN_HEIGHT/3,SCREEN_WIDTH - 40 ,SCREEN_HEIGHT-100, al_map_rgb(50,50,50));
            dessinerTexteRegleDuJeu(policeTexte2);
        }
        if (etape==2){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            dessinerInformationsGenerales(policeTexte2,policeTexteGrande);
        }
        if (etape==3){
            al_clear_to_color(al_map_rgb(0, 0, 0));
            dessinerBoutonSelectionMode(policeTexte2, policeTexteGrande);
        }
        if (etape==4){
            if (event.type == ALLEGRO_EVENT_TIMER) {
                tempsRestant += 0.1;
                mois = tempsRestant/15;
                al_clear_to_color(al_map_rgb(255, 255, 255));
                dessinneGrille(X1GRILLE, Y1GRILLE, X2GRILLE, Y2GRILLE, 1, al_map_rgb(0, 0, 0), policeTexte);
                al_get_mouse_state(&sourisState);
                colorierCaseGrille(sourisState.x, sourisState.y);
                dessinnerTouteCasesColorie();
                afficherTempsRestant(tempsRestant,mois, policeTexte);
                dessinerBoutonOutil(policeTexte, policeTexte);
                dessinerInfosJeu(policeTexte, policeTexte,argent , habitant, capelec,capeau);
                if(boite){
                    dessinerBoiteOutil(policeTexte, policeTexte);
                }
                if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
                    al_flip_display();
                }
            }
            al_flip_display();
        }
        al_flip_display();
    }
    while (!fin);
    al_destroy_display(display);
    display = NULL;
    al_destroy_timer(timer);
    al_destroy_event_queue(temps);
    al_destroy_bitmap(imageMenu);
    return 0;
}