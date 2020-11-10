/*
** EPITECH PROJECT, 2020
** Pizza
** File description:
** hpp
*/

#ifndef PIZZA_HPP_
#define PIZZA_HPP_

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

class Pizza {
    public:
        Pizza();
        ~Pizza();

    protected:
    private:
};

#endif /* !PIZZA_HPP_ */
