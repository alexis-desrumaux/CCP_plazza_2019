/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** ftp
*/

#include "ftp.hpp"

/**
 * @brief Set the readfds object for client
 * 
 * @param: clientFtp_t *client
 * @return 
 */
void set_readfds_client(clientFtp_t *client)
{
    client->max = client->sockfd;
    FD_ZERO(&client->rdfs);
    FD_SET(client->sockfd, &client->rdfs);
}

/**
 * @brief Set the readfds object
 * 
 * @param: serverFtp_t *server
 * @return 
 */
void set_readfds(serverFtp_t *server)
{
    FD_ZERO(&server->rdfs);
    FD_SET(server->sockfd, &server->rdfs);
    server->max = server->sockfd;
}

int listen_socket(serverFtp_t *server)
{
    if (listen(server->sockfd, 100) != 0)
        return -1;
    return 0;
}

int create_sockfd(serverFtp_t *server)
{
    int sockfd = 0;
    server->sock_server = new sockaddr_in;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        delete server->sock_server;
        return 84;
    }
    bzero(&*server->sock_server, sizeof(*server->sock_server));
    server->sock_server->sin_family = AF_INET;
    server->sock_server->sin_addr.s_addr = htonl(INADDR_ANY);
    server->sock_server->sin_port = htons(server->port);

    bind(sockfd, (SA*)&*server->sock_server, sizeof(*server->sock_server));
    return sockfd;
}

void initStruct(serverFtp_t *server)
{
    server->port = PORT;
    server->nbClients = 0;
    server->sockfd = 0;
    server->new_csock = 0;
}

int createClient(clientFtp_t *client)
{
    client->port = PORT;
    client->sockfd = 0;
    client->sock_cli = new sockaddr_in;
    
    if ((client->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "CLIENT SOCKET FAILED" << std::endl;
        return -1;
    }
    bzero(&*client->sock_cli, sizeof(*client->sock_cli));
    client->sock_cli->sin_family = AF_INET;
    client->sock_cli->sin_port = htons(PORT);
    client->sock_cli->sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(client->sockfd, (SA*)&*client->sock_cli, sizeof(*client->sock_cli)) == -1)
        return -1;
    return 0;
}

/**
 * @brief Create server hosted by localhost 127.0.0.1.
 * Server listening to new clients
 * 
 * @param: serverFtp_t *server
 * @return -1 if server failed or 0 otherwise
 */
int createServer(serverFtp_t *server)
{
    /*J'ai repris le code de mon my_FTP*/

    initStruct(server);
    int check = create_sockfd(server);
    if (check == 84)
        return -1;
    server->sockfd = check;
    if (listen_socket(server) == -1)
        return -1;
    server->max = server->sockfd;
    return 0;
}