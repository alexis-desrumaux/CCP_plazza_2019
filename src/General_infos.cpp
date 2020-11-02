/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** General_infos
*/

#include "GI.hpp"

GI::GI(float a, int b, int c)
{
    this->multi_cooking_time = a;
    this->nb_cooks_per_kitchen = b;
    this->time = c;
    this->max_pizza_per_kitchen = b * 2;
}

GI::~GI()
{
}