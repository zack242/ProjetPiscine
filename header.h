#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <allegro.h>
#include <stdio.h>
#include <algorithm>


struct indice
{
    float degre_non_normamise,degre_nomralise;
};


class Sommet
{

private :
    int m_num;
    std::string m_nom;
    int m_x,m_y;
    indice m_indice;
    ///chaque sommet possède la liste de ses successeurs (un vecteur de pointeurs sur Sommet)
    std::map<const Sommet*,int> m_successeurs;
    int  m_couleur;

public :
    /*constructeur*/
    Sommet(int num,std::string nom,int x,int y,indice a):m_num{num},m_nom{nom},m_x{x},m_y{y},m_indice{a}
    {
        m_couleur=0;

    };

    /*accesseurs*/
    int getNum()const
    {
        return m_num;
    }
    int getX()const
    {
        return m_x;
    }

    int getY()const
    {
        return m_y;
    }

    void setColor(int couleur)
    {

        m_couleur=couleur;


    }

    int getColor()
    {

        return m_couleur;

    }

    float getIndice()
    {
        return m_indice.degre_non_normamise;
    }

    ///accesseur : pour la liste des successeurs
    const std::map<const Sommet*,int>& getSuccesseurs()const
    {
        return m_successeurs;
    }

    /* pour ajouter un successeur à la liste*/
    void ajouterSucc(const Sommet*s,int poids)
    {
        m_successeurs[s]=poids;
    }


    /* méthode d'affichage*/
    void afficher() const
    {
        std::cout<<"     sommet "<<m_nom<<"-"<<m_num<<" Coords : "<<m_x<<" ; "<<m_y<<" : ";
        for (auto s : m_successeurs)
            std::cout<<s.first->getNum()<<" ";
    }
    void afficherindicedegre() const
    {
        std::cout<<" sommet : "<<m_nom<< std::endl;
        std::cout<<"indice de degre normalise : "<<m_indice.degre_nomralise<<" , \n"<<"indice de degre nonnormalise : "<<m_indice.degre_non_normamise<<" .";

    }

    void indice_degre(float ordre);


    void Dessiner(BITMAP* bmp,int couleur)
    {

        const char *nom = m_nom.c_str();
        circlefill(bmp,m_x*100,m_y*100,30,makecol(m_couleur,0,0));
        circlefill(bmp,m_x*100,m_y*100,3,makecol(255,255,255));

        textprintf_ex(bmp,font,m_x*100,m_y*100-15,makecol(0,0,0),-1,nom);

        for (auto s : m_successeurs)
        {
            line(bmp,m_x*100,m_y*100,s.first->getX()*100,s.first->getY()*100,makecol(255,0,0));

        }


    }


};



class Graphe
{



private :

    ///liste des sommets (vecteur de pointeurs sur Sommet)
    std::vector<Sommet*> m_sommets;
    int m_orientation;

public :
    /* La construction du réseau peut se faire à partir d'un fichier
     dont le nom est passé en paramètre
    */
    Graphe() {};


    Graphe(std::string fichier_topo,std::string fichier_ponde )
    {

        std::ifstream ifs{fichier_topo};
        std::ifstream ifp{fichier_ponde};

        if (!ifs)
            throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier_topo );

        ifs >> m_orientation;

        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture orientation du graphe");

        int ordre;
        ifs >> ordre;
        std::cout<<ordre;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture ordre du graphe");

        for(int i=0; i<ordre; i++)
        {

            int index;
            ifs >> index;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture de l'index du sommet");

            std::string nom ;
            ifs >> nom ;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture du nom du sommet");

            int x,y;
            ifs >> x>>y;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture des coords du sommet");

            indice temp;
            temp.degre_non_normamise=0;
            temp.degre_nomralise=0;
            m_sommets.push_back( new Sommet{index,nom,x,y,temp});


        }

        int taille;
        ifs >> taille;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture taille du graphe");

        int num1,num2,index,poids;

        for (int i=0; i<taille; ++i)
        {
            ifs>>index>>num1>>num2;
            ifp>>poids;

            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture arc");


            m_sommets[num1]->ajouterSucc(m_sommets[num2],poids);
            ///si le graphe n'est pas orienté
            ///si num2 est successeur de num1, num1 est successeur de num2
            if(!m_orientation)
                m_sommets[num2]->ajouterSucc(m_sommets[num1],poids);


        }

    }

    void Dessinerindice()
    {
        calcul_indice_degres();
        std::vector<float> valeurindice;

        for( auto s : m_sommets)
            valeurindice.push_back(s->getIndice());

        std::sort(valeurindice.begin(),valeurindice.end());




        for(auto k : m_sommets)
        {

            // std::cout<<"Indice :"<<valeurindice[i]<<std::endl;
            for(int i =0 ; i<valeurindice.size(); i++)
            {
                if(valeurindice[i]==k->getIndice())
                {

                    if(k->getColor()==0)
                    {
                        std::cout<<k->getColor();
                        k->setColor(255-20*i);
                        std::cout<<255-5*i<<"----"<<k->getColor()<<std::endl;

                    }
                }


            }


        }

    }



    /*destructeur*/
    ~Graphe()
    {
        for (auto s : m_sommets)
            delete s;
    }

    /*méthode d'affichage*/
    void afficher() const
    {

        std::cout<<std::endl<<"graphe ";
        if(m_orientation)
            std::cout<<"oriente"<<std::endl<<"  ";
        else
            std::cout<<"non oriente"<<std::endl<<"  ";
        std::cout<<"ordre = "<<m_sommets.size()<<std::endl<<"  ";
        std::cout<<"listes d'adjacence :"<<std::endl;
        for (auto s : m_sommets)
        {
            s->afficher();
            std::cout<<std::endl;
        }
    }

    void afficherindicedegre() const
    {
        for (auto s : m_sommets)
        {
            s->afficherindicedegre();
            std::cout<<std::endl;
        }

    }
    void Dessiner()
    {

        BITMAP* page ;
        int i=0;
        page=create_bitmap(SCREEN_W,SCREEN_H);
        clear_to_color(page,makecol(255,255,255));

        for (auto s : m_sommets)
        {
            s->Dessiner(page, i);

        }

        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);


    }

    void calcul_indice_degres() ;



};

///Proto
Graphe* menu(Graphe* A);

Graphe* Chargement_Graphe();



#endif // HEADER_H_INCLUDED
