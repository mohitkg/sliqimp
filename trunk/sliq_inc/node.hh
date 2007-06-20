#ifndef SLIQ_NODE_HH
# define SLIQ_NODE_HH

# include "../sliq/engine.hh"

class Visitor;

namespace Incremental_sliq
{
    class   Node : public Sliq::Node
    {
    public:
        Node (int id, int nb_classes);
        void    divide ();
        void    accept(Visitor *v);
        std::vector<int>    &nb_error_per_class_get () {return nb_error_per_class_;}
        void    error_set (int c) {nb_error_per_class_[c]++;}
    private:
        std::vector<int>    nb_error_per_class_;
    };

}


std::ostream    &operator<<(std::ostream &os, Incremental_sliq::Node &node);

#endif
