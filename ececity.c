//
// Created by lulub on 27/11/2022.
//
#include "ececity.h"


void afficher_successeurs(pSommet * sommet, int num)
{
    printf("Sommet %d :\n",num);
    if(sommet[num]->arc == NULL){
        printf("sommet[num] NULL\n");   //si il n'y a pas de successeurs
    }
    pArc arc=sommet[num]->arc;  //pointeur d'arc

    while(arc!=NULL)//tant qu'il reste un arc sur le sommet on affiche son numéro
    {
        printf("%d \n",arc->sommet);
        printf("poids : %d\n",arc->poids);
        arc=arc->arc_suivant;       //on passe au sommet suivant
    }
}
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int poids)
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
        while( temp->arc_suivant!=NULL)
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
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
        Newgraphe->pSommet[i]->pred=-1;
    }
    Newgraphe->ordre=ordre;
    return Newgraphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(InfoGeneral * infoGeneral)
{
    printf("\nordre = %d\n",infoGeneral->graphe->ordre);   //affiche l'ordre
    printf("listes d'adjacence :\n");
    for (int i=0; i<infoGeneral->graphe->ordre; i++)
    {
        afficher_successeurs(infoGeneral->graphe->pSommet, i);//affiche les sommets adjacents
    }
}

InfoGeneral* rechercheRoute(int i, int j, int tab[45][35],InfoGeneral* infoGeneral)
{
    int k;
    tab[i][j]=0;
    if ((infoGeneral->distance>2))
    {
        if(((tab[i][j + 1] ==2))||((tab[i][j+1] ==11)&&(tab[i][j+2] == 2)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i][j+1].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i][j+1].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i][j+1].numConstruction]->NbrHabitant=NB_HABITANT_CABANE;
            return infoGeneral;
        }
        if((tab[i][j-1]==2)||((tab[i][j-1] ==11)&&(tab[i][j-2] == 2)))
        {
            printf("\nnouveau sommet : %d, %d",matriceCase[i][j-1].numConstruction, infoGeneral->source);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i][j-1].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i][j-1].numConstruction]->NbrHabitant=NB_HABITANT_CABANE;
            return infoGeneral;
        }
        if((tab[i-1][j]==2)||((tab[i-1][j] ==11)&&(tab[i-2][j] == 2)))
        {
            printf("\nnouveau sommet : %d %d",matriceCase[i-1][j].numConstruction, infoGeneral->source);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i-1][j].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i-1][j].numConstruction]->NbrHabitant=NB_HABITANT_CABANE;
            return infoGeneral;
        }
        if(((tab[i+1][j] ==2))||((tab[i+1][j] ==11)&&(tab[i+2][j] == 2)))
        {
            printf("\nnouveau sommet : %d %d",matriceCase[i+1][j].numConstruction,infoGeneral->source);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i+1][j].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i+1][j].numConstruction]->NbrHabitant=NB_HABITANT_CABANE;
            return infoGeneral;
        }
        if(((tab[i][j + 1] ==3))||((tab[i][j+1] ==11)&&(tab[i][j+2] == 3)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i][j+1].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i][j+1].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i][j+1].numConstruction]->NbrHabitant=NB_HABITANT_MAISON;
            return infoGeneral;
        }
        if((tab[i][j-1]==3)||((tab[i][j-1] ==11)&&(tab[i][j-2] == 3)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i][j-1].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i][j-1].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i][j-1].numConstruction]->NbrHabitant=NB_HABITANT_MAISON;
            return infoGeneral;
        }
        if((tab[i-1][j]==3)||((tab[i-1][j] ==11)&&(tab[i-2][j] == 3)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i-1][j].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i-1][j].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i-1][j].numConstruction]->NbrHabitant=NB_HABITANT_MAISON;
            return infoGeneral;
        }
        if(((tab[i+1][j] ==3))||((tab[i+1][j] ==11)&&(tab[i+2][j] == 3)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i+1][j].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i+1][j].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i+1][j].numConstruction]->NbrHabitant=NB_HABITANT_MAISON;
            return infoGeneral;
        }
        if(((tab[i][j + 1] ==4))||((tab[i][j+1] ==11)&&(tab[i][j+2] == 4)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i][j+1].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i][j+1].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i][j+1].numConstruction]->NbrHabitant=NB_HABITANT_IMMEUBLE;
            return infoGeneral;
        }
        if((tab[i][j-1]==4)||((tab[i][j-1] ==11)&&(tab[i][j-2] == 4)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i][j-1].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i][j-1].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i][j-1].numConstruction]->NbrHabitant=NB_HABITANT_IMMEUBLE;
            return infoGeneral;
        }
        if((tab[i-1][j]==4)||((tab[i-1][j] ==11)&&(tab[i-2][j] == 4)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i-1][j].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i-1][j].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i-1][j].numConstruction]->NbrHabitant=NB_HABITANT_IMMEUBLE;

            return infoGeneral;
        }
        if(((tab[i+1][j] ==4))||((tab[i+1][j] ==11)&&(tab[i+2][j] == 4)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i+1][j].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i+1][j].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i+1][j].numConstruction]->NbrHabitant=NB_HABITANT_IMMEUBLE;

            return infoGeneral;
        }
        if((tab[i][j + 1] ==5)||((tab[i][j+1] ==11)&&(tab[i][j+2] == 5)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i][j+1].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i][j+1].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i][j+1].numConstruction]->NbrHabitant=NB_HABITANT_GRATTECIEL;

            return infoGeneral;
        }
        if((tab[i][j-1]==5)||((tab[i][j-1] ==11)&&(tab[i][j-2] == 5)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i][j-1].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i][j-1].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i][j-1].numConstruction]->NbrHabitant=NB_HABITANT_GRATTECIEL;
            return infoGeneral;
        }
        if((tab[i-1][j]==5)||((tab[i-1][j] ==11)&&(tab[i-2][j] == 5)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i-1][j].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i-1][j].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i-1][j].numConstruction]->NbrHabitant=NB_HABITANT_GRATTECIEL;
            return infoGeneral;
        }
        if((tab[i+1][j] ==5)||((tab[i+1][j] ==11)&&(tab[i+2][j] == 5)))
        {
            printf("\nnouveau sommet : %d",matriceCase[i+1][j].numConstruction);
            infoGeneral->graphe->pSommet=CreerArete(infoGeneral->graphe->pSommet, infoGeneral->source, matriceCase[i+1][j].numConstruction,infoGeneral->distance); //ajout de l'arete au graphe
            infoGeneral->graphe->pSommet[matriceCase[i+1][j].numConstruction]->NbrHabitant=NB_HABITANT_GRATTECIEL;
            return infoGeneral;
        }
    }
    if (tab[i - 1][j] == 6)
    {
        infoGeneral->distance++;
        infoGeneral = rechercheRoute(i-1, j, tab,infoGeneral);
        printf("\ndistance : %d",infoGeneral->distance);
    }
    if (tab[i + 1][j] == 6)
    {
        infoGeneral->distance++;
        infoGeneral= rechercheRoute(i+1, j, tab,infoGeneral);
        printf("\ndistance : %d",infoGeneral->distance);
    }
    if (tab[i][j - 1] == 6)
    {
        infoGeneral->distance++;
        infoGeneral= rechercheRoute(i, j-1, tab,infoGeneral);
        printf("\ndistance : %d",infoGeneral->distance);
    }
    if (tab[i][j + 1] == 6)
    {
        infoGeneral->distance++;
        infoGeneral = rechercheRoute(i, j+1, tab,infoGeneral);
        printf("\ndistance : %d",infoGeneral->distance);
    }
    printf("\ndistance : %d",infoGeneral->distance);
    infoGeneral->distance--;

    return infoGeneral;
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

