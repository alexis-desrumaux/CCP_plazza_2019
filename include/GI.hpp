/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** GI
*/

#ifndef GI_HPP_
#define GI_HPP_

class GI {
    public:
        GI(float, int, int);
        ~GI();

        float multi_cooking_time;
        int nb_cooks_per_kitchen;
        int time;
        int max_pizza_per_kitchen;
};

#endif /* !GI_HPP_ */
