/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Reception
*/

#include "include.hpp"
#include "tools.hpp"
#include "watchers.hpp"

/**
 * @brief manage connexions with Kitchen and STDIN
 * 
 * @param
 * @return 0
 */
int Reception::manageInput()
{
    /*timeval *t = new timeval;

    t->tv_sec = 0;
    t->tv_usec = 500000;
    set_readfds(this->sockStruct);

    select(this->sockStruct->max + 1, &this->sockStruct->rdfs, NULL, NULL, t);
    watch_socket(this->sockStruct);
    //this->iKitchen->manageConnexionKitchen();
    delete t;*/

    return 0;
}

/**
 * @brief read input from stdin
 * 
 * @param
 * @return 0
 */
int Reception::getInput()
{
    this->input.clear();
    std::cout << "> ";
    getline(std::cin, this->input);
    if (this->input.empty())
        this->getInput();
    this->input = clean_str(this->input);
    return 0;
}

/**
 * @brief get state of kitchens and display them
 * set waitState to false after that
 * 
 * @param
 * @return
 */
void Reception::getState()
{
    std::vector<std::string> state;

    state = this->iKitchen->getState();

    for (size_t i = 0; i != state.size(); i += 1) {
        std::cout << state.at(i) << std::endl;
    }
}

/**
 * @brief get infos from kitchens
 * 
 * @param
 * std::string: command to send to kitchens
 * @return 0
 */
int Reception::getInfoFromKitchen(std::string command)
{
    return this->iKitchen->getInfoFromKitchen(command);
}

/**
 * @brief send parsed pizzas to kitchens
 * 
 * @param
 * std::vector\<std::vector\<std::string>> : pizzas orders to send to kitchens
 * @return 0
 */
int Reception::sendPizzasToKitchen(std::vector<std::vector<std::string>> command)
{
    std::string p_order = parsingPizzas(command);
    return this->iKitchen->sendPizzasToKitchen(p_order);
}

/**
 * @brief clear all vectors from class
 * 
 * @param
 * @return
 */
void Reception::clearVector()
{
    this->input.clear();
    this->_validCommand.clear();
    this->_parseCommand.clear();
    this->_listCommand.clear();
    this->_isCorrect.clear();
}

/**
 * @brief 
 * 
 * @param command 
 * @return int 
 */
int checkValidCommand(std::string command)
{
    if (command == "help" || command == "exit")
        return 0;
    if (command == "status")
        return 1;
    return -1;
}

std::string parsingPizzasToString(std::vector<std::vector<std::string>> out)
{
    std::string str;

    for (size_t i = 0; i != out.size(); i += 1) {
        size_t j = 0;
        for (; j != out.at(i).size(); j += 1) {
            if (j == 0)
                str += out.at(i).at(j);
            else if (j != 0) {
                str += " ";
                str += out.at(i).at(j);
            }
        }
        str += '\n';
    }
    return str;
}


/**
 * @brief Assemble pizzas to make it more easy to understand
 * 
 * @param
 * std::vector\<std::vector\<std::string>>: pizza order
 * @return std::string with parsed pizzas
 */
std::string Reception::parsingPizzas(std::vector<std::vector<std::string>> command)
{
    std::vector<std::vector<std::string>> in = command;
    std::vector<std::vector<std::string>> out;
    std::string pizza;
    std::string size;
    int q = 0;
    int check = 0;
    size_t index = 0;
    std::vector<size_t> gindex;

    while (check != 1) {
        pizza = in.at(index).at(0);
        size = in.at(index).at(1);
        q = stoi(in.at(index).at(2).substr(1));
        gindex.clear();
        out.clear();

        for (size_t i = 0; i != in.size(); i += 1) {
            if (i != index && in.at(i).at(0) == pizza && in.at(i).at(1) == size)
                q += stoi(in.at(i).at(2).substr(1));
            else if (i != index)
                gindex.push_back(i);
        }
        out.push_back(std::vector<std::string>{pizza, size, std::to_string(q)});
        for (size_t i = 0; i != gindex.size(); i += 1)
            out.push_back(in.at(gindex.at(i)));
        in = out;
        if (index + 1 == in.size())
            break;
        index++;
    }
    return parsingPizzasToString(out);
}

/**
 * @brief Parse the command class's std::string input
 * between ';' character delimiter and stock it into _validCommand
 * 
 * @param
 * @return 0
 */
int Reception::parsingInput()
{
    this->_listCommand = parse_commande(this->input, ';');
    for (size_t i = 0; i < this->_listCommand.size(); i++) {
        this->_listCommand.at(i) = clean_str(this->_listCommand.at(i));
        this->_parseCommand = parse_commande(this->_listCommand.at(i), ' ');
        this->_validCommand.push_back(this->_parseCommand);
    }
    return 0;
}

bool Reception::compute()
{
    int checkCommand = -1;
    size_t checkOrderIsValid = 0;
    
    clearVector();
    std::cout << "> ";
    while (getline(std::cin, this->input)) {


        this->input = clean_str(this->input);


        if (this->input.empty() == false) {
            checkOrderIsValid = 0;
            checkCommand = -1;
            this->parsingInput();




            if (!this->_validCommand.empty()) {
                checkCommand = checkValidCommand(this->_validCommand.at(0).at(0));
                if (checkCommand == 0) {
                    if (this->_validCommand.at(0).at(0) == "exit") {
                        return true;
                    }
                    else
                        helpCommand();
                }
                this->iKitchen->checkTimeOut();
                if (checkCommand == 1) {
                    this->getInfoFromKitchen(this->input);
                    this->iKitchen->printAnswerKitchens();
                }
                else if (checkCommand == -1) {
                    for (size_t i = 0; i != this->_validCommand.size() && this->isExit == false; i += 1) {
                        if (check_is_correct(this->_validCommand.at(i), i) == true) {
                            checkOrderIsValid += 1;
                        }
                    }
                    if (checkOrderIsValid == this->_validCommand.size()) {
                        this->sendPizzasToKitchen(this->_validCommand);
                    }
                }
            }
        }
        this->iKitchen->printPizzasReady();
        std::cout << "> ";
        clearVector();
    }
    return true;
}


Reception::Reception(GI *gi)
{
    this->gi = gi;
    this->sockStruct = new serverFtp_t;
    this->input = "";
    if (createServer(this->sockStruct) == -1) {
        std::cerr << "Server failed" << std::endl;
        delete this->sockStruct;
        exit(84);
    }
    this->sockStruct->max = this->sockStruct->sockfd;
    this->iKitchen = new IKitchen(gi, sockStruct);
    this->waitState = false;
    this->isExit = false;
}

Reception::~Reception()
{
    for (size_t i = 0; i != this->sockStruct->clients.size(); i += 1) {
        dprintf(this->sockStruct->clients.at(i)->socket, "%s", "exit");
        close(this->sockStruct->clients.at(i)->socket);
    }
    close(this->sockStruct->sockfd);
    delete this->gi;
    delete this->iKitchen;
    delete this->sockStruct->sock_server;
    delete this->sockStruct;
}