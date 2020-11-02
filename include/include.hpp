/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** include
*/

#ifndef INCLUDE_HPP_
#define INCLUDE_HPP_

#include <condition_variable>
#include <mutex>
#include <thread>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>

//#include "Kitchen.hpp"
#include "Reception.hpp"
#include "Pizza.hpp"
#include "GI.hpp"

/*********************** @file loop_plazza.cpp ***********************************/

int loop(Reception *reception);

/*********************** @file is_correct.cpp ***********************************/

int is_good_pizza(std::string);
int is_good_size(std::string);
int is_good_quantity(std::string);
bool check_is_correct(std::vector<std::string>, size_t);

/*********************** @file help.cpp ***********************************/

void display_welcome(void);

#endif /* !INCLUDE_HPP_ */
