#ifndef ATTRIBUTE_HH
# define ATTRIBUTE_HH

# include <vector>
# include "node.hh"

namespace Sliq
{
    class   Node;

    namespace Attribute
    {

        class Choice
        {
        public:
            Choice (Choice &att, int before_after);
            int min_get ();
            int max_get ();
            int number_get ();
        private:
            int min_;
            int max_;
            int number_;
        };

        // Liste d'attributs
        // Liste ordonnée des valeurs d'un attribut (seulement des entiers)
        // Créé avant le lancement de la construction de l'arbre
        class List
        {
        public:
            List (int attribute);
            std::vector<std::pair<int, int> >   &values_indexes_get ();
            int                 num_get ();
            // tri par insertion
            int                 insert(int value, int index);
            void                check_best_test (int attribute, std::vector<std::pair<int, Node*> > &class_list);
            void                execute_cut (int attribute, std::vector<std::pair<int, Node*> > &class_list);
        private:
            std::vector<std::pair<int, int> >    values_indexes_;
            int                 num_;
        };
    }
}

#endif

