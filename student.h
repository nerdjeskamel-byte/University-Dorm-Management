#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <string>

class Student : public Person
{
private:
    std::string academicYear;
    bool accommodated;

public:
    Student(
        std::string id = "",
        std::string name = "",
        std::string academicYear = "");

    std::string getAcademicYear() const;

    bool getAccommodationStatus() const;

    void setAcademicYear(
        std::string academicYear);

    void setAccommodationStatus(
        bool status);

    void displayInfo() const override;
};

#endif