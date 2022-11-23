//
// Created by emili on 10/11/2022.
//

#ifndef ECE_CITY_2_G_LUCIE_H
#define ECE_CITY_2_G_LUCIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

typedef struct souris{
    short Casex, Casey;
    bool interieurPlateau;
}souris;

typedef  struct Usine {
    int caseX, caseY;
    int nbUsine;
}Usine;

typedef  struct Citerne {
    int caseX, caseY;
    int nbCiterne;
}Citerne;

//Définition de la file d'attente

typedef struct maillon
{
    int numero;
    int distanceS;
    struct maillon* suivant;
}t_maillon;

typedef struct attente
{
    t_maillon* tete;
    t_maillon* fin;
}t_attente;

/* Structure d'un arc*/
struct Arc
{
    int sommet; // numero de sommet d'un arc adjacent au sommet initial
    int poids;      //aussi la capacité maximale de chaque arc
    int flot;       //flot de l'arc, commence à 0 puis augmente
    int ecart;      // écart entre le flot actuel et la capacité maximale
    struct Arc* arc_suivant;
}Arc;

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

typedef  struct Maison {
    //ALLEGRO_BITMAP image_stade_batiment[6];
    int largeur,hauteur;
    int date_creation;
    int caseX, caseY;
    int eau_utilise;
    int elec_utilise;
    int stade;
    int viable;
    int nbMaison;
    struct Arc* arc;
    bool citerne;
    int capacite;
    bool usine;
    int NbrHabitant;
    int valeur;
    int distance;
    int pred;
    int couleur;
}Maison;

typedef struct InfoGeneral{
    int argent;
    int habitant;
    int capelec;
    int capeau;
    Maison* maison;
    Usine usine [10];
    Citerne citerne [10];
    int nombreMaison;
    int nombreUsine;
    int nombreCiterne;
    int ordre;
    int** matrice;
    char* tabSommet;
    t_attente* attente;
}InfoGeneral;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    bool chateau;
    int capacite;
    bool habitation;
    int NbrHabitant;
    int distance;
    int pred;
    int couleur;
}Sommet;

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct graphe
{
    int ordre;
    int** matrice;
    char* tabSommet;
    pSommet* pSommet;
    t_attente* attente;
}Graphe;

t_attente* ajoutListe(t_attente*attente, int numero);
t_attente *removeListe(t_attente*attente);
Graphe* CreerGraphe(int ordre);// creer le graphe
Graphe * lire_graphe(char * nomFichier);
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids);// Ajouter l'arete entre les sommets s1 et s2 du graphe
void afficher_successeurs(pSommet * sommet, int num);/* affichage des successeurs du sommet num*/
void graphe_afficher(Graphe* graphe);/*affichage du graphe avec les successeurs de chaque sommet */

void afficher_successeurs(pSommet * sommet, int num)/* affichage des successeurs du sommet num*/
{
    printf("Sommet %d :\n",num);

    if(sommet[num]->arc == NULL){
        printf("sommet[num] NULL\n");   //si il n'y a pas de successeurs
    }
    pArc arc=sommet[num]->arc;  //pointeur d'arc

    while(arc!=NULL)
    {
        printf("%d \n",arc->sommet);    //tant qu'il reste un arc sur le sommet on affiche son numéro
        arc=arc->arc_suivant;       //on passe au sommet suivant
    }
}

pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids)  // Ajouter l'arete entre les sommets s1 et s2 du graphe
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids=poids;
        sommet[s1]->arc=Newarc;
        return sommet;
    }
    else
    {
        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids=poids;

        if(temp->sommet>s2)
        {
            Newarc->poids=temp->poids;
            temp->poids=poids;
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }
        temp->arc_suivant=Newarc;
        return sommet;
    }
}

Graphe* CreerGraphe(int ordre)// creer le graphe
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->arc=NULL;
        Newgraphe->pSommet[i]->pred=-1;
    }
    Newgraphe->ordre=ordre;
    return Newgraphe;
}

Graphe * lire_graphe(char * nomFichier) //récupérer les infos du fichier
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int poids, ordre,i,j;

    if (!ifs) //vérification de l'ouverture du fichier
    {   printf("Erreur de lecture fichier\n");
        exit(-1);}

    fscanf(ifs,"%d\n",&ordre);  //on récupère l'odre du graphe

    int** matrice=(int**)malloc(ordre*sizeof(int*));    //déclaration, allocation d'une matrice 2D

    for(i = 0 ; i < ordre ; i++)    //déclaration, allocation d'une matrice 2D
    {
        matrice[i] = malloc(ordre * sizeof (int));
    }
    graphe=CreerGraphe(ordre); // creer le graphe vide d'ordre sommets
    graphe->matrice=matrice;    //la matrice est enregistrée dans le graphe

    for(i=0;i<ordre;i++)        //récupérer la matrice d'adjacence
    {
        for(j=0;j<ordre;j++)
        {
            fscanf(ifs,"%d ",&graphe->matrice[i][j]); //chercher dans le fichier le poids de l'arete
            poids=graphe->matrice[i][j];
            if(poids!=0)        //Si le poids n'est pas nul, il y a une arete
            {
                graphe->pSommet=CreerArete(graphe->pSommet, i, j,poids); //ajout de l'arete au graphe
            }
        }
    }
    return graphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("ordre = %d\n",graphe->ordre);   //affiche l'ordre
    printf("listes d'adjacence :\n");
    for (int i=0; i<graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);//affiche les sommets adjacents
    }
}