InfoGeneral * initDistributionEau(InfoGeneral* infoGeneral, int source)  //Partie initialisation du BFS
{
    t_maillon* maille = malloc(sizeof(t_maillon)); //initialisation à null
    infoGeneral->graphe->attente = malloc(sizeof(t_attente));  //création de la file

    infoGeneral->graphe->attente->tete=infoGeneral->graphe->attente->fin=NULL;

    maille->numero=source;      //enfiler le premier maillon avec le numéro de la source
    infoGeneral->graphe->attente->tete= infoGeneral->graphe->attente->fin=maille;     //On le fait que la premiere fois
    infoGeneral->graphe->attente->tete->suivant=infoGeneral->graphe->attente->fin;        //quand la file est vide
    infoGeneral->graphe->attente->fin->suivant=NULL;

    //infoGeneral->graphe->pSommet[source]->chateau=1;//normalement on a déja cette info
    //infoGeneral->graphe->pSommet[source]->habitation=0;

    for(int i=0;i<infoGeneral->graphe->ordre;i++)
    {
        //infoGeneral->graphe->pSommet[i]->habitation=1;
        //infoGeneral->graphe->pSommet[i]->chateau=0;
        //infoGeneral->graphe->pSommet[i]->NbrHabitant=2000;
        infoGeneral->graphe->pSommet[i]->couleur=0;//On note tous les sommets comme non repérés
        infoGeneral->graphe->pSommet[i]->distance=500;
        infoGeneral->graphe->pSommet[i]->pred=-1;
    }
    infoGeneral->graphe->pSommet[source]->distance=0;
    infoGeneral->graphe->pSommet[source]->couleur=1; //la source est marquée
    infoGeneral->graphe->pSommet[source]->capacite=5000;

    return infoGeneral;
}

int selectionProchainSommet(InfoGeneral * infoGeneral)
{
    int numero;
    int dmin=-1;
    t_maillon* position = malloc(sizeof(t_maillon));//initialisation à null

    position=infoGeneral->graphe->attente->tete;
    while(position!=NULL)
    {
        if(dmin==-1)
        {
            dmin=infoGeneral->graphe->pSommet[position->numero]->distance;
            numero=position->numero;
        }
        else if((infoGeneral->graphe->pSommet[position->numero]->distance<dmin))
        {
            dmin=infoGeneral->graphe->pSommet[position->numero]->distance;
            numero=position->numero;
        }
        position=position->suivant;
    }
    return numero;
}

