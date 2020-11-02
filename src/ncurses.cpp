/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** ncurses
*/

#include <ncurses.h>
#include "include.hpp"

void init_ncurses()
{
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    erase();
}

void display_ncurses()
{
    // int nb = 0;
    // std::string input = "";

    // // while (1) {
    // //     nb = getch();
    // //     if (nb > 0) {
    // //         input.push_back(nb);
    // //         mvprintw(0, 0, input.c_str());
    // //     }
    // //     if (nb == 84)
    // //         break;
    // // }

}

void end_ncurses()
{
    endwin();
}