#ifndef DORMITORY_H
#define DORMITORY_H

#include <string>
#include <vector>
#include "room.h"
#include "restaurant.h"

class Dormitory
{
private:
    std::string dormName;
    std::vector<Room> roomsList;
    Restaurant dormRestaurant;

public:
    Dormitory(std::string dormName = "");

    std::string getDormName() const;
    void setDormName(std::string dormName);

    void addRoom(const Room& room);

    bool allocateStudent(const Student& student, int roomNumber);
    bool removeStudentFromRoom(std::string studentId);

    std::vector<Room>& getRooms();
    const std::vector<Room>& getRooms() const;

    Restaurant& getRestaurant();
 const Restaurant& getRestaurant() const;
};

#endif // DORMITORY_H