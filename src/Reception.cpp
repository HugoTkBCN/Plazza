/*
** EPITECH PROJECT, 2020
** Reception
** File description:
** cpp
*/

#include <utility>
#include "Reception.hpp"
#include "Plazza.hpp"
#include "Utils.hpp"

Reception::Reception(char **av)
{
    (void) (av);
    this->_logFile.open("plazza.log");
    this->_isRunning = true;
    this->_nbrCommand = 0;
    this->_loadBalancer = new LoadBalancer(av[1], av[3]);
}

Reception::~Reception()
{
    this->_logFile.close();
}

void Reception::printInLogFile(std::string message)
{
    this->_logFile << message;
}

void Reception::printCommandInLogFile(void)
{
    time_t tt;
    struct tm *ti;
    time(&tt);
    ti = localtime(&tt);
    std::string date = asctime(ti);
    date = date.substr(0, date.size() - 1);

    printInLogFile(date + ": ");
    printInLogFile(this->_completeCommand + "\n");
}

PizzaSize Reception::getPizzaSize(const std::string &element)
{
    if (element == "m") {
        return (PizzaSize::M);
    } else if (element == "l") {
        return (PizzaSize::L);
    } else if (element == "xl") {
        return (PizzaSize::XL);
    } else if (element == "xxl") {
        return (PizzaSize::XXL);
    } else {
        return (PizzaSize::S);
    }
}

PizzaType Reception::getPizzaType(const std::string &element)
{
    if (element == "regina") {
        return (PizzaType::Regina);
    } else if (element == "americana") {
        return (PizzaType::Americana);
    } else if (element == "fantasia") {
        return (PizzaType::Fantasia);
    } else {
        return (PizzaType::Margarita);
    }
}


void Reception::sortCommand(std::string command)
{
    std::vector<std::string> commands = mySplit(std::move(command), ";");
    std::vector<std::string> elements;
    std::regex regexPizza{PIZZA_REGEX};
    std::regex regexSize{SIZE_REGEX};
    std::regex regexNbrPizza{PIZZA_NBR_REGEX};
    Command commandSorted;

    commandSorted.id = this->_nbrCommand;
    for (const std::string &toSort : commands) {
        elements = mySplit(toSort, " ");
        for (std::string element : elements) {
            if (std::regex_match(element, regexPizza) == 1) {
                commandSorted.pizzaType = this->getPizzaType(element);
            } else if (std::regex_match(element, regexSize) == 1) {
                commandSorted.pizzaSize = this->getPizzaSize(element);
            } else if (std::regex_match(element, regexNbrPizza) == 1) {
                element.erase(0, 1);
                commandSorted.nbrPizzas = std::stoi(element);
            }
        }
        commandSorted.pizzasFinished = false;
        commandSorted.pizzasRemaining = commandSorted.nbrPizzas;
        this->_command.push_back(commandSorted);
        this->_allCommands.push_back(commandSorted);
    }
}

void checkKitchen(const bool *isRunning)
{
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //std::cout << "do some checks\n";
    }
}

void Reception::printPizzaCommandStatus()
{
    std::cout << "Current commands being processed. Please be patient, are cooks are working hard!!" << std::endl;
    for (Command command : this->_allCommands) {
        if (command.pizzaType == PizzaType::Margarita) {
            std::cout << command.pizzasRemaining << "Margaritas," << std::endl;
        } else if (command.pizzaType == PizzaType::Fantasia) {
            std::cout << command.pizzasRemaining << "Fantasias," << std::endl;
        } else if (command.pizzaType == PizzaType::Americana) {
            std::cout << command.pizzasRemaining << "Americanas," << std::endl;
        } else {
            std::cout << command.pizzasRemaining << "Reginas," << std::endl;
        }
    }
}

