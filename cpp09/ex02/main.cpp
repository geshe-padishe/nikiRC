#include "PmergeMe.hpp"

bool has_duplicates(std::vector<int>& vec)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        for (size_t j = i + 1; j < vec.size(); j++)
        {
            if (vec[i] == vec[j]) return true;
        }
    }
    return false;
}

void print_vec(std::vector<int>& vec)
{
    std::cout << "";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << "\b]" << std::endl;
}

void    print_args(int ac, char **argv)
{
    std::cout << "Before: ";
    for (int i = 0; i < ac; i++)
        std::cout << atoi(argv[i]) << " ";
    std::cout << '\b' << std::endl;
}

bool    is_posnumber(char *nb)
{
    if (nb[0] == '\0')
        return (0);
    for (int i = 0; nb[i] != '\0'; i++)
        if (!isdigit(nb[i]) || atoi(nb) < 0)
            return (0);
    return (1);
}

int main(int ac, char **argv)
{
    ac--;
    argv++;
    
    std::vector<int> vec;
    std::list<int> lst;
    if (ac < 2)
        return (std::cout << "Error" << std::endl, 1);
    for (int i = 0; i < ac; i++)
    {
        if (!is_posnumber(argv[i]))
            return (std::cout << "Error" << std::endl, 1);
        vec.push_back(atoi(argv[i]));
        lst.push_back(atoi(argv[i]));
    }
    if (has_duplicates(vec))
        std::cout << "Found duplicate" << std::endl;

    //print_vec(vec);
    print_args(ac, argv);
    clock_t begin, end;
    begin = std::clock();
    fordJohnsonSort<int, std::vector>(vec, 1);
    end = std::clock();
    double elapsed_secs_v = double(end - begin) / CLOCKS_PER_SEC * 1e6;
    std::cout << "Time to process a range of " << ac <<  " elements with std::vector: " << elapsed_secs_v << "us" << std::endl;
    begin = std::clock();
    fordJohnsonSort(lst, 0);
    end = std::clock();
    double elapsed_secs_l = double(end - begin) / CLOCKS_PER_SEC * 1e6;
    std::cout << "Time to process a range of " << ac <<  " elements with std::list: " << elapsed_secs_l << "us" << std::endl;
    return (0);
}