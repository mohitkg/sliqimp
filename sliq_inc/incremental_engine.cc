#include "incremental_engine.hh"


// Pour trouver l'arbre idéal, faire tourner sliq sur un exemple d'exemple
// représentant toutes les possibilités (en proportions correctes)

// Attention les classes suivantes n'ont pas toutes le même cardinal!

// Algo d'abord équiprobable de tomber sur chaque couleur:
//  - on tire un nombre entre 1 et 6 (+ une chance de généner un truc complètement aléatoire qui pourra être du bruit)
//  -

// plus simple:
// on tire trois chiffre au hasard entre 0 et 255, on vérifie si c'est une des couleurs,
// si oui -> ok, si non -> ok avec une tt petite proba

#define R   0
#define G   1
#define B   2

#define Rouge   1
#define Vert    2
#define Bleu    3
#define Jaune   4
#define Violet  5
#define Cyan    6
#define Bruit   7


int alea(int n)
{
    int partSize   = (n == RAND_MAX) ?        1 : 1 + (RAND_MAX - n)/(n+1);
    int maxUsefull = partSize * n + (partSize-1);
    int draw;

    do
    {
        draw = rand();
    }
    while (draw > maxUsefull);
    return draw/partSize;
}

namespace Incremental_sliq
{

    Engine::Engine (std::string config_filename, std::vector<std::vector<int> > *examples)
    {
        srand((int)time(NULL));
        *examples = load_examples(config_filename);
    }

    Sliq::Node    *Engine::init_node(int id, int nb_classes)
    {
        return new Node(id, nb_classes);
    }

    void        Engine::test(std::vector<Example> data)
    {
        int cpt = 0;
        int good = 0;
        std::vector<int> cpts;
        cpts.push_back(0);
        cpts.push_back(0);
        cpts.push_back(0);
        cpts.push_back(0);
        cpts.push_back(0);
        cpts.push_back(0);
        cpts.push_back(0);
        cpts.push_back(0);
        for (std::vector<std::vector<int> >::iterator it = data.begin ();
                it != data.end ();
                ++it)
        {
            cpt++;
            cpts[get_class(*it)]++;
            // std::cout << "classify : " << engine_->classify(*it) << " ::: " << get_class(*it) << std::endl;
            if (classify(*it) == get_class(*it))
                good++;
            else
            {
                (*it).push_back(classify(*it));
                (*it).push_back(get_class(*it));
                error_log_.push_back(*it);
            }
        }

        std::cout << "Resultat pour " << cpt << " donnees : " << std::endl;
        for (int i = 1; i < 8; ++i)
            std::cout << i << ":" << (double) cpts[i] / cpt << std::endl;
        std::cout << "Bien classifie : " << 100 * (double) good / cpt << " %" << std::endl;
        std::cout << "---------" << std::endl;
        update_tree_with_errors();
    }

    Example     &Engine::generate_data ()
    {
        Example *result = new Example ();
        int     r = 0;
        int     g = 0;
        int     b = 0;
        int     cpt = 0;

        result->push_back(r);
        result->push_back(g);
        result->push_back(b);
        while (1)
        {
            (*result)[R] = alea(255);
            (*result)[G] = alea(255);
            (*result)[B] = alea(255);
            if (get_class(*result) != Bruit)
            {
                // std::cout << cpt << std::endl;
                return *result;
            }
            cpt++;
            if (cpt > 10)
                return *result;
        }

        return *result;
    }

    int         Engine::get_class(Example &ex)
    {
        // rouge : R > G && R > B && abs(G - B) <= 20 && R - G >= 70
        if (ex[R] > ex[G] && ex[R] > ex[B] && abs(ex[G] - ex[B]) <= 20 && ex[R] - ex[G] >= 70)
            return Rouge;
        // vert : G > R && G > B && abs(R - B) <= 20 && G - R >= 70
        if (ex[G] > ex[R] && ex[G] > ex[B] && abs(ex[R] - ex[B]) <= 20 && ex[G] - ex[R] >= 70)
            return Vert;
        // bleu : B > R && B > G && abs(R - G) <= 20 && B - R >= 70
        if (ex[B] > ex[R] && ex[B] > ex[G] && abs(ex[R] - ex[G]) <= 20 && ex[B] - ex[R] >= 70)
            return Bleu;
        // violet : B > G && R > G && abs(R - B) <= 20 && B - G >= 30
        if (ex[B] > ex[G] && ex[R] > ex[G] && abs(ex[R] - ex[B]) <= 20 && ex[B] - ex[G] >= 30)
            return Violet;
        // jaune : R > B && G > B && abs(R - G) <= 20 && R - B >= 130
        if (ex[R] > ex[B] && ex[G] > ex[B] && abs(ex[R] - ex[G]) <= 20 && ex[R] - ex[B] >= 100 /* 130 */)
            return Jaune;
        // cyan : B > R && G > R && abs(B - G) <= 20 && B - R >= 40
        if (ex[B] > ex[R] && ex[G] > ex[R] && abs(ex[B] - ex[G]) <= 20 && ex[B] - ex[R] >= 40)
            return Cyan;
        else
            return Bruit;
    }

    void    Engine::update_tree_with_errors()
    {

        for (std::vector<Example>::iterator it = error_log_.begin ();
                it != error_log_.end ();
                ++it)
        {
            Node    *node = dynamic_cast<Node *>(tree_);

            while (node)
            {
                int attribute = node->test_get().attribute_get ();
                int lim = node->test_get().lim_get ();

                node->error_set((*it)[attribute_names_.size () + 1]);

                if ((*it)[attribute] <= lim)
                    node = dynamic_cast<Node *>(node->fg_get ());
                else
                    node = dynamic_cast<Node *>(node->fd_get ());
            }
        }
    }

}
