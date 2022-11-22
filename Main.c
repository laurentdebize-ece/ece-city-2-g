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
#define X1PAUSE 830
#define X2PAUSE 970
#define Y1PAUSE 560
#define Y2PAUSE 600
#define X1SAUVEGARDE 1050
#define X2SAUVEGARDE 1200
#define Y1SAUVEGARDE 560
#define Y2SAUVEGARDE 600

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
    short x1Case, x2Case, y1Case, y2Case, obstacle,etat,ordre;
    ALLEGRO_COLOR couleurCase;
}Case;

Case matriceCase[NOMBRELIGNE][NOMBRECOLONNE];

typedef struct souris{
    short Casex, Casey;
    bool interieurPlateau;
}souris;




typedef  struct Maison {
    //ALLEGRO_BITMAP image_stade_batiment[6];
    int largeur,hauteur;
    int date_creation;
    int caseX, caseY;
    int nb_habitant;
    int eau_utilise;
    int elec_utilise;
    int stade;
    int viable;
    int nbMaison
}Maison;

typedef  struct Usine {
    int caseX, caseY;
    int nbUsine;
}Usine;

typedef  struct Citerne {
    int caseX, caseY;
    int nbCiterne;
}Citerne;


typedef struct InfoGeneral{
    int argent;
    int habitant;
    int capelec; //capacité
    int capeau;
    Maison maison [100];
    Usine usine [10];
    Citerne citerne [10];
    int nombreMaison;
    int nombreUsine;
    int nombreCiterne;
}InfoGeneral;

/*
typedef  struct Maison_alimentee {
   int numero_maison;
   int quantite;
}Maison_alimentee;

typedef  struct Ressource {
   //ALLEGRO_BITMAPimage_batiment[2];
   int type;
   int largeur,hauteur;
   int caseX, caseY;
   int capacite_max;
   int capacite_utilisee;
   int nb_maison_alimentee;
   Maison_alimentee* tab_des_maisons_alimentee;
}Ressource;

typedef struct Plateau {
   int largeur_case;
   int nb_ligne;
   int nb_colonne;
   int compte_en_banque;
   int tab_des_prix;
   Case **map;
   int nb_stade_different;
   int tab_nb_habitant_pour_chaque_stade_de_maison;
   int nb_maison;
   Maison* tab_de_maison;
   int nb_chateau_eau;
   Ressource tab_chateau_eau;
   int nb_centrale_elec;
   Ressource tab_centrale_elec;
} Plateau;
*/
void initAllegro(){
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_audio();
    al_init_acodec_addon();
}
/*
void fichierTexte() {
    FILE *ifs = fopen("../fichierTexte", "r");
    Plateau *plateau;

    int largeur_case, nb_colonne, nb_ligne;
    int obstacle;
    int nb_stade, nb_habitant_necesaire;
    int banque_initial, prix;


    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }


    plateau->nb_colonne = NOMBRECOLONNE;
    plateau->nb_ligne = NOMBRELIGNE;
    plateau->largeur_case = 16;

    for (int i = 0; i < plateau->nb_ligne; i++) {
        for (int j = 0; j < plateau->nb_colonne; j++) {
            fscanf(ifs, "%d", &obstacle);
            plateau->map[i][j].obstacle = obstacle;
        }
    }

    fscanf(ifs, "%d", &nb_stade);
    plateau->nb_stade_different = nb_stade;
    for (int i = 0; i < plateau->nb_stade_different; i++) {
        fscanf(ifs, "%d", &nb_habitant_necesaire);
        //plateau->tab_nb_habitant_pour_chaque_stade_de_maison[i] = nb_habitant_necesaire;
    }
    plateau->compte_en_banque = banque_initial;
    for (int i = 0; i < 4; i++) {
        fscanf(ifs, "%d", &prix);
        //plateau->tab_des_prix[i] = prix;
    }

    plateau->nb_maison = 0;
    plateau->nb_chateau_eau = 0;
    plateau->nb_centrale_elec = 0;

    //return plateau;
}

void liresauv(Case tab[NOMBRELIGNE][NOMBRECOLONNE]) {
    FILE *ifs = fopen("../fichierTexte", "r");
    int etat;
    for (int i = 0; i < NOMBRELIGNE; ++i) {
        for (int j = 0; j < NOMBRECOLONNE; ++j) {
            fscanf(ifs, "%d", &etat);
            tab[i][j].etat = etat;
        }
    }
    fclose(ifs);
}

void sauvegarde(Case tab[NOMBRELIGNE][NOMBRECOLONNE]) {
    FILE *ifs = fopen("../fichierTexte", "w");
    int etat;
    for (int i = 0; i < NOMBRELIGNE; ++i) {
        for (int j = 0; j < NOMBRECOLONNE; ++j) {
            fprintf(ifs, "%d ", &etat);
            tab[i][j].etat = etat;
        }
        fprintf(ifs, "\n");
    }
    fclose(ifs);
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
            matriceCase[i][j].ordre=0;
            matriceCase[i][j].couleurCase = al_map_rgba(0,0,0,0);
        }
    }
}
void chercherCaseDeLaSourie(int x, int y, int *caseX, int *caseY, bool *dansPlateau) {
    if ((x >= 20 && x <= 920) && (y >= 20 && y <= 720)) {
        *dansPlateau = true;
    } else {
        *dansPlateau = false;
    }
    int a = 0;
    for (int i = 0; i < NOMBRELIGNE; i++) {
        for (int j = 0; j < NOMBRECOLONNE; j++) {
            if (((x - 20) >= j * 16 && (x - 20) <= (j + 1) * 16) &&
                ((y - 20) >= i * 16 && (y - 20) < (i + 1) * 16)) {
                *caseX = j;
                *caseY = i;
            } else {
                a++;
            }
        }
    }
    if (a == NOMBRECOLONNE * NOMBRELIGNE) {
        *caseX = 0;
        *caseY = 0;
    }
}

void initDonneesJeu(){
    //initialiserTabBouton();
    initialiserCasesGrille();
    //initialiserObstacle();
}


void dessinerArrierePlanMenu(ALLEGRO_BITMAP *imageMenu){
    al_draw_scaled_bitmap(imageMenu, 0, 0, 1280, 738, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
}
void dessinerTerrain(ALLEGRO_BITMAP *imageTerrain,int x,int y){
    al_draw_bitmap(imageTerrain, x, y, 1);
}
void dessinerCabane(ALLEGRO_BITMAP *imageCabane,int x,int y){
    al_draw_bitmap(imageCabane, x, y, 1);
}
void dessinerMaison(ALLEGRO_BITMAP *imageMaison,int x,int y){
    al_draw_bitmap(imageMaison, x, y, 1);
}
void dessinerImmeuble(ALLEGRO_BITMAP *imageImmeuble,int x,int y){
    al_draw_bitmap(imageImmeuble, x, y, 1);
}
void dessinerUsine(ALLEGRO_BITMAP *imageUsine,int x,int y){
    al_draw_bitmap(imageUsine, x, y, 1);
}
void dessinerGratteCiel(ALLEGRO_BITMAP *imageGratteCiel,int x,int y){
    al_draw_bitmap(imageGratteCiel, x, y, 1);
}
void dessinerCiterne(ALLEGRO_BITMAP *imageCiterne,int x,int y){
    al_draw_bitmap(imageCiterne, x, y, 1);
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

void dessinerBoiteOutil(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(X1NIVEAU0, Y1NIVEAU0 , X2NIVEAU0 ,Y2NIVEAU0 , al_map_rgb(150,150,150), "niveau 0", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1NIVEAU1, Y1NIVEAU1 , X2NIVEAU1 ,Y2NIVEAU1 , al_map_rgb(150,150,150), "niveau -1", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1NIVEAU2, Y1NIVEAU2 , X2NIVEAU2 ,Y2NIVEAU2 , al_map_rgb(150,150,150), "niveau -2", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1TERRAIN, Y1TERRAIN , X2TERRAIN ,Y2TERRAIN , al_map_rgb(150,150,150), "terrain", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1CITERNE, Y1CITERNE , X2CITERNE ,Y2CITERNE , al_map_rgb(150,150,150), "citerne", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1USINE, Y1USINE , X2USINE,Y2USINE , al_map_rgb(150,150,150), "usine", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1DESTRUCTION, Y1DESTRUCTION , X2DESTRUCTION ,Y2DESTRUCTION , al_map_rgb(150,150,150), "detruire", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1ROUTE, Y1ROUTE , X2ROUTE,Y2ROUTE , al_map_rgb(150,150,150), "route", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
    dessinerBouton(X1PAUSE, Y1PAUSE , X2PAUSE,Y2PAUSE , al_map_rgb(250,150,150), "pause", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
}

void dessinerSauvegarde(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(X1SAUVEGARDE, Y1SAUVEGARDE , X2SAUVEGARDE,Y2SAUVEGARDE , al_map_rgb(250,150,150), "sauvegarde", policeTexte, TAILLEPOLICEBOUTTONNORMALE);
}

void dessinerInfosJeu(ALLEGRO_FONT* policeTexteGrande,float xcase, float ycase, InfoGeneral* infoGeneral) {
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X1ARGENT, Y1ARGENT,0,"argent : %d", infoGeneral->argent);
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X1HABITANT,Y1HABITANT,0,"habitant : %d",infoGeneral->habitant);
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X1CAPEAU, Y1CAPEAU,0,"cap eau : %d",infoGeneral->capeau);
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X1CAPELEC, Y1CAPELEC,0,"cap elec : %d",infoGeneral->capelec);
    al_draw_textf(policeTexteGrande, al_map_rgb(0,0,0), X2GRILLE + 20, Y1GRILLE ,0,"case : [%.0f] [%.0f] ",xcase +1,ycase+1);
}

void afficherTempsRestant(float tempsRestant,float mois, ALLEGRO_FONT* policeTexte){
    al_draw_textf(policeTexte, al_map_rgb(0,0,0), XCHRONO + 60, YCHRONO - 20,0,"%.1f secondes", tempsRestant);
    al_draw_textf(policeTexte, al_map_rgb(0,0,0), XCHRONO + 60, YCHRONO ,0,"%.0f mois", mois);
    double angle = (tempsRestant)*(-0.42);
    if(tempsRestant >= 12){
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

void colorierCaseSouris(short xSouris, short ySouris,short niveau,ALLEGRO_FONT* policeTexte,ALLEGRO_BITMAP* imageCiterne,ALLEGRO_BITMAP* imageCabane,ALLEGRO_BITMAP* imageMaison,ALLEGRO_BITMAP* imageImmeuble,ALLEGRO_BITMAP* imageGratteCiel, ALLEGRO_BITMAP* imageTerrain,ALLEGRO_BITMAP* imageUsine){
    dessinneGrille(X1GRILLE, Y1GRILLE, X2GRILLE, Y2GRILLE, 1, al_map_rgb(0, 0, 0),policeTexte);
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                al_draw_filled_rectangle(coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j +1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i +1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),al_map_rgb(200,0,0));
            }
            if(niveau == 0){
                if (matriceCase[j][i].obstacle > 0 && matriceCase[j][i].obstacle != 6 && matriceCase[j][i].obstacle < 9) {
                    matriceCase[j][i].couleurCase = al_map_rgba(0, 0, 0,70);
                }
                if (matriceCase[j][i].etat == 1) {
                    al_draw_bitmap(imageTerrain, 16*i+20, 16*j+20, 0);
                }
                if (matriceCase[j][i].etat == 2) {
                    al_draw_bitmap(imageCabane, 16*i+20, 16*j+20, 0);
                }
                if (matriceCase[j][i].etat == 3) {
                    al_draw_bitmap(imageMaison, 16*i+20, 16*j+20, 0);
                }
                if (matriceCase[j][i].etat == 4) {
                    //matriceCase[j][i].couleurCase = al_map_rgb(100, 200, 0);
                    al_draw_bitmap(imageImmeuble, 16*i+20, 16*j+20, 0);
                }
                if (matriceCase[j][i].etat == 5) {
                    //matriceCase[j][i].couleurCase = al_map_rgb(200, 0, 100);
                    al_draw_bitmap(imageGratteCiel, 16*i+20, 16*j+20, 0);
                }
                if (matriceCase[j][i].obstacle == 6) {
                    matriceCase[j][i].couleurCase = al_map_rgb(40, 40, 40);
                }

                if (matriceCase[j][i].etat == 7) {
                    al_draw_bitmap(imageCiterne, 16*i+20, 16*j+20, 0);
                }
                if (matriceCase[j][i].etat == 8) {
                    al_draw_bitmap(imageUsine, 16*i+20, 16*j+20, 0);
                }
                if (matriceCase[j][i].obstacle == 9) {
                    matriceCase[j][i].couleurCase = al_map_rgba(200, 100, 40,200);
                }
            }
            if(niveau == 1){
                if (matriceCase[j][i].obstacle == 6) {
                    matriceCase[j][i].couleurCase = al_map_rgb(0, 100, 255);
                }
            }
            if(niveau == 2){
                if (matriceCase[j][i].obstacle == 6) {
                    matriceCase[j][i].couleurCase = al_map_rgb(200, 200, 0);
                }
            }
        }
    }
}

void construireroute(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral){
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                if((matriceCase[ycase][xcase].obstacle == 0 || matriceCase[ycase][xcase].obstacle == 9 )&& infoGeneral->argent >= 10) {
                    matriceCase[ycase][xcase].etat = 6;
                    matriceCase[ycase][xcase].obstacle = 6;
                    infoGeneral->argent -=10;
                }
            }
        }
    }
}

void construireterrain(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral){
    int caseVide = 0;
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                for(short k = 0; k< 3; k++) {
                    for (short l = 0; l < 3; l++) {
                        if((matriceCase[k + ycase][l + xcase].obstacle == 0 || matriceCase[k + ycase][ l + xcase].obstacle == 9)&& xcase<43 && ycase <33) {
                            caseVide ++;
                        }
                    }
                }
                if(caseVide == 9 && infoGeneral->argent >= 1000) {
                    infoGeneral->argent -= 1000;
                    infoGeneral->nombreMaison +=1;
                    infoGeneral->maison[infoGeneral->nombreMaison].caseX = xcase;
                    infoGeneral->maison[infoGeneral->nombreMaison].caseY = ycase;
                    for(short k = 0; k< 3; k++) {
                        for (short l = 0; l < 3; l++) {
                            matriceCase[k + ycase][l + xcase].obstacle = 1;
                            matriceCase[ycase][xcase].etat = 1;
                            matriceCase[ycase][xcase].ordre++;
                        }
                    }
                }
            }
        }
    }
}

void construireciterne(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral,ALLEGRO_BITMAP* imageCiterne ){
    short caseVide = 0;
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                for(short k = 0; k< 6; k++) {
                    for (short l = 0; l < 4; l++) {
                        if((matriceCase[k + ycase][ l + xcase].obstacle == 0 || matriceCase[k + ycase][ l + xcase].obstacle == 9) && xcase<42 && ycase <30) {
                            caseVide ++;
                        }
                    }
                }
                if(caseVide == 24 && infoGeneral->argent >= 100000){
                    infoGeneral->argent -=100000;
                    infoGeneral->nombreCiterne +=1;
                    infoGeneral->capeau +=5000;
                    infoGeneral->citerne[infoGeneral->nombreCiterne].caseX = xcase;
                    infoGeneral->citerne[infoGeneral->nombreCiterne].caseY = ycase;
                    for(short k = 0; k< 6; k++) {
                        for (short l = 0; l < 4; l++) {
                            matriceCase[k + ycase][l + xcase].obstacle = 7;
                            matriceCase[ycase][xcase].etat = 7;
                            matriceCase[ycase][xcase].ordre++;
                        }
                    }
                }
            }
        }
    }
}

int construireusine(short xSouris, short ySouris, short xcase , short ycase, InfoGeneral* infoGeneral){
    short caseVide = 0;
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                for(short k = 0; k< 6; k++) {
                    for (short l = 0; l < 4; l++) {
                        if((matriceCase[k + ycase][ l + xcase].obstacle == 0 || matriceCase[k + ycase][ l + xcase].obstacle == 9 )&& xcase<42 && ycase <30) {
                            caseVide ++;
                        }
                    }
                }
                if(caseVide == 24 && infoGeneral->argent >= 100000){
                    infoGeneral->argent -=100000;
                    infoGeneral->nombreUsine +=1;
                    infoGeneral->capelec +=5000;
                    infoGeneral->usine[infoGeneral->nombreUsine].caseX = xcase;
                    infoGeneral->usine[infoGeneral->nombreUsine].caseY = ycase;
                    for(short k = 0; k< 6; k++) {
                        for (short l = 0; l < 4; l++) {
                            matriceCase[k + ycase][l + xcase].obstacle = 8;
                            matriceCase[ycase][xcase].etat = 8;
                            matriceCase[ycase][xcase].ordre++;
                        }
                    }
                }
            }
        }
    }
}

void destructionConstruction(short xSouris, short ySouris, short xcase , short ycase){
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                if(matriceCase[ycase][xcase].etat == 7 || matriceCase[ycase][xcase].etat == 8){
                    matriceCase[ycase][xcase].etat = 0;
                    for(short k = 0; k< 6; k++) {
                        for (short l = 0; l < 4; l++) {
                            matriceCase[k + ycase][ l + xcase].obstacle = 9;
                        }
                    }
                }
                if(matriceCase[ycase][xcase].etat >0 && matriceCase[ycase][xcase].etat<6){
                    matriceCase[ycase][xcase].etat = 0;
                    for(short k = 0; k< 3; k++) {
                        for (short l = 0; l < 3; l++) {
                            matriceCase[k + ycase][ l + xcase].obstacle = 9;
                        }
                    }
                }
                if(matriceCase[ycase][xcase].etat == 6){
                    matriceCase[ycase][xcase].etat = 0;
                    matriceCase[ycase][xcase].obstacle = 9;
                }
            }
        }
    }
}

void evolutionTerrain(InfoGeneral* infoGeneral){
    for(short i = 0; i< NOMBRECOLONNE; i++) {
        for (short j = 0; j < NOMBRELIGNE; j++) {
            if(matriceCase[j][i].obstacle == 4 ){
                matriceCase[j][i].obstacle = 5;
                if(matriceCase[j][i].etat == 4 ) {
                    matriceCase[j][i].etat = 5;
                    infoGeneral->habitant+=900;
                }
            }
            if(matriceCase[j][i].obstacle == 3 ){
                matriceCase[j][i].obstacle = 4;
                if(matriceCase[j][i].etat == 3 ){
                    matriceCase[j][i].etat = 4;
                    infoGeneral->habitant+=50;
                }
            }
            if(matriceCase[j][i].obstacle == 2 ){
                matriceCase[j][i].obstacle = 3;
                if(matriceCase[j][i].etat == 2 ){
                    matriceCase[j][i].etat = 3;
                    infoGeneral->habitant+=40;
                }
            }
            if(matriceCase[j][i].obstacle == 1 ){
                matriceCase[j][i].obstacle = 2;
                if(matriceCase[j][i].etat == 1 ){
                    matriceCase[j][i].etat = 2;
                    infoGeneral->habitant+=10;
                }
            }
        }
    }
}



void dessinerBoutonOutil(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(X1OUTIL, Y1OUTIL , X2OUTIL ,Y2OUTIL , al_map_rgb(150,150,150), "OUTILS", policeTexteGrande, TAILLEPOLICEBOUTTONGRANDE);
}

int main() {
    initAllegro();
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT_QUEUE *temps = NULL;
    ALLEGRO_EVENT event;
    al_reserve_samples(10);
    ALLEGRO_BITMAP *imageMenu = al_load_bitmap("../etape1.png");
    ALLEGRO_BITMAP *imageCabane = al_load_bitmap("../CABANE.png");
    ALLEGRO_BITMAP *imageMaison = al_load_bitmap("../house1.png");
    ALLEGRO_BITMAP *imageTerrain = al_load_bitmap("../grass.png");
    ALLEGRO_BITMAP *imageImmeuble = al_load_bitmap("../immeuble.png");
    ALLEGRO_BITMAP *imageUsine = al_load_bitmap("../Nuclear.png");
    ALLEGRO_BITMAP *imageGratteCiel = al_load_bitmap("../Skyscraper.png");
    ALLEGRO_BITMAP *imageCiterne = al_load_bitmap("../watertower.png");
    ALLEGRO_SAMPLE *son = al_load_sample("../The-Sims-Soundtrack_-Buy-Mode-1.ogg");
    ALLEGRO_SAMPLE_INSTANCE *instanceSon = al_create_sample_instance(son);
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
    InfoGeneral infoGeneral;
    infoGeneral.argent = 500000;
    infoGeneral.habitant = 0;
    infoGeneral.capeau = 0;
    infoGeneral.capelec = 0;
    infoGeneral.nombreMaison = 0;
    infoGeneral.nombreCiterne = 0;
    infoGeneral.nombreUsine = 0;
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
    //sauvegarde();
    //liresauv();
    bool fin = false;
    al_flip_display();
    do {
        chercherCaseDeLaSourie(sourisState.x, sourisState.y, &souris1.Casex, &souris1.Casey, &souris1.interieurPlateau);
        al_wait_for_event(queue, &event);
        ALLEGRO_KEYBOARD_STATE clavierState;
        al_get_keyboard_state(&clavierState);
        al_get_mouse_state(&sourisState);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE : {
                fin = true;
                break;
            }
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN : {
                if (checkSourisDansBouton(sourisState.x, sourisState.y, BOUTTONX1, BOUTTONY1, BOUTTONX2, BOUTTONY2) &&
                    etape <= 3) {
                    etape = 0;
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
                                          SCREEN_WIDTH / 3 - 50, SCREEN_HEIGHT - 220) && etape == 1) {
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
                    construireroute(sourisState.x, sourisState.y, souris1.Casex, souris1.Casey,&infoGeneral);
                }
                if (etape == 4 && terrain) {
                    construireterrain(sourisState.x, sourisState.y, souris1.Casex, souris1.Casey, &infoGeneral);
                }
                if (etape == 4 && citernec) {
                    construireciterne(sourisState.x, sourisState.y, souris1.Casex, souris1.Casey, &infoGeneral,
                                      imageCiterne);
                }
                if (etape == 4 && usinec) {
                    construireusine(sourisState.x, sourisState.y, souris1.Casex, souris1.Casey, &infoGeneral);
                }
                if (etape == 4 && destruction) {
                    destructionConstruction(sourisState.x,sourisState.y,souris1.Casex,souris1.Casey);
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
                }
            }
            case ALLEGRO_EVENT_KEY_DOWN : {
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_SPACE : {
                        if (pause){
                            pause = 0;
                        }
                        else{
                            pause = 1;
                        }
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
        if (etape == 3) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            dessinerBoutonSelectionMode(policeTexte2, policeTexteGrande);
        }
        if (etape == 4) {
            if (event.type == ALLEGRO_EVENT_TIMER) {
                al_clear_to_color(al_map_rgb(255, 255, 255));
                //dessinneGrille(X1GRILLE, Y1GRILLE, X2GRILLE, Y2GRILLE, 1, al_map_rgb(0, 0, 0), policeTexte);
                al_get_mouse_state(&sourisState);
                colorierCaseSouris(sourisState.x, sourisState.y, niveau, policeTexte, imageCiterne,imageCabane,imageMaison,imageImmeuble,imageGratteCiel,imageTerrain,imageUsine);
                dessinnerTouteCasesColorie();
                afficherTempsRestant(tempsRestant, mois, policeTexte);
                dessinerBoutonOutil(policeTexte, policeTexte);
                dessinerInfosJeu(policeTexte, souris1.Casex,souris1.Casey,&infoGeneral);
                if (pause){
                    dessinerSauvegarde(policeTexte, policeTexte);
                }
                else if (tempsRestant >= 15.0) {
                    tempsRestant = 0.0;
                    mois++;
                    evolutionTerrain(&infoGeneral);
                    infoGeneral.argent = infoGeneral.argent+ 10 * infoGeneral.habitant;
                } else {
                    tempsRestant += 0.1;
                }
                if (boite) {
                    dessinerBoiteOutil(policeTexte, policeTexte);
                }
                if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
                    al_flip_display();
                }
            }
            al_flip_display();
        }
        al_flip_display();
    } while (!fin);
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
    al_destroy_sample(son);
    al_destroy_sample_instance(instanceSon);
    return 0;
}