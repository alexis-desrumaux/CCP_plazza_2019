/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** is_correct
*/

#include "include.hpp"
#include <algorithm>

/**
 * @brief Transform maj characters to lower characters
 * 
 * @param
 * char c : letter to be convert into lower char
 * @return lower char (97-122 ASCII)
 */
char asciitolower(char c) {
    if (c <= 'Z' && c >= 'A')
        return c - ('Z' - 'z');
    return c;
}

/**
 * @brief check if the string is a valid pizza
 * 
 * @param
 * std::string : string
 * @return 0 if it's valid, -1 otherwise
 */
int is_good_pizza(std::string str)
{
    std::vector<std::string> pizza = {"regina", "margarita", "americana", "fantasia"};
    
    for (size_t i = 0; i < pizza.size(); i++) {
        if (pizza.at(i) == str)
            return 0;
    }
    return -1;
}

/**
 * @brief check if the string is a valid size
 * 
 * @param
 * std::string : string
 * @return 0 if it's valid, -1 otherwise
 */
int is_good_size(std::string str)
{
    std::vector<std::string> size = {"S", "M", "L", "XL", "XXL"};
    
    //std::transform(str.begin(), str.end(), str.begin(), asciitolower);
    for (size_t i = 0; i < size.size(); i++) {
        if (size.at(i) == str)
            return 0;
    }
    return -1;
}

/**
 * @brief check if the string is a valid quantity
 * 
 * @param
 * std::string : string
 * @return 0 if it's valid, -1 otherwise
 */
int is_good_quantity(std::string str)
{
    char c = str[0];
    std::string nb_str;
    int nb = 0;

    if ((c != 'x'/* && c != 'X'*/) || str.size() <= 1)
        return -1;
    for (size_t i = 1; i < str.size(); i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != 'x'/* && str[i] != 'X'*/)
            return -1;
    }
    for (size_t i = 1; i < str.size(); i++)
        nb_str += str[i];
    nb = std::stoi(nb_str);
    if (nb <= 0)
        return -1;
    return 0;
}

/** 
 * @brief: Check if the command passed as parameters is a valid pizza order
 *
 * @parameters:
 * std::vector\<std::string> : command order
 * size_t : index of the line
 * 
 * @return
 * true if command is valid, false otherwise
 */
bool check_is_correct(std::vector<std::string> parse_command, size_t i)
{
    if (parse_command.at(0).size() <= 0)
        return false;
    if (parse_command.size() != 3) {
        std::cerr << "Command " << i + 1 << ": not enought argument." << std::endl;
        return false;
    }
    if (is_good_pizza(parse_command.at(0)) == -1) {
        std::cerr << "Command " << i + 1 << ": Unknown pizza." << std::endl;
        return false;
    }
    if (is_good_size(parse_command.at(1)) == -1) {
        std::cerr << "Command " << i + 1 << ": Unknown size." << std::endl;
        return false;
    }
    if (is_good_quantity(parse_command.at(2)) == -1) {
        std::cerr << "Command " << i + 1 << ": not a valid quantity." << std::endl;
        return false;
    }
    return true;
}
