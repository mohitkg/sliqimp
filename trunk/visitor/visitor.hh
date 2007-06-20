#ifndef VISITOR_HH

# define VISITOR_HH

# include "../sliq_inc/incremental_engine.hh"
# include "../sliq_inc/node.hh"

class   Visitor
{
    public:
        virtual void    visit (Sliq::Node *node) = 0;
        virtual void    visit (Incremental_sliq::Node *node) = 0;
    private:
};

#endif
