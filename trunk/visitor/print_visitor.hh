#ifndef PRINT_VISITOR_HH
# define PRINT_VISITOR_HH

# include "visitor.hh"

class   Print_visitor : public Visitor
{
    public:
        Print_visitor (std::ostream &os) {os_ = &os;}
        void    visit (Sliq::Node *node);
        void    visit (Incremental_sliq::Node *node);
    private:
        std::ostream    *os_;
};


#endif
