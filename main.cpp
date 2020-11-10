/*
** EPITECH PROJECT, 2020
** main
** File description:
** plazza
*/

#include <string>
#include <iostream>
#include <regex>
#include "Reception.hpp"
#include "Plazza.hpp"
#include "Utils.hpp"

int checkError(int ac, char **av)
{
    std::regex regexCommand{COMMAND_LINE_REGEX};
    std::string commandLine;

    if (ac < 4 || ac > 4) {
        return (EPITECH_ERROR);
    }
    for (int i = 0; av[i]; i++) {
        commandLine = commandLine + " " + av[i];
    }
    if (std::regex_match(commandLine, regexCommand) != 1) {
        return (84);
    } else if (strcmp(av[1], "-h") == 0 && ac == 2) {
        return (1);
    }
    return (0);
}

int main(int ac, char **av)
{
    int ret = checkError(ac, av);

    if (ret != 0) {
        printHelp();
        return (ret == 1 ? 0 : 84);
    } else {
        Reception reception(av);
        reception.run();
    }
    return (0);
}