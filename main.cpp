#include <iostream>
#include "header.h"

using namespace std;

int main()
{
    cout << "--Projet Theorie des graphes-- \n" << endl;
    while(!0)
    menu();

    return 0;
}

void menu()
{
int choix ;
std::string fichier_topo;
std::string fichier_ponde;

std::cout<<"            Menu \n\n";

std::cout<<"1/Chargement d'un Graphe. \n";
std::cout<<"2/Chagement du systeme de ponderation. \n";
std::cout<<"3/Calculer, afficher et Sauvegarder les differents indices de centralite.\n";
std::cout<<"4/Tester la vulnerabilite. \n";
std::cout<<"99/Exit\n\n ";
std::cout<<"Votre choix : " ;
std::cin>>choix ;
std::cout<<"\n";

switch (choix)
{

case 1 :

    std::cout<<"- Chargement d'un Graphe.\n";

    std::cout<<"Nom du fichier de topologie : ";
    std::cin>>fichier_topo;
    std::cout<<"Nom du fichier de ponderations : ";
    std::cin>>fichier_ponde;

    std::cout<<"\n Chargement du graphe avec "<<fichier_topo << "et" <<fichier_ponde<< " \n\n" ;

break;

case 99 :
    exit(0);


default :
    std::cout<<"Erreur \n";

}



}
