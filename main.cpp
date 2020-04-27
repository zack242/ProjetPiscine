#include <iostream>
#include "header.h"

using namespace std;

int main()
{
 allegro_init();


    cout << "--Projet Theorie des graphes-- \n" << endl;

    while(!0)
        menu();


    return 0;

}END_OF_MAIN();

void menu()
{
    int choix ;


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

        Chargement_Graphe();
        break;

    case 99 :

        exit(0);
        break;

    }



}

void Chargement_Graphe()
{

    set_color_depth(desktop_color_depth());

    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* page ;
    std::string fichier_topo;
    std::string fichier_ponde;

    std::cout<<"Nom du fichier de topologie : ";
   // std::cin>>fichier_topo;
    std::cout<<"Nom du fichier de ponderations : ";
  //  std::cin>>fichier_ponde;
    std::cout<<"\n Chargement du graphe avec "<<fichier_topo << "et" <<fichier_ponde<< " \n\n" ;
     fichier_ponde="poids.txt"; /// A vire a la fin
     fichier_topo="graphe.txt";

    Graphe A { fichier_topo,fichier_ponde };
    A.afficher();
    A.Dessiner();



}
