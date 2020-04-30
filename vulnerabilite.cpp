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
        std::cout<<"Graphe Connexe \n";

}



void Graphe::TestVulnerabilite()
{

    std::vector<int> t_indice;
    std::map<const Sommet*,int> succes;



    std::cout<<"Arrets : \n";

    for(int i =0 ; i<m_arrets.size() ; i++)
        std::cout<<"Indice : "<<i<<" : "<<m_arrets[i].first<<"-"<<m_arrets[i].second<<std::endl;

    int indice;


    while(indice!=99)
    {
        std::cout<<"\n99 / Pour quitter la saisie \n ";
        std::cout<<"Saisir l'indice des aretes a supprimer \n";

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
