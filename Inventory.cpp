#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cctype>

using namespace std;

Inventory::Inventory()
{
    itemID = "";
    itemName = "";
    category = "";
    quantity = 0;
    unitPrice = 0.0;
    reorderLevel = 0;
    items = nullptr;
    itemCount = 0;
    fileName = "";
    isModified = false;
}

Inventory::Inventory(string file)
{
    itemID = "";
    itemName = "";
    category = "";
    quantity = 0;
    unitPrice = 0.0;
    reorderLevel = 0;
    items = new Inventory[MAX_SIZE];
    itemCount = 0;
    fileName = file;
    isModified = false;
}

Inventory::Inventory(string id, string name, string cat, int qty, double price, int reorder)
{
    itemID = id;
    itemName = name;
    category = cat;
    quantity = qty;
    unitPrice = price;
    reorderLevel = reorder;
    items = nullptr;
    itemCount = 0;
    fileName = "";
    isModified = false;
}

Inventory::Inventory(const Inventory &other)
{
    itemID = other.itemID;
    itemName = other.itemName;
    category = other.category;
    quantity = other.quantity;
    unitPrice = other.unitPrice;
    reorderLevel = other.reorderLevel;
    itemCount = other.itemCount;
    fileName = other.fileName;
    isModified = other.isModified;

    if (other.items != nullptr)
    {
        items = new Inventory[MAX_SIZE];
        for (int i = 0; i < itemCount; i++)
        {
            items[i] = other.items[i];
        }
    }
    else
    {
        items = nullptr;
    }
}

Inventory &Inventory::operator=(const Inventory &other)
{
    if (this == &other)
        return *this;

    itemID = other.itemID;
    itemName = other.itemName;
    category = other.category;
    quantity = other.quantity;
    unitPrice = other.unitPrice;
    reorderLevel = other.reorderLevel;
    itemCount = other.itemCount;
    fileName = other.fileName;
    isModified = other.isModified;

    delete[] items;
    if (other.items != nullptr)
    {
        items = new Inventory[MAX_SIZE];
        for (int i = 0; i < itemCount; i++)
        {
            items[i] = other.items[i];
        }
    }
    else
    {
        items = nullptr;
    }

    return *this;
}

Inventory::~Inventory()
{
    delete[] items;
}

string Inventory::getItemID() const { return itemID; }
string Inventory::getItemName() const { return itemName; }
string Inventory::getCategory() const { return category; }
int Inventory::getQuantity() const { return quantity; }
double Inventory::getUnitPrice() const { return unitPrice; }
int Inventory::getReorderLevel() const { return reorderLevel; }
string Inventory::getFileName() const { return fileName; }
bool Inventory::getIsModified() const { return isModified; }

void Inventory::setItemName(string name) { this->itemName = name; }
void Inventory::setCategory(string cat) { category = cat; }
void Inventory::setQuantity(int qty) { quantity = qty; }
void Inventory::setUnitPrice(double price) { unitPrice = price; }
void Inventory::setReorderLevel(int level) { reorderLevel = level; }

bool Inventory::isLowStock() const
{
    return quantity <= reorderLevel;
}

void Inventory::displayItem() const
{
    cout << setw(8) << left << itemID << " "
         << setw(30) << left << itemName << " "
         << setw(10) << left << category << " "
         << setw(5) << left << quantity << " "
         << setw(12) << left << fixed << setprecision(2) << unitPrice << " "
         << setw(15) << left << reorderLevel << " "
         << setw(11) << left << (isLowStock() ? "Low" : "OK") << endl;
}

void Inventory::displayItemAt(int index) const
{
    if (index >= 0 && index < itemCount)
    {
        items[index].displayItem();
    }
}

string Inventory::toLower(string s) const
{
    for (size_t i = 0; i < s.length(); i++)
    {
        s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
    }
    return s;
}

int Inventory::getItemCount() const
{
    return itemCount;
}

void Inventory::printTableHeader() const
{
    cout << "ItemID |          Item Name           | Category | Qty | Unit Price | Reorder Level | Low Stock " << endl;
}

