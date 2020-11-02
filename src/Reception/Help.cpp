/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Help
*/

#include "include.hpp"
#include "Reception.hpp"

/**
 * @brief: Display Plazza Help
 *
 * @parameters:
 * @return
 */
void display_welcome()
{
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "|                 Welcome to The Plazza                  |" << std::endl;
    std::cout << "|                                                        |" << std::endl;
    std::cout << "|      Made with Love by Alexis, Benjamin and Damien     |" << std::endl;
    std::cout << "|                                                        |" << std::endl;
    std::cout << "|                          Menu                          |" << std::endl;
    std::cout << "|           PIZZA                        SIZE            |" << std::endl;
    std::cout << "|                                                        |" << std::endl;
    std::cout << "|                                                        |" << std::endl;
    std::cout << "|         Regina                      S M L XL XXL       |" << std::endl;
    std::cout << "|         Fantasia                    S M L XL XXL       |" << std::endl;
    std::cout << "|         Margarita                   S M L XL XXL       |" << std::endl;
    std::cout << "|         Americaine                  S M L XL XXL       |" << std::endl;
    std::cout << "|                                                        |" << std::endl;
    std::cout << "|                                                        |" << std::endl;
    std::cout << "|          Type \"help\" in you have any questions         |" << std::endl;
    std::cout << "|                                                        |" << std::endl;
    std::cout << "|                                                        |" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
}

/**
 * @brief display Help
 * 
 * @param
 * @return
 */
void Reception::helpCommand(void)
{
    std::cout << std::endl <<  "Welcome to The Plazza" << std::endl << std::endl;
    std::cout << "If you want to order a pizza, please respect the following grammar:" << std::endl;
    std::cout << "\tTYPE SIZE NUMBER [; PIZZA SIZE NUMBER ]*" << std::endl;
    std::cout << "\t- PIZZA  := [a..zA..Z]" << std::endl;
    std::cout << "\t- SIZE   := S|M|L|XL|XXL" << std::endl;
    std::cout << "\t- NUMBER := x[1..9][0..9]*" << std::endl << std::endl;
    std::cout << "For example:" << std::endl;
    std::cout << "\"regina XXL x2; fantasia M x3; margarita S x1\" is a valid command." << std::endl;
    std::cout << "But \"calzone XM xA\" isn\'t a valid command." << std::endl << std::endl;
    std::cout << "List of available commands:" << std::endl;
    std::cout << "\t- exit := close the restaurant..." << std::endl;
    std::cout << "\t- help := display this instructions" << std::endl;
    std::cout << "\t- PIZZA SIZE NUMBER with:" << std::endl;
    std::cout << "\t\t- PIZZA for the name of the pizza" << std::endl;
    std::cout << "\t\t- SIZE for the size of the pizza" << std::endl;
    std::cout << "\t\t- NUMBER for the quantity of the pizza you want" << std::endl;
    std::cout << "For example:" << std::endl;
    std::cout << "\tregina XXL x2" << std::endl << std::endl;
    std::cout << "Have a good day!" << std::endl;
}