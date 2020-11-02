/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

class Kitchen;

class Cook {
    public:
    //functions
        Cook();
        ~Cook();
        void makePizza(std::string, std::string, Kitchen *);
        bool canCook();
        void cookThisPizza(Kitchen *);
        bool addPizza(std::string, std::string);
        std::string getStatus();
        std::vector<std::pair<std::string, std::string>> pizzas;
        int maxPizza;
        int nbPizzas;
        int isWorking;
    private:
    //data
};

#endif /* !COOK_HPP_ */
