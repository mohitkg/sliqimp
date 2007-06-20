#ifndef TEST_HH
# define TEST_HH

# include <iostream>

class Test
{
public:
    int     attribute_get ()
    {
        return attribute_;
    }
    int     lim_get ()
    {
        return lim_;
    }
    void    set(int value, int attribute)
    {
        attribute_ = attribute;
        lim_ = value;
    }
private:
    int     attribute_;
    int     lim_;

};

std::ostream    &operator<<(std::ostream &os, Test &test);

#endif
