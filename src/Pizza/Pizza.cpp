/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Pizza
*/

#include <unistd.h>
#include "Pizza.hpp"
#include <mutex>

std::mutex mutex;

bool Pizza::Regina::canBeCooked(std::map<Ingredients, int> ingredients)
{
    mutex.lock();
    if (ingredients.find(_doe)->second > 0 && ingredients.find(_tomato)->second > 0 && ingredients.find(_gruyere)->second > 0 && ingredients.find(_ham)->second > 0 && ingredients.find(_mushrooms)->second > 0) {
        mutex.unlock();
        return true;
    }
    mutex.unlock();
    return false;
}

void Pizza::Regina::make(std::map<Ingredients, int> *ingredients, int mTime)
{
    if (this->canBeCooked((*ingredients)) == true) {
        mutex.lock();
        ingredients->find(_doe)->second -= 1;
        ingredients->find(_tomato)->second -= 1;
        ingredients->find(_gruyere)->second -= 1;
        ingredients->find(_ham)->second -= 1;
        ingredients->find(_mushrooms)->second -= 1;
        mutex.unlock();
        usleep(mTime);
    }
}

bool Pizza::Margarita::canBeCooked(std::map<Ingredients, int> ingredients)
{
    mutex.lock();
    if (ingredients.find(_doe)->second > 0 && ingredients.find(_tomato)->second > 0 && ingredients.find(_gruyere)->second > 0) {
        mutex.unlock();
        return true;
    }
    return false;
}

void Pizza::Margarita::make(std::map<Ingredients, int> *ingredients, int mTime)
{
    if (this->canBeCooked((*ingredients)) == true) {
        mutex.lock();
        ingredients->find(_doe)->second -= 1;
        ingredients->find(_tomato)->second -= 1;
        ingredients->find(_gruyere)->second -= 1;
        mutex.unlock();
        usleep(mTime);
    }
}

bool Pizza::Fantasia::canBeCooked(std::map<Ingredients, int> ingredients)
{
    mutex.lock();
    if (ingredients.find(_doe)->second > 0 && ingredients.find(_tomato)->second > 0 && ingredients.find(_eggplant)->second > 0 && ingredients.find(_goat_cheese)->second > 0 && ingredients.find(_chief_love)->second > 0) {
        mutex.unlock();
        return true;
    }
    mutex.unlock();
    return false;
}

void Pizza::Fantasia::make(std::map<Ingredients, int> *ingredients, int mTime)
{
    if (this->canBeCooked((*ingredients)) == true) {
        mutex.lock();
        ingredients->find(_doe)->second -= 1;
        ingredients->find(_tomato)->second -= 1;
        ingredients->find(_eggplant)->second -= 1;
        ingredients->find(_goat_cheese)->second -= 1;
        ingredients->find(_chief_love)->second -= 1;
        mutex.unlock();
        usleep(mTime);
    }
}

bool Pizza::Americana::canBeCooked(std::map<Ingredients, int> ingredients)
{
    mutex.lock();
    if (ingredients.find(_doe)->second > 0 && ingredients.find(_tomato)->second > 0 && ingredients.find(_gruyere)->second > 0 && ingredients.find(_steak)->second > 0) {
        mutex.unlock();
        return true;
    }
    mutex.unlock();
    return false;
}

void Pizza::Americana::make(std::map<Ingredients, int> *ingredients, int mTime)
{
    if (this->canBeCooked((*ingredients)) == true) {
        mutex.lock();
        ingredients->find(_doe)->second -= 1;
        ingredients->find(_tomato)->second -= 1;
        ingredients->find(_gruyere)->second -= 1;
        ingredients->find(_steak)->second -= 1;
        mutex.unlock();
        usleep(mTime);
    }
}