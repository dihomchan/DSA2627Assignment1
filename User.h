#ifndef USER_H
#define USER_H

#include "Inventory.h"
#include <string>

using namespace std;

class User {
protected:
    string userID;
    string username;
    string role;

public:
    User();
    User(string id, string name, string r);
    virtual ~User();

    string getUserID() const;
    string getUsername() const;
    string getRole() const;
    void setUsername(string name);

    virtual void displayMenu(Inventory &sys) = 0;

    void searchMenu(Inventory &sys);
    void sortMenu(Inventory &sys);
};

#endif