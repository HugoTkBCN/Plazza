/*
** EPITECH PROJECT, 2020
** Created by Fergus Alexander Bray on 27/04/2020.
** Copyright (c) 2020 TheExquisiteCrumpet. All rights reserved.
** command.hpp description:
**
*/


#ifndef CCP_PLAZZA_2019_COMMAND_HPP
#define CCP_PLAZZA_2019_COMMAND_HPP

#include "Pizza.hpp"

typedef struct command_s
{
    PizzaType pizzaType;
    PizzaSize pizzaSize;
    int nbrPizzas;
    int id;
    bool pizzasFinished;
    int pizzasRemaining;
} Command;


#endif //CCP_PLAZZA_2019_COMMAND_HPP
