/*
** EPITECH PROJECT, 2020
** Kitchen
** File description:
** hpp
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include "Pizza.hpp"
#include <mqueue.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <mutex>

class Kitchen
{
public:
    Kitchen(std::string multiplier, std::string incrementTime);
    ~Kitchen();

    void makeRegina();
    void makeMargarita();
    void makeAmericana();
    void makeFantasia();

    void incrementIngredient();

    int getDoe() const;
    int getTomato() const;
    int getGruyere() const;
    int getHam() const;
    int getMushrooms() const;
    int getSteak() const;
    int getEggplant() const;
    int getGoatcheese() const;

    int removeDoe(int size);

    int removeTomato(int size);

    int removeGruyere(int size);

    int removeHam(int size);

    int removeMushrooms(int size);

    int removeSteak(int size);

    int removeEggplant(int size);

    int removeGoatcheese(int size);

    int getNbrOfAvailableCooks();

    std::string getMultiplier();

    std::string getIncrementTime();

    void DecreaseAvailableCooks(int amount = 1);

    void IncreaseAvailableCooks(int amount = 1);

    void receiveMessage(int queueId);
protected:
private:
    int _doe;
    int _tomato;
    int _gruyere;
    int _ham;
    int _mushrooms;
    int _steak;
    int _eggplant;
    int _goatcheese;

    std::mutex _mutex;

    std::string _multiplier;
    std::string _incrementTime;

    int _nbrOfAvailableCooks;

    void initQueue();

    std::vector<std::string> _inbox;
    mqd_t _input;
    mqd_t _output;
};

#endif /* !KITCHEN_HPP_ */
