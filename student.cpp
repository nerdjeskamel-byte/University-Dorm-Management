#include "Student.h"
#include <iostream>

Student::Student(
    std::string id,
    std::string name,
    std::string academicYear)
    : Person(id, name)
{
    this->academicYear = academicYear;
    accommodated = false;
}

std::string Student::getAcademicYear() const
{
    return academicYear;
}

bool Student::getAccommodationStatus() const
{
    return accommodated;
}

void Student::setAcademicYear(
    std::string academicYear)
{
    this->academicYear = academicYear;
}

void Student::setAccommodationStatus(
    bool status)
{
    accommodated = status;
}

void Student::displayInfo() const
{
    std::cout << "Student ID: "
              << id << std::endl;

    std::cout << "Name: "
              << name << std::endl;

    std::cout << "Academic Year: "
              << academicYear << std::endl;

    std::cout << "Accommodation: ";

    if (accommodated)
        std::cout << "Yes";
    else
        std::cout << "No";

    std::cout << std::endl;
}