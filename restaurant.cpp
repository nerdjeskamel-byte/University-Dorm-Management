#include "Restaurant.h"

Restaurant::Restaurant()
{
    mealsServedCount = 0;
}

void Restaurant::setBreakfastMenu(
    const std::vector<std::string>& menu)
{
    breakfastMenu = menu;
}

void Restaurant::setLunchMenu(
    const std::vector<std::string>& menu)
{
    lunchMenu = menu;
}

void Restaurant::setDinnerMenu(
    const std::vector<std::string>& menu)
{
    dinnerMenu = menu;
}

std::vector<std::string>
Restaurant::getBreakfastMenu() const
{
    return breakfastMenu;
}

std::vector<std::string>
Restaurant::getLunchMenu() const
{
    return lunchMenu;
}

std::vector<std::string>
Restaurant::getDinnerMenu() const
{
    return dinnerMenu;
}

void Restaurant::serveMeal()
{
    mealsServedCount++;
}

int Restaurant::getMealsCount() const
{
    return mealsServedCount;
}