#pragma once
#include "Inventory.h"
#include "validation.h"
#include <iostream>

using namespace std;

const int MIN_NAME_LENGTH = 1;
const float MIN_PRICE = 0.1f;
const int MIN_QUANTITY = 1;

const int MAX_NAME_LENGTH = 50;
const float MAX_PRICE = 10000.0f;
const int MAX_QUANTITY = 1000;

class InventoryManager
{
private:
	Inventory* inventory;
public:
	// constructor and destructor
	InventoryManager();
	~InventoryManager();

	// display inventory
	void DisplayInventory();
	// sort inventory by attribute and order
	void SortInventory();
	// add item to inventory, head, tail, or body
	void AddItem();
	// edit item in inventory by position, if position not exist, display error message
	void EditItem();
	// delete item from inventory by position, head or tail, if position not exist, display error message
	void DeleteItem();
	// load inventory from file, if file not exist, display error message
	void LoadInventory();
	// save inventory to file, if file not exist, display error message
	void SaveInventory();

	// display file menu, specific file or default file, and get user choice, if user input invalid, display error message
	void DisplayFileMenu();
	// display item position menu, head, tail, or body
	void DisplayItemPositionMenu();
	// display type of item
	void DisplayItemTypeMenu();
	// display search menu, search by name or position
	void DisplaySearchMenu();
	// display attribute menu, name, type, price, or quantity
	void DisplayAttributeMenu();
	// display main menu
	void DisplayMenu();
	// display MDS header
	void DisplayMDSHeader();
	
	void Run();
};
