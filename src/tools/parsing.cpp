/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** parsing
*/

#include "include.hpp"

/**
 * @brief Parse the command between the char delimiter 
 * 
 * @param
 * std::string : line to be parsed
 * @return fill the std::vector with parsed lines
 */
std::vector<std::string> parse_commande(std::string input, char c)
{
    std::string tmp;
    std::vector<std::string> commande;

    for (size_t i = 0; i < input.size(); i++) {
        if (input.at(i) == c) {
            commande.push_back(tmp);
            tmp.erase();
        } else {
            tmp.push_back(input[i]);
        }
    }
    commande.push_back(tmp);
    return commande;
}
