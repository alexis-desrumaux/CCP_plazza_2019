/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#include "Pizza.hpp"
#include "clock.hpp"
#include "include.hpp"
#include "Kitchen.hpp"
#include "Cook.hpp"

std::condition_variable cv;
std::mutex cv_mutex;
bool done = false;

Cook::Cook()
{
    this->maxPizza = 2;
    this->nbPizzas = 0;
    this->isWorking = false;
}

Cook::~Cook()
{
}

void waits(std::string type)
{
    type = type;
    std::unique_lock<std::mutex> uk (cv_mutex);
    //std::cout << "Waiting ingredient...\n";
    cv.wait(uk, [] {return done == true;});
    cv_mutex.lock();
    done = false;
}

void signal()
{
    //std::cout << "Ingredient OK !...\n";
    /* while (1) {
        //Verify ingrédients...
        if (type == "regina")
        if (type == "fantasia")
        if (type == "margarita")
        if (type == "americana")
        break;
    } */
    cv.notify_one();
    std::unique_lock<std::mutex> uk(cv_mutex);
    cv_mutex.unlock();
    done = true;
}

void Cook::makePizza(std::string type, std::string size, Kitchen *kitchen)
{
    Pizza::Regina regina;
    Pizza::Fantasia fantasia;
    Pizza::Margarita margarita;
    Pizza::Americana americana;
    Clock clock;
    int seconde = 0;

    while (1) {
        done = true;
        clock.tickClock();
        if (type == "regina" && regina.canBeCooked(kitchen->ing)) {
            seconde = (2 * ((kitchen->gi->time / 1000))) * 1000000;
            regina.make(&kitchen->ing, seconde);
            kitchen->displayReadyPizza += "Regina " + size + " Ready\n";
            //std::cout << kitchen->displayReadyPizza;
            this->isWorking = false;
            break;
        }
        if (type == "fantasia" && fantasia.canBeCooked(kitchen->ing)) {
            seconde = (4 * ((kitchen->gi->time / 1000))) * 1000000;
            fantasia.make(&kitchen->ing, seconde);
            kitchen->displayReadyPizza += "Fantasia " + size + " Ready\n";
            //std::cout << kitchen->displayReadyPizza;
            this->isWorking = false;
            break;
        }
        if (type == "margarita" && margarita.canBeCooked(kitchen->ing)) {
            seconde = (1 * ((kitchen->gi->time / 1000))) * 1000000;
            margarita.make(&kitchen->ing, seconde);
            kitchen->displayReadyPizza += "Margarita " + size + " Ready\n";
            //std::cout << kitchen->displayReadyPizza;
            this->isWorking = false;
            break;
        }
        if (type == "americana" && americana.canBeCooked(kitchen->ing)) {
            seconde = (2 * ((kitchen->gi->time / 1000))) * 1000000;
            americana.make(&kitchen->ing, seconde);
            kitchen->displayReadyPizza += "Americana " + size + " Ready\n";
            //std::cout << kitchen->displayReadyPizza;
            this->isWorking = false;
            break;
        }
    }
    done = false;
}

void Cook::cookThisPizza(Kitchen *kitchen)
{
    Clock clock;
    std::vector<std::thread> _waitsThread;
    std::vector<std::thread> _signalThread;
    std::thread waitsThread;
    std::thread signalThread;
    size_t tmp = 0;

    while (1) {
        if (pizzas.size() > 0)
            this->isWorking = true;
        while (tmp != pizzas.size()) {
            this->isWorking = true;
            waitsThread = std::thread (&Cook::makePizza, this, pizzas.at(0).first, pizzas.at(0).second, kitchen);
            signalThread = std::thread (signal);
            _waitsThread.push_back(std::move(waitsThread));
            _signalThread.push_back(std::move(signalThread));
            pizzas.erase(pizzas.begin());
            this->nbPizzas = this->nbPizzas - 1;
        }
        while (tmp != _waitsThread.size()) {
            _waitsThread.at(0).join();
            _signalThread.at(0).join();
            _waitsThread.erase(_waitsThread.begin());
            _signalThread.erase(_signalThread.begin());
        }
        clock.tickClock();
    }
}

bool Cook::canCook()
{
    if (this->nbPizzas >= 2) {
        return false;
    } else
        return true;
}

bool Cook::addPizza(std::string type, std::string size)
{
    this->pizzas.push_back(std::pair<std::string, std::string>(type, size));
    this->nbPizzas += 1;
    return true;
}

std::string Cook::getStatus()
{
    if (this->isWorking)
    {
        return "is working\n";
    }
    else
    {
        return "is not working\n";
    }
}