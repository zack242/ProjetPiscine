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
    std::string fichier_topo;
    std::string fichier_ponde;



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


        std::cout<<"Nom du fichier de topologie : ";
       // std::cin>>fichier_topo;
        std::cout<<"Nom du fichier de ponderations : ";

       // std::cin>>fichier_ponde;
      fichier_ponde="poids";
    fichier_topo="graphe";

////ouhhhhhh
        A=Chargement_Graphe(fichier_topo,fichier_ponde);
        A->setnomFichier(fichier_topo);

        break;

    case 2 : ///Chargement du systeme de ponderation

        fichier_topo=A->getFichier();
        std::cout<<"Nom du fichier de ponderations : ";
        std::cin>>fichier_ponde;

        A=Chargement_Graphe(fichier_topo,fichier_ponde);
        A->setnomFichier(fichier_topo);

        break;


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

            A->calcul_vecteur_propre();
            A->affi_indice_Tvecteur();
            A->Visualisation_indice(choix_indice);
            A->Dessiner();
            A->sauvgarder(choix_indice);



            break ;

        case 3 : /// Indice de proximite

            A->calcul_indice_proximite();
            A->affi_indice_Tproximite();
            A->Visualisation_indice(choix_indice);
            A->Dessiner();
            A->sauvgarder(choix_indice);


            break;

        case 4 : ///Centralite d'intermediaire


            break;



        default :

            break ;

        }

        break;

        case 4 :

            A->GrapheConnexe();
            A->TestVulnerabilite();
            A->Dessiner();
            A->afficher();

            break;



    default :

        break ;
    }

    return A;

}


Graphe* Chargement_Graphe(std::string fichier_topo, std::string fichier_ponde)  ///SS Chargement d'un graphe depuis fichier
{

    Graphe* B{};
    std::string temp_topo,temp_pond;

    std::cout<<"\n Chargement du graphe avec "<<fichier_topo << " et " <<fichier_ponde<< " \n\n" ;

    temp_topo=fichier_topo+".txt";
    temp_pond=fichier_ponde+".txt";

    std::cout<<temp_topo;


    B=new Graphe{temp_topo,temp_pond}; /// Allocation du graphe

    B->Dessiner();
    B->afficher();

    return B;

}

