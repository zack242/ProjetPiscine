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

}