bool Inventory::loadFromFile()
{
    ifstream inFile(fileName);
    if (!inFile)
    {
        cout << "[Notice] Could not open file: " << fileName << " (Starting fresh).\n";
        isModified = false;
        return false;
    }

    string line;
    itemCount = 0;

    while (itemCount < MAX_SIZE && getline(inFile, line))
    {
        if (line.empty())
            continue;

        // Extract Item ID (first token)
        size_t firstSpace = line.find_first_of(" \t");
        if (firstSpace == string::npos)
            continue;
        string id = line.substr(0, firstSpace);
        string rest = line.substr(firstSpace + 1);

        // Extract Reorder Level (last token)
        size_t pos4 = rest.find_last_of(" \t");
        if (pos4 == string::npos)
            continue;
        int reorder = stoi(rest.substr(pos4 + 1));
        rest = rest.substr(0, pos4);

        // Extract Unit Price (second from last)
        size_t pos3 = rest.find_last_of(" \t");
        if (pos3 == string::npos)
            continue;
        double price = stod(rest.substr(pos3 + 1));
        rest = rest.substr(0, pos3);

        size_t pos2 = rest.find_last_of(" \t");
        if (pos2 == string::npos)
            continue;
        int qty = stoi(rest.substr(pos2 + 1));
        rest = rest.substr(0, pos2);

        size_t pos1 = rest.find_last_of(" \t");
        if (pos1 == string::npos)
            continue;
        string cat = rest.substr(pos1 + 1);
        string name = rest.substr(0, pos1);

        items[itemCount] = Inventory(id, name, cat, qty, price, reorder);
        itemCount++;
    }

    inFile.close();
    isModified = false;
    return true;
}

bool Inventory::saveToFile()
{
    if (!isModified)
    {
        return false;
    }

    ofstream outFile(fileName);
    if (!outFile)
    {
        cout << "[Error] Error opening the file for writing: " << fileName << endl;
        return false;
    }
    for (int i = 0; i < itemCount; i++)
    {
        outFile << items[i].getItemID() << " "
                << items[i].getItemName() << " "
                << items[i].getCategory() << " "
                << items[i].getQuantity() << " "
                << fixed << setprecision(2) << items[i].getUnitPrice() << " "
                << items[i].getReorderLevel() << "\n";
    }
    outFile.close();
    isModified = false;
    return true;
}

bool Inventory::addInventory(const Inventory &newItem)
{
    if (itemCount >= MAX_SIZE)
    {
        cout << "[Error] Inventory array is full!\n";
        return false;
    }
    if (binarySearchByID(newItem.getItemID()) != -1)
    {
        printTableHeader();
        cout << "[Error] Item ID '" << newItem.getItemID() << "' already exists!\n";
        return false;
    }
    items[itemCount++] = newItem;
    insertionSort(1, true);
    isModified = true;
    saveToFile();
    return true;
}

