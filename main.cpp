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
    Graphe A{};


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

        A=Chargement_Graphe();
        break;

    case 3 :
        menu2(A);

    case 99 :

        exit(0);
        break;

    }



}

void menu2(Graphe A)
{
    int choix_indice,choix ;

    std::cout<<"           Choix indice \n\n";

    std::cout<<"1/La centralite de degre \n";
    std::cout<<"2/La centralite de vecteur propre \n";
    std::cout<<"3/La centralite de proximite \n";
    std::cout<<"4/La centralite d’intermediarite \n";
    std::cout<<"99/Exit\n\n ";
    std::cout<<"Votre choix : " ;
    std::cin>>choix_indice ;
    std::cout<<"\n";

    std::cout<<"            Que faire ? \n\n";

    std::cout<<"1/Calculer l'indice\n";
    std::cout<<"2/Afficher l'indice\n";
    std::cout<<"3/Sauvegarder l'indice\n";
    std::cout<<"99/Exit\n\n ";
    std::cout<<"Votre choix : " ;
    std::cin>>choix ;
    std::cout<<"\n";

    switch (choix_indice)
    {

    case 1 :
        switch(choix)
        {
        case 1 :
           // A.calcul_indice_degres();

            break;

        case 2 :


            break ;


        case 3 :
            break;



        default :

            break;


        }


        break;



    case 99 :
        exit(0);
        break;
}

}

Graphe Chargement_Graphe()
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

    A.Dessiner();
    A.calcul_indice_degres();
    A.afficher();

return A;

}
