#include <iostream>
#include "header.h"

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
void Graphe::Dijkstra(int num_s0, int num_sf)const
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
    for (auto i = 0; i != NbNodes; ++i)                                            // résultat
    {
        if(i !=num_s0 )
        {
            std::cout << "\nnoeud  " << num_s0 << " au noeud " << i << " longueur :  " << Distances[i] << std::endl;

            std::cout << i;
            for (auto p = Parents[i]; p != -1; p = Parents[p])
                std::cout << " <- " << p;
            std::cout << std::endl;
        }
    }

/*
//on affiche uniquement le sommet finale demander
    std::cout << "\n noeud " << num_s0 << " a noeud " << num_sf << " longueur :  " << Distances[num_sf] << std::endl;
    std::cout << num_sf;
    std::vector<int> sommelon;
    int precedent=num_sf;
    std::pair<const Sommet*,double> i;
    std::map<const Sommet*,int> temp;
    for (int p = Parents[num_sf]; p != -1; p = Parents[p])
    {
        std::cout << " <-- " << p;
        temp=m_sommets[p]->getSuccesseurs();//on récupaire le détail de la somme des distances
        for (auto s : temp)
        {
            if(s.first->getNum()==precedent)
            {
                sommelon.push_back(s.second);
            }
        }
        precedent=p;
    }
    std::cout << " : longueur  " << sommelon[0] ;//on affiche le détail de la somme
    sommelon.erase (sommelon.begin()+0);
    for(auto s : sommelon)
    {
        std::cout <<" + "  <<s ;
    }
    std::cout << " = "<< Distances[num_sf] ;
    std::cout << std::endl;
*/
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


