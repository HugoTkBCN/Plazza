/*
** EPITECH PROJECT, 2020
** LoadBlancer
** File description:
** cpp
*/

#include "LoadBalancer.hpp"

#include <utility>
#include <mqueue.h>

LoadBalancer::LoadBalancer(std::string multiplier, std::string incrementTime)
{
    this->_kitchens.emplace_back(new Kitchen(std::move(multiplier), std::move(incrementTime)));
}

LoadBalancer::~LoadBalancer()
= default;

void make_regina(Kitchen *kitchen)
{
    kitchen->makeRegina();
}

void make_margarita(Kitchen *kitchen)
{
    kitchen->makeMargarita();
}

void make_americana(Kitchen *kitchen)
{
    kitchen->makeAmericana();
}

void make_fantasia(Kitchen *kitchen)
{
    kitchen->makeFantasia();
}

void makePizza(Command *command, Kitchen *kitchen)
{
    std::vector<std::thread> tmp;
    PizzaType type = command->pizzaType;
    PizzaSize size = command->pizzaSize;

    while (command->pizzasRemaining != 0) {
        //std::cout << kitchen->getDoe() << " / " << kitchen->getTomato() << "/" << kitchen->getGruyere() << "/" << kitchen->getHam() << "/" << kitchen->getMushrooms() << "/" << kitchen->getSteak() << "/" << kitchen->getEggplant() << "/" << kitchen->getGoatcheese() << "\n";
        if (type == PizzaType::Regina && kitchen->getDoe() >= size && kitchen->getTomato() >= size && kitchen->getGruyere() >= size && kitchen->getHam() >= size && kitchen->getMushrooms() >= size) {
            (*command).pizzasRemaining--;
            kitchen->removeDoe(size);
            kitchen->removeTomato(size);
            kitchen->removeGruyere(size);
            kitchen->removeHam(size);
            kitchen->removeMushrooms(size);
            tmp.push_back(std::thread(make_regina, kitchen));
        } else if (type == PizzaType::Margarita && kitchen->getDoe() >= size && kitchen->getTomato() >= size && kitchen->getGruyere() >= size) {
            kitchen->removeDoe(size);
            kitchen->removeTomato(size);
            kitchen->removeGruyere(size);
            tmp.push_back(std::thread(make_margarita, kitchen));
            (*command).pizzasRemaining--;
        } else if (type == PizzaType::Americana && kitchen->getDoe() >= size && kitchen->getTomato() >= size && kitchen->getGruyere() >= size && kitchen->getSteak() >= size) {
            kitchen->removeDoe(size);
            kitchen->removeTomato(size);
            kitchen->removeGruyere(size);
            kitchen->removeSteak(size);
            tmp.push_back(std::thread(make_americana, kitchen));
            (*command).pizzasRemaining--;
        } else if (type == PizzaType::Fantasia && kitchen->getDoe() >= size && kitchen->getTomato() >= size && kitchen->getEggplant() >= size && kitchen->getGoatcheese() >= size) {
            kitchen->removeDoe(size);
            kitchen->removeTomato(size);
            kitchen->removeEggplant(size);
            kitchen->removeGoatcheese(size);
            tmp.push_back(std::thread(make_fantasia, kitchen));
            (*command).pizzasRemaining--;
        }
    }
    for (std::vector<int>::size_type i = 0; i < tmp.size(); i++)
        tmp[i].join();
    command->pizzasFinished = true;
}

void incr_ingredient(Kitchen *kitchen, Command *command)
{
    while (!command->pizzasFinished) {
        kitchen->incrementIngredient();
    }
}

std::string LoadBalancer::printSize(PizzaSize size)
{
    switch(size) {
        case PizzaSize::S :
            return ("S");
        case PizzaSize::M :
            return ("M");
        case PizzaSize::L :
            return ("L");
        case PizzaSize::XL :
            return ("XL");
        case PizzaSize::XXL :
            return ("XXL");
        default:
            return ("");
    }
    return ("");
}

std::string LoadBalancer::printType(PizzaType type)
{
    switch (type) {
        case PizzaType::Regina :
            return ("Regina");
        case PizzaType::Margarita :
            return ("Margarita");
        case PizzaType::Americana :
            return ("Americana");
        case PizzaType::Fantasia :
            return ("Fantasia");
        default:
            return ("");
    }
    return ("");
}

void LoadBalancer::runCommand(std::vector<Command> &commands)
{
    std::vector<std::thread> tmp;
    std::vector<std::thread> tmpIncrementIngredient;


    for (Command &command : commands) {
        tmp.emplace_back(makePizza, &command, this->_kitchens.back());
        tmpIncrementIngredient.emplace_back(incr_ingredient, this->_kitchens.back(), &command);
    }
    for (auto &i : tmpIncrementIngredient) {
        i.join();
    }
    for (auto &i : tmp) {
        i.join();
    }
    std::cout << "Your pizzas are ready!!: " << std::endl;
    for (Command &command : commands) {
        std::cout << "Command: " << command.id << " with " << command.nbrPizzas << " "
                  << this->printSize(command.pizzaSize) << " " << this->printType(command.pizzaType) << " is prepared"
                  << std::endl;
    }
    std::cout << ">";
    exit(0);
}

void LoadBalancer::sendMessage(int queueId, const std::string &message)
{
    mq_send(queueId, message.c_str(), message.length(), 0);
}