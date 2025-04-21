#include "staff.h"
#include <stdexcept>

// Constructor
Staff::Staff(int id, std::string name, std::string position) 
    : staffID(id), name(name), position(position), isActive(true) {
    if (id <= 0) throw std::invalid_argument("Staff ID must be positive");
    if (name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (position.empty()) throw std::invalid_argument("Position cannot be empty");
}

// Getters
int Staff::getStaffID() const {
    return staffID;
}

std::string Staff::getName() const {
    return name;
}

std::string Staff::getPosition() const {
    return position;
}

bool Staff::getIsActive() const {
    return isActive;
}

// Setters
void Staff::setName(std::string newName) {
    if (newName.empty()) {
        throw std::invalid_argument("Name cannot be empty");
    }
    name = newName;
}

void Staff::setPosition(std::string newPosition) {
    if (newPosition.empty()) {
        throw std::invalid_argument("Position cannot be empty");
    }
    position = newPosition;
}

void Staff::setIsActive(bool active) {
    isActive = active;
}

// Other methods
void printStaffMember(Staff& staffMember) {
    std::cout << "Employee ID: " << staffMember.getStaffID() << ", Name: " << staffMember.getName() << ", Position: " << staffMember.getPosition() << ", Currently active?: " << staffMember.getIsActive();
}