bool Inventory::updateInventory(string id)
{
    int index = binarySearchByID(id);
    if (index == -1)
    {
        cout << "[Error] Item ID '" << id << "' not found.\n";
        return false;
    }

    cout << "\nCurrent Item Details:\n";
    items[index].displayItem();

    string newName, newCat;
    int newQty, newReorder;
    double newPrice;
    bool edited = false;

    int choice = 0;
    cout << "-----------------------" << endl
         << " Update Inventory Menu " << endl
         << "-----------------------" << endl
         << "1. Item name" << endl
         << "2. Category" << endl
         << "3. Quantity" << endl
         << "4. Unit price" << endl
         << "5. Reorder Level" << endl
         << "0. Finish" << endl;

    bool loop = true;
    while (loop)
    {
        cout << "Enter your choice: ";
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
            cout << "\nEnter New Item Name (or '0' to keep [" << items[index].getItemName() << "]): ";
            getline(cin >> ws, newName);
            if (newName != "0" && newName != items[index].getItemName())
            {
                items[index].setItemName(newName);
                edited = true;
            }
            break;

        case 2:
            cout << "Enter New Category (or '0' to keep [" << items[index].getCategory() << "]): ";
            getline(cin >> ws, newCat);
            if (newCat != "0" && newCat != items[index].getCategory())
            {
                items[index].setCategory(newCat);
                edited = true;
            }
            break;

        case 3:
            do
            {
                cout << "Enter New Quantity (current: " << items[index].getQuantity() << "): ";
                cin >> newQty;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[Error] Invalid option. Please enter a number.\n";
                    continue;
                }

                if (newQty >= 0 && newQty != items[index].getQuantity())
                {
                    items[index].setQuantity(newQty);
                    edited = true;
                    break;
                }
            } while (true);
            break;

        case 4:
            do
            {
                cout << "Enter New Unit Price RM (current: " << items[index].getUnitPrice() << "): ";
                cin >> newPrice;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[Error] Invalid option. Please enter a number.\n";
                    continue;
                }
                if (newPrice >= 0 && newPrice != items[index].getUnitPrice())
                {
                    items[index].setUnitPrice(newPrice);
                    edited = true;
                    break;
                }
            } while (true);

            break;

        case 5:
            do
            {
                cout << "Enter New Reorder Level (current: " << items[index].getReorderLevel() << "): ";
                cin >> newReorder;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[Error] Invalid option. Please enter a number.\n";
                    continue;
                }
                if (newReorder >= 0 && newReorder != items[index].getReorderLevel())
                {
                    items[index].setReorderLevel(newReorder);
                    edited = true;
                    break;
                }
            } while (true);

            break;

        case 0:
            loop = false;
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }

    if (edited)
    {
        isModified = true;
        saveToFile();
        cout << "[Success] Item '" << id << "' updated and saved.\n";
    }
    else
    {
        cout << "[Notice] No changes made to item '" << id << "'. Original file unchanged.\n";
    }
    return true;
}

bool Inventory::deleteInventory(string id)
{
    int index = binarySearchByID(id);
    if (index == -1)
    {
        cout << "[Error] Item ID '" << id << "' not found.\n";
        return false;
    }
    for (int i = index; i < itemCount - 1; i++)
    {
        items[i] = items[i + 1];
    }
    itemCount--;
    isModified = true;
    saveToFile();
    cout << "[Success] Item '" << id << "' deleted from inventory.\n";
    return true;
}

bool Inventory::stockInOut(string id, int amount, bool isStockIn)
{
    int index = binarySearchByID(id);
    if (index == -1)
    {
        cout << "[Error] Item ID '" << id << "' not found.\n";
        return false;
    }
    if (amount <= 0)
    {
        cout << "[Error] Amount must be greater than 0.\n";
        return false;
    }

    int currentQty = items[index].getQuantity();
    if (isStockIn)
    {
        items[index].setQuantity(currentQty + amount);
        cout << "[Success] Stock-In complete. New quantity: " << items[index].getQuantity() << endl;
    }
    else
    {
        if (currentQty < amount)
        {
            cout << "[Error] Insufficient stock! Current stock is only " << currentQty << ".\n";
            return false;
        }
        items[index].setQuantity(currentQty - amount);
        cout << "[Success] Stock-Out complete. New quantity: " << items[index].getQuantity() << endl;
    }
    isModified = true;
    saveToFile();
    return true;
}

void Inventory::displayAllInventory() const
{
    if (itemCount == 0)
    {
        cout << "[Notice] Inventory is currently empty.\n";
        return;
    }
    printTableHeader();
    double totalValue = 0;
    for (int i = 0; i < itemCount; i++)
    {
        items[i].displayItem();
        totalValue += items[i].getQuantity() * items[i].getUnitPrice();
    }
    cout << string(102, '-') << endl;
    cout << "Total Unique Items: " << itemCount
         << " | Total Inventory Value: RM " << fixed << setprecision(2) << totalValue << endl;
}

void Inventory::displayLowStockAlerts() const
{
    cout << "\n=== LOW STOCK ALERT REPORT (Quantity <= Reorder Level) ===\n";
    printTableHeader();
    int lowCount = 0;
    for (int i = 0; i < itemCount; i++)
    {
        if (items[i].isLowStock())
        {
            items[i].displayItem();
            lowCount++;
        }
    }
    if (lowCount == 0)
    {
        cout << "All items are well-stocked above reorder levels.\n";
    }
    else
    {
        cout << string(102, '-') << endl;
        cout << "Total Low-Stock Items Requiring Restock: " << lowCount << endl;
    }
}

