#include <iostream>
#include "header.h"

float nbtopluscourtchemin(int sum_1, int sum_2,int taille,float matrice[10][10],int p)
{
    float ca[taille][taille],cb[taille][taille],tot;
    float nbtotal=0;

//transfert de notre matrice dans une matrice de calcul
    for(int i=0; i<taille; i++)
    {
        for(int j=0; j<taille; j++)
        {
            ca[i][j]=matrice[i][j];
        }
    }
//si la puissance demander vaut 1 on affiche juste
    if(p==1)
    {
    }
    else
    {

        for(int v=0; v<p-1; v++)
        {
            for(int i=0; i<taille; i++)
            {
                for(int j=0; j<taille; j++)
                {
                    cb[i][j]=ca[i][j];
                }
            }

            for(int i=0; i<taille; i++)
            {

                for(int j=0; j<taille; j++)
                {

                    for(int k=0; k<taille; k++)
                    {
                        tot=tot+(cb[i][k]*matrice[k][j]);
                    }

                    ca[j][i]=tot;
                    tot=0;
                }
            }

        }

    }
    nbtotal=ca[sum_1][sum_2];
    return nbtotal;
}
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


auto cmp = [](std::pair<const Sommet*,double> p1, std::pair<const
              Sommet*,double> p2)
{
    return p2.second<p1.second;
};
std::vector<int> Graphe::Dijkstra(int num_s0)const
{
    int NbNodes=m_sommets.size();
    std::vector<int> Distances(NbNodes, std::numeric_limits<int>::max());//pour chaque sommets on mets une distance infinie( std::numeric_limits<int>::max()) correspond a la valeur mas que peut contenir un int en C++
    Distances[num_s0] = 0;//la distance entre le sommets de départs et lui-meme est 0
    std::vector<int> Parents(NbNodes, -1);//pour chaque sommets on definie son parents a -1 qui corspondt a aucun parents

/// déclaration de la file de priorité
    std::priority_queue<std::pair<const Sommet*,double>,
        std::vector<std::pair<const Sommet*,double>>,decltype(cmp)> file(cmp);

    file.push({m_sommets[num_s0],0});//on mets dans le liste le sommet de commencement

    while(!file.empty())
    {
        int v = file.top().first->getNum();//on récupaire le succeur avec la plus grande priorité, on le marque(supression)
        int w = file.top().second;
        file.pop();

        if (w <= Distances[v]) // si la distance entre le succeur et sont prédécesseur est infèrieur ou égale avec la distance total
        {
            std::map<const Sommet*,int> m_successeurs; //on récupaire le vecteur contenant les succeurs
            m_successeurs=m_sommets[v]->getSuccesseurs();
            for (auto s : m_successeurs)//on parcours le vecteur des succeurs
            {
                int v2 = s.first->getNum();
                int w2 = s.second;

                if (Distances[v] + w2 < Distances[v2])//si la somme de la distance entre le parcours et le prédécésseur est infèrieur a la distance du sommet où l'on arrive
                {
                    Distances[v2] = Distances[v] + w2;//on remplace cette distance
                    Parents[v2] = v;//on change le predessesseur
                    file.push({m_sommets[v2],Distances[v2]});//on push le sommet et la ditance dans notre file
                }

            }
        }
    }

    return Distances;

}
void Sommet::indice_centralite(float ordre,float indicenn)
{
    float normalisation=0;

    normalisation=(ordre*ordre-3*ordre+2)/2;

    //std::cout<<" test : "<<indicenn/normalisation<<" nn : "<<indicenn<< std::endl;
    m_indice.intermediaire_non_normamise=indicenn;

    m_indice.intermediaire_nomralise=(indicenn/normalisation);
}
void Graphe::centraliteintermediarite()const
{

    int taille=m_sommets.size();
    float matrice[10][10];
    float matricedist[10][10];
    float indice_nn=0;
    std::vector<float> tempindice;
    std::map<const Sommet*,int> suceur;
    int nbtotal=0;
    //on inisialise la matrice
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            matrice[i][j] = 0;
            matricedist[i][j] = 0;
        }
    }

    //remplisage de la matrice d'adjacence
    for(size_t s=0; s<m_sommets.size(); ++s)
    {
        suceur=m_sommets[s]->getSuccesseurs();
        for(auto r : suceur)
        {
            matrice[s][r.first->getNum()]=1;
        }

    }

    std::vector<int> Distances(taille, 0);
    for(int i=0; i<taille; ++i)
    {
        Distances=Dijkstra(i);
        for(int j=0; j<taille; ++j)
        {
            matricedist[i][j]=Distances[j];
        }
    }


    for (int i = 0; i < taille; ++i)
    {

        for(int j=0; j<taille; ++j)
        {

            for(int k=0; k<taille; ++k)
            {
                if(i !=j && i!=k)
                {

                    if(matricedist[j][i]+matricedist[i][k]==matricedist[j][k])
                    {

                        float tempjk=0;
                        tempjk=nbtopluscourtchemin(j,k,taille,matrice,matricedist[j][k]);
                        //if(1 < tempjk){
                        float tempji,tempik;
                        tempji=nbtopluscourtchemin(j,i,taille,matrice,matricedist[j][i]);
                        tempik=nbtopluscourtchemin(i,k,taille,matrice,matricedist[i][k]);
                        tempik=tempik-1;
                        float temp=(tempji+tempik)/tempjk;
                        indice_nn=indice_nn+temp;
                        // std::cout<<"id:"<<i<<" , "<<j<<" , "<<k<<" :"<< matricedist[j][i]<<" + "<<matricedist[i][k]<<" = "<<matricedist[j][k]<<std::endl;
                        //std::cout<<"temp: "<<temp<<" "<<indice_nn<<"test2 "<<i<<" : "<<temp<<" : "<<tempji<<" : "<<tempik<<" : "<<tempjk<<std::endl;

                    }
                }


            }


        }
        tempindice.push_back(indice_nn);
        indice_nn=0;
    }
    /*for(int i=0; i<taille; ++i)
    {
        std::cout<<"sommet " << i << " indice: "<<tempindice[i]<<std::endl;
    }*/
    for(int i=0; i<taille; ++i)
        m_sommets[i]->indice_centralite(taille,tempindice[i]); //On envoie l'ordre du graphe -1
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


