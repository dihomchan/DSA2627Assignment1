#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

using namespace std;

const int MAX_SIZE = 3000;

class Inventory
{
private:
    string itemID;
    string itemName;
    string category;
    int quantity;
    double unitPrice;
    int reorderLevel;
    Inventory* items;
    int itemCount;
    string fileName;
    bool isModified;
public:
    Inventory();
    Inventory(string file);
    Inventory(string id, string name, string cat, int qty, double price, int reorder);
    Inventory(const Inventory& other);
    Inventory& operator=(const Inventory& other);
    ~Inventory();

    string getItemID() const;
    string getItemName() const;
    string getCategory() const;
    int getQuantity() const;
    double getUnitPrice() const;
    int getReorderLevel() const;
    string getFileName() const;
    bool getIsModified() const;

    void setItemName(string name);
    void setCategory(string cat);
    void setQuantity(int qty);
    void setUnitPrice(double price);
    void setReorderLevel(int level);

    bool isLowStock() const;
    void displayItem() const;
    void displayItemAt(int index) const;
    string toLower(string s) const;

    void printTableHeader() const;
    int getItemCount() const;
    bool loadFromFile();
    bool saveToFile();

    bool addInventory(const Inventory &newItem);
    bool updateInventory(string id);
    bool deleteInventory(string id);
    bool stockInOut(string id, int amount, bool isStockIn);

    void displayAllInventory() const;
    void displayLowStockAlerts() const;

    void linearSearch(string keyword, bool searchByCategory) const;
    int binarySearchByID(string targetID);

    void selectionSort(int criteria, bool silent = false);
    void insertionSort(int criteria, bool silent = false);
};

#endif