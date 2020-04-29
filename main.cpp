#include <iostream>
#include "header.h"

using namespace std;

int main()
{
    allegro_init();

    Graphe* A{};

    cout << "--Projet Theorie des graphes-- \n" << endl;

    while(!0)
        A=menu(A);


    return 0;

}
END_OF_MAIN();



Graphe* menu(Graphe* A)
{

    int choix=0,choix_indice=0,choix_action=0 ;


    std::cout<<"\n          Menu \n\n";

    std::cout<<"1/Chargement d'un Graphe. \n";
    std::cout<<"2/Changement du systeme de ponderation. \n";
    std::cout<<"3/Calculer, afficher et Sauvegarder les differents indices de centralite.\n";
    std::cout<<"4/Tester la vulnerabilite. \n";
    std::cout<<"99/Exit\n\n ";
    std::cout<<"Votre choix : " ;

    std::cin>>choix ;



    switch (choix)
    {

    case 1 : ///Chargement du graphe

        A=Chargement_Graphe();

        break;

    case 2 : ///Chargement du systeme de ponderation

           A=Changement_Graphe_ponderation();

    case 3 : /// Calculer , afficher , Saivgarder


        std::cout<<"           Choix indice \n\n";

        std::cout<<"1/La centralite de degre \n";
        std::cout<<"2/La centralite de vecteur propre \n";
        std::cout<<"3/La centralite de proximite \n";
        std::cout<<"4/La centralite d’intermediarite \n";
        std::cout<<"Votre choix : " ;

        std::cin>>choix_indice ;
        std::cout<<"\n";


        switch (choix_indice)
        {


        case 1 : /// Indice degres normalise et non

            A->calcul_indice_degres();
            A->affi_indice_Tdegre();
            A->Visualisation_indice(choix_indice);
            A->Dessiner();
            A->sauvgarder(choix_indice);


            break;

        case 2 : /// Indice centralite de degres propre



            break ;

        case 3 : /// Indice de proximite


            break;

        case 4 : ///Centralite d'intermediaire


            break;



        default :

            break ;


        }

    default :

        break ;
    }

    return A;

}






Graphe* Chargement_Graphe() ///SS Chargement d'un graphe depuis fichier
{

    Graphe* B{};

    BITMAP* page ;
    int i;
    std::string fichier_topo;
    std::string fichier_ponde;

    std::cout<<"Nom du fichier de topologie : ";
    // std::cin>>fichier_topo;
    std::cout<<"Nom du fichier de ponderations : ";
    //  std::cin>>fichier_ponde;

    fichier_ponde="poids.txt"; /// A vire a la fin
    fichier_topo="graphe.txt";

    std::cout<<"\n Chargement du graphe avec "<<fichier_topo << " et " <<fichier_ponde<< " \n\n" ;

    B=new Graphe{fichier_topo,fichier_ponde}; /// Allocation du graphe

    B->Dessiner();
    B->afficher();

    return B;

}

Graphe* Changement_Graphe_ponderation()

{

  Graphe* B{};

    BITMAP* page ;
    int i;
    std::string fichier_ponde;
    std::string fichier_topo;

    std::cout<<"Nom du fichier de ponderations : ";
    std::cin>>fichier_ponde;

    fichier_topo="graphe.txt";

    std::cout<<"\n Chargement du graphe avec "<<fichier_topo << " et " <<fichier_ponde<< " \n\n" ;

    B=new Graphe{fichier_topo,fichier_ponde}; /// Allocation du graphe

    B->Dessiner();
    B->afficher();

    return B;

}
