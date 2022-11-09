#include "sims.h"


void initAllegro(){
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    //al_init_image_addon();
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


void dessinerBouton(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexte,short taillePolice ){
    al_draw_filled_rectangle(x1, y1, x2, y2,couleur);
    al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(50,50,50), 2);
    al_draw_text(policeTexte, al_map_rgb(0,0,0),(x1 +x2)/2-10 - strlen(texte)*taillePolice/5, (y2+y1)/2-taillePolice/2,0,texte );
}


void dessinerCadre(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur ){
    al_draw_filled_rectangle(x1, y1, x2, y2,couleur);
    al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(50,50,50), 2);
}

void dessinnerBouton(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexte,short taillePolice ){
    al_draw_filled_rectangle(x1, y1, x2, y2,couleur);
    al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(50,50,50), 2);
    al_draw_text(policeTexte, al_map_rgb(0,0,0),(x1 +x2)/2 - strlen(texte)*taillePolice/5, (y2+y1)/2-taillePolice/2,0,texte );
}

ALLEGRO_FONT* initialiserPoliceTexte2(short taillePolice){
    ALLEGRO_FONT* policeTexte = NULL ;
    policeTexte = al_load_ttf_font("../Bangers-Regular.ttf", taillePolice,0);
    return policeTexte;
}

ALLEGRO_FONT* initialiserPoliceTexteGrande(short taillePoliceGrande){
    ALLEGRO_FONT* policeTexteGrande = NULL ;
    policeTexteGrande = al_load_ttf_font("", taillePoliceGrande,0);
    return policeTexteGrande;
}

ALLEGRO_FONT* initialiserPoliceTexteTitre(short taillePoliceTitre){
    ALLEGRO_FONT* policeTexteTitre = NULL ;
    policeTexteTitre = al_load_ttf_font("", taillePoliceTitre,0);
    return policeTexteTitre;
}

void dessinerBoutonGrand(int x1,int y1,int x2,int y2,ALLEGRO_COLOR couleur, char* texte, ALLEGRO_FONT* policeTexteGrande,short taillePoliceGrande ){
    al_draw_filled_rectangle(x1, y1, x2, y2,couleur);
    al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(50,50,50), 2);
    al_draw_text(policeTexteGrande, al_map_rgb(0,0,0),(x1 +x2)/2-15 - strlen(texte)*taillePoliceGrande/5, (y2+y1)/2-taillePoliceGrande/2,0,texte );
}

void afficherChrono(double angle, ALLEGRO_COLOR couleur){
    al_draw_circle(XCHRONO, YCHRONO, 30,couleur, 5 );
    al_draw_filled_circle(XCHRONO, YCHRONO, 5, couleur);
    al_draw_line(XCHRONO, YCHRONO - 30, XCHRONO, YCHRONO - 36, couleur, 4);
    al_draw_line(XCHRONO -3, YCHRONO - 35, XCHRONO +3, YCHRONO - 35, couleur, 4);
    al_draw_filled_triangle(XCHRONO-cos(angle)*2, YCHRONO +sin(angle)*2, XCHRONO +cos(angle)*2, YCHRONO - sin(angle)*2, XCHRONO - sin(angle)*25, YCHRONO - cos(angle)*25, couleur);
}





void afficherTempsRestant(float tempsRestant, ALLEGRO_FONT* policeTexte){
    al_draw_textf(policeTexte, al_map_rgb(0,0,0), XCHRONO + 60, YCHRONO - 20,0,"%.1f secondes", tempsRestant);
    double angle = (15-tempsRestant)*0.42;
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
            al_draw_textf(policeTexte,couleurGrille, x1 + i*largeurCase +3, y1 - 15,0,"%d", i+1);}
    }
    for(int j = 0; j <= NOMBRELIGNE; j++){
        al_draw_line(x1, y1+ j*hauteurCase, x2, y1 + j*hauteurCase, couleurGrille, epaisseur);
        if(j<NOMBRELIGNE){
            al_draw_textf(policeTexte, couleurGrille,x1 -16, y1 + j*hauteurCase +2,0,"%d", j+1 );}
    }
}

void colorierCaseGrille(short xSouris, short ySouris, ALLEGRO_FONT* policeTexte){
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++){
            if(checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i+1),
                                     coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE,j+1 ), coordonneX2CaseGrille(X1GRILLE,X2GRILLE, i+1),
                                     coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j+1) )) {
                matriceCase[j][i].couleurCase = al_map_rgba(80, 80, 80, 0.4);
            }
            else if(matriceCase[j][i].obstacle != -1){matriceCase[j][i].couleurCase = al_map_rgba(0,0,0, 0);}
            else if(matriceCase[j][i].obstacle == -1 ){matriceCase[j][i].couleurCase  = al_map_rgba(0,0,130,100);}
        }
    }
}