InfoGeneral * PlusCourtCheminDistributionEau(InfoGeneral * infoGeneral)
{
    int numero,sommetDecouvert;
    int distance;
    pArc arc;//pointeur sur structure arc

    while(infoGeneral->graphe->attente->tete!=NULL)  //tant que la liste n'est pas vide
    {

        numero=selectionProchainSommet(infoGeneral);   //on récupère le numéro du premier sommet
        arc=infoGeneral->graphe->pSommet[numero]->arc;   //on pointe sur un de ses arcs
        if (arc==NULL)
        {
            printf("arc nul\n");
        }
        while(arc!=NULL)
        {
            sommetDecouvert=arc->sommet;
            distance=arc->poids;
            printf("arc poids : %d",arc->poids);

            if(infoGeneral->graphe->pSommet[sommetDecouvert]->distance>(distance+infoGeneral->graphe->pSommet[numero]->distance))
            {
                infoGeneral->graphe->pSommet[sommetDecouvert]->distance=(distance+infoGeneral->graphe->pSommet[numero]->distance);
                printf("\ndistance sommet %d : %d\n",sommetDecouvert,infoGeneral->graphe->pSommet[sommetDecouvert]->distance);
                infoGeneral->graphe->pSommet[sommetDecouvert]->pred = numero;  //marquer prédecesseur du new sommet
                if (infoGeneral->graphe->pSommet[sommetDecouvert]->couleur == 0)  //si le sommet adjacent n'est pas découvert
                {
                    printf("tete liste : %d\n",infoGeneral->graphe->attente->tete->numero);

                    infoGeneral->graphe->attente = ajoutListe(infoGeneral->graphe->attente, sommetDecouvert);    //enfiler le new sommet
                    printf("tete liste : %d\n",infoGeneral->graphe->attente->tete->suivant->numero);

                    infoGeneral->graphe->pSommet[sommetDecouvert]->couleur = 1;        //marquer le sommet découvert
                }
                else if (infoGeneral->graphe->pSommet[sommetDecouvert]->couleur == 1)  //si le sommet adjacent est découvert
                {
                    infoGeneral->graphe->attente = ajoutListe(infoGeneral->graphe->attente, sommetDecouvert);    //enfiler le new sommet
                    printf("tete liste : %d\n",infoGeneral->graphe->attente->tete->numero);
                }
            }
            arc = arc->arc_suivant;     //pointer sur l'arc suivant
        }
        infoGeneral->graphe->attente=removeListe(infoGeneral->graphe->attente);   //défiler le sommet actuel
        printf("tete liste : %d\n",infoGeneral->graphe->attente->tete->numero);

    }
    return infoGeneral;
}
void afficheDistributionEau(InfoGeneral* infoGeneral)    //afficher le résultat du BFS
{
    int i=0,j;
    int source=infoGeneral->nbConstruction;
    while(infoGeneral->graphe->pSommet[i]!=NULL)    //pour chaque sommet
    {
        j=i;
        printf("\n%d",i);

        while (j != source)        //tant qu'on est pas remonté à la source
        {
            j = infoGeneral->graphe->pSommet[j]->pred;
            printf("<--%d", j);  //affichage du précédent
        }
        printf(" distance : %d", infoGeneral->graphe->pSommet[i]->distance);
        i++;
    }
}