void Inventory::selectionSort(int criteria, bool silent)
{
    long long comparisons = 0;
    long long swaps = 0;
    clock_t start = clock();

    for (int i = 0; i < itemCount - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < itemCount; j++)
        {
            comparisons++;
            bool isSmaller = false;

            if (criteria == 1)
                isSmaller = (items[j].getItemID() < items[minIndex].getItemID());
            else if (criteria == 2)
                isSmaller = (items[j].getUnitPrice() < items[minIndex].getUnitPrice());
            else if (criteria == 3)
                isSmaller = (items[j].getQuantity() < items[minIndex].getQuantity());

            if (isSmaller)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            Inventory temp = items[i];
            items[i] = items[minIndex];
            items[minIndex] = temp;
            swaps++;
        }
    }

    clock_t stop = clock();
    double durationMs = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

    if (!silent)
    {
        cout << "\n[Selection Sort Completed]\n";
        cout << " -> Records Sorted : " << itemCount << "\n"
             << " -> Comparisons    : " << comparisons << "\n"
             << " -> Swaps          : " << swaps << "\n"
             << " -> Execution Time : " << fixed << setprecision(4) << durationMs << " ms\n";
    }
}

void Inventory::insertionSort(int criteria, bool silent)
{
    long long comparisons = 0;
    long long moves = 0;
    clock_t start = clock();

    for (int i = 1; i < itemCount; i++)
    {
        Inventory key = items[i];
        int j = i - 1;

        while (j >= 0)
        {
            comparisons++;
            bool shift = false;
            if (criteria == 1)
                shift = (items[j].getItemID() > key.getItemID());
            else if (criteria == 2)
                shift = (items[j].getUnitPrice() > key.getUnitPrice());
            else if (criteria == 3)
                shift = (items[j].getQuantity() > key.getQuantity());

            if (shift)
            {
                items[j + 1] = items[j];
                moves++;
                j--;
            }
            else
            {
                break;
            }
        }
        items[j + 1] = key;
    }

    clock_t stop = clock();
    double durationMs = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

    if (!silent)
    {
        cout << "\n[Insertion Sort Completed]\n";
        cout << " -> Records Sorted : " << itemCount << "\n"
             << " -> Comparisons    : " << comparisons << "\n"
             << " -> Moves/Shifts   : " << moves << "\n"
             << " -> Execution Time : " << fixed << setprecision(4) << durationMs << " ms\n";
    }
}

int Inventory::binarySearchByID(string targetID)
{
    insertionSort(1, true);

    long long comparisons = 0;
    clock_t start = clock();

    int low = 0, high = itemCount - 1;
    int foundIndex = -1;

    while (low <= high)
    {
        comparisons++;
        int mid = low + (high - low) / 2;

        if (items[mid].getItemID() == targetID)
        {
            foundIndex = mid;
            break;
        }
        else if (items[mid].getItemID() < targetID)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    clock_t stop = clock();
    double durationMs = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

    cout << "\n[Binary Search Metrics] Matches: " << (foundIndex != -1 ? 1 : 0)
         << " | Comparisons: " << comparisons
         << " | Time: " << fixed << setprecision(4) << durationMs << " ms\n";

    return foundIndex;
}

void Inventory::linearSearch(string keyword, bool searchByCategory) const
{
    long long comparisons = 0;
    clock_t start = clock();

    string keyLower = toLower(keyword);
    int matchCount = 0;

    cout << endl;
    printTableHeader();
    for (int i = 0; i < itemCount; i++)
    {
        comparisons++;
        string field = searchByCategory ? toLower(items[i].getCategory())
                                        : toLower(items[i].getItemName());
        if (field.find(keyLower) != string::npos)
        {
            items[i].displayItem();
            matchCount++;
        }
    }

    clock_t stop = clock();
    double durationMs = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

    if (matchCount == 0)
    {
        cout << "[Result] No matching records found for '" << keyword << "'.\n";
    }
    cout << "\n[Linear Search Metrics] Matches: " << matchCount
         << " | Comparisons: " << comparisons
         << " | Time: " << fixed << setprecision(4) << durationMs << " ms\n";
}