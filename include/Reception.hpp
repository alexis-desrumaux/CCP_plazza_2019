/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Kitchen.hpp"
#include "GI.hpp"

class Reception {
    public:
    //functions
        Reception(GI *gi);
        ~Reception();
        bool compute();
    //data
        bool isExit;
    protected:
    private:
    //functions
        void getState();
        int parsingInput();
        int getInput();
        int manageInput();
        void clearVector();
        int sendPizzasToKitchen(std::vector<std::vector<std::string>> command);
        int getInfoFromKitchen(std::string command);
        void helpCommand(void);
        std::string parsingPizzas(std::vector<std::vector<std::string>> command);
    //data
        std::string input;
        GI *gi;
        IKitchen *iKitchen;
        std::vector<std::string> _listCommand;
        std::vector<std::string> _parseCommand;
        std::vector<std::vector<std::string>> _validCommand;
        std::vector<bool> _isCorrect;
        
        bool waitState;
        serverFtp_t *sockStruct;
};


#endif /* !RECEPTION_HPP_ */
