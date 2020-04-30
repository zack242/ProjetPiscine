#include <iostream>
#include "header.h"


float nbtopluscourtchemin(int sum_1, int sum_2,int taille,float matrice[100][100],int p)
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
    int Parents [NbNodes][NbNodes];//pour chaque sommets on definie son parents a -1 qui corspondt a aucun parents

    for (int i = 0; i < NbNodes; i++)
    {
        for (int j = 0; j < NbNodes; j++)
        {
            Parents[i][j] = -1;

        }
    }
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
                    Parents[v2][0] = v;//on change le predessesseur
                    for (int i=1; i<NbNodes; ++i)
                    {
                        Parents[v2][i] = -1;//on change le predessesseur
                    }
                    file.push({m_sommets[v2],Distances[v2]});//on push le sommet et la ditance dans notre file
                }
                else if (Distances[v] + w2 == Distances[v2])
                {
                    int dep=0;
                    while(Parents[v2][dep] != -1)
                    {
                        ++dep;
                    }
                    Parents[v2][dep] = v;
                }

            }
        }
    }
    /*for (auto i = 0; i<NbNodes; ++i)                                            // résultat
    {
        if(i !=num_s0 )
        {
            int pbis[NbNodes];
            for(int j=0; j<NbNodes; ++j)
            {
                pbis[j]=-1;
            }
            std::cout << "\nnoeud  " << num_s0 << " au noeud " << i << " longueur :  " << Distances[i] << std::endl;
            int k=1;
            while(Parents[i][k]!= -1)
            {
                pbis[k-1]=Parents[i][k];
                ++k;
            }
            std::cout << i;
            for (auto p = Parents[i][0]; p != -1; p = Parents[p][0])
            {
                std::cout << " <- " << p;
                if(pbis[0]!=-1)
                {
                    k=0;
                    while (pbis[k]!= -1)
                    {
                        std::cout << " ( " << pbis[k]<<")";
                        pbis[k]=-1;
                        ++k;
                    }
                }
                int l=1;
                while (Parents[p][l]!= -1)
                {
                    //std::cout<<"test"<<std::endl;
                    std::cout << " ( " << Parents[p][1]<<")";
                    ++l;
                }
            }

            std::cout << std::endl;
        }
    }*/

    int taille=0;
    int chemin_t[NbNodes] ;
    float matrice[100][100];
    for (int i = 0; i < NbNodes; i++)
    {
        chemin_t[i]=0;
        for (int j = 0; j < NbNodes; j++)
        {
            matrice[i][j] = 0;
        }
    }
    for (int i = 0; i < NbNodes; i++)
    {
        int j=0;
        while (Parents[i][j] != -1)
        {
            matrice[i][Parents[i][j]]=1;
            ++j;
            ++taille;
        }

    }
    for (int j = 0; j < NbNodes; j++)
    {
        if(j !=num_s0 )
        {
            for (int i = 0; i < taille; i++)
            {
            chemin_t[j]=chemin_t[j]+nbtopluscourtchemin(j,num_s0,taille,matrice,i);
            }
        }

    }


    std::cout<<"sommet "<<num_s0<<" taille "<<taille<<" : "<< std::endl;
    for (int i = 0; i < NbNodes; i++)
    {
        for (int j = 0; j < NbNodes; j++)
        {
            std::cout<<matrice[i][j]<<" ";
        }
         std::cout << std::endl;
    }
    for (auto i = 0; i != NbNodes; ++i)                                            // résultat
    {
        if(i !=num_s0 )
        {
            std::cout << "\nnoeud  " << num_s0 << " au noeud " << i << " longueur :  " << Distances[i]<< " nombre_chemin  " << chemin_t[i]<< std::endl;

            std::cout << i;
            for (auto p = Parents[i][0]; p != -1; p = Parents[p][0])
                std::cout << " <- " << p;
            std::cout << std::endl;
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
    float matrice[100][100];
    float matricedist[100][100];
    float indice_nn=0;
    std::vector<float> tempindice;
    std::map<const Sommet*,int> suceur;
    int nbtotal=0;
    //on inisialise les matrice
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
            matrice[s][r.first->getNum()]=r.second;
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
    /*
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            std::cout<<matricedist[i][j]<<" ";
        }
        std::cout<<std::endl;
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
                         std::cout<<"id:"<<i<<" , "<<j<<" , "<<k<<" :"<< matricedist[j][i]<<" + "<<matricedist[i][k]<<" = "<<matricedist[j][k]<<std::endl;
                        std::cout<<"temp: "<<temp<<" "<<indice_nn<<"test2 "<<i<<" : "<<temp<<" : "<<tempji<<" : "<<tempik<<" : "<<tempjk<<std::endl;

                    }
                }


            }


        }
        tempindice.push_back(indice_nn);
        indice_nn=0;
    }
    for(int i=0; i<taille; ++i)
    {
        std::cout<<"sommet " << i << " indice: "<<tempindice[i]<<std::endl;
    }
    for(int i=0; i<taille; ++i)
        m_sommets[i]->indice_centralite(taille,tempindice[i]); //On envoie l'ordre du graphe -1
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


    }
    while(lamda != lamdatemp);

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



float Graphe::AlegoDjiskra(int num_D) // Alego de Djiskra
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

    return total;

}




void Graphe::calcul_indice_proximite()
{
    float temp;
    for(auto s : m_sommets)
    {
        s->setIndice_proximite((m_taille-1)/AlegoDjiskra(s->getNum()));
        std::cout<<"\n Sommet "<<s->getNom()<<"Indice : "<<s->getIndice(3);
        //temp=(m_taille-1)/(AlegoDjiskra(s->getNum()));

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


