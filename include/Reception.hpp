/*
** EPITECH PROJECT, 2020
** reception
** File description:
** hpp
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include <string>
#include <iostream>
#include <algorithm>
#include <regex>
#include <fstream>
#include <thread>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "LoadBalancer.hpp"

class Reception
{
public:
    explicit Reception(char **av);

    ~Reception();

    void run();

    bool isRunning(bool *isRunning);

protected:
private:
    std::ofstream _logFile;
    std::string _completeCommand;
    std::vector<Command> _command;
    std::vector<Command> _allCommands;

    bool _isRunning;
    int _nbrCommand;

    LoadBalancer *_loadBalancer;
private:

    void printInLogFile(std::string message);

    void printCommandInLogFile();

    void sortCommand(std::string command);

    static PizzaSize getPizzaSize(const std::string &element);

    static PizzaType getPizzaType(const std::string &element);

    void printStatus();

    void getInput();

    void commandHandler();

    void printPizzaCommandStatus();

    void printKitchensStatus();

    void deleteUselessKitchens();

    int getTotalNbrOfPizzasInCommand();

    void balanceLoad(int amount);
};

#endif /* !RECEPTION_HPP_ */
