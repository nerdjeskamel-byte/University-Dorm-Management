#include "universitysystem.h" // 👈
#include <fstream>
#include <sstream>

UniversitySystem::UniversitySystem() {
    loadData();
}

void UniversitySystem::registerStudent(const Student& student) {
    for (const auto& s : allStudents) {
        if (s.getId() == student.getId()) {
            return;
        }
    }
    allStudents.push_back(student);
}

bool UniversitySystem::removeStudent(std::string studentId) {
    for (auto& dorm : allDormitories) {
        dorm.removeStudentFromRoom(studentId);
    }
    for (auto it = allStudents.begin(); it != allStudents.end(); ++it) {
        if (it->getId() == studentId) {
            allStudents.erase(it);
            return true;
        }
    }
    return false;
}

void UniversitySystem::addDormitory(const Dormitory& dormitory) {
    allDormitories.push_back(dormitory);
}

bool UniversitySystem::assignStudentToDorm(std::string studentId, std::string dormitoryName, int roomNumber) {
    for (auto& student : allStudents) {
        if (student.getId() == studentId && !student.getAccommodationStatus()) {
            for (auto& dorm : allDormitories) {
                if (dorm.getDormName() == dormitoryName) {
                    if (dorm.allocateStudent(student, roomNumber)) {
                        student.setAccommodationStatus(true);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void UniversitySystem::saveData() {
    std::ofstream file("students.txt");
    if (!file.is_open()) return;
    for (const auto& student : allStudents) {
        file << student.getId() << ","
             << student.getName() << ","
             << student.getAcademicYear() << ","
             << student.getAccommodationStatus() << "\n";
    }
    file.close();
}

void UniversitySystem::loadData() {
    std::ifstream file("students.txt");
    if (!file.is_open()) return;
    allStudents.clear();
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string id, name, year, status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, year, ',');
        getline(ss, status, ',');
        if (!id.empty()) {
            Student s(id, name, year);
            if (status == "1") {
                s.setAccommodationStatus(true);
            }
            allStudents.push_back(s);
        }
    }
    file.close();
}

std::vector<Student>& UniversitySystem::getAllStudents() {
    return allStudents;
}

std::vector<Dormitory>& UniversitySystem::getAllDormitories() {
    return allDormitories;
}