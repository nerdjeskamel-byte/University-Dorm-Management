#include "Person.h"

Person::Person(std::string id, std::string name)
{
    this->id = id;
    this->name = name;
}

std::string Person::getId() const
{
    return id;
}

std::string Person::getName() const
{
    return name;
}

void Person::setId(std::string id)
{
    this->id = id;
}

void Person::setName(std::string name)
{
    this->name = name;
}

Person::~Person()
{
}