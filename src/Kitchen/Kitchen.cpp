/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Kitchen
*/

#include "include.hpp"
#include "watchers.hpp"
#include "tools.hpp"

//Ingredients:
//Tomate: 5
//Pomme: 7
//....



/**
 * @brief clear all vectors from class
 * 
 * @param
 * @return
 */
/* void Kitchen::clearVector()
{
    this->brutCommand.clear();
    for (size_t i = 0; i != this->_validCommand.size(); i += 1) {
        for (size_t j = 0; j != this->_validCommand.at(i).size(); j += 1) {
            this->_validCommand.at(i).at(j).clear();
        }
    }
} */

void Kitchen::addIng(int i)
{
    this->ing.find(_doe)->second += i;
    this->ing.find(_tomato)->second += i;
    this->ing.find(_gruyere)->second += i;
    this->ing.find(_ham)->second += i;
    this->ing.find(_mushrooms)->second += i;
    this->ing.find(_steak)->second += i;
    this->ing.find(_eggplant)->second += i;
    this->ing.find(_goat_cheese)->second += i;
    this->ing.find(_chief_love)->second += i;
}

/* int Kitchen::parsingInput()
{
    std::vector<std::string> listCommand;
    std::vector<std::string> parseCommand;

    listCommand = parse_commande(this->brutCommand, '\n');
    for (size_t i = 0; i < listCommand.size(); i++) {
        listCommand.at(i) = clean_str(listCommand.at(i));
        parseCommand = parse_commande(listCommand.at(i), ' ');
        this->_validCommand.push_back(parseCommand);
    }
    return 0;
} */

int Kitchen::manageInput(std::string command)
{
    if (command != "") {
        this->brutCommand = clean_str(command);
        return 0;
    }
    std::string buff;
    set_readfds_client(this->sockStruct);
    select(this->sockStruct->max + 1, &this->sockStruct->rdfs, NULL, NULL, NULL);
    if (FD_ISSET(this->sockStruct->sockfd, &this->sockStruct->rdfs)) {
        buff = read_client(this->sockStruct->sockfd);
        this->brutCommand = clean_str(buff);
    }
    return 0;
}

clientFtp_t *Kitchen::getSockStruct()
{
    return this->sockStruct;
}

void Kitchen::sendStateToIKitchen()
{
    std::string status;

    status = "------------------- " + std::string("PID : ") + std::to_string(this->pid) + " -------------------------\n";
    status += "Ingrédients:\n";
    status += "\t - Doe : " + std::to_string(this->ing.find(_doe)->second) + "\n";
    status += "\t - Tomato : " + std::to_string(this->ing.find(_tomato)->second) + "\n";
    status += "\t - Gruyere : " + std::to_string(this->ing.find(_gruyere)->second) + "\n";
    status += "\t - Ham : " + std::to_string(this->ing.find(_ham)->second) + "\n";
    status += "\t - Mushrooms : " + std::to_string(this->ing.find(_mushrooms)->second) + "\n";
    status += "\t - Steak : " + std::to_string(this->ing.find(_steak)->second) + "\n";
    status += "\t - Eggplant : " + std::to_string(this->ing.find(_eggplant)->second) + "\n";
    status += "\t - Goat cheese : " + std::to_string(this->ing.find(_goat_cheese)->second) + "\n";
    status += "\t - Chief Love : " + std::to_string(this->ing.find(_chief_love)->second) + "\n";
    status += "-------------------------------------------------------\n";
    status += "Cooker - Status :\n";
    for (unsigned int i = 0; i < this->cooks.size(); i++)
        if (this->cooks.at(i))
            status += "\t - Cook n°" + std::to_string(i + 1) + " : " + this->cooks.at(i)->getStatus();
    write(this->sockStruct->sockfd, status.c_str(), status.size());
}

Kitchen::Kitchen(GI *gi, pid_t pid)
{
    this->ing.insert(std::pair<Ingredients, int>(_doe, 5));
    this->ing.insert(std::pair<Ingredients, int>(_tomato, 5));
    this->ing.insert(std::pair<Ingredients, int>(_gruyere, 5));
    this->ing.insert(std::pair<Ingredients, int>(_ham, 5));
    this->ing.insert(std::pair<Ingredients, int>(_mushrooms, 5));
    this->ing.insert(std::pair<Ingredients, int>(_steak, 5));
    this->ing.insert(std::pair<Ingredients, int>(_eggplant, 5));
    this->ing.insert(std::pair<Ingredients, int>(_goat_cheese, 5));
    this->ing.insert(std::pair<Ingredients, int>(_chief_love, 5));
    this->displayReadyPizza = "";
    this->gi = gi;
    this->pid = pid;
    this->timeout = false;
    this->maxPizza = this->gi->nb_cooks_per_kitchen * 2;
    this->processPizza = maxPizza;
    for (int i = 0; i != gi->nb_cooks_per_kitchen; i++) {
        Cook *cook = new Cook;
        this->cooks.push_back(cook);
    }
    this->sockStruct = new clientFtp_t;
    if (createClient(this->sockStruct) == -1) {
        std::cerr << "Server failed" << std::endl;
        delete this->sockStruct;
        exit(84);
    }
}

Kitchen::~Kitchen()
{
}
