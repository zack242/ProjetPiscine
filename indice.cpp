#include <iostream>
#include "header.h"

void Sommet::indice_degre(float ordre)
{
    int nbrsucc=0;

    for( auto s : m_successeurs)
        nbrsucc++;

    m_indice.degre_non_normamise=nbrsucc;
    m_indice.degre_nomralise=(nbrsucc/ordre);

}

void Graphe::calcul_indice_degres()
{
    for(auto s : m_sommets)
        s->indice_degre(m_sommets.size()-1); //On envoie l'ordre du graphe -1

}

void Sommet::affi_degre_sommmet() const
{
    std::cout<<" sommet : "<<m_nom<< std::endl;
    std::cout<<"indice de degre normalise : "<<m_indice.degre_nomralise<<" , \n"<<"indice de degre nonnormalise : "<<m_indice.degre_non_normamise<<" .";

}

void Graphe::affi_indice_Tdegre() const
{
    for (auto s : m_sommets)
    {
        s->affi_degre_sommmet();
        std::cout<<std::endl;
    }
}










































void Graphe::Visualisation_indice(int indice)
{

    std::vector<float> valeurindice;

    switch (indice)
    {

    case 1 :  ///Pour chaque indice on push l'indice dans valeur indice suivant le choix du client

        for(auto k : m_sommets)
            valeurindice.push_back(k->getIndice(indice));

        break;

    case 2 : /// Indice vecteur propre

        for(auto k : m_sommets)
            valeurindice.push_back(k->getIndice(indice));

        break;


    case 3 : /// Indice vecteur proximite

        for(auto k : m_sommets)
            valeurindice.push_back(k->getIndice(indice));

        break;

    case 4 : /// Indice intermediare

        for(auto k : m_sommets)
            valeurindice.push_back(k->getIndice(indice));

        break;

    }

    std::sort(valeurindice.begin(),valeurindice.end());

    for(auto k : m_sommets)
        for(int i=0 ; i<valeurindice.size(); i++)
            if(valeurindice[i]==k->getIndice(indice))
                if(k->getColor()==0)
                    k->setColor(100+20*i);




}


