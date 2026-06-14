#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
protected:
    std::string id;
    std::string name;

public:
    Person(std::string id = "", std::string name = "");

    std::string getId() const;
    std::string getName() const;

    void setId(std::string id);
    void setName(std::string name);

    virtual void displayInfo() const = 0;

    virtual ~Person();
};

#endif