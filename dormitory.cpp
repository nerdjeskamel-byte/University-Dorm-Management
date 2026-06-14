#include "dormitory.h"

Dormitory::Dormitory(std::string dormName)
{
    this->dormName = dormName;
}

std::string Dormitory::getDormName() const
{
    return dormName;
}

void Dormitory::setDormName(std::string dormName)
{
    this->dormName = dormName;
}

void Dormitory::addRoom(const Room& room)
{
    roomsList.push_back(room);
}

bool Dormitory::allocateStudent(const Student& student, int roomNumber)
{
    for (auto& room : roomsList)
    {
        if (room.getRoomNumber() == roomNumber)
        {
            return room.addStudent(student);
        }
    }
    return false;
}

bool Dormitory::removeStudentFromRoom(std::string studentId)
{
    for (auto& room : roomsList)
    {
        if (room.removeStudent(studentId))
        {
            return true;
        }
    }
    return false;
}

std::vector<Room>& Dormitory::getRooms()
{
    return roomsList;
}

const std::vector<Room>& Dormitory::getRooms() const
{
    return roomsList;
}

Restaurant& Dormitory::getRestaurant()
{
    return dormRestaurant;
}

const Restaurant& Dormitory::getRestaurant() const
{
    return dormRestaurant;
}