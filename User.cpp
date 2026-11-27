#include "User.h"
#include "Inventory.h"
#include <iostream>

using namespace std;

User::User() {
    userID = "";
    username = "";
    role = "";
}

User::User(string id, string name, string r) {
    userID = id;
    username = name;
    role = r;
}

User::~User() {}

string User::getUserID() const { return userID; }
string User::getUsername() const { return username; }
string User::getRole() const { return role; }
void User::setUsername(string name) { username = name; }

void User::searchMenu(Inventory& sys) {
    int choice;
    cout << "\n--- Search Inventory ---\n"
         << "1. Search by Item ID (Binary Search)\n"
         << "2. Search by Item Name (Linear Search)\n"
         << "3. Search by Category (Linear Search)\n"
         << "Enter choice: ";
    cin >> choice;

    string query;
    if (choice == 1) {
        cout << "Enter exact Item ID (e.g., I005): ";
        cin >> query;
        int idx = sys.binarySearchByID(query);
        if (idx != -1) {
            cout << endl;
            sys.printTableHeader();
            sys.displayItemAt(idx);
        } else {
            cout << "[Result] No item found with ID '" << query << "'.\n";
        }
    } else if (choice == 2) {
        cout << "Enter Item Name keyword: ";
        getline(cin >> ws, query);
        sys.linearSearch(query, false);
    } else if (choice == 3) {
        cout << "Enter Category keyword: ";
        getline(cin >> ws, query);
        sys.linearSearch(query, true);
    } else {
        cout << "[Error] Invalid search option.\n";
    }
}

void User::sortMenu(Inventory& sys) {
    int sort, criteria;
    cout << "\n--- Sort Inventory ---\n"
         << "Select Algorithm:\n"
         << "1. Selection Sort\n"
         << "2. Insertion Sort\n"
         << "Enter choice: ";
    cin >> sort;

    cout << "\nSelect Sort Criteria:\n"
         << "1. Sort by Item ID (Ascending)\n"
         << "2. Sort by Unit Price (Ascending)\n"
         << "3. Sort by Quantity (Ascending)\n"
         << "Enter choice: ";
    cin >> criteria;

    if (criteria < 1 || criteria > 3) {
        cout << "[Error] Invalid criteria.\n";
        return;
    }

    if (sort == 1) sys.selectionSort(criteria);
    else if (sort == 2) sys.insertionSort(criteria);
    else {
        cout << "[Error] Invalid algorithm choice.\n";
        return;
    }
    sys.displayAllInventory();
}