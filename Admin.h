#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Staff.h"
#include <string>

using namespace std;

const int MAX_ADMIN_SIZE = 10;

class Admin : public User {
private:
    string adminPass;

public:
    Admin();
    Admin(string id, string name, string pass);

    bool verifyPass(string inputPass) const;

    // Inventory management
    void addNewItem(Inventory& sys);
    void editItem(Inventory& sys);
    void removeItem(Inventory& sys);
    void manageStockMovement(Inventory& sys);

    // Staff management
    void manageStaffMenu(Staff staffs[], int& staffCount);
    void viewAllStaff(const Staff staffs[], int staffCount) const;
    void addNewStaff(Staff staffs[], int& staffCount);
    void editStaff(Staff staffs[], int staffCount);
    void removeStaff(Staff staffs[], int& staffCount);

    void displayMenu(Inventory& sys) override;
    void displayMenu(Inventory& sys, Staff staffs[], int& staffCount);
};

#endif