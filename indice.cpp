#include <iostream>
#include "header.h"

//////////////////////////////////////////////// Indice de degre

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



//////////////////////////////////////////////////////////////////// Indice Vecteur propre


void Graphe::calcul_vecteur_propre()
{


    float S_indice=0;
    float S_total=0;
    float lamda=0;
    float lamdatemp=0;
    std::vector<float> stock((int)m_sommets.size(),0);

    int j=0;
    int k=0;

    calcul_indice_degres();
    do
    {

          lamdatemp=lamda;

        k=0;
        S_total=0;
        for (auto s : m_sommets)
        {
            S_indice=0;
            for(auto succ : s->getSuccesseurs())
            {
                S_indice+=succ.first->getIndice(2);

            }
            stock[k]=S_indice;

            S_total+=pow(S_indice,2);
            k++;

        }

        lamda=sqrt(S_total);

        int i=0;

        for(auto s : m_sommets)
        {

            s->setIndice_vecteur(stock[i]/lamda);
            i++;

        }


    }while(lamda != lamdatemp);

}


void Sommet::affi_indice_vecteur() const
{
    std::cout<<"Sommet : "<<m_nom<< std::endl;
    std::cout<<"Indice  : "<<m_indice.vecteur<<"\n" ;

}

void Graphe::affi_indice_Tvecteur() const
{
    for (auto s : m_sommets)
    {
        s->affi_indice_vecteur();
        std::cout<<std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////



std::vector<int> Graphe::AlegoDjiskra(int num_D) // Alego de Djiskra
    {

        //tableau pour le marquage ;
        std::vector<int> marquage((int)m_sommets.size(),0);
        //tableau des distances
        std::vector<int> distance((int)m_sommets.size(),999);
        //tableau des preds
        std::vector<int> preds((int)m_sommets.size(),-1);


        int num_F=5;
        bool M = false; //booleen pour savoir si tout les sommets sont marquees
        int temp=999; // Utiliser pour determiner le min
        int index=0;
        float total=0;

        distance[num_D]=0; //Initialisation de la distance du Sommet 0 a 0
        const Sommet* k;



        for(auto z : m_sommets) //On met a jour les distances des adjacents
        {
            if(z->getNum()==num_D)
            {
                for(auto succ : z->getSuccesseurs())
                {
                    distance[succ.first->getNum()]=succ.second;
                }
                marquage[num_D]=1; // On  marque le sommet s0

            }

        }


        do
        {
            M=false;

            for(int i=0 ; i<distance.size(); i++) // On cherche le sommets avec la plus petite distance
            {
                if(marquage[i]==0 && i!=num_D)
                {

                    if(distance[i]<=temp)
                    {
                        temp=distance[i];
                        index=i;

                    }

                    M=true;

                }

            }

            for(auto s : m_sommets)
                if(s->getNum()==index) //On recherche le pointeur Sommet¨* le plus proche de s0
                    k=s;

            if(M==true)
                distance[index]=temp;

            marquage[index]=1;



            for(auto X : k->getSuccesseurs())
            {

                if(marquage[X.first->getNum()]==0)
                {

                    if(distance[k->getNum()]+X.second<distance[X.first->getNum()]) //Si le chemin est plus court on le met a jour
                    {
                        distance[X.first->getNum()]=distance[k->getNum()]+X.second;
                        // std::cout<<k->getNum()<<"-->"<<X.first->getNum()<<std::endl;
                       //  preds[k->getNum()]=X.first->getNum();

                    }

                }


            }

            temp=999;



        }
        while(M==true); // tant que tout les sommets ne sont pas marque
        int i=0;
         for(auto s :m_sommets)
            {
         //     std::cout<<"Distance "<<s->getNom()<<": "<<distance[i]<<"\n";
              total+=distance[i];
              i++;
         }

   // distance_min=distance[num_F]; // On affect la distance min

return distance;

}



void Graphe::calcul_indice_proximite()
{
float temp;
std::vector<int> preds;

for(auto s : m_sommets)
{
    temp=0;
    preds=AlegoDjiskra(s->getNum());

       for(int i=0 ; i<preds.size();i++)
        {
        temp+=preds[i];
      //  std::cout<<"\n temp "<<temp<<"preds "<<preds[i];
        }

       s->setIndice_proximite((m_taille-1)/temp);

}

}


void Sommet::affi_indice_proximite() const
{
    std::cout<<"Sommet : "<<m_nom<< std::endl;
    std::cout<<"Indice  : "<<m_indice.proximite<<"\n" ;

}

void Graphe::affi_indice_Tproximite() const
{
    for (auto s : m_sommets)
    {
        s->affi_indice_proximite();
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


