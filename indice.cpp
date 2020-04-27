#include <iostream>
#include "header.h"

void Sommet::indice_degre(float ordre)
{
int nbrsucc=0;
for( auto s : m_successeurs)
    {

    nbrsucc++;

    }

m_indice.degre_non_normamise=nbrsucc;
m_indice.degre_nomralise=(nbrsucc/ordre);


}

void Graphe::calcul_indice_degres()
{
    for(auto s : m_sommets)
        s->indice_degre(m_sommets.size()-1);//On envoie l'ordre du graphe -1



}
