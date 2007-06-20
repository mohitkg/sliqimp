#include <fstream>
#include <sstream>
#include <iostream>
#include "engine.hh"

// fonction qui enlève les espaces de début et de fin
void trim(std::string& str)
{
    std::string::size_type pos = str.find_last_not_of(' ');
    if(pos != std::string::npos)
    {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        if(pos != std::string::npos)
            str.erase(0, pos);
    }
    else
        str.erase(str.begin(), str.end());
}

namespace Sliq
{

    Engine::Engine (std::string config_filename, std::vector<std::vector<int> > *examples)
    {
        *examples = load_examples(config_filename);
    }

    Node    *Engine::init_node(int id, int nb_classes)
    {
        return new Node(id, nb_classes);
    }

    std::vector<std::vector<int> >      &Engine::load_examples(std::string    &config_filename)
    {
        std::vector<int>                temp;
        std::vector<std::vector<int> >  *result = new std::vector<std::vector<int> > ();
        std::ifstream file(config_filename.c_str ());
        bool    parse_colors = true;
        bool    parse_attributes = true;
        int     index = 0;
        int     int_value;

        if (file)
        {
            std::string line;
            std::cout << "Parsing classes..." << std::endl;
            classes_names_.push_back("");
            while (parse_colors && std::getline(file, line))
            {
                if (!line.compare("-"))
                    parse_colors = false;
                else
                {
                    std::string cl = line.substr(0, line.find_first_of("//") - 1);
                    trim(cl);
                    classes_names_.push_back(cl);
                    std::cout << cl << std::endl;
                }
            }
            tree_ = init_node(1, classes_names_.size ());
            std::cout << "Parsing attributes..." << std::endl;
            while (parse_attributes && std::getline(file, line))
            {
                if (!line.compare("-"))
                    parse_attributes = false;
                else
                {
                    std::string att = line.substr(0, line.find_first_of("//") - 1);
                    trim(att);
                    attribute_names_.push_back(att);
                    std::cout << att << std::endl;
                }
            }
            std::cout << "Parsing examples..." << std::endl;
            while (std::getline(file, line))
            {
                if (!line.compare(""))
                    continue;
                int nb_attributes = attribute_names_.size ();
                temp.clear ();
                for (int i = 0; i < nb_attributes; ++i)
                {
                    std::string value = line.substr(0, line.find_first_of(","));
                    line = line.substr(line.find_first_of(",") + 1);
                    trim(value);
                    std::istringstream iss(value);
                    iss >> int_value;
                    attribute_lists_.push_back(Attribute::List (i));
                    attribute_lists_[i].insert(int_value, index);
                    temp.push_back(int_value);
                }
                std::istringstream iss(line);
                iss >> int_value;
                class_list_.push_back(std::pair<int, Node*>(int_value, tree_));
                temp.push_back(int_value);
                result->push_back(temp);
                index += 1;
            }
            for (std::vector<std::pair<int, Node*> >::iterator it = class_list_.begin ();
                    it != class_list_.end ();
                    ++it)
            {
                tree_->add_example((*it).first);
            }

        }
        return *result;
    }

    bool        Engine::compute_sliq ()
    {
        bool    only_real_leafs = false;
        Test    *test;
        int i = 0;

        while (!only_real_leafs)
        {
            for (int i = 0; i < attribute_names_.size (); ++i)
                attribute_lists_[i].check_best_test(i, class_list_);

            for (int i = 0; i < attribute_names_.size (); ++i)
                attribute_lists_[i].execute_cut(i, class_list_);

            only_real_leafs = true;
            for (std::vector<std::pair<int, Node*> >::iterator it = class_list_.begin ();
                    it != class_list_.end (); ++it)
            {
                only_real_leafs = only_real_leafs && (*it).second->is_leaf ();
            }
        }
    }

    int         Engine::classify(std::vector<int> ex)
    {
        Node    *node = tree_;

        while (!node->is_leaf())
        {
            int attribute = node->test_get().attribute_get ();
            int lim = node->test_get().lim_get ();

            if (ex[attribute] <= lim)
                node = node->fg_get ();
            else
                node = node->fd_get ();
        }
        return node->class_get();
    }

}

std::ostream    &operator<<(std::ostream &os, Sliq::Engine &engine)
{
    os << "digraph G {\n"
	    << "edge [color=\"#8855FF\", arrowsize=1]\n"
	    << "node [fontsize=7, fontname=Verdana]\n";
    os << *engine.tree_get ();
    os << "}" << std::endl;
    return os;
}
