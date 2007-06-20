#include "attribute.hh"

namespace Sliq
{
    namespace Attribute
    {

        List::List (int attribute)
        {
                num_ = attribute;
        }

        int List::insert(int value, int index)
        {
            std::vector<std::pair<int, int> >::iterator it;
            for (it = values_indexes_.begin ();
                    it != values_indexes_.end () && value > (*it).first;
                    ++it)
                ;
            it = values_indexes_.insert(it, std::pair<int, int>(value, index));
        }

        void    List::check_best_test (int attribute, std::vector<std::pair<int, Node*> > &class_list)
        {
            std::vector<std::pair<int, int> >::iterator it;
            for (it = values_indexes_.begin ();
                    (it + 1) != values_indexes_.end ();
                    ++it)
            {
                std::pair<int, Node *>   example = class_list[(*it).second];
                if (!example.second->is_leaf ())
                {
                    if (!example.second->has_children())
                    {
                        example.second->divide ();
                    }
                    // std::cout << example.second->id_get () << std::endl;
                    example.second->update_histogram_and_test(attribute, example.first, (*it).first, (*(it + 1)).first);
                }
            }
        }

        void    List::execute_cut (int attribute, std::vector<std::pair<int, Node*> > &class_list)
        {
            std::vector<std::pair<int, int> >::iterator it;
            for (it = values_indexes_.begin ();
                    it != values_indexes_.end ();
                    ++it)
            {
                Node    *node = class_list[(*it).second].second;

                if (!node->is_leaf () && node->has_children ())
                {
                    if (node->test_get ().attribute_get () == attribute)
                    {
                        if ((*it).first <= node->test_get ().lim_get ())
                        {
                            class_list[(*it).second].second = node->fg_get ();
                            node->fg_get ()->add_example (class_list[(*it).second].first);
                        }
                        else
                        {
                            class_list[(*it).second].second = node->fd_get ();
                            node->fd_get ()->add_example (class_list[(*it).second].first);
                        }
                    }
                }
            }
        }

    }

}