t_attente* ajoutListe(t_attente* attente,int numero)    //ajouter un numéro en fin de liste
{
    t_maillon* maille = malloc(sizeof(t_maillon));  //alloc nouveau maillon
    maille->numero=numero;
    maille->suivant=NULL;
    attente->fin->suivant=maille;   //ajout du maillon à la fin
    attente->fin= maille;       //on pointe sur le nouveau maillon qui est à la fin
    return attente;
}
t_attente *removeListe(t_attente* attente)
{
    attente->tete=attente->tete->suivant;   //on pointe sur le deuxième maillon : on perd le premier
    return attente;
}

Graphe* initDistributionEau(Graphe* graphe,int numero)  //Partie initialisation du BFS
{
    int source=0;
    t_maillon* maille = malloc(sizeof(t_maillon));//initialisation à null

    graphe->attente = malloc(sizeof(t_attente));  //création de la file
    graphe->attente->tete=graphe->attente->fin=NULL;

    maille->numero=numero;      //enfiler le premier maillon avec le numéro de la source
    graphe->attente->tete= graphe->attente->fin=maille;     //On le fait que la premiere fois
    graphe->attente->tete->suivant=graphe->attente->fin;        //quand la file est vide
    graphe->attente->fin->suivant=NULL;

    graphe->pSommet[source]->chateau=1;//normalement on a déja cette info
    graphe->pSommet[source]->habitation=0;
    graphe->pSommet[source]->capacite=5000;
    graphe->pSommet[source]->couleur=1; //la source est marquée
    graphe->pSommet[source]->distance=0;
    graphe->pSommet[source]->pred=-1;    //tous les predecesseurs sont à -1: il n'y en a pas

    for(int i=1;i<graphe->ordre;i++)
    {
        graphe->pSommet[i]->habitation=1;
        graphe->pSommet[i]->chateau=0;
        graphe->pSommet[i]->NbrHabitant=2000;
        graphe->pSommet[i]->couleur=0;//On note tous les sommets comme non repérés
        graphe->pSommet[i]->pred=-1;    //tous les predecesseurs sont à -1: il n'y en a pas
        graphe->pSommet[i]->distance=500;
    }
    return graphe;
}

int selectionProchainSommet(Graphe* graphe)
{
    int numero;
    int dmin=-1;
    t_maillon* position = malloc(sizeof(t_maillon));//initialisation à null

    position=graphe->attente->tete;
    while(position!=NULL)
    {
        if(dmin==-1)
        {
            dmin=graphe->pSommet[position->numero]->distance;
            numero=position->numero;
        }
        else if((graphe->pSommet[position->numero]->distance<dmin))
        {
            dmin=graphe->pSommet[position->numero]->distance;
            numero=position->numero;
        }
        position=position->suivant;
    }
    return numero;
}

Graphe* PlusCourtCheminDistributionEau(Graphe* graphe)
{
    int numero,sommetDecouvert;
    int distance;
    pArc arc;//pointeur sur structure arc

    while(graphe->attente->tete!=NULL)  //tant que la liste n'est pas vide
    {
        numero=selectionProchainSommet(graphe);   //on récupère le numéro du premier sommet
        arc=graphe->pSommet[numero]->arc;   //on pointe sur un de ses arcs
        while(arc!=NULL)
        {
            sommetDecouvert=arc->sommet;
            distance=arc->poids;
            if(graphe->pSommet[sommetDecouvert]->distance>(distance+graphe->pSommet[numero]->distance))
            {
                graphe->pSommet[sommetDecouvert]->distance=(distance+graphe->pSommet[numero]->distance);
                printf("\ndistance sommet %d : %d",sommetDecouvert,graphe->pSommet[sommetDecouvert]->distance);
                graphe->pSommet[sommetDecouvert]->pred = numero;  //marquer prédecesseur du new sommet
                if (graphe->pSommet[sommetDecouvert]->couleur == 0)  //si le sommet adjacent n'est pas découvert
                {
                    graphe->attente = ajoutListe(graphe->attente, sommetDecouvert);    //enfiler le new sommet
                    graphe->pSommet[sommetDecouvert]->couleur = 1;        //marquer le sommet découvert
                }
                else if (graphe->pSommet[sommetDecouvert]->couleur == 1)  //si le sommet adjacent n'est pas découvert
                {
                    graphe->attente = ajoutListe(graphe->attente, sommetDecouvert);    //enfiler le new sommet
                }
            }
            arc = arc->arc_suivant;     //pointer sur l'arc suivant
        }
        graphe->attente=removeListe(graphe->attente);   //défiler le sommet actuel
    }
    return graphe;
}
void afficheDistributionEau(Graphe* graphe)    //afficher le résultat du BFS
{
    int i,j;
    for(i=0;i<graphe->ordre;i++)    //pour chaque sommet
    {
        j=i;
        printf("\n%d",i);
        while (j!=0)        //tant qu'on est pas remonté à la source
        {
            j=graphe->pSommet[j]->pred;
            printf("<--%d",j);  //affichage du précédent
        }
        printf(" distance : %d",graphe->pSommet[i]->distance);
    }
}

