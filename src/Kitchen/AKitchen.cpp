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
#include <fstream>

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

    while (1) {
        if (kitchen->timeout == true)
            break;
        clock->tickClock();
        float time = kitchen->gi->time / 1000;
        if (clock->getTime() >= time) {
            tmp = (int)clock->getTime() / time;
            kitchen->addIng(tmp);
            clock->resetClock();
        }
    }
}

void clockTimeOut(Clock *clock, Kitchen *kitchen)
{
    while (1) {
        if (kitchen->timeout == true)
            break;
        clock->tickClock();
        for (size_t i = 0; i != kitchen->cooks.size(); i++) {
            if (kitchen->cooks.at(i)->isWorking == true)
                clock->resetClock();
        }
        if ((kitchen->kitchenPizza.size() == 0) && (clock->getTime() >= (float)5)) {
            //std::cout << "TIMEOUT\n";
            kitchen->timeout = true;
        }
    }
}

/* void makePizza(Cook *cook, std::string type, Kitchen *kitchen)
{
    cook->cookThisPizza(type, kitchen);
    done = false;
} */


void managePizza(Clock *clock, Kitchen *kitchen)
{
    size_t tmp = 0;

    while (1) {
        if (kitchen->timeout == true)
            break;
        while (tmp != kitchen->kitchenPizza.size()) {
            for (size_t i = 0; i != kitchen->cooks.size(); i++) {
                if (kitchen->cooks.at(i)->canCook() == true) {
                    kitchen->cooks.at(i)->addPizza(kitchen->kitchenPizza.at(0).first, kitchen->kitchenPizza.at(0).second);
                    kitchen->kitchenPizza.erase(kitchen->kitchenPizza.begin());
                    break;
                }
            }
        }
        clock->tickClock();
    }
}

void createLogPizza(std::string logPizza)
{
    std::ofstream outfile ("ticketOrder.txt", std::ios_base::app);

    outfile << logPizza;
    outfile.close();
}

int startLoop(Kitchen *kitchen, std::string command)
{
    std::string finalCommand = "";

    while (1)
    {
        kitchen->manageInput(command);
        kitchen->processPizza = kitchen->maxPizza - kitchen->kitchenPizza.size();
        if (kitchen->brutCommand == "exit") {
            //std::cout << "exit pid = " << kitchen->pid << std::endl;
            exit(0);
        }
        if (kitchen->brutCommand == "status") {
            kitchen->sendStateToIKitchen();
            continue;
        }
        if (kitchen->brutCommand == "timeout") {
            if (kitchen->timeout == false) {
                dprintf(kitchen->getSockStruct()->sockfd, "false\n");
                continue;
            } else if (kitchen->timeout == true) {
                if (kitchen->displayReadyPizza != "") {
                    std::cout << kitchen->displayReadyPizza.c_str();
                }
                dprintf(kitchen->getSockStruct()->sockfd, "true\n");
                break;
            }
        }
        if (kitchen->brutCommand == "isready") {
            if (kitchen->displayReadyPizza == "")
                kitchen->displayReadyPizza = "\n";
            dprintf(kitchen->getSockStruct()->sockfd, "%s", kitchen->displayReadyPizza.c_str());
            createLogPizza(kitchen->displayReadyPizza);
            kitchen->displayReadyPizza = "";
            continue;
        }
        if (kitchen->processPizza <= 0) {
            dprintf(kitchen->getSockStruct()->sockfd, "%s", kitchen->brutCommand.c_str());
            continue;
        }
        finalCommand = checkPizza(kitchen->brutCommand, &kitchen->kitchenPizza, kitchen->processPizza);
        kitchen->processPizza = kitchen->maxPizza - kitchen->kitchenPizza.size();
        if (kitchen->processPizza < 0)
            kitchen->processPizza = 0;
        dprintf(kitchen->getSockStruct()->sockfd, "%s", finalCommand.c_str());
        command = "";
    }
    exit(0);
}

void fonctionCook(Cook *cook, Kitchen *kitchen)
{
    cook->cookThisPizza(kitchen);
}

void startCooker(Clock *clock, Kitchen *kitchen)
{
    std::vector<std::thread> _cookerThread;
    std::thread cooker;

    for (size_t i = 0; i != kitchen->cooks.size(); i++) {
        cooker = std::thread(fonctionCook, kitchen->cooks.at(i), kitchen);
        _cookerThread.push_back(std::move(cooker));
    }
    while (1) {
        if (kitchen->timeout == true)
            break;
        clock->tickClock();
    }
    for (size_t i = 0; i != _cookerThread.size(); i++)
        _cookerThread.at(i).join();
}

int startKitchen(std::string command, GI *gi, pid_t pid)
{
    Clock clockPizza;
    Clock clockIng;
    Clock clockTimeout;
    Clock clockCooker;
    Kitchen *kitchen = new Kitchen(gi, pid);

    std::thread t1(startLoop, kitchen, command);
    std::thread t2(addIngKitchen, &clockIng, kitchen);
    std::thread t3(clockTimeOut, &clockTimeout, kitchen);
    std::thread t4(startCooker, &clockCooker, kitchen);
    std::thread t5(managePizza, &clockPizza, kitchen);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    return 0;
}