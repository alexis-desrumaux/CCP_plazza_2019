/*
** EPITECH PROJECT, 2020
** undefined
** File description:
** clock
*/

#include "clock.hpp"

Clock::Clock()
{
    this->time = 0;
    this->startClock();
}

void Clock::startClock()
{
    this->start = std::chrono::high_resolution_clock::now();
    usleep(1000);
}

void Clock::resetClock()
{
    this->time = 0;
}

void Clock::durationClock()
{
    this->end = std::chrono::high_resolution_clock::now();
}

void Clock::tickClock()
{
    this->durationClock();
    std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(this->end - this->start);
    this->time += time_span.count();
    this->startClock();
}

float Clock::getTime() const
{
    return this->time;
}

/* int main(void)
{
    Clock clock;

    while (1) {
        clock.tickClock();
        std::cout << clock.getTime() << "\n";
    }
    return 0;
} */