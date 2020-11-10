/*
** EPITECH PROJECT, 2020
** LoadBalancer
** File description:
** hpp
*/

#ifndef LOADBALANCER_HPP_
#define LOADBALANCER_HPP_

#include "command.hpp"
#include "Kitchen.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>


class LoadBalancer
{
public:
    LoadBalancer(std::string, std::string);

    ~LoadBalancer();

    void runCommand(std::vector<Command> &commands);

public:
    std::vector<Kitchen *> _kitchens;

private:
    void makeRegina(PizzaSize size);

    void makeMargarita(PizzaSize size);

    void makeAmericana(PizzaSize size);

    void makeFantasia(PizzaSize size);

    std::string printSize(PizzaSize);

    std::string printType(PizzaType);

    static void sendMessage(int queueId, const std::string &message);
};

#endif /* !LOADBALANCER_HPP_ */
