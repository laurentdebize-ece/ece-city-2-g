//
// Created by lulub on 27/11/2022.
//

#ifndef ECE_CITY_2_G_ECECITY_H
#define ECE_CITY_2_G_ECECITY_H

//Bibliothèque dont Allegro

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

// Macro

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
#define Y1ARGENT 140
#define X1HABITANT 830
#define Y1HABITANT 180

#define X1CAPEAU 1050
#define Y1CAPEAU 140
#define Y1CAPEAU 140
#define X1CAPELEC 1050
#define Y1CAPELEC 180

#define NB_HABITANT_CABANE 10
#define NB_HABITANT_MAISON 50
#define NB_HABITANT_IMMEUBLE 100
#define NB_HABITANT_GRATTECIEL 1000

typedef struct Bouton{ //pour affichage
    short  x1Bouton, y1Bouton, x2Bouton, y2Bouton, taillePolice, action;
    char nomBouton[20];
    ALLEGRO_COLOR couleurBouton, couleurTexte, couleurPassageBouton;
    struct Bouton * bouton;
}Bouton;

typedef struct Case{
    short x1Case, x2Case, y1Case, y2Case, obstacle,etat;
    int batiment,numConstruction;
    ALLEGRO_COLOR couleurCase;
}Case;

Case matriceCase[NOMBRELIGNE][NOMBRECOLONNE]; //plateau de jeu

typedef struct souris{ // info souris
    short Casex, Casey;
    bool interieurPlateau;
}souris;

typedef  struct Maison {
    int caseX, caseY;
    int vivable;
}Maison;

typedef  struct Usine {
    int caseX, caseY;
    int nbUsine;
    int capelec; //capacité
}Usine;

typedef  struct Citerne {
    int caseX, caseY;
    int nbCiterne;
    int capeau;
}Citerne;

typedef struct InfoGeneral{
    int argent;
    int habitant;
    Maison maison [100];
    Usine usine [10];
    Citerne citerne [10];
    int nombreMaison;
    int nombreUsine;
    int nombreCiterne;
    int nbConstruction;
    int capeau;
    int capelec;
    int distance;
    int source;
}InfoGeneral;

typedef struct infosJeu{
    int prixTerrain;
    int prixUsine;
    int prixCiterne;
    int prixRoute;
    int nbHabcabane;
    int nbHabmaison;
    int nbHabimmeuble;
    int nbHabgratteciel;
}t_infosJeu;


t_infosJeu recupererInfosJeu(t_infosJeu infos);

void initAllegro();

int largeurCaseGrille(short x1, short x2);
int hauteurCaseGrille(short y1, short y2);
short coordonneX1CaseGrille(short x1, short x2,short noCollonne);
float coordonneX2CaseGrille(short x1, short x2,short noCollonne) ;
float coordonneY1CaseGrille( short y1,  short y2,short noLigne) ;
float coordonneY2CaseGrille( short y1,  short y2,short noLigne);

void initialiserCasesGrille();
void chercherCaseDeLaSourie(int x, int y, int *caseX, int *caseY, bool *dansPlateau) ;
void initDonneesJeu();
void dessinerArrierePlanMenu(ALLEGRO_BITMAP *imageMenu);
void dessinerTerrain(ALLEGRO_BITMAP *imageTerrain,int x,int y);
void dessinerCabane(ALLEGRO_BITMAP *imageCabane,int x,int y);
void dessinerMaison(ALLEGRO_BITMAP *imageMaison,int x,int y);
void dessinerImmeuble(ALLEGRO_BITMAP *imageImmeuble,int x,int y);
void dessinerUsine(ALLEGRO_BITMAP *imageUsine,int x,int y);
void dessinerGratteCiel(ALLEGRO_BITMAP *imageGratteCiel,int x,int y);
void dessinerCiterne(ALLEGRO_BITMAP *imageCiterne,int x,int y);
void dessinerBouton(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexte,short taillePolice );
void dessinerCadre(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur );

// initilisation police d'écriture

ALLEGRO_FONT* initialiserPoliceTexte(short taillePolice);

ALLEGRO_FONT* initialiserPoliceTexte2(short taillePolice);
ALLEGRO_FONT* initialiserPoliceTexteGrande(short taillePoliceGrande);
ALLEGRO_FONT* initialiserPoliceTexteTitre(short taillePoliceTitre);
void dessinerBoutonGrand(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexteGrande,short taillePoliceGrande );