InfoGeneral * DistributionEau(InfoGeneral* infoGeneral)
{
    int* tab=malloc(infoGeneral->graphe->ordre*sizeof(int));
    int* tableau=malloc(infoGeneral->graphe->ordre*sizeof(int));
    int permutateur,i,j,position;
    int source= infoGeneral->nbConstruction;

    for(i=0;i<infoGeneral->graphe->ordre;i++)
    {
        tableau[i] = infoGeneral->graphe->pSommet[i]->distance;
        tab[i] = i;
    }
    for (i=0; i < (infoGeneral->graphe->ordre-1); i++)
    {
        position = i;
        for (j = i + 1; j < infoGeneral->graphe->ordre; j++)
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
    for (i=0;i<infoGeneral->nbConstruction;i++)
    {
        if ((infoGeneral->graphe->pSommet[source]->NbrHabitant = 0)||(infoGeneral->graphe->pSommet[source]->capacite == 0)) {}
        else if (infoGeneral->graphe->pSommet[source]->capacite - infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant >= 0)
        {
            infoGeneral->graphe->pSommet[source]->capacite = infoGeneral->graphe->pSommet[source]->capacite - infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant;
            printf("\nSommet %d allimente: %dL par le sommet %d", tab[i], infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant,source);
            infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant=0;
        }
        else if (infoGeneral->graphe->pSommet[source]->capacite - infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant < 0)
        {
            infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant = infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant - infoGeneral->graphe->pSommet[source]->capacite;
            infoGeneral->graphe->pSommet[source]->capacite = 0;
            printf("\nSommet %d allimente partiellement par le sommet %d, reste %dL a remplir", tab[i],source, infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant);
        }
    }
    return infoGeneral;
}

InfoGeneral * AlimentationEnEau(InfoGeneral* infoGeneral, int source)
{
    infoGeneral=initDistributionEau(infoGeneral, source);   //démarrer bfs
    infoGeneral=PlusCourtCheminDistributionEau(infoGeneral); //faire bfs
    //printf("salut");
    //afficheDistributionEau(graphe,source); //afficher bfs
    //infogeneral=DistributionEau(infoGeneral);
    return infoGeneral;
}
InfoGeneral *initDistributionElec(InfoGeneral *infoGeneral)
{
    int source=infoGeneral->nbConstruction;
    t_maillon* maille = malloc(sizeof(t_maillon));//initialisation à null

    infoGeneral->graphe->attente = malloc(sizeof(t_attente));  //création de la file
    infoGeneral->graphe->attente->tete=infoGeneral->graphe->attente->fin=NULL;

    maille->numero=infoGeneral->nbConstruction;      //enfiler le premier maillon avec le numéro de la source
    infoGeneral->graphe->attente->tete= infoGeneral->graphe->attente->fin=maille;     //On le fait que la premiere fois
    infoGeneral->graphe->attente->tete->suivant=infoGeneral->graphe->attente->fin;        //quand la file est vide
    infoGeneral->graphe->attente->fin->suivant=NULL;

    //graphe->pSommet[source]->chateau=1;//normalement on a déja cette info
    //graphe->pSommet[source]->habitation=0;
    infoGeneral->graphe->pSommet[source]->capacite=5000;
    infoGeneral->graphe->pSommet[source]->couleur=1; //la source est marquée
    infoGeneral->graphe->pSommet[source]->distance=0;
    infoGeneral->graphe->pSommet[source]->pred=-1;    //tous les predecesseurs sont à -1: il n'y en a pas

    for(int i=1;i<infoGeneral->graphe->ordre;i++)
    {
        //graphe->pSommet[i]->habitation=1;
        //graphe->pSommet[i]->chateau=0;
        infoGeneral->graphe->pSommet[i]->NbrHabitant=2000;
        infoGeneral->graphe->pSommet[i]->couleur=0;//On note tous les sommets comme non repérés
        infoGeneral->graphe->pSommet[i]->pred=-1;    //tous les predecesseurs sont à -1: il n'y en a pas
        infoGeneral->graphe->pSommet[i]->distance=500;
    }
    return infoGeneral;
}
InfoGeneral *PlusCourtCheminDistributionElec(InfoGeneral *infoGeneral)
{
    int numero,sommetDecouvert;
    int distance;
    pArc arc;//pointeur sur structure arc

    while(infoGeneral->graphe->attente->tete!=NULL)  //tant que la liste n'est pas vide
    {
        numero=selectionProchainSommet(infoGeneral);   //on récupère le numéro du premier sommet
        arc=infoGeneral->graphe->pSommet[numero]->arc;   //on pointe sur un de ses arcs
        while(arc!=NULL)
        {
            sommetDecouvert=arc->sommet;
            distance=arc->poids;
            if(infoGeneral->graphe->pSommet[sommetDecouvert]->distance>(distance+infoGeneral->graphe->pSommet[numero]->distance))
            {
                infoGeneral->graphe->pSommet[sommetDecouvert]->distance=(distance+infoGeneral->graphe->pSommet[numero]->distance);
                printf("\ndistance sommet %d : %d",sommetDecouvert,infoGeneral->graphe->pSommet[sommetDecouvert]->distance);
                infoGeneral->graphe->pSommet[sommetDecouvert]->pred = numero;  //marquer prédecesseur du new sommet
                if (infoGeneral->graphe->pSommet[sommetDecouvert]->couleur == 0)  //si le sommet adjacent n'est pas découvert
                {
                    infoGeneral->graphe->attente = ajoutListe(infoGeneral->graphe->attente, sommetDecouvert);    //enfiler le new sommet
                    infoGeneral->graphe->pSommet[sommetDecouvert]->couleur = 1;        //marquer le sommet découvert
                }
                else if (infoGeneral->graphe->pSommet[sommetDecouvert]->couleur == 1)  //si le sommet adjacent n'est pas découvert
                {
                    infoGeneral->graphe->attente = ajoutListe(infoGeneral->graphe->attente, sommetDecouvert);    //enfiler le new sommet
                }
            }
            arc = arc->arc_suivant;     //pointer sur l'arc suivant
        }
        infoGeneral->graphe->attente=removeListe(infoGeneral->graphe->attente);   //défiler le sommet actuel
    }
    return infoGeneral;
}
void afficheDistributionElec(Graphe *graphe)
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
InfoGeneral *DistributionElec(InfoGeneral *infoGeneral)
{
    int* tab=malloc(infoGeneral->graphe->ordre*sizeof(int));
    int* tableau=malloc(infoGeneral->graphe->ordre*sizeof(int));
    int permutateur,i,j,position;

    for(i=0;i<infoGeneral->graphe->ordre;i++)
    {
        tableau[i] = infoGeneral->graphe->pSommet[i]->distance;
        tab[i] = i;
    }
    for (i=0; i < (infoGeneral->graphe->ordre-1); i++)
    {
        position = i;
        for (j = i + 1; j < infoGeneral->graphe->ordre; j++)
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
    infoGeneral->graphe->pSommet[4]->NbrHabitant=3;

    for (i=0;i<infoGeneral->graphe->ordre;i++)
    {
        if ((infoGeneral->graphe->pSommet[0]->NbrHabitant = 0)||(infoGeneral->graphe->pSommet[0]->capacite == 0))
        {
            printf("\nSommet %d non allimente", tab[i]);
        }
        else if (infoGeneral->graphe->pSommet[0]->capacite - infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant > 0)
        {
            infoGeneral->graphe->pSommet[0]->capacite = infoGeneral->graphe->pSommet[0]->capacite - infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant;
            printf("\nSommet %d allimente: %dL", tab[i], infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant);
        }
        else if (infoGeneral->graphe->pSommet[0]->capacite - infoGeneral->graphe->pSommet[tab[i]]->NbrHabitant < 0)
        {
            printf("\nSommet %d non allimente car manque d'elec", tab[i]);
        }
    }
    return infoGeneral;
}
InfoGeneral * AlimentationElectricite(InfoGeneral * infoGeneral)
{
    infoGeneral=initDistributionElec(infoGeneral);
    infoGeneral=PlusCourtCheminDistributionElec(infoGeneral);
    afficheDistributionElec(infoGeneral);
    infoGeneral=DistributionElec(infoGeneral);
    return infoGeneral;
}

InfoGeneral* remplissageGraphe(InfoGeneral* infoGeneral) {
    FILE *ifs = fopen("Test_matrice.txt","r");
    FILE *ifs2 = fopen("matriceCase.txt","w");

    int tab[45][35];
    infoGeneral->distance=0;
    int numConstruction;
    int i,j,k,l;
    int ordre=0;

    if(ifs==NULL)    {printf("erreur");}
    if(ifs2==NULL)    {printf("erreur");}

    for ( i = 0; i < 35; i++) //récupérer les données de la matrice
    {
        for ( j = 0; j < 45; j++)
        {
            tab[i][j]=matriceCase[i][j].batiment;
            printf("%d ", matriceCase[i][j].batiment);
            fprintf(ifs2,"%d ",matriceCase[i][j].batiment);
        }
        printf("\n");
        fprintf(ifs2,"\n ");
    }
    fclose(ifs);
    fclose(ifs2);
    //infoGeneral->graphe= CreerGraphe(infoGeneral->nbConstruction); // creer le graphe vide d'ordre sommets

    for ( i = 0; i < 35; i++) //récupérer les données de la matrice
    {
        for ( j = 0; j < 45; j++)
        {
            if(tab[i][j]==11)
            {
                switch (tab[i][j+1])
                {
                    case 7: //citerne 4*6
                        for (k = 0; k < 6; k++)
                        {
                            for (l = 0; l < 4; l++)
                            {
                                //infoGeneral=rechercheRoute(i+k,j+l,tab, infoGeneral);
                                infoGeneral->distance=0;
                            }
                        }
                        printf("\n");
                        break;
                    case 8: //centrale elec
                        break;
                }
            }
        }
    }
    graphe_afficher(infoGeneral);
    return infoGeneral;
}

t_infosJeu recupererInfosJeu(t_infosJeu infos){
    FILE *ifs = fopen("../infosJeu","r");
    int i = 0,j = 0;
    if(ifs==NULL)    {printf("erreur");}

    matriceCase[i][j].couleurCase = al_map_rgba(0,0,0,0);
    fscanf(ifs,"%d ",&infos.prixTerrain);
    fscanf(ifs,"%d ",&infos.prixUsine);
    fscanf(ifs,"%d ",&infos.prixCiterne);
    fscanf(ifs,"%d ",&infos.prixRoute);
    fscanf(ifs,"%d ",&infos.nbHabcabane);
    fscanf(ifs,"%d ",&infos.nbHabmaison);
    fscanf(ifs,"%d ",&infos.nbHabimmeuble);
    fscanf(ifs,"%d ",&infos.nbHabgratteciel);
    fclose(ifs);
    return infos;
}


void initAllegro(){ //initialisation d'Allegro
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

int largeurCaseGrille(short x1, short x2){
    return (x2 - x1)/NOMBRECOLONNE;
}
int hauteurCaseGrille(short y1, short y2){
    return (y2 - y1)/NOMBRELIGNE;
}
short coordonneX1CaseGrille(short x1, short x2,short noCollonne) {
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
void initialiserCasesGrille()
{
    FILE *ifs = fopen("matriceDebut.txt","r");
    int i,j;
    if(ifs==NULL)    {printf("erreur");}

    for ( i = 0; i < NOMBRELIGNE; i++) //récupérer les données de la matrice
    {
        for ( j = 0; j < NOMBRECOLONNE; j++)
        {
            matriceCase[i][j].x1Case = coordonneX1CaseGrille(X1GRILLE, X2GRILLE, j+1);
            matriceCase[i][j].y1Case = coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, i+1);
            matriceCase[i][j].x2Case = coordonneX2CaseGrille(X1GRILLE, X2GRILLE, j+1);
            matriceCase[i][j].y2Case = coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, i+1);
            //matriceCase[i][j].batiment=0;
            //matriceCase[i][j].numConstruction=0;
            matriceCase[i][j].couleurCase = al_map_rgba(0,0,0,0);
            fscanf(ifs,"%d ",&matriceCase[i][j].obstacle);
            fscanf(ifs,"%d ",&matriceCase[i][j].etat);
        }
    }
    fclose(ifs);
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

// initilisation police d'écriture

ALLEGRO_FONT* initialiserPoliceTexte(short taillePolice){
    ALLEGRO_FONT* policeTexte = NULL ;
    policeTexte = al_load_ttf_font("../Bangers-Regular.ttf", taillePolice,0);
    return policeTexte;
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
void afficherTempsRestant(float tempsRestant,float mois, ALLEGRO_FONT* policeTexte){ //chronomètre
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


void rechercheCentral(InfoGeneral* infoGeneral, int x, int y, bool*connecteEau, bool*connecteElec,Case matricePlateau[NOMBRELIGNE][NOMBRECOLONNE]) {
    if (!(*connecteEau) || !(*connecteElec)) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (!(i == j || i == -j)) {
                    switch (matriceCase[y + i][x + j].obstacle) {
                        case 6 : {
                            matricePlateau[y + i][x + j].obstacle = 22;
                            rechercheCentral(infoGeneral, x + j, y + i, connecteEau, connecteElec,matricePlateau);
                            break;
                        }
                        case 7 : {
                            *connecteElec = true;
                            break;
                        }
                        case 8 : {
                            *connecteEau = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int verificationViable(InfoGeneral* infoGeneral, Case plateau[NOMBRELIGNE][NOMBRECOLONNE],int x, int y) {
    bool connecteEau = false;
    bool connecteElec = false;
    int compteur = 0;
    for (int i = -1; i < 4; i++) {
        for (int j = -1; j < 4; j++) {
            if (compteur != 0 && compteur != 4 && compteur != 20 && compteur != 24) {
                if (plateau[i + y][j + x].obstacle == 6) {
                    rechercheCentral(infoGeneral, j + x, i + y, &connecteEau, &connecteElec,matriceCase);
                }
            }
            compteur++ ;
        }
    }
    for (int i = 0; i < NOMBRELIGNE; i++) {
        for (int j = 0; j < NOMBRECOLONNE; j++) {
            if (plateau[i][j].obstacle == 22)
                plateau[i][j].obstacle = 6;
        }
    }
    if (connecteElec && connecteEau)
        return 1;
    else
        return 0;
}

void verificationMaisonNonViables(InfoGeneral * infoGeneral,Case plateau[NOMBRELIGNE][NOMBRECOLONNE],int x, int y) {
    for (int i = 0; i < 50; i++) {
        if (infoGeneral->maison[i].vivable == 0) {
            infoGeneral->maison[i].vivable = verificationViable(infoGeneral, plateau,x , y);
        }
    }
}




void colorierCaseSouris(short xSouris, short ySouris,short niveau,ALLEGRO_FONT* policeTexte,ALLEGRO_BITMAP* imageCiterne,ALLEGRO_BITMAP* imageCabane,ALLEGRO_BITMAP* imageMaison,ALLEGRO_BITMAP* imageImmeuble,ALLEGRO_BITMAP* imageGratteCiel, ALLEGRO_BITMAP* imageTerrain,ALLEGRO_BITMAP* imageUsine){
    dessinneGrille(X1GRILLE, Y1GRILLE, X2GRILLE, Y2GRILLE, 1, al_map_rgb(0, 0, 0),policeTexte);
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                al_draw_filled_rectangle(coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),al_map_rgb(200,0,0));
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
                    al_draw_bitmap(imageImmeuble, 16*i+20, 16*j+20, 0);
                }
                if (matriceCase[j][i].etat == 5) {
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

void sauvegarde()
{
    FILE *ifs = fopen("SauvegardeObstacle.txt","w");
    FILE *ifs2 = fopen("SauvegardeEtat.txt","w");
    int i,j;
    if(ifs==NULL)    {printf("erreur");}
    if(ifs2==NULL)    {printf("erreur");}

    for ( i = 0; i < 35; i++) //récupérer les données de la matrice
    {
        for ( j = 0; j < 45; j++)
        {
            fprintf(ifs,"%d ",matriceCase[i][j].obstacle);
            fprintf(ifs2,"%d ",matriceCase[i][j].etat);
        }
        fprintf(ifs,"\n ");
        fprintf(ifs2,"\n ");
    }
    fclose(ifs);
    fclose(ifs2);
}

InfoGeneral* construireroute(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral);

InfoGeneral* construireterrain(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral){
    int caseVide = 0;
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                for(short k = 0; k< 3; k++) {
                    for (short l = 0; l < 3; l++) {
                        if((matriceCase[k + ycase][ l + xcase].obstacle == 0 || matriceCase[k + ycase][ l + xcase].obstacle == 9)&& xcase<43 && ycase <33) {
                            caseVide ++;
                        }
                    }
                }
                if(caseVide == 9 && infoGeneral->argent >= 1000) { //si les 9 cases sont vides et argent suffisant
                    infoGeneral->argent -= 1000;
                    infoGeneral->nombreMaison =infoGeneral->nombreMaison+1;
                    infoGeneral->nbConstruction =infoGeneral->nbConstruction+1;
                    infoGeneral->maison[infoGeneral->nombreMaison].caseX = xcase;
                    infoGeneral->maison[infoGeneral->nombreMaison].caseY = ycase;
                    verificationViable(infoGeneral,matriceCase, xcase,ycase);
                    for(short k = 0; k< 3; k++) {
                        for (short l = 0; l < 3; l++) {
                            matriceCase[k + ycase][l + xcase].obstacle = 1;
                            matriceCase[ycase][xcase].etat = 1;// pixel en haut à gauche du batiment
                            matriceCase[k+ycase][l+xcase].batiment=1;
                            //matriceCase[k+ycase][l + xcase].numConstruction=infoGeneral->nombreMaison;
                            matriceCase[k+ycase][l + xcase].numConstruction=infoGeneral->nbConstruction;
                        }
                    }
                    matriceCase[ycase][xcase].batiment=11;
                    //infoGeneral= remplissageGraphe(infoGeneral);
                }
            }
        }
    }
    return infoGeneral;
}

InfoGeneral* construireciterne(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral,ALLEGRO_BITMAP* imageCiterne ){
    short caseVide = 0;
    int distance=0;
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
                if(caseVide == 24 && infoGeneral->argent >= 100000){ //si case vides et argent necessaire
                    infoGeneral->argent -=100000;
                    infoGeneral->nombreCiterne =infoGeneral->nombreCiterne +1;
                    infoGeneral->nbConstruction=infoGeneral->nbConstruction+1;
                    infoGeneral->capeau +=5000; //capicité en haut incrementée
                    infoGeneral->citerne[infoGeneral->nombreCiterne].caseX = xcase;
                    infoGeneral->citerne[infoGeneral->nombreCiterne].caseY = ycase;
                    for(short k = 0; k< 6; k++)
                    {
                        for (short l = 0; l < 4; l++)
                        {
                            matriceCase[k + ycase][l + xcase].obstacle = 7;
                            matriceCase[ycase][xcase].etat = 7;
                            matriceCase[k+ycase][l+xcase].batiment=7;
                            //matriceCase[k + ycase][l + xcase].numConstruction=infoGeneral->nombreCiterne;
                            matriceCase[k+ycase][l + xcase].numConstruction=infoGeneral->nbConstruction;
                        }
                    }
                    matriceCase[ycase][xcase].batiment=11;
                    //infoGeneral= remplissageGraphe(infoGeneral);
                    //infoGeneral=AlimentationEnEau(infoGeneral);
                }
            }
        }
    }
    return infoGeneral;
}

InfoGeneral* construireusine(short xSouris, short ySouris, short xcase , short ycase, InfoGeneral* infoGeneral){
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
                if(caseVide == 24 && infoGeneral->argent >= 100000){ // vérification que toutes le scases sont libres et argent suffisant
                    infoGeneral->argent -=100000;
                    infoGeneral->nombreUsine +=1;
                    infoGeneral->nbConstruction++;
                    infoGeneral->capelec +=5000;
                    infoGeneral->usine[infoGeneral->nombreUsine].caseX = xcase;
                    infoGeneral->usine[infoGeneral->nombreUsine].caseY = ycase;
                    for(short k = 0; k< 6; k++) {
                        for (short l = 0; l < 4; l++) {
                            matriceCase[k + ycase][l + xcase].obstacle = 8;
                            matriceCase[ycase][xcase].etat = 8;//pixel en haut à gauche de l'image
                            matriceCase[k+ycase][l+xcase].batiment=8;
                            //matriceCase[k + ycase][l + xcase].numConstruction=infoGeneral->nombreUsine;
                            matriceCase[k + ycase][l + xcase].numConstruction=infoGeneral->nbConstruction;
                        }
                    }
                    matriceCase[ycase][xcase].batiment=11;
                    //infoGeneral= remplissageGraphe(infoGeneral);
                }
            }
        }
    }
    return infoGeneral;
}
InfoGeneral* destructionConstruction(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral)
{
for(short i = 0; i< NOMBRECOLONNE; i++){
for(short j = 0; j<NOMBRELIGNE; j++) {
if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
if(matriceCase[ycase][xcase].etat == 7 || matriceCase[ycase][xcase].etat == 8){
if(matriceCase[ycase][xcase].etat == 7){
infoGeneral->capeau -= 5000;
}
if(matriceCase[ycase][xcase].etat == 8){
infoGeneral->capelec -= 5000;
}
matriceCase[ycase][xcase].etat = 0;
for(short k = 0; k< 6; k++) {
for (short l = 0; l < 4; l++) {
matriceCase[k + ycase][ l + xcase].obstacle = 9;
matriceCase[ycase][xcase].batiment = 0;
matriceCase[k + ycase][l + xcase].numConstruction=0;
}
}
}
if(matriceCase[ycase][xcase].etat >0 && matriceCase[ycase][xcase].etat<6){
if(matriceCase[ycase][xcase].etat ==2) {
infoGeneral->habitant -= 10;
}
if(matriceCase[ycase][xcase].etat ==3) {
infoGeneral->habitant -= 50;
}
if(matriceCase[ycase][xcase].etat ==4) {
infoGeneral->habitant -= 100;
}
if(matriceCase[ycase][xcase].etat ==5) {
infoGeneral->habitant -= 1000;
}
matriceCase[ycase][xcase].etat = 0;
for(short k = 0; k< 3; k++) {
for (short l = 0; l < 3; l++) {
matriceCase[k + ycase][ l + xcase].obstacle = 9;
matriceCase[ycase][xcase].batiment = 0;
matriceCase[k + ycase][l + xcase].numConstruction=0;
}
}
}
if(matriceCase[ycase][xcase].etat == 6){
matriceCase[ycase][xcase].etat = 0;
matriceCase[ycase][xcase].obstacle = 9;
matriceCase[ycase][xcase].batiment = 0;
}
}
}
}
return infoGeneral;
}