void Reception::printKitchensStatus()
{
    int kitchenNbr = 0;

    for (auto i : this->_loadBalancer->_kitchens) {
        std::cout << "Kitchen number " << kitchenNbr << " has ";
        std::cout << i->getNbrOfAvailableCooks() << " of available cooks" << std::endl;
        std::cout << "Here is a list of its current amount of ingredients: " << std::endl;
        std::cout << "Portions of Tomato: " << i->getTomato() << std::endl;
        std::cout << "Portions of Steak: " << i->getSteak() << std::endl;
        std::cout << "Portions of Mushrooms: " << i->getMushrooms() << std::endl;
        std::cout << "Portions of Ham: " << i->getHam() << std::endl;
        std::cout << "Portions of Gruyere: " << i->getGruyere() << std::endl;
        std::cout << "Portions of GoatCheese: " << i->getGoatcheese() << std::endl;
        std::cout << "Portions of EggPlant! " << i->getEggplant() << std::endl;
        std::cout << "Portions of Doe: " << i->getDoe() << "\n" << std::endl;
        kitchenNbr++;
    }
}

void Reception::printStatus()
{
    this->printPizzaCommandStatus();
    this->printKitchensStatus();
}

void Reception::getInput()
{
    std::cout << "> ";
    std::getline(std::cin, this->_completeCommand);
    std::transform(this->_completeCommand.begin(), this->_completeCommand.end(),
                   this->_completeCommand.begin(), ::tolower);
    std::cout << "\n";
}

void Reception::deleteUselessKitchens()
{
    for (unsigned int i = 0; i <= this->_loadBalancer->_kitchens.size(); i++) {
        if (this->_loadBalancer->_kitchens[i]->getNbrOfAvailableCooks() == 10) {
            this->_loadBalancer->_kitchens.erase(this->_loadBalancer->_kitchens.begin() + i);
        }
    }
}

int Reception::getTotalNbrOfPizzasInCommand()
{
    int nbrOfPizzas = 0;

    for (auto &i : this->_command) {
        nbrOfPizzas += i.nbrPizzas;
    }
    return (nbrOfPizzas);
}

void Reception::balanceLoad(int amount)
{
    for (auto i : this->_loadBalancer->_kitchens) {
        if (amount == 0) {
            break;
        }
        if (i->getNbrOfAvailableCooks() < 10) {
            if ((amount + i->getNbrOfAvailableCooks()) <= 10) {
                i->IncreaseAvailableCooks(amount);
                amount = 0;
                break;
            } else {
                int tmp = (amount + i->getNbrOfAvailableCooks()) - 10;
                amount -= (amount - tmp);
                i->IncreaseAvailableCooks(10);
                this->_loadBalancer->_kitchens.emplace_back(new Kitchen(std::move(this->_loadBalancer->_kitchens.back
                        ()->getMultiplier()), std::move(this->_loadBalancer->_kitchens.back()->getIncrementTime())));
            }
        } else {
            this->_loadBalancer->_kitchens.emplace_back(new Kitchen(std::move(this->_loadBalancer->_kitchens.back
                    ()->getMultiplier()), std::move(this->_loadBalancer->_kitchens.back()->getIncrementTime())));
            i->IncreaseAvailableCooks(10);
            amount -= 10;
        }
    }
}

void Reception::commandHandler()
{
    int nbrOfPizzas = 0;
    int pid = 0;

    this->sortCommand(this->_completeCommand);
    this->printCommandInLogFile();
    nbrOfPizzas = this->getTotalNbrOfPizzasInCommand();
    this->balanceLoad(nbrOfPizzas);

    pid = fork();
    if (pid == -1) {
        exit(84);
    } else if (pid == 0) {
        this->_loadBalancer->runCommand(this->_command);
    }
    this->_command.clear();
    this->_nbrCommand++;

    //this->deleteUselessKitchens();
}

void Reception::run()
{
    std::regex regexCommand{COMMAND_REGEX};
    this->printInLogFile("##Addition##\n");
    std::thread kitchenCheking = std::thread(checkKitchen, &this->_isRunning);

    while (this->_isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->getInput();
        if (std::cin.eof() == 1 || this->_completeCommand == "stop" || this->_completeCommand == "exit") {
            this->_isRunning = false;
        } else if (std::regex_match(this->_completeCommand, regexCommand) != 1) {
            std::cout << "Wrong command!\n" << std::endl;
        } else if (this->_completeCommand == "status") {
            this->printStatus();
        } else {
            this->commandHandler();
        }
    }
    kitchenCheking.detach();
}