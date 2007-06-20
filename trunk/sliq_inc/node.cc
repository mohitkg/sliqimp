#include "node.hh"
#include "../visitor/print_visitor.hh"

namespace Incremental_sliq
{


    Node::Node (int id, int nb_classes)
    {
        std::cout << "Création de noeud INCREMENTAUX\n";
        fg_ = 0;
        fd_ = 0;
        id_ = id;
        is_leaf_ = true;
        gini_min_ = 1;
        first_class_ = -1;
        current_attribute_ = -1;
        for (int i = 0; i <= nb_classes; ++i)
        {
            histo_init_.push_back(0);
            nb_error_per_class_.push_back(0);
        }
    }

    void    Node::divide ()
    {
        fg_ = new Node(id_ * 2, histo_init_.size ());
        fd_ = new Node(id_ * 2 + 1, histo_init_.size ());
    }

    void    Node::accept(Visitor *v)
    {
        v->visit(this);
    }

    std::ostream    &operator<<(std::ostream &os, Incremental_sliq::Node &node)
    {
        std::cout << "bonjour\n";
    }
}
