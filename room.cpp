#include "Room.h"

Room::Room(
    int roomNumber,
    int capacity)
{
    this->roomNumber = roomNumber;
    this->capacity = capacity;
}

int Room::getRoomNumber() const
{
    return roomNumber;
}



int Room::getAvailableSlots() const
{
    return capacity -
           static_cast<int>(
               studentsList.size());
}

bool Room::isFull() const
{
    return studentsList.size() >=
           static_cast<size_t>(capacity);
}

bool Room::addStudent(
    const Student& student)
{
    if (isFull())
    {
        return false;
    }

    studentsList.push_back(student);

    return true;
}

bool Room::removeStudent(
    std::string studentId)
{
    for (auto it = studentsList.begin();
         it != studentsList.end();
         ++it)
    {
        if (it->getId() == studentId)
        {
            studentsList.erase(it);
            return true;
        }
    }

    return false;
}

int Room::getCapacity() const {
    return capacity;
}

std::vector<Student> Room::getStudents() const {
    return studentsList; }