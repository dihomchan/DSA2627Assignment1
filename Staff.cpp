#include "Staff.h"
#include <iostream>
#include <iomanip>

using namespace std;

Staff::Staff() : User("", "", "Staff") {
    department = "";
}

Staff::Staff(string id, string name, string dept)
    : User(id, name, "Staff") {
    department = dept;
}

string Staff::getDepartment() const { return department; }
void Staff::setDepartment(string dept) { department = dept; }

void Staff::displayStaffInfo() const {
    cout << left << setw(12) << userID
         << setw(25) << username
         << setw(20) << department << endl;
}

void Staff::displayMenu(Inventory &sys) {
    int choice;
    do {
        cout << "\n=============================================\n"
             << "   STAFF MENU (" << username << " - " << department << ")\n"
             << "=============================================\n"
             << "1. View All Inventory\n"
             << "2. Search Inventory (Binary / Linear)\n"
             << "3. Sort Inventory (Selection / Insertion)\n"
             << "4. Check Low Stock Alerts\n"
             << "0. Logout to Main Menu\n"
             << "---------------------------------------------\n"
             << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Invalid option. Please enter a number.\n";
            choice = -1;
            continue;
        }
        
        switch (choice) {
            case 1: sys.displayAllInventory(); break;
            case 2: searchMenu(sys); break;
            case 3: sortMenu(sys); break;
            case 4: sys.displayLowStockAlerts(); break;
            case 0: cout << "Logging out from Staff session...\n"; break;
            default: cout << "[Error] Invalid option. Try again.\n";
        }
    } while (choice != 0);
}