Graphe* DistributionEau(Graphe* graphe)
{
    int* tab=malloc(graphe->ordre*sizeof(int));
    int* tableau=malloc(graphe->ordre*sizeof(int));
    int permutateur,i,j,position;

    for(i=0;i<graphe->ordre;i++)
    {
        tableau[i] = graphe->pSommet[i]->distance;
        tab[i] = i;
    }
    for (i=0; i < (graphe->ordre-1); i++)
    {
        position = i;
        for (j = i + 1; j < graphe->ordre; j++)
        {
            if (tableau[position] > tableau[j])
                position = j;
        }
        if (position != i)
        {
            permutateur = tableau[i];
            tableau[i] = tableau[position];
            tableau[position] = permutateur;
            permutateur = tab[i];
            tab[i] = tab[position];
            tab[position] = permutateur;
        }
        printf("\nValeur: %d",tab[i]);
    }
    for (i=0;i<graphe->ordre;i++)
    {
        if ((graphe->pSommet[0]->NbrHabitant = 0)||(graphe->pSommet[0]->capacite == 0)) {}
        else if (graphe->pSommet[0]->capacite - graphe->pSommet[tab[i]]->NbrHabitant > 0)
        {
            graphe->pSommet[0]->capacite = graphe->pSommet[0]->capacite - graphe->pSommet[tab[i]]->NbrHabitant;
            printf("\nSommet %d allimente: %dL", tab[i], graphe->pSommet[tab[i]]->NbrHabitant);
        }
        else if (graphe->pSommet[0]->capacite - graphe->pSommet[tab[i]]->NbrHabitant < 0)
        {
            graphe->pSommet[tab[i]]->NbrHabitant = graphe->pSommet[tab[i]]->NbrHabitant - graphe->pSommet[0]->capacite;
            graphe->pSommet[0]->capacite = 0;
            printf("\nSommet %d allimente partiellement, reste %dL a remplir", tab[i], graphe->pSommet[tab[i]]->NbrHabitant);
        }
    }
}
Graphe* AlimentationEnEau(Graphe* graphe)
{
    graphe=initDistributionEau(graphe,0);   //démarrer bfs
    graphe=PlusCourtCheminDistributionEau(graphe); //faire bfs
    afficheDistributionEau(graphe); //afficher bfs
    graphe=DistributionEau(graphe);
    return graphe;
}
Graphe *initDistributionElec(Graphe *graphe,int source)
{
    t_maillon* maille = malloc(sizeof(t_maillon));//initialisation à null

    graphe->attente = malloc(sizeof(t_attente));  //création de la file
    graphe->attente->tete=graphe->attente->fin=NULL;

    maille->numero=source;      //enfiler le premier maillon avec le numéro de la source
    graphe->attente->tete= graphe->attente->fin=maille;     //On le fait que la premiere fois
    graphe->attente->tete->suivant=graphe->attente->fin;        //quand la file est vide
    graphe->attente->fin->suivant=NULL;

    graphe->pSommet[source]->chateau=1;//normalement on a déja cette info
    graphe->pSommet[source]->habitation=0;
    graphe->pSommet[source]->capacite=5000;
    graphe->pSommet[source]->couleur=1; //la source est marquée
    graphe->pSommet[source]->distance=0;
    graphe->pSommet[source]->pred=-1;    //tous les predecesseurs sont à -1: il n'y en a pas

    for(int i=1;i<graphe->ordre;i++)
    {
        graphe->pSommet[i]->habitation=1;
        graphe->pSommet[i]->chateau=0;
        graphe->pSommet[i]->NbrHabitant=2000;
        graphe->pSommet[i]->couleur=0;//On note tous les sommets comme non repérés
        graphe->pSommet[i]->pred=-1;    //tous les predecesseurs sont à -1: il n'y en a pas
        graphe->pSommet[i]->distance=500;
    }
    return graphe;
}
Graphe *PlusCourtCheminDistributionElec(Graphe *graphe)
{
    int numero,sommetDecouvert;
    int distance;
    pArc arc;//pointeur sur structure arc

    while(graphe->attente->tete!=NULL)  //tant que la liste n'est pas vide
    {
        numero=selectionProchainSommet(graphe);   //on récupère le numéro du premier sommet
        arc=graphe->pSommet[numero]->arc;   //on pointe sur un de ses arcs
        while(arc!=NULL)
        {
            sommetDecouvert=arc->sommet;
            distance=arc->poids;
            if(graphe->pSommet[sommetDecouvert]->distance>(distance+graphe->pSommet[numero]->distance))
            {
                graphe->pSommet[sommetDecouvert]->distance=(distance+graphe->pSommet[numero]->distance);
                printf("\ndistance sommet %d : %d",sommetDecouvert,graphe->pSommet[sommetDecouvert]->distance);
                graphe->pSommet[sommetDecouvert]->pred = numero;  //marquer prédecesseur du new sommet
                if (graphe->pSommet[sommetDecouvert]->couleur == 0)  //si le sommet adjacent n'est pas découvert
                {
                    graphe->attente = ajoutListe(graphe->attente, sommetDecouvert);    //enfiler le new sommet
                    graphe->pSommet[sommetDecouvert]->couleur = 1;        //marquer le sommet découvert
                }
                else if (graphe->pSommet[sommetDecouvert]->couleur == 1)  //si le sommet adjacent n'est pas découvert
                {
                    graphe->attente = ajoutListe(graphe->attente, sommetDecouvert);    //enfiler le new sommet
                }
            }
            arc = arc->arc_suivant;     //pointer sur l'arc suivant
        }
        graphe->attente=removeListe(graphe->attente);   //défiler le sommet actuel
    }
    return graphe;
}
Graphe *afficheDistributionElec(Graphe *graphe)
{
    int i,j;
    for(i=0;i<graphe->ordre;i++)    //pour chaque sommet
    {
        j=i;
        printf("\n%d",i);
        while (j!=0)        //tant qu'on est pas remonté à la source
        {
            j=graphe->pSommet[j]->pred;
            printf("<--%d",j);  //affichage du précédent
        }
        printf(" distance : %d",graphe->pSommet[i]->distance);
    }
    return graphe;
}
Graphe *DistributionElec(Graphe *graphe)
{
    int* tab=malloc(graphe->ordre*sizeof(int));
    int* tableau=malloc(graphe->ordre*sizeof(int));
    int permutateur,i,j,position;

    for(i=0;i<graphe->ordre;i++)
    {
        tableau[i] = graphe->pSommet[i]->distance;
        tab[i] = i;
    }
    for (i=0; i < (graphe->ordre-1); i++)
    {
        position = i;
        for (j = i + 1; j < graphe->ordre; j++)
        {
            if (tableau[position] > tableau[j])
                position = j;
        }
        if (position != i)
        {
            permutateur = tableau[i];
            tableau[i] = tableau[position];
            tableau[position] = permutateur;
            permutateur = tab[i];
            tab[i] = tab[position];
            tab[position] = permutateur;
        }
        printf("\nValeur: %d",tab[i]);
    }
    graphe->pSommet[4]->NbrHabitant=3;

    for (i=0;i<graphe->ordre;i++)
    {
        if ((graphe->pSommet[0]->NbrHabitant = 0)||(graphe->pSommet[0]->capacite == 0))
        {
            printf("\nSommet %d non allimente", tab[i]);
        }
        else if (graphe->pSommet[0]->capacite - graphe->pSommet[tab[i]]->NbrHabitant > 0)
        {
            graphe->pSommet[0]->capacite = graphe->pSommet[0]->capacite - graphe->pSommet[tab[i]]->NbrHabitant;
            printf("\nSommet %d allimente: %dL", tab[i], graphe->pSommet[tab[i]]->NbrHabitant);
        }
        else if (graphe->pSommet[0]->capacite - graphe->pSommet[tab[i]]->NbrHabitant < 0)
        {
            printf("\nSommet %d non allimente car manque d'elec", tab[i]);
        }
    }
    return graphe;
}
Graphe* AlimentationElectricite(Graphe* graphe)
{
    graphe=initDistributionElec(graphe,0);
    graphe=PlusCourtCheminDistributionElec(graphe);
    afficheDistributionElec(graphe);
    graphe=DistributionElec(graphe);

    return graphe;
}

#endif //ECE_CITY_2_G_LUCIE_H
