/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <iostream>
#include <chrono>
#include <unistd.h>

class Clock {
    public:
        Clock();
        ~Clock() = default;
        float getTime() const;
        void startClock();
        void resetClock();
        void tickClock();
        void durationClock();
    private:
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;
        float time;
};

#endif /* !CLOCK_HPP_ */
