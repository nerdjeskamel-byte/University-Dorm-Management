#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>

#include "Student.h"

class Room
{
private:
    int roomNumber;
    int capacity;

    std::vector<Student> studentsList;

public:
    Room(
        int roomNumber = 0,
        int capacity = 0);

    int getRoomNumber() const;



    int getAvailableSlots() const;

    bool isFull() const;

    bool addStudent(
        const Student& student);

    bool removeStudent(
        std::string studentId);



    int getCapacity() const; // 👈 زيادة const هنا
    std::vector<Student> getStudents() const; // 👈 زيادة const هنا


};

#endif