#ifndef NODE_HH_
# define NODE_HH_

# include <iostream>
# include <vector>
# include <string>
# include "test.hh"
class Visitor;

namespace Sliq
{
    // Noeud d'un arbre binaire créé par Sliq
    class Node
    {
    public:
        //
        Node () {}
        // Crée le noeud en lui associant un identifiant
        Node (int id, int nb_classes);
        // Détruit le noeud
        ~Node ();
        // Indique si c'est une (vraie) feuille (retourne is_leaf_)
        bool    is_leaf () {return is_leaf_;};
        int    class_get () {return first_class_;}
        bool    has_children () {return fd_ != 0 && fg_ != 0; }
        int     nb_example();
        // Getters
        int     id_get (){return id_;}
        Node    *fg_get (){return fg_;}
        Node    *fd_get () {return fd_;}
        Test    &test_get () {return test_;}
        // Calcule le gini de l'histogramme actuel
        double  gini();
        // Maj l'histogramme, calcul le gini, et maj le test si < gini_min_
        bool    update_histogram_and_test(int attribute, int classe, int value, int next_value);
        // Crée le fils gauche et le fils droit
        virtual void    divide ();
        // Réinitialise l'histogramme avec les données de histo_init_
        int     reinit_histo (int attribute);
        // Ajoute un exemple (maj de histo_init_, first_class_, et is_leaf_)
        void    add_example(int classe);
        // Visitors
        virtual void    accept(Visitor *v);
    protected:
        // Histogramme de l'attribut en cours de traitement
        std::vector<std::pair<int, int> >   histogram_;
        int                                 current_attribute_;
        // Données d'initialisation de l'histogramme
        std::vector<int>                    histo_init_;
        // Fils gauche et droit
        Node                                *fg_;
        Node                                *fd_;
        // Identifiant
        int                                 id_;
        // Test du noeud
        Test                                test_;
        double                              gini_min_;
        // Est-ce une vraie feuille
        bool                                is_leaf_;
        int                                 first_class_;
    };
}

std::ostream    &operator<<(std::ostream &os, Sliq::Node &node);

#endif
