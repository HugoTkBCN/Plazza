/*
** EPITECH PROJECT, 2020
** Created by Fergus Alexander Bray on 27/04/2020.
** Copyright (c) 2020 TheExquisiteCrumpet. All rights reserved.
** utils.cpp description:
**
*/

#include <vector>
#include <string>
#include <iostream>

void printHelp()
{
    std::cout << "USAGE\n";
    std::cout << "\t./plazza [multiplier] [numberCooks] [incrementTime]\n\n";
    std::cout << "DESCRIPTION\n";
    std::cout << "\tmultiplier\tMultiplier for cooking time\n";
    std::cout << "\tnumberCooks\tCooks per kitchen\n";
    std::cout << "\tincrementTime\tIngredients incrementation time\n\n";
    std::cout << "COMMANDS\n";
    std::cout << "\torder\tExample: regina XXL x2; fantasia M x10; margarita S x1\n";
    std::cout << "\tstatus\tPrint Kitchen's status\n";
    std::cout << "\texit|stop\tExit the program\n";
}

std::vector<std::string> mySplit(std::string string, const std::string &delimiter)
{
    size_t pos = 0;
    std::string token;
    std::vector<std::string> result;

    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        result.push_back(token);
        string.erase(0, pos + delimiter.length());
    }
    result.push_back(string);
    return (result);
}