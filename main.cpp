#include <iostream>
#include "Inventory.h"
#include "Admin.h"
#include "Staff.h"

using namespace std;

int main() {

    // Use inventory_100 for 10 items (default)
    // Use inventory_500 for 100 items
    // Use inventory_1000 for 1000 items

    Inventory system("inventory_100.txt");
    if (system.loadFromFile()) {
        cout << "[System] Loaded " << system.getItemCount() << " records from '" << system.getFileName() << "'.\n";
    }

    // Array of Admin objects (size 10)
    Admin admins[MAX_ADMIN_SIZE];
    int adminCount = 0;
    admins[adminCount++] = Admin("ADM01", "Store Manager", "1234");
    admins[adminCount++] = Admin("ADM02", "Assistant Manager", "5678");

    // Array of Staff objects (size 50)
    Staff staffs[MAX_STAFF_SIZE];
    int staffCount = 0;
    staffs[staffCount++] = Staff("STF01", "Warehouse Staff", "Logistics");
    staffs[staffCount++] = Staff("STF02", "Inventory Clerk", "Operations");

    int roleChoice;
    do {
        cout << "\n*********************************************\n"
             << "      INVENTORY MANAGEMENT SYSTEM (A1)       \n"
             << "*********************************************\n"
             << "1. Login as Admin (e.g., ADM01 / PIN: 1234)\n"
             << "2. Login as Staff (e.g., STF01)\n"
             << "0. Exit System\n"
             << "---------------------------------------------\n"
             << "Select User Role: ";
        cin >> roleChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Invalid option. Please enter a number.\n";
            roleChoice = -1;
            continue;
        }

        if (roleChoice == 1) {
            string id, pass;
            cout << "Enter Admin ID: ";
            cin >> id;

            int adminIndex = -1;
            for (int i = 0; i < adminCount; i++) {
                if (admins[i].getUserID() == id) {
                    adminIndex = i;
                    break;
                }
            }

            if (adminIndex == -1) {
                cout << "[Access Denied] Admin ID not found.\n";
            } else {
                cout << "Enter Admin PIN: ";
                cin >> pass;
                if (admins[adminIndex].verifyPass(pass)) {
                    admins[adminIndex].displayMenu(system, staffs, staffCount);
                } else {
                    cout << "[Access Denied] Incorrect Admin PIN.\n";
                }
            }
        } else if (roleChoice == 2) {
            string id;
            cout << "Enter Staff ID: ";
            cin >> id;

            int staffIndex = -1;
            for (int i = 0; i < staffCount; i++) {
                if (staffs[i].getUserID() == id) {
                    staffIndex = i;
                    break;
                }
            }

            if (staffIndex == -1) {
                cout << "[Access Denied] Staff ID not found.\n";
            } else {
                staffs[staffIndex].displayMenu(system);
            }
        } else if (roleChoice == 0) {
            if (system.getIsModified()) {
                system.saveToFile();
                cout << "[System] All changes saved to '" << system.getFileName() << "'. Goodbye!\n";
            } else {
                cout << "[System] Exiting system. Original file '" << system.getFileName() << "' was not altered. Goodbye!\n";
            }
        } else {
            cout << "[Error] Invalid selection. Please choose 1, 2, or 0.\n";
        }
    } while (roleChoice != 0);

    return 0;
}