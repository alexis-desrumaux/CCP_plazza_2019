/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IKitchen
*/

#include <iostream>
#include "Kitchen.hpp"
#include <unistd.h>
#include "watchers.hpp"
#include "tools.hpp"

int IKitchen::manageConnexionKitchen()
{
    watch_clients(this->sockStruct);
    return 0;
}

std::vector<std::string> IKitchen::getState()
{
    std::vector<std::string> state;

    for (size_t i = 0; i != this->sockStruct->clients.size(); i += 1) {
        if (this->sockStruct->clients.at(i)->command == "status") {
            state.push_back(this->sockStruct->clients.at(i)->answer);
        }
    }
    return state;
}

void IKitchen::printAnswerKitchens()
{
    for (size_t i = 0; i != this->sockStruct->clients.size(); i += 1) {
        std::cout << this->sockStruct->clients.at(i)->answer;
    }
}

void IKitchen::printPizzasReady()
{
    std::string buff;

    for (size_t i = 0; i != this->sockStruct->clients.size(); i += 1) {
        dprintf(this->sockStruct->clients.at(i)->socket, "%s", "isready");
        buff = read_client(this->sockStruct->clients.at(i)->socket);
        if (buff != "\n\n") {
            std::cout << buff;
        }
    }
}

void IKitchen::checkTimeOut()
{
    std::string buff;
    std::vector<client_t *> c;
    for (size_t i = 0; i != this->sockStruct->clients.size(); i += 1) {
        dprintf(this->sockStruct->clients.at(i)->socket, "%s", "timeout");
        buff = read_client(this->sockStruct->clients.at(i)->socket);
        if (buff == "false\n") {
            c.push_back(this->sockStruct->clients.at(i));
        }
        else if (buff == "true\n") {
            close(this->sockStruct->clients.at(i)->socket);
        }
    }
    this->sockStruct->clients = c;
}

std::string deleteZeroCommandOrder(std::string command)
{
    std::string r;
    std::vector<std::string> v;
    std::vector<std::string> p;
    std::vector<std::vector<std::string>> vc;
    std::vector<std::vector<std::string>> nc;
    std::vector<size_t> index;

    command.pop_back();
    v = parse_commande(command, '\n');
    for (size_t i = 0; i != v.size(); i += 1) {
        v.at(i) = clean_str(v.at(i));
        p = parse_commande(v.at(i), ' ');

        vc.push_back(p);
    }
    for (size_t i = 0; i != vc.size(); i += 1) {
        if (stoi(vc.at(i).at(2)) != 0)
            index.push_back(i);
    }
    for (size_t i = 0; i != index.size(); i += 1) {
        nc.push_back(vc.at(index.at(i)));
    }
    for (size_t i = 0; i != nc.size(); i += 1) {
        if (i != 0)
            r += "\n";
        for (size_t j = 0; j != nc.at(i).size(); j += 1) {
            if (j != 0)
                r += " ";
            r += nc.at(i).at(j);
        }
    }
    r += '\n';
    return r;
}

int IKitchen::sendPizzasToKitchen(std::string command)
{
    pid_t pid;
    std::string pizza_command = command;
    int last_len = 0;

    if (this->sockStruct->clients.empty()) {
        pid = fork();
        if (pid == 0) {
            //std::cout << "NEW CUISINE" << std::endl;
            startKitchen("", this->gi, pid);
        }
        else if (pid != 0) {
            //std::cout << "NEW CUISINE WATCH SOCKET" << std::endl;
            watch_socket(this->sockStruct);
        }
        
    }
    if (!this->sockStruct->clients.empty()) {
        for (size_t i = 0; i != this->sockStruct->clients.size(); i += 1) {
            //std::cout << "pizza command = " << pizza_command;
            dprintf(this->sockStruct->clients.at(i)->socket, "%s", pizza_command.c_str());
            pizza_command = read_client(this->sockStruct->clients.at(i)->socket);

            //regina M 3\n

            //std::cout << "pizza command after read " << pizza_command;
            pizza_command = deleteZeroCommandOrder(pizza_command);
            //std::cout << "pizza command after delete " << pizza_command;

            //

            //std::cout << "pizza command end" << std::endl;
            this->sockStruct->clients.at(i)->answer = pizza_command;
            if (pizza_command == "\n") {
                break;
            }
        }
        last_len = this->sockStruct->clients.size();
        while (pizza_command != "\n") {
            pid = fork();
            if (pid == 0) {
                //std::cout << "NEW CUISINE" << std::endl;
                startKitchen("", this->gi, pid);
            }
            if (pid != 0) {
                //std::cout << "NEW CUISINE WATCH SOCKET" << std::endl;
                watch_socket(this->sockStruct);
            }
            //std::cout << "last_len = " << last_len << "size =" << this->sockStruct->clients.size() << std::endl;
            for (size_t i = last_len; i != this->sockStruct->clients.size(); i += 1) {
                //std::cout << "pizza command = " << pizza_command;
                dprintf(this->sockStruct->clients.at(i)->socket, "%s", pizza_command.c_str());
                pizza_command = read_client(this->sockStruct->clients.at(i)->socket);

                //regina M 3\n

                //std::cout << "pizza command after read " << pizza_command;
                pizza_command = deleteZeroCommandOrder(pizza_command);
                //std::cout << "pizza command after delete " << pizza_command;
                
                //std::cout << "pizza command end" << std::endl;
                this->sockStruct->clients.at(i)->answer = pizza_command;
                if (pizza_command == "\n") {
                    return 0;
                }
            }
            last_len = this->sockStruct->clients.size();
        }
    }
    return 0;
}

int IKitchen::getInfoFromKitchen(std::string command)
{
    if (!this->sockStruct->clients.empty()) {
        for (size_t i = 0; i != this->sockStruct->clients.size(); i += 1) {
            dprintf(this->sockStruct->clients.at(i)->socket, "%s", command.c_str());
            this->sockStruct->clients.at(i)->answer = read_client(this->sockStruct->clients.at(i)->socket);
        }
    }
    return 0;
}

IKitchen::IKitchen(GI *gi, serverFtp_t *server)
{
    this->gi = gi;
    this->nbKitchen = 0;
    this->sockStruct = server;
    
    /*this->socket_server = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket_server == 0) {
        std::cerr << "socket failed" << std::endl;
        this->errorServer = 1;
    }
    if (this->errorServer == 0 && setsockopt(this->socket_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt) == -1)) {
        std::cerr << "setsocket failed" << std::endl;
        this->errorServer = 1;
    }
    if (this->errorServer == 0) {
        this->serv_addr.sin_family = AF_INET;
        this->serv_addr.sin_addr.s_addr = INADDR_ANY;
        this->serv_addr.sin_port = htons(8880);
    }
    if (this->errorServer == 0 && bind(this->socket_server, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr)) < 0) {
        std::cerr << "bind failed" << std::endl;
        this->errorServer = 1;
    }
    if (this->errorServer == 0 && listen(this->socket_server, 100)) {
        std::cerr << "listen failed" << std::endl;
        this->errorServer = 1;
    }*/

}

IKitchen::~IKitchen()
{
    
}
