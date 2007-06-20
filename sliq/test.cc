#include "test.hh"

std::ostream    &operator<<(std::ostream &os, Test &test)
{
        os << "attribut " << test.attribute_get () << " \\<= " << test.lim_get ();
        return os;
}
