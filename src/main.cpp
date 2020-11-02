/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** main
*/

#include "include.hpp"

int plazza(float multi_time, int nb_cooks, int time)
{
    Reception *reception = new Reception(new GI(multi_time, nb_cooks, time));
    return loop(reception);
}

void error_handling_argument(float multi_time, int nb_cooks, int time)
{
    if (multi_time <= 0) {
        std::cerr << "The 'multiplier' must be an 'int' or 'float' and it must be greather than 0." << std::endl;
        exit(84);
    }
    if (nb_cooks <= 0) {
        std::cerr << "The 'number of cooks per kitchen' must be an 'int' and it must be greather than 0." << std::endl;
        exit(84);
    }
    if (time <= 0) {
        std::cerr << "The 'time' must be an 'int' and it must be greather than 0." << std::endl;
        exit(84);
    }
}

int display_help()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./plazza a b c" << std::endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\ta\tmultiplier for the cooking time of the pizzas." << std::endl;
    std::cout << "\tb\tnumber of cooks per kitchen." << std::endl;
    std::cout << "\tc\ttime in milliseconds, used by the kitchen stock to replace ingredients" << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 4 && ac != 2)
        return 84;
    if (ac == 2 && strcmp(av[1], "-h") == 0)
        return display_help();
    else if (ac == 2 && strcmp(av[1], "-h") != 0)
        return 84;
    error_handling_argument(atof(av[1]), atoi(av[2]), atoi(av[3]));
    return plazza(atof(av[1]), atoi(av[2]), atoi(av[3]));
}