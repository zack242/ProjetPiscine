#include <iostream>
#include "header.h"

void Sommet::indice_degre(int ordre)
{
int nbrsucc=0;
for( auto s : m_successeurs)
    {

    nbrsucc++;

    }




}

void Graphe::calcul_indice_degres()
{
    for(auto s : m_sommets)
        s->indice_degre(m_sommets.size()-1);//On envoie l'ordre du graphe -1



}
