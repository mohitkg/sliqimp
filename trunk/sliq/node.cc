#include "node.hh"
#include "../visitor/print_visitor.hh"

namespace Sliq
{
    Node::Node (int id, int nb_classes)
    {
        std::cout << "Création de noeud NORMAUX\n";
        fg_ = 0;
        fd_ = 0;
        id_ = id;
        is_leaf_ = true;
        gini_min_ = 1;
        first_class_ = -1;
        current_attribute_ = -1;
        for (int i = 0; i < nb_classes; ++i)
        {
            histo_init_.push_back(0);
        }
    }

    Node::~Node ()
    {
        if (fg_)
            delete(fg_);
        if (fd_)
            delete(fd_);

    }

    double  Node::gini()
    {
        double  total_inf = histogram_[0].first;
        double  total_sup = histogram_[0].second;
        double  total = total_inf + total_sup;
        double  somme_proba_inf = 0;
        double  somme_proba_sup = 0;
        double  proba;

        if (total_inf == 0 || total_sup == 0)
            return 1;
        std::vector<std::pair<int, int> >::iterator it = histogram_.begin ();
        for (++it;
                it != histogram_.end ();
                ++it)
        {
            proba = (*it).first / total_inf;
            somme_proba_inf += proba * proba;
            proba = (*it).second / total_sup;
            somme_proba_sup += proba * proba;
        }
        return (total_inf / total ) * (1 - somme_proba_inf)
               + (total_sup / total) * (1 - somme_proba_sup);
    }

    bool        Node::update_histogram_and_test(int attribute, int classe, int value, int next_value)
    {
        double  val_gini;

        if (current_attribute_ != attribute)
            reinit_histo(attribute);
        histogram_[classe].first++;
        histogram_[classe].second--;
        histogram_[0].first++;
        histogram_[0].second--;

        if (value == next_value)
            return true;

        val_gini = gini();
        if (val_gini < gini_min_)
        {
            test_.set(value, current_attribute_);
            // std::cout << "(" << nb_example () << ")"<< val_gini << test_ << std::endl;
            gini_min_ = val_gini;
        }

    }

    void    Node::divide ()
    {
        fg_ = new Node(id_ * 2, histo_init_.size ());
        fd_ = new Node(id_ * 2 + 1, histo_init_.size ());
    }

    int     Node::reinit_histo (int attribute)
    {
        current_attribute_ = attribute;
        histogram_.clear ();
        for (std::vector<int>::iterator it = histo_init_.begin ();
                it != histo_init_.end ();
                ++it)
        {
            histogram_.push_back(std::pair<int, int> (0, *it));
        }
    }

    void    Node::add_example(int classe)
    {
        if (first_class_ == -1)
            first_class_ = classe;
        else if (first_class_ != classe)
            is_leaf_ = false;
        histo_init_[classe]++;
        histo_init_[0]++;
    }

    int     Node::nb_example()
    {
        return histo_init_[0];
    }

    void    Node::accept(Visitor *v)
    {
        v->visit(this);
    }
}


std::ostream    &operator<<(std::ostream &os, Sliq::Node &node)
{
    Print_visitor visitor(os);
    node.accept(&visitor);
    return os;
}
