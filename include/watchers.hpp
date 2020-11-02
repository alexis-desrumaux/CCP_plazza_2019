/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** watchers
*/

#ifndef WATCHERS_HPP_
#define WATCHERS_HPP_

#include "ftp.hpp"

/*********************** @file watchers.cpp ***********************************/

std::string read_client(Socket socket);
int watch_clients(serverFtp_t *server);
int watch_socket(serverFtp_t *server);

#endif /* !WATCHERS_HPP_ */
