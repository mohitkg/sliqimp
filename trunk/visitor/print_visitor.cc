#include "print_visitor.hh"
#include "../sliq/node.hh"

void    Print_visitor::visit (Sliq::Node *node)
{
    if (node->has_children ())
    {
        *os_ << node->id_get () << " [label=\"nb_exemple=" << node->nb_example () << "-" << node->test_get () << "\"]" << std::endl;
        *os_ << node->id_get () << " -> " << node->fg_get ()->id_get () << std::endl;
        *os_ << node->id_get () << " -> " << node->fd_get ()->id_get () << std::endl;
        *os_ << *node->fg_get ();
        *os_ << *node->fd_get ();
    }
}


void    Print_visitor::visit (Incremental_sliq::Node *node)
{
    if (node)
    {
        *os_ << node->id_get () << " [label=\"";
        if (node->is_leaf ())
            *os_ << "CLASSE : " << node->class_get() << "\\n";
        *os_ << "nb_exemple=" << node->nb_example ();
        if (!node->is_leaf ())
            *os_ << "\\n" << node->test_get ();
        *os_ << "\\n Errs=" << node->nb_error_per_class_get ()[1]
        << " : " << node->nb_error_per_class_get ()[2]
        << " : " << node->nb_error_per_class_get ()[3]
        << " : " << node->nb_error_per_class_get ()[4]
        << " : " << node->nb_error_per_class_get ()[5]
        << " : " << node->nb_error_per_class_get ()[6]
        << " : " << node->nb_error_per_class_get ()[7];
        if (!node->is_leaf ())
            *os_<< "\", " << "shape=record, sides=4, color=\"#FFFFFF\", style=filled, fillcolor=\"#AA88FF\", fontsize=7]" << std::endl;
        else
            *os_<< "\", " << "shape=polygon, sides=8, color=\"#222222\", style=filled, fillcolor=\"#FFFFFF\", fontsize=7]" << std::endl;

    }
    if (node->has_children ())
    {
        *os_ << node->id_get () << " -> " << node->fg_get ()->id_get () << std::endl;
        *os_ << node->id_get () << " -> " << node->fd_get ()->id_get () << std::endl;
        *os_ << *node->fg_get ();
        *os_ << *node->fd_get ();
    }
}