InfoGeneral* evolutionTerrain(InfoGeneral* infoGeneral, short *mode){
    if(verificationViable(infoGeneral,matriceCase,infoGeneral->maison[infoGeneral->nombreMaison].caseX,infoGeneral->maison[infoGeneral->nombreMaison].caseY) || *mode == 2){ // si relié à citerne et centrale
        for(short i = 0; i< NOMBRECOLONNE; i++)
        {
            for (short j = 0; j < NOMBRELIGNE; j++) {
                if(matriceCase[j][i].obstacle == 4 && infoGeneral->habitant < infoGeneral->capelec && infoGeneral->habitant < infoGeneral->capeau){
                    matriceCase[j][i].obstacle = 5;
                    if(matriceCase[j][i].etat == 4 )
                    {
                        matriceCase[j][i].etat = 5;
                        infoGeneral->habitant+=900;
                    }
                    if(matriceCase[j][i].batiment == 4 )
                    {
                        matriceCase[j][i].batiment = 5;
                    }
                }
                if(matriceCase[j][i].obstacle == 3 && infoGeneral->habitant < infoGeneral->capelec && infoGeneral->habitant < infoGeneral->capeau){
                    matriceCase[j][i].obstacle = 4;
                    if(matriceCase[j][i].etat == 3 ){
                        matriceCase[j][i].etat = 4;
                        infoGeneral->habitant+=50;
                    }
                    if(matriceCase[j][i].batiment == 3 )
                    {
                        matriceCase[j][i].batiment = 4;
                    }
                }
                if(matriceCase[j][i].obstacle == 2 && infoGeneral->habitant < infoGeneral->capelec && infoGeneral->habitant < infoGeneral->capeau){
                    matriceCase[j][i].obstacle = 3;
                    if(matriceCase[j][i].etat == 2 ){
                        matriceCase[j][i].etat = 3;
                        infoGeneral->habitant+=40;
                    }
                    if(matriceCase[j][i].batiment == 2 )
                    {
                        matriceCase[j][i].batiment = 3;
                    }
                }
                if(matriceCase[j][i].obstacle == 1 && infoGeneral->habitant < infoGeneral->capelec && infoGeneral->habitant < infoGeneral->capeau){
                    matriceCase[j][i].obstacle = 2;
                    if (matriceCase[j][i].etat == 1) {
                        matriceCase[j][i].etat = 2;
                        infoGeneral->habitant += 10;
                    }
                    if (matriceCase[j][i].batiment == 1) {
                        matriceCase[j][i].batiment = 2;
                    }
                }
                if(matriceCase[j][i].batiment == 11)
                {
                    //infoGeneral= remplissageGraphe(infoGeneral);
                    //infoGeneral=AlimentationEnEau(infoGeneral,infoGeneral->source);
                }
            }
        }
    }
    return infoGeneral;
}
void dessinerBoutonOutil(ALLEGRO_FONT* policeTexte,ALLEGRO_FONT* policeTexteGrande){
    dessinerBouton(X1OUTIL, Y1OUTIL , X2OUTIL ,Y2OUTIL , al_map_rgb(150,150,150), "OUTILS", policeTexteGrande, TAILLEPOLICEBOUTTONGRANDE);
}

InfoGeneral* construireroute(short xSouris, short ySouris, short xcase , short ycase,InfoGeneral* infoGeneral){
    for(short i = 0; i< NOMBRECOLONNE; i++){
        for(short j = 0; j<NOMBRELIGNE; j++) {
            if (checkSourisDansBouton(xSouris, ySouris, coordonneX1CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY1CaseGrille(Y1GRILLE, Y2GRILLE, j + 1),coordonneX2CaseGrille(X1GRILLE, X2GRILLE, i + 1),coordonneY2CaseGrille(Y1GRILLE, Y2GRILLE, j + 1))) {
                if((matriceCase[ycase][xcase].obstacle == 0 || matriceCase[ycase][xcase].obstacle == 9 )&& infoGeneral->argent >= 10) {
                    matriceCase[ycase][xcase].etat = 6;
                    matriceCase[ycase][xcase].obstacle = 6;
                    matriceCase[ycase][xcase].batiment=6;
                    infoGeneral->argent -=10;
                    //infoGeneral= remplissageGraphe(infoGeneral);
                    verificationMaisonNonViables(infoGeneral,matriceCase, xcase,ycase);
                }
            }
        }
    }
    return infoGeneral;
}