void dessinerInformationsGenerales(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande);
void dessinerTitre(ALLEGRO_FONT* policeTexteTitre);
void dessinerBoutonMenu(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande, ALLEGRO_FONT* policeTexteTitre);
void dessinerRegleDuJeu(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande);
void dessinerTexteRegleDuJeu(ALLEGRO_FONT* policeTexte);
void dessinerBoutonSelectionMode(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande);
void afficherChrono(double angle, ALLEGRO_COLOR couleur);
void dessinerBoiteOutil(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande);
void dessinerSauvegarde(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande);
void dessinerInfosJeu(ALLEGRO_FONT* policeTexteGrande,float xcase, float ycase, InfoGeneral* infoGeneral) ;
void afficherTempsRestant(float tempsRestant,float mois, ALLEGRO_FONT* policeTexte);
void dessinnerTouteCasesColorie();

bool checkSourisDansBouton(short xSouris, short ySouris, short x1, short y1,short x2, short y2 );
void dessinneGrille( int x1, int y1, int x2, int y2, int epaisseur, ALLEGRO_COLOR couleurGrille, ALLEGRO_FONT* policeTexte);


void rechercheCentral(InfoGeneral* infoGeneral, int x, int y, bool*connecteEau, bool*connecteElec,Case matricePlateau[NOMBRELIGNE][NOMBRECOLONNE]) ;
int verificationViable(InfoGeneral* infoGeneral, Case plateau[NOMBRELIGNE][NOMBRECOLONNE],int x, int y) ;

void verificationMaisonNonViables(InfoGeneral * infoGeneral,Case plateau[NOMBRELIGNE][NOMBRECOLONNE],int x, int y);


void colorierCaseSouris(short xSouris, short ySouris,short niveau,ALLEGRO_FONT* policeTexte,ALLEGRO_BITMAP* imageCiterne,ALLEGRO_BITMAP* imageCabane,ALLEGRO_BITMAP* imageMaison,ALLEGRO_BITMAP* imageImmeuble,ALLEGRO_BITMAP* imageGratteCiel, ALLEGRO_BITMAP* imageTerrain,ALLEGRO_BITMAP* imageUsine);

void sauvegarde();
InfoGeneral* construireroute(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral);

InfoGeneral* construireterrain(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral);
InfoGeneral* construireciterne(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral,ALLEGRO_BITMAP* imageCiterne );

InfoGeneral* construireusine(short xSouris, short ySouris, short xcase , short ycase, InfoGeneral* infoGeneral);

InfoGeneral* destructionConstruction(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral);

InfoGeneral* evolutionTerrain(InfoGeneral* infoGeneral, short *mode);

void dessinerBoutonOutil(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Fonctions pour distribuer l'eau et l'électricité. Ne sont pas fonctionnelles à 100% et ne sont donc pas utilisées mais méritent d'être regardées
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Définition de la file d'attente

typedef struct maillon
{
    int numero;
    struct maillon* suivant;
}t_maillon;

typedef struct attente
{
    t_maillon* tete;
    t_maillon* fin;
}t_attente;

// Structure d'un arc//
struct Arc
{
    int sommet; // numero de sommet d'un arc adjacent au sommet initial
    int poids;      //aussi la capacité maximale de chaque arc
    struct Arc* arc_suivant;
};

// Alias de pointeur sur un Arc //
typedef struct Arc* pArc;

// Structure d'un sommet//
struct Sommet
{
    struct Arc* arc;
    int capacite;
    int NbrHabitant;
    int valeur;
    int distance;
    int pred;
    int couleur;
};

// Alias de pointeur sur un Sommet //
typedef struct Sommet* pSommet;

typedef struct graphe
{
    int ordre;
    pSommet* pSommet;
    t_attente* attente;
} Graphe;

void afficher_successeurs(pSommet * sommet, int num);
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids);
Graphe* CreerGraphe(int ordre);
void graphe_afficher(InfoGeneral * infoGeneral);
t_attente* ajoutListe(t_attente* attente,int numero);
t_attente *removeListe(t_attente* attente);
int selectionProchainSommet(InfoGeneral * infoGeneral);

InfoGeneral* rechercheRoute(int i, int j, int tab[45][35],InfoGeneral* infoGeneral);
InfoGeneral * initDistributionEau(InfoGeneral* infoGeneral, int source); //Partie initialisation du BFS
InfoGeneral * PlusCourtCheminDistributionEau(InfoGeneral * infoGeneral);
void afficheDistributionEau(InfoGeneral* infoGeneral) ;
InfoGeneral * DistributionEau(InfoGeneral* infoGeneral);
InfoGeneral *initDistributionElec(InfoGeneral *infoGeneral);
InfoGeneral *PlusCourtCheminDistributionElec(InfoGeneral *infoGeneral);
void afficheDistributionElec(Graphe *graphe);
InfoGeneral *DistributionElec(InfoGeneral *infoGeneral);
InfoGeneral * AlimentationElectricite(InfoGeneral * infoGeneral);
InfoGeneral* remplissageGraphe(InfoGeneral* infoGeneral) ;
*/

#endif //ECE_CITY_2_G_ECECITY_H
