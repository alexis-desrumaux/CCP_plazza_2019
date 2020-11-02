/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** watchers
*/

#include "watchers.hpp"
#include "tools.hpp"

std::string fill_cmd(char *buff)
{
    std::string cmd;

    for (int i = 0; buff[i] != '\0'; i++) {
        if (buff[i] != '\r') {
            cmd.push_back(buff[i]);
        }
    }
    return cmd;
}

std::string read_client(Socket socket)
{
    std::string line;
    char *buff = new char[2048];
    std::string cmd;
    int nb = 0;

    bzero(buff, 2048);
    nb = read(socket, buff, 2047);
    if (nb <= 0) {
        return "^C";
    }
    buff[nb + 1] = '\0';
    cmd = fill_cmd(buff);
    bzero(buff, 2047);
    if (cmd.empty())
        return NULL;
    return cmd;
}

int watch_clients(serverFtp_t *server)
{
    std::string buff;

    for (size_t i = 0; server->clients.size() != 0 && i != server->clients.size(); i += 1) {
        if (FD_ISSET(server->clients.at(i)->socket, &server->rdfs)) {
            buff = read_client(server->clients.at(i)->socket);
            if (buff.empty())
                continue;
            else {
                server->clients.at(i)->answer = buff;
            }
        }
    }
    return 0;
}

int accept_client(int sockfd, struct sockaddr_in *cli)
{
    int connfd = 0;
    socklen_t len = sizeof(*cli);

    connfd = accept(sockfd, (SA*)&*cli, &len);
    if (connfd < 0) {
        exit(0);
    }
    else {
        //printf("Server acccept the client with IP: %s PORT: %d\n",
        //inet_ntoa(cli->sin_addr), ntohs(cli->sin_port));
    }
    return connfd;
}

int watch_socket(serverFtp_t *server)
{
    client_t *new_client = NULL;

    /*if (FD_ISSET(server->sockfd, &server->rdfs)) {*/
    server->new_cli = new sockaddr_in;
    server->new_csock = accept_client(server->sockfd, server->new_cli);
    new_client = new client_t;
    new_client->socket = server->new_csock;
    new_client->info = server->new_cli;
    server->clients.push_back(new_client);
    //}
    return 0;
}