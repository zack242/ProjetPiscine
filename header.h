#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <allegro.h>
#include <stdio.h>
#include <algorithm>
#include <string>



struct indice
{
    float degre_non_normamise,degre_nomralise;
    float vecteur;
    float proximite;
};


class Sommet
{

private :
    std::string m_nom;
    int m_num;
    int m_x,m_y;
    indice m_indice; ///Struct stockant les indices


    std::map<const Sommet*,int> m_successeurs; ///chaque sommet poss�de la liste de ses successeurs (un vecteur de pointeurs sur Sommet)
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

    std::string getNom()const
    {
        return m_nom;
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


    float getIndice(int choix) const
    {
        switch(choix)
        {
        case 1 :
            return m_indice.degre_nomralise;

        case 2 :
            return m_indice.vecteur;

        case 3 :
            return m_indice.proximite;




        }

    }


    void setColor(int couleur)
    {
        m_couleur=couleur;

    }

    void setIndice_vecteur(float indice)
    {

        m_indice.vecteur=indice;

    }

    void setIndice_proximite(float indice)
    {

        m_indice.proximite=indice;

    }

    void setsucc(std::map<const Sommet*,int> succ)
    {

        m_successeurs=succ;

    }


    ///accesseur : pour la liste des successeurs
    const std::map<const Sommet*,int>& getSuccesseurs()const
    {
        return m_successeurs;
    }

    /* pour ajouter un successeur � la liste*/
    void ajouterSucc(const Sommet*s,int poids)
    {
        m_successeurs[s]=poids;
    }


    /* m�thode d'affichage*/
    void afficher() const
    {
        std::cout<<"     sommet "<<m_nom<<"-"<<m_num<<" Coords : "<<m_x<<" ; "<<m_y<<" : ";
        for (auto s : m_successeurs)
            std::cout<<s.first->getNum()<<" ("<<s.second<<") ";
    }



    void Dessiner(BITMAP* bmp)
    {
        const char *nom = m_nom.c_str();

        textprintf_ex(bmp,font,m_x*10,m_y*10-30,makecol(0,0,0),-1,nom);


        for (auto s : m_successeurs) ///Dessin des Arcs
        {
            line(bmp,m_x*10,m_y*10,s.first->getX()*10,s.first->getY()*10,makecol(255,0,0));

        }

        circlefill(bmp,m_x*10,m_y*10,10,makecol(m_couleur,0,0)); ///Cercle pour la visu des indices

        circlefill(bmp,m_x*10,m_y*10,3,makecol(0,0,0));

    }


    void sauvgarderindice(std::ofstream &ofs,int choix) const
    {

        switch(choix)
        {

        case 1 :
            ofs << m_num <<" "<<m_indice.degre_nomralise<<" "<<m_indice.degre_non_normamise << std::endl ;
            break;

        case 2 :
            ofs << m_num <<" "<<m_indice.vecteur <<std::endl ;
            break;

        case 3 :
            ofs << m_num <<" "<<m_indice.proximite <<std::endl ;
            break;




        }
    }

///Proto

    void indice_degre(float ordre);
    void  affi_degre_sommmet() const  ;

    void Calcul_indice_adjac() ;
    void affi_indice_vecteur() const;

    void affi_indice_proximite() const;


};



class Graphe
{

private :

    ///liste des sommets (vecteur de pointeurs sur Sommet)
    std::vector<Sommet*> m_sommets;
    std::vector<std::pair<int,int>> m_arrets;
    int m_orientation;
    int m_taille;

    std::string nomFichier;


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
            temp.vecteur=1;
            m_sommets.push_back( new Sommet{index,nom,x,y,temp});

        }

        int taille_topo;
        int taille_pondo;

        ifs >> taille_topo;
        ifp >> taille_pondo;

        if(taille_pondo!=taille_topo)
        {
            std::cout<<"Erreur  taille  ";
            exit(0);

        }
        m_taille=taille_topo;

        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture taille du graphe");

        int num1,num2,index,poids;

        std::vector<std::pair<int,int>> arrets(m_taille);

        for (int i=0; i<taille_topo; ++i)
        {
            ifs>>index>>num1>>num2;
            ifp>>index>>poids;

            arrets[i].first=num1;
            arrets[i].second=num2;

            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture arc");

            m_sommets[num1]->ajouterSucc(m_sommets[num2],poids);
            ///si le graphe n'est pas orient�
            ///si num2 est successeur de num1, num1 est successeur de num2
            if(!m_orientation)
                m_sommets[num2]->ajouterSucc(m_sommets[num1],poids);

        }

          m_arrets=arrets;


        ///Partie Initialisation




    }



    /*destructeur*/
    ~Graphe()
    {
        for (auto s : m_sommets)
            delete s;
    }

    /*m�thode d'affichage*/
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

    void sauvgarder(int choix) const
    {

        std::string nomFichier;

        switch (choix) ///Automatisation de la sauvgarde
        {
        case 1 :
            nomFichier="indice_degre.txt";
            break ;

        case 2 :
            nomFichier="indice_vecteur.txt";
            break ;

        case 3 :
            nomFichier="indice_proximite.txt";
            break ;

        case 4 :
            nomFichier="indice_intermediaire.txt";
            break ;
        }

        std::ofstream ofs{nomFichier};

        for (auto s : m_sommets)
        {
            s->sauvgarderindice(ofs,choix);

        }

        std::cout<<"\n ----Sauvgarde reussi dans "<<nomFichier<<" ----"<<std::endl;

    }

    void setnomFichier(std::string fichier)
    {

        nomFichier=fichier;

    }



    std::string getFichier()
    {
        return nomFichier;
    }


    void calcul_indice_degres() ;
    void Visualisation_indice(int i);
    void affi_indice_Tdegre() const ;
    void calcul_vecteur_propre() ;
    void DFS(int num_S,std::vector<int> couleurs);
    void affi_indice_Tvecteur() const;
    std::vector<int> AlegoDjiskra(int num_D);
    void calcul_indice_proximite();
    void affi_indice_Tproximite() const;
    void GrapheConnexe();
    void TestVulnerabilite() ;
};

///Proto
Graphe* menu(Graphe* A);

Graphe* Chargement_Graphe(std::string fichier_topo,std::string fichier_pondo);



#endif // HEADER_H_INCLUDED
