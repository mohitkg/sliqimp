#ifndef ENGINE_HH
# define ENGINE_HH

# include <iostream>
# include <string>
# include <vector>
# include "node.hh"
# include "attribute.hh"

namespace Sliq
{
    // Contient les données, les fonctions d'inialisation
    // et les fonctions de lancement de construction de l'arbre
    class Engine
    {
    public:
        // Constructeur
        Engine () {};
        Engine (std::string config_filename, std::vector<std::vector<int> > *examples);
        virtual Node    *init_node(int id, int nb_classes);
        // Charge les exemples d'un fichier
        std::vector<std::vector<int> >    &load_examples(std::string &filename);

        // Crée les listes d'attributs à partir d'une ensemble d'exemples
        // ne sert à rien également je pense
        // bool    compute_attribute_lists (std::vector<Example> examples);
        // Construit l'arbre de racine tree
        bool    compute_sliq ();
        Node    *tree_get () {return tree_;}
        // Met à jour les histogrammes de toutes les feuilles temporaires
        // pour l'attribut passé en paramètre
        // Les meilleurs tests sont conservés au fur et à mesure
        void   Engine::update_histograms (int attribut);
        // Retourne le numéro de la classe de l'exemple ex
        int    classify(std::vector<int> ex);

    protected:
        // liste de tous les noeuds de l'arbre
        // sert à rien finalement
        // std::map<int, Node*>                nodes;
        // Class list
        // Associe à chaque index d'exemple (l'indice) l'index d'une classe
        // et un noeud (son indice dans la map)
        std::vector<std::pair<int, Node*> > class_list_;
        // Liste des attributs (associe un nom à chaque numéro d'attribut)
        std::vector<std::string>            attribute_names_;
        // Liste des classes (associe un nom à chaque numéro de classe)
        std::vector<std::string>            classes_names_;
        // Liste des attribute_list (associé au numéro d'attribut)
        std::vector<Attribute::List>        attribute_lists_;
        // Racine de l'arbre créé à partir des exemples
        Node                                *tree_;
    };
}

std::ostream    &operator<<(std::ostream &os, Sliq::Engine &engine);

#endif
