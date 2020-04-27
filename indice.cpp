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
int i=0 ;

float S_indice=0;
float S_total=0;
float lamda=0;
std::vector<int> stock;

calcul_indice_degres();

for (auto s : m_sommets)
{
    S_indice=0;

    for(auto succ : s->getSuccesseurs())
    {
        S_indice+=succ.first->getIndice_vecteurP();


    }
       S_total+=pow(S_indice,2) ;
       stock.push_back(S_indice);

std::cout<<"\n CVP 1 : "<<S_indice;
}

lamda=sqrt(S_total);
std::cout<<"\n Lambda :"<<lamda ;

for(int i=0 ; i<m_sommets.size();i++)
{
    m_sommets[i]->setIndice_vecteurP(stock[i]/lamda);
    std::cout<<"\n CVP 2 : "<< m_sommets[i]->getIndice_vecteurP();

}

std::cout<<"\n";
}
