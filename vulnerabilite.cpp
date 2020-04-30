#include <iostream>
#include "header.h"

void Graphe::GrapheConnexe()
{

    std::vector<int> distance;
    std::vector<int> couleur((int)m_sommets.size(),0);
    std::vector<std::vector<int>> CC;
    int NonSommet=0;
    int k=0;
    bool check=true ;

    while(check!=false)
    {
        std::cout<<"Composant Connexe : ";
        check=false;
        distance=AlegoDjiskra(NonSommet);

        for(int i=0; i<distance.size(); i++)
        {

            if(distance[i]==999 && couleur[i]==0)
            {
                NonSommet=i;
                check=true;
            }
            else if(couleur[i]==0)
            {
                std::cout<<" "<<m_sommets[i]->getNom();
                couleur[i]=1;

            }

        }
        k++;
        std::cout<<"\n";

    }

    if(k==1)
        std::cout<<"\n Le Graphe est Connexe \n";
    else
        std::cout<<"\n Le Graphe n'est pas Connexe \n";


}



Graphe* Graphe::Sup_aretes()
{
//Calculer des indices avant suppression graphe
calcul_indice_degres();
calcul_indice_proximite();
calcul_vecteur_propre();



    std::vector<int> t_indice;
    std::map<const Sommet*,int> succes;



    std::cout<<"Arrets : \n";

    for(int i =0 ; i<m_arrets.size() ; i++)
        std::cout<<"Indice : "<<i<<" : "<<m_arrets[i].first<<"-"<<m_arrets[i].second<<std::endl;

    int indice;



        std::cout<<"\n99 / Pour quitter la saisie \n ";
        std::cout<<"Saisir l'indice des aretes a supprimer \n";
         while(indice!=99)
    {
        std::cout<<"Indice : ";

        std::cin>>indice;
        t_indice.push_back(indice);

    }


    t_indice.pop_back();



    for(auto s : m_sommets)
    {
        std::map<const Sommet*,int> temp;
        for(int z=0; z < t_indice.size(); z++)
        {
            if(s->getNum()== m_arrets[t_indice[z]].first )
            {
                for( auto succ : s->getSuccesseurs() )
                {
                    if (succ.first->getNum() != m_arrets[t_indice[z]].second)
                        temp[succ.first]=succ.second;
                }

                s->setsucc(temp);
            }

            std::map<const Sommet*,int> temp2;
            if(s->getNum()== m_arrets[t_indice[z]].second )
            {
                for( auto succ : s->getSuccesseurs() )
                {
                    if (succ.first->getNum() != m_arrets[t_indice[z]].first)
                        temp2[succ.first]=succ.second;
                }

                s->setsucc(temp2);
            }


        }

    }

}


void Graphe::ComparaisonIndice()
{
std::cout<<"\n \nComparaison entre les deux graphes \n";
int i=0;
float temp,temp2;

std::vector<float> vecteur_propre;
std::vector<float> indice_proximite;
std::vector<float> indice_intermedaire;
std::vector<float> indice_degresN;
std::vector<float> indice_degresNN;


for(auto k : m_sommets)
    {

    vecteur_propre.push_back(k->getIndice(2));
    indice_proximite.push_back(k->getIndice(3));
    indice_degresNN.push_back(k->getIndice(0));
    indice_degresN.push_back(k->getIndice(1));


    }

calcul_indice_degres();
calcul_indice_proximite();
calcul_vecteur_propre();

for(auto s : m_sommets)
{
    std::cout<<"\nSommet   "<<s->getNom()<<std::endl;

     std::cout<<"Indice degres normalise :     ";
     std::cout<<indice_degresN[i]<<" - "<<s->getIndice(1)<<" = "<<indice_degresN[i]-s->getIndice(1)<<std::endl;
     std::cout<<"Indice degres non normalise : ";
     std::cout<<indice_degresNN[i]<<" - "<<s->getIndice(0)<<" = "<<indice_degresN[i]-s->getIndice(0)<<std::endl;
     std::cout<<"Indice vecteur :              ";
     std::cout<<vecteur_propre[i]<<" - "<<s->getIndice(2)<<" = "<<vecteur_propre[i]-s->getIndice(2)<<std::endl;
     std::cout<<"Indice proximite :            ";
     std::cout<<indice_proximite[i]<<" - "<<s->getIndice(3)<<" = "<<indice_proximite[i]-s->getIndice(3)<<std::endl;
     std::cout<<"Indice intermediare :         ";
   //  std::cout<<indice_intermedaire[i]<<" - "<<s->getIndice(4)<<" = "<<indice_intermedaire[i]-s->getIndice(4)<<std::endl;

     std::cout<<"\n";
i++;
}


}





