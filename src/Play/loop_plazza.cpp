/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** loop_plazza
*/

#include "include.hpp"
#include "ftp.hpp"
#include "Reception.hpp"

int loop(Reception *reception)
{
    display_welcome();
    reception->compute();
    std::cout << "Good bye!" << std::endl;
    delete reception;
    return 0;
}