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


void Graphe::calcul_vecteur_propre()
{
int i ;
float S_indice=0;
float S_total=0;
float temp=0;

calcul_indice_degres();

for(auto s : m_sommets)
{
   S_indice=0;

   for(auto succ : s->getSuccesseurs())
    {
    S_indice+=succ.first->getIndice_vecteurP();

    }
    std::cout<<"\n Somme : "<<S_indice;
    s->setIndice_vecteurP(S_indice);
    S_total+=S_indice*S_indice;

}

temp=sqrt(S_total);


for(auto k : m_sommets)
    {
k->setIndice_vecteurP(k->getIndice_vecteurP()/temp);
std::cout<<"\n Indice : "<<k->getIndice_vecteurP();

}



}
