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


       // std::cout<<"ououou "<< s->getNum() << " - "<<m_arrets[t_indice.back()].first<<std::endl;

        if( s->getNum() == m_arrets[t_indice.back()].first  )
        {

            succes=s->getSuccesseurs();

            for(auto succ : succes)
            {
                std::cout<<m_arrets[t_indice.back()].first<<"oooo "<< succ.first->getNum() <<"\n";

                if (succ.first->getNum()== m_arrets[t_indice.back()].second)
                {
                    std::cout<<"ppppppppppppppppppp";
                    succes.erase(succ);

                    t_indice.pop_back();
                }


            }

        }

    }





}

