/*
** EPITECH PROJECT, 2020
** plazza
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Ingredients.hpp"

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};
enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

namespace Pizza {
    /* class Pizza {
        public:
            Pizza() = default;
            virtual ~Pizza() = default;
            virtual bool canBeCooked(std::map<Ingredients, int>);
            virtual void make(std::map<Ingredients, int> *ing, int mTime);
        protected:
        //data
            int id;
            bool isCooked;
            float timeCooking;
            bool isMaking;
        private:
        //data
            PizzaType type;
    }; */
    
    class Fantasia {//}: public Pizza {
        public:
        //functions
            Fantasia() = default;
            ~Fantasia() = default;
            bool canBeCooked(std::map<Ingredients, int>);
            void make(std::map<Ingredients, int> *ing, int mTime);
        private:
    };

    class Americana {//}: public Pizza {
        public:
        //functions
            Americana() = default;
            ~Americana() = default;
            bool canBeCooked(std::map<Ingredients, int>);
            void make(std::map<Ingredients, int> *ing, int mTime);
        private:
    };

    class Regina {//}: public Pizza {
        public:
        //functions
            Regina() = default;
            ~Regina() = default;
            bool canBeCooked(std::map<Ingredients, int>);
            void make(std::map<Ingredients, int> *ing, int mTime);
        private:
    };

    class Margarita {//}: public Pizza {
        public:
        //functions
            Margarita() = default;
            ~Margarita() = default;
            bool canBeCooked(std::map<Ingredients, int>);
            void make(std::map<Ingredients, int> *ing, int mTime);
        private:
        //data
    };

}

#endif /* !PIZZA_HPP_ */
