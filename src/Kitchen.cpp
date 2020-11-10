/*
** EPITECH PROJECT, 2020
** Kitchen
** File description:
** cpp
*/

#include <utility>
#include "Kitchen.hpp"

Kitchen::Kitchen(std::string multiplier, std::string incrementTime)
{
    this->_doe = 5;
    this->_tomato = 5;
    this->_gruyere = 5;
    this->_ham = 5;
    this->_mushrooms = 5;
    this->_steak = 5;
    this->_eggplant = 5;
    this->_goatcheese = 5;

    this->_multiplier = std::move(multiplier);
    this->_incrementTime = std::move(incrementTime);

    this->_nbrOfAvailableCooks = 10;
}

Kitchen::~Kitchen()
= default;

int Kitchen::getDoe() const
{
    return (this->_doe);
}

int Kitchen::getTomato() const
{
    return (this->_tomato);
}

int Kitchen::getGruyere() const
{
    return (this->_gruyere);
}

int Kitchen::getHam() const
{
    return (this->_ham);
}

int Kitchen::getMushrooms() const
{
    return (this->_mushrooms);
}

int Kitchen::getSteak() const
{
    return (this->_steak);
}

int Kitchen::getEggplant() const
{
    return (this->_eggplant);
}

int Kitchen::getGoatcheese() const
{
    return (this->_goatcheese);
}

int Kitchen::removeDoe(int size)
{
    this->_doe -= size;
    return (this->_doe);
}

int Kitchen::removeTomato(int size)
{
    this->_tomato -= size;
    return (this->_tomato);
}

int Kitchen::removeGruyere(int size)
{
    this->_gruyere -= size;
    return (this->_gruyere);
}

int Kitchen::removeHam(int size)
{
    this->_ham -= size;
    return (this->_ham);
}

int Kitchen::removeMushrooms(int size)
{
    this->_mushrooms -= size;
    return (this->_mushrooms);
}

int Kitchen::removeSteak(int size)
{
    this->_steak -= size;
    return (this->_steak);
}

int Kitchen::removeEggplant(int size)
{
    this->_eggplant -= size;
    return (this->_eggplant);
}

int Kitchen::removeGoatcheese(int size)
{
    this->_goatcheese -= size;
    return (this->_goatcheese);
}

void Kitchen::incrementIngredient()
{
    std::chrono::milliseconds interval(std::stol(this->_incrementTime, nullptr, 0));
    std::this_thread::sleep_for(interval);

    this->_doe += 1;
    this->_tomato += 1;
    this->_gruyere += 1;
    this->_ham += 1;
    this->_mushrooms += 1;
    this->_steak += 1;
    this->_eggplant += 1;
    this->_goatcheese += 1;
}

void Kitchen::makeRegina()
{
    std::chrono::seconds interval(2 * std::stol(this->_multiplier, nullptr, 0));
    std::this_thread::sleep_for(interval);
}

void Kitchen::makeMargarita()
{
    std::chrono::seconds interval(1 * std::stol(this->_multiplier, nullptr, 0));
    std::this_thread::sleep_for(interval);
}

void Kitchen::makeAmericana()
{
    std::chrono::seconds interval(2 * std::stol(this->_multiplier, nullptr, 0));
    std::this_thread::sleep_for(interval);
}

void Kitchen::makeFantasia()
{
    std::chrono::seconds interval(4 * std::stol(this->_multiplier, nullptr, 0));
    std::this_thread::sleep_for(interval);
}

int Kitchen::getNbrOfAvailableCooks()
{
    return (this->_nbrOfAvailableCooks);
}

void Kitchen::DecreaseAvailableCooks(int amount)
{
    this->_nbrOfAvailableCooks -= amount;
    if (this->_nbrOfAvailableCooks <= 10) {
        this->_nbrOfAvailableCooks = 0;
    }
}

void Kitchen::IncreaseAvailableCooks(int amount)
{
    this->_nbrOfAvailableCooks += amount;
    if (this->_nbrOfAvailableCooks >= 10) {
        this->_nbrOfAvailableCooks = 10;
    }
}

std::string Kitchen::getMultiplier()
{
    return (this->_multiplier);
}

std::string Kitchen::getIncrementTime()
{
    return (this->_incrementTime);
}

void Kitchen::initQueue()
{
    struct mq_attr mqAttr{};
    std::string queueName = "kitchen";

    mqAttr.mq_maxmsg = 100;
    mqAttr.mq_msgsize = 100;

    this->_input = mq_open(queueName.c_str(), O_RDWR | O_CREAT, &mqAttr);
    this->_output = mq_open(queueName.c_str(), O_RDWR | O_CREAT, &mqAttr);
}

void Kitchen::receiveMessage(int queueId)
{
    char buffer[100];

    mq_receive(queueId, buffer, 100, 0);
    this->_inbox.emplace_back(buffer);
}