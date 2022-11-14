//
// Created by emili on 10/11/2022.
//

#include "Lucie.h"

int main()
{
    Graphe * g=lire_graphe("tp6.txt");
    graphe_afficher(g);    // afficher le graphe
    g= AlimentationEnEau(g);
    AlimentationElectricite(g);
    return 0;
}
