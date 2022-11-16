#ifndef ECE_CITY_2_G_SIMS_H
#define ECE_CITY_2_G_SIMS_H

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
#define X2GRILLE 807
#define Y1GRILLE 20
#define Y2GRILLE 628
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


void initAllegro();

/*void initialiserObstacle();
 */


float largeurCaseGrille(short x1, short x2);

float hauteurCaseGrille(short y1, short y2);

float coordonneX1CaseGrille(short x1, short x2,short noCollonne) ;

float coordonneX2CaseGrille(short x1, short x2,short noCollonne) ;

float coordonneY1CaseGrille( short y1,  short y2,short noLigne) ;

float coordonneY2CaseGrille( short y1,  short y2,short noLigne) ;

void initialiserCasesGrille();

//Bouton * initialiserTabBouton();

void initDonneesJeu();


void dessinerBouton(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexte,short taillePolice );

void dessinerCadre(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur );

void dessinnerBouton(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexte,short taillePolice );

ALLEGRO_FONT* initialiserPoliceTexte2(short taillePolice);

ALLEGRO_FONT* initialiserPoliceTexteGrande(short taillePoliceGrande);

ALLEGRO_FONT* initialiserPoliceTexteTitre(short taillePoliceTitre);

void dessinerBoutonGrand(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexteGrande,short taillePoliceGrande );

void afficherChrono(double angle, ALLEGRO_COLOR couleur);

void afficherTempsRestant(float tempsRestant, ALLEGRO_FONT* policeTexte);

void dessinnerTouteCasesColorie() ;

ALLEGRO_FONT* initialiserPoliceTexte(short taillePolice);



bool checkSourisDansBouton(short xSouris, short ySouris, short x1, short y1,short x2, short y2 );

void dessinneGrille( int x1, int y1, int x2, int y2, int epaisseur, ALLEGRO_COLOR couleurGrille, ALLEGRO_FONT* policeTexte);

void colorierCaseGrille(short xSouris, short ySouris, ALLEGRO_FONT* policeTexte);



#endif //ECE_CITY_2_G_SIMS_H
