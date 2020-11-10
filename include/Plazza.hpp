/*
** EPITECH PROJECT, 2020
** Created by Fergus Alexander Bray on 27/04/2020.
** Copyright (c) 2020 TheExquisiteCrumpet. All rights reserved.
** Plazza.hpp description:
**
*/


#ifndef CCP_PLAZZA_2019_PLAZZA_HPP
#define CCP_PLAZZA_2019_PLAZZA_HPP

//REGEX EXPRESSIONS
#define COMMAND_REGEX R"((((regina|margarita|americana|fantasia) (s|m|l|xl|xxl) (x[1-9][0-9]*) ?; ?)*((regina|margarita|americana|fantasia) (s|m|l|xl|xxl) (x[1-9][0-9]*) ?))|(stop)|(status)|(exit))"
#define PIZZA_REGEX R"((regina|margarita|americana|fantasia))"
#define SIZE_REGEX R"((s|m|l|xl|xxl))"
#define PIZZA_NBR_REGEX R"((x[1-9][0-9]*))"
#define COMMAND_LINE_REGEX R"((( ./plazza )(([1-9][0-9]*(\.[0-9]+)?)|([0-9]+\.[0-9]+)) [1-9][0-9]* [1-9][0-9]*)|(./plazza -h))"

#define EPITECH_ERROR 84
#endif //CCP_PLAZZA_2019_PLAZZA_HPP
