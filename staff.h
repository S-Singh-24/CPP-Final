#ifndef STAFF_H
#define STAFF_H

#include <string>

class Staff {
private:
    int staffID;
    std::string name;
    std::string position;
    bool isActive;
    
public:
    // Constructor
    Staff(int id, std::string name, std::string position);
    
    // Getters
    int getStaffID() const;
    std::string getName() const;
    std::string getPosition() const;
    bool getIsActive() const;
    
    // Setters
    void setName(std::string newName);
    void setPosition(std::string newPosition);
    void setIsActive(bool active);

    // Other methods
    void printStaffMember(Staff& staffMember);

};

#endif // STAFF_H
