#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <allegro.h>
#include <stdio.h>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>


float nbtopluscourtchemin(int sum_1, int sum_2,int taille,float matrice[10][10],int p);
struct indice
{
    float degre_non_normamise,degre_nomralise;
    float intermediaire_non_normamise,intermediaire_nomralise;

};


class Sommet
{

private :

    int m_num;
    int m_x,m_y;
    indice m_indice; ///Struct stockant les indices
    std::string m_nom;

    std::map<const Sommet*,int> m_successeurs; ///chaque sommet possède la liste de ses successeurs (un vecteur de pointeurs sur Sommet)
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

    int getColor()
    {

        return m_couleur;

    }


    float getIndice(int choix)
    {
        switch(choix)
        {
        case 1 :
            return m_indice.degre_nomralise;

        case 2 :
            return m_indice.degre_non_normamise;


        }

    }


    void setColor(int couleur)
    {
        m_couleur=couleur;

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



    void Dessiner(BITMAP* bmp)
    {
        const char *nom = m_nom.c_str();

        circlefill(bmp,m_x*100,m_y*100,30,makecol(m_couleur,0,0)); ///Cercle pour la visu des indices
        circlefill(bmp,m_x*100,m_y*100,3,makecol(0,0,0));

        textprintf_ex(bmp,font,m_x*100,m_y*100-15,makecol(0,0,0),-1,nom);

        for (auto s : m_successeurs) ///Dessin des Arcs
        {
            line(bmp,m_x*100,m_y*100,s.first->getX()*100,s.first->getY()*100,makecol(255,0,0));

        }

    }


    void sauvgarderindice() const
    {

        std::fstream ofs("indice.txt");
        ofs.seekp(0,std::ios::end);


        ofs << m_num <<" "<<m_indice.degre_nomralise<<" "<<m_indice.degre_non_normamise <<" " ;

        ofs << m_num <<" "<<m_indice.intermediaire_nomralise<<" "<<m_indice.intermediaire_non_normamise << std::endl ;

        ofs.close();
    }

///Proto

    void indice_degre(float ordre);
    void  affi_degre_sommmet() const  ;
    void indice_centralite(float ordre,float indicenn);

};



class Graphe
{

private :

    ///liste des sommets (vecteur de pointeurs sur Sommet)
    std::vector<Sommet*> m_sommets;
    int m_orientation;


public :

    Graphe() {}; // Constructeur

    Graphe(std::string fichier_topo,std::string fichier_ponde) //Constructeur a partir de fichier
    {

        std::ifstream ifs{fichier_topo}; ///Ouverture des flux
        std::ifstream ifp{fichier_ponde};

        if (!ifs)
            throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier_topo );

        ifs >> m_orientation;

        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture orientation du graphe");

        int ordre;
        ifs >> ordre;

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

        ///Partie Initialisation




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



    void Dessiner()
    {

        set_color_depth(desktop_color_depth()); /// Setup allegro
        BITMAP* page ;
        install_keyboard();

        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0)!=0)
        {
            allegro_message("prb gfx mode");
            allegro_exit();
            exit(EXIT_FAILURE);
        }


        page=create_bitmap(SCREEN_W,SCREEN_H);
        clear_to_color(page,makecol(255,255,255));


        for (auto s : m_sommets)
        {
            s->Dessiner(page);

        }

        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);


        ///Proto des methodes


    }

    void sauvgarder() const
    {
        std::ofstream ofs{"indice.txt"};
        for (auto s : m_sommets)
        {
            s->sauvgarderindice();

        }

        std::cout<<"\n ----Sauvgarde reussi----"<<std::endl;

    }

    void calcul_indice_degres() ;


std::vector<int> Dijkstra(int num_s0)const;
void centraliteintermediarite()const;

    void Visualisation_indice(int i);
    void affi_indice_Tdegre() const ;

};

///Proto
Graphe* menu(Graphe* A);

Graphe* Chargement_Graphe();



#endif // HEADER_H_INCLUDED
