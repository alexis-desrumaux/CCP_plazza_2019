/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** clean_str
*/

#include <iostream>
#include <string>
#include "include.hpp"

/**
 * @brief delete \t and space of string 
 * 
 * @param
 * std::string : string
 * @return string cleaned
 */
std::string clean_str(std::string string)
{
    std::string new_string;
    int begin = 0;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ' && begin == 0);
        else if ((string[i] == ' ' && string[i + 1] == ' ') ||
            (string[i] == ' ' && string[i + 1] == '\0')) {
        } else {
            begin = 1;
            new_string = new_string + string[i];
        }
    }
    return new_string;
}