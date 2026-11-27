#ifndef STAFF_H
#define STAFF_H

#include "User.h"
#include <string>

using namespace std;

const int MAX_STAFF_SIZE = 50;

class Staff : public User {
private:
    string department;

public:
    Staff();
    Staff(string id, string name, string dept);

    string getDepartment() const;
    void setDepartment(string dept);
    void displayStaffInfo() const;

    void displayMenu(Inventory &sys) override;
};

#endif