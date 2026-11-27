#include "Admin.h"
#include <iostream>
#include <iomanip>

using namespace std;

Admin::Admin() : User("", "", "Admin")
{
    adminPass = "";
}

Admin::Admin(string id, string name, string pass)
    : User(id, name, "Admin")
{
    adminPass = pass;
}

bool Admin::verifyPass(string inputPass) const
{
    return inputPass == adminPass;
}

void Admin::addNewItem(Inventory &sys)
{
    string id, name, cat;
    int qty, reorder;
    double price;

    do
    {
        cout << "\n--- Add New Inventory Item ---\n";
        cout << "Enter Item ID (e.g., I011): ";
        cin >> id;
        cout << "Enter Item Name: ";
        getline(cin >> ws, name);
        cout << "Enter Category: ";
        getline(cin >> ws, cat);
        do
        {
            cout << "Enter Initial Quantity: ";
            cin >> qty;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "[Error] Quantity only can be integer.\n";
                continue;
            }
            do
            {
                cout << "Enter Unit Price (RM): ";
                cin >> price;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[Error] Price only can be integer.\n";
                    continue;
                }
                do
                {
                    cout << "Enter Reorder Level: ";
                    cin >> reorder;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "[Error] Reorder only can be integer.\n";
                        continue;
                    }
                    break;
                } while (true);
                break;
            } while (true);
            break;
        } while (true);

        if (qty < 0 || price < 0 || reorder < 0)
        {
            cout << "[Error] Quantity, price, and reorder level cannot be negative.\n";
            return;
        }
        break;
    } while (true);

    Inventory newItem(id, name, cat, qty, price, reorder);
    if (sys.addInventory(newItem))
    {
        cout << "[Success] Item added and saved to file.\n";
    }
}

void Admin::editItem(Inventory &sys)
{
    string id;
    cout << "\nEnter Item ID to update: ";
    cin >> id;
    sys.updateInventory(id);
}

void Admin::removeItem(Inventory &sys)
{
    string id;
    cout << "\nEnter Item ID to delete: ";
    cin >> id;
    sys.deleteInventory(id);
}

void Admin::manageStockMovement(Inventory &sys)
{
    string id;
    int type, amount;
    do
    {
        cout << "\n--- Stock-In / Stock-Out Management ---\n";
        cout << "Enter Item ID: ";
        cin >> id;
        cout << "1. Stock-In (Restock)\n"
             << "2. Stock-Out (Issue/Sale)\n"
             << "0. Back\n"
             << "Select type (0 - 2): ";
        cin >> type;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Invalid option. Please enter a number.\n";
            continue;
        }
        if (type == 0) break;
        
        cout << "Enter Quantity Amount: ";
        cin >> amount;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Invalid option. Please enter a number.\n";
            continue;
        }

        if (type == 1){
            sys.stockInOut(id, amount, true);
            break;
        }
        else if (type == 2){
            sys.stockInOut(id, amount, false);
            break;
        }
    } while (type != 0);
}

void Admin::viewAllStaff(const Staff staffs[], int staffCount) const
{
    if (staffCount == 0)
    {
        cout << "\n[Notice] No staff records found.\n";
        return;
    }

    cout << "\n---------------------------------------------------------\n";
    cout << left << setw(12) << "Staff ID"
         << setw(25) << "Name"
         << setw(20) << "Department" << endl;
    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < staffCount; i++)
    {
        staffs[i].displayStaffInfo();
    }
    cout << "---------------------------------------------------------\n";
    cout << "Total Staff: " << staffCount << " / " << MAX_STAFF_SIZE << endl;
}

void Admin::addNewStaff(Staff staffs[], int &staffCount)
{
    if (staffCount >= MAX_STAFF_SIZE)
    {
        cout << "[Error] Staff array is full (Maximum " << MAX_STAFF_SIZE << " staff).\n";
        return;
    }

    string id, name, dept;
    cout << "\n--- Add New Staff ---\n";
    cout << "Enter Staff ID (e.g., STF03): ";
    cin >> id;

    for (int i = 0; i < staffCount; i++)
    {
        if (staffs[i].getUserID() == id)
        {
            cout << "[Error] Staff ID '" << id << "' already exists!\n";
            return;
        }
    }

    cout << "Enter Staff Name: ";
    getline(cin >> ws, name);
    cout << "Enter Department: ";
    getline(cin >> ws, dept);

    staffs[staffCount] = Staff(id, name, dept);
    staffCount++;
    cout << "[Success] Staff '" << name << "' (" << id << ") added.\n";
}

void Admin::editStaff(Staff staffs[], int staffCount)
{
    if (staffCount == 0)
    {
        cout << "[Notice] No staff records to edit.\n";
        return;
    }

    string id;
    cout << "\nEnter Staff ID to update: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < staffCount; i++)
    {
        if (staffs[i].getUserID() == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "[Error] Staff ID '" << id << "' not found.\n";
        return;
    }

    int choice;
    do
    {
        cout << "\n--- Update Staff (" << staffs[index].getUserID() << ") ---\n"
             << "1. Update Name (Current: " << staffs[index].getUsername() << ")\n"
             << "2. Update Department (Current: " << staffs[index].getDepartment() << ")\n"
             << "0. Finish\n"
             << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Invalid option. Please enter a number.\n";
            choice = -1;
            continue;
        }

        if (choice == 1)
        {
            string newName;
            cout << "Enter New Name: ";
            getline(cin >> ws, newName);
            staffs[index].setUsername(newName);
            cout << "[Success] Staff name updated.\n";
        }
        else if (choice == 2)
        {
            string newDept;
            cout << "Enter New Department: ";
            getline(cin >> ws, newDept);
            staffs[index].setDepartment(newDept);
            cout << "[Success] Staff department updated.\n";
            break;
        }
        else if (choice != 0)
        {
            cout << "[Error] Invalid option.\n";
        }
    } while (choice != 0);
}

void Admin::removeStaff(Staff staffs[], int &staffCount)
{
    if (staffCount == 0)
    {
        cout << "[Notice] No staff records to delete.\n";
        return;
    }

    string id;
    cout << "\nEnter Staff ID to delete: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < staffCount; i++)
    {
        if (staffs[i].getUserID() == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "[Error] Staff ID '" << id << "' not found.\n";
        return;
    }

    for (int i = index; i < staffCount - 1; i++)
    {
        staffs[i] = staffs[i + 1];
    }
    staffCount--;
    cout << "[Success] Staff '" << id << "' deleted.\n";
}

void Admin::manageStaffMenu(Staff staffs[], int &staffCount)
{
    int choice;
    do
    {
        cout << "\n---------------------------------------------\n"
             << "   STAFF MANAGEMENT MENU (" << username << ")\n"
             << "---------------------------------------------\n"
             << "1. View All Staff\n"
             << "2. Add New Staff\n"
             << "3. Update Staff Details\n"
             << "4. Delete Staff\n"
             << "0. Back to Admin Menu\n"
             << "---------------------------------------------\n"
             << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Invalid option. Try again.\n";
            choice = -1;
            continue;
        }

        switch (choice)
        {
        case 1:
            viewAllStaff(staffs, staffCount);
            break;
        case 2:
            addNewStaff(staffs, staffCount);
            break;
        case 3:
            editStaff(staffs, staffCount);
            break;
        case 4:
            removeStaff(staffs, staffCount);
            break;
        case 0:
            break;
        default:
            cout << "[Error] Invalid option. Try again.\n";
        }
    } while (choice != 0);
}

void Admin::displayMenu(Inventory &sys)
{
    Staff dummyStaffs[MAX_STAFF_SIZE];
    int dummyCount = 0;
    displayMenu(sys, dummyStaffs, dummyCount);
}

void Admin::displayMenu(Inventory &sys, Staff staffs[], int &staffCount)
{
    int choice;
    do
    {
        cout << "\n=============================================\n"
             << "   ADMIN MENU (" << username << ")\n"
             << "=============================================\n"
             << "1. View All Inventory\n"
             << "2. Add New Inventory Item\n"
             << "3. Update Inventory Details\n"
             << "4. Delete Inventory Item\n"
             << "5. Record Stock-In / Stock-Out\n"
             << "6. Search Inventory (Binary / Linear)\n"
             << "7. Sort Inventory (Selection / Insertion)\n"
             << "8. Check Low Stock Alerts\n"
             << "9. Manage Staff\n"
             << "0. Logout to Main Menu\n"
             << "---------------------------------------------\n"
             << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[Error] Invalid option. Please enter a number.\n";
            choice = -1;
            continue;
        }

        switch (choice)
        {
        case 1:
            sys.displayAllInventory();
            break;
        case 2:
            addNewItem(sys);
            break;
        case 3:
            editItem(sys);
            break;
        case 4:
            removeItem(sys);
            break;
        case 5:
            manageStockMovement(sys);
            break;
        case 6:
            searchMenu(sys);
            break;
        case 7:
            sortMenu(sys);
            break;
        case 8:
            sys.displayLowStockAlerts();
            break;
        case 9:
            manageStaffMenu(staffs, staffCount);
            break;
        case 0:
            cout << "Logging out from Admin session...\n";
            break;
        default:
            cout << "[Error] Invalid option. Try again.\n";
        }
    } while (choice != 0);
}