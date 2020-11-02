/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ftp
*/

#ifndef FTP_HPP_
#define FTP_HPP_

#include <ostream>
#include <string.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SA struct sockaddr
#define PORT 8080

typedef int Socket;

typedef struct clientFtp_s
{
    Socket sockfd;
    struct sockaddr_in *sock_cli;
    fd_set rdfs;
    int max;
    uint16_t port;
} clientFtp_t;

typedef struct client_s
{
    Socket socket;
    std::string command;
    std::string answer;
    struct sockaddr_in *info;
} client_t;

typedef struct serverFtp_s
{
    Socket sockfd;
    Socket new_csock;
    struct sockaddr_in *new_cli;
    struct sockaddr_in *sock_server;
    int max;
    std::vector<client_t *> clients;
    int nbClients;
    fd_set rdfs;
    fd_set wfs;
    uint16_t port;
} serverFtp_t;

/*********************** @file ftp.cpp ***********************************/


void set_readfds(serverFtp_t *server);
void set_readfds_client(clientFtp_t *client);
int listen_socket(serverFtp_t *server);
int bind_socketfd_ip(int sockfd, sockaddr_in *servaddr, uint16_t port);
int create_sockfd(serverFtp_t *server);
int createClient(clientFtp_t *client);
int createServer(serverFtp_t *server);

#endif /* !FTP_HPP_ */
