/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** AKitchen
*/

#include "Pizza.hpp"
#include "tools.hpp"
#include "include.hpp"
#include "clock.hpp"
#include "Kitchen.hpp"
#include <unistd.h>

//bool makePizza = false;

std::string takePizza(std::string command, std::vector<std::pair<std::string, std::string>> *kitchenPizza)
{
    std::vector<std::string> pizza = parse_commande(command, ' ');
    int nbPizza = atoi(pizza.at(2).c_str());

    if(nbPizza > 0) {
        nbPizza = nbPizza - 1;
        kitchenPizza->push_back(std::pair<std::string, std::string>(pizza.at(0), pizza.at(1)));
        return pizza.at(0) + " " + pizza.at(1) + " " + std::to_string(nbPizza);
    }
    return command;
}

std::string checkPizza(std::string command, std::vector<std::pair<std::string, std::string>> *kitchenPizza, int processPizza)
{
    int tmp = 0;
    std::string finalCommand = "";
    command = command.substr(0, command.size() - 1);
    std::vector<std::string> Pizza = parse_commande(command, '\n');

    while (1) {
        if (tmp >= processPizza)
            break;
        for (size_t i = 0; i != Pizza.size(); i++) {
            Pizza.at(i) = takePizza(Pizza.at(i), kitchenPizza);
            tmp++;
        }
    }
    for (size_t i = 0; i != Pizza.size(); i++)
        finalCommand += Pizza.at(i) + "\n";
    return finalCommand;
}

void addIngKitchen(Clock *clock, Kitchen *kitchen)
{
    int tmp = 0;

    float time = kitchen->gi->time / 1000;
    if (clock->getTime() >= time) {
        tmp = (int)clock->getTime() / time;
        kitchen->addIng(tmp);
        clock->resetClock();
    }
}

/* void verifyIngPizza(Kitchen *kitchen, std::mutex *mutex, Clock *clock)
{
    std::lock_guard<std::mutex> lock((*mutex));

    while (1) {
        clock->tickClock();
        addIngKitchen(clock, kitchen);
    }
}

void cookThisPizza(Kitchen *kitchen, std::string type, std::string size, std::mutex *mutex, std::condition_variable *cond)
{
    std::unique_lock<std::mutex> lock {(*mutex)};

    cond->wait(lock, [] { return (makePizza);});
    if (type == "regina") {
        Pizza::Regina regina;
    }
}

void managePizza(Kitchen *kitchen, Clock *clock)
{
    std::thread t1;
    std::thread t2;
    std::mutex mutex;
    std::condition_variable cond;

    for (size_t i = 0; i != kitchen->kitchenPizza.size(); i++) {
        t1 = std::thread (cookThisPizza, kitchen, kitchen->kitchenPizza.at(i).first, kitchen->kitchenPizza.at(i).second, &mutex, &cond);
        t2 = std::thread (verifyIngPizza, kitchen, );
        t1.join();
        t2.join();
    }
} */

int startLoop(Kitchen *kitchen, std::string command)
{
    Clock clock;
    std::string finalCommand = "";

    while (1)
    {
        clock.tickClock();
        kitchen->manageInput(command);
        addIngKitchen(&clock, kitchen);
        if (kitchen->brutCommand == "status") {
            kitchen->sendStateToIKitchen();
            continue;
        }
        if (kitchen->brutCommand == "timeout") {
            dprintf(kitchen->getSockStruct()->sockfd, "false\n");
            continue;
        }
        if (kitchen->processPizza <= 0) {
            dprintf(kitchen->getSockStruct()->sockfd, kitchen->brutCommand.c_str());
            continue;
        }
        finalCommand = checkPizza(kitchen->brutCommand, &kitchen->kitchenPizza, kitchen->processPizza);
        // La variable kitchen->processPizza, elle correspond au nombre de Pizza que la cuisine peut encore acceuillir,
        // elle se réduit par rapport au nombre de Pizza reçu et non traité
        kitchen->processPizza = kitchen->processPizza - kitchen->kitchenPizza.size();
        //std::cout << "size : " << kitchen->kitchenPizza.size() << "\n";
        // Ici on envoit la string avec les Pizza en soustraction par socket.
        dprintf(kitchen->getSockStruct()->sockfd, finalCommand.c_str());
        command = "";
    }
    exit(0);
}

int startKitchen(std::string command, GI *gi, pid_t pid)
{
    Kitchen *kitchen = new Kitchen(gi, pid);

    startLoop(kitchen, command);
    return 0;
}


/* if (!kitchen->_validCommand.empty()) {
            for (size_t i = 0; i != kitchen->_validCommand.size(); i += 1) {
                for (size_t j = 0; j != kitchen->_validCommand.at(i).size(); j += 1) {
                    if (kitchen->_validCommand.at(i).at(j) == "status")
                        kitchen->sendStateToIKitchen();
                }
            }
            dprintf(kitchen->getSockStruct()->sockfd, "TEST\n");
        } */