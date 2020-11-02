/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include <ostream>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Cook.hpp"
#include "GI.hpp"
#include "Ingredients.hpp"
#include "Pizza.hpp"
#include "ftp.hpp"

class Kitchen {
    public:
    //functions
        Kitchen(GI *, pid_t);
        ~Kitchen();
        void sendStateToIKitchen();
        void addIng(int i);
        bool regenIng();
        clientFtp_t *getSockStruct();
        int parsingInput();
        int manageInput(std::string command);
        void clearVector();
    //data
        std::map<Ingredients, int> ing;
        std::string displayReadyPizza;
        GI *gi;
        int processPizza;
        int maxPizza;
        int timeout;
        std::string brutCommand;
        std::vector<Cook *> cooks;
        std::vector<std::pair<std::string, std::string>> kitchenPizza;
        pid_t pid;
    protected:
    private:
    //data
        std::string *state;
        clientFtp_t *sockStruct;
};

class IKitchen {
    public:
    //functions
        IKitchen(GI *gi, serverFtp_t *);
        ~IKitchen();
        int manageConnexionKitchen();
        int sendCommandToKitchen(std::string);
        int sendPizzasToKitchen(std::string command);
        int getInfoFromKitchen(std::string command);
        void printAnswerKitchens();
        void checkTimeOut();
        void printPizzasReady();
        std::vector<std::string>getState();
    private:
    //data
        GI *gi;
        std::vector<std::string> state;
        int nbKitchen;
        serverFtp_t *sockStruct;
};

/*********************** @file AKitchen.cpp ***********************************/

int startKitchen(std::string, GI *, pid_t);

#endif /* !KITCHEN_HPP_ */
