#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <string>

class Restaurant
{
private:
    std::vector<std::string> breakfastMenu;
    std::vector<std::string> lunchMenu;
    std::vector<std::string> dinnerMenu;

    int mealsServedCount;

public:
    Restaurant();

    void setBreakfastMenu(
        const std::vector<std::string>& menu);

    void setLunchMenu(
        const std::vector<std::string>& menu);

    void setDinnerMenu(
        const std::vector<std::string>& menu);

    std::vector<std::string> getBreakfastMenu() const;

    std::vector<std::string> getLunchMenu() const;

    std::vector<std::string> getDinnerMenu() const;

    void serveMeal();

    int getMealsCount() const;
};

#endif