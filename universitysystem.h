#ifndef UNIVERSITYSYSTEM_H
#define UNIVERSITYSYSTEM_H

#include <vector>
#include <string>
#include "student.h"
#include "dormitory.h"

class UniversitySystem
{
private:
    std::vector<Student> allStudents;
    std::vector<Dormitory> allDormitories;

public:
    UniversitySystem();

    void registerStudent(const Student& student);
    bool removeStudent(std::string studentId);
    void addDormitory(const Dormitory& dormitory);

    bool assignStudentToDorm(std::string studentId, std::string dormitoryName, int roomNumber);

    void saveData();
    void loadData();

    std::vector<Student>& getAllStudents();
    std::vector<Dormitory>& getAllDormitories();
};

#endif // UNIVERSITYSYSTEM_H