#pragma once
#include "Inventory.h"
#include "validation.h"
#include <iostream>

using namespace std;

// Minimun allowed values
const int MIN_NAME_LENGTH = 1;
const float MIN_PRICE = 0.1f;
const int MIN_QUANTITY = 1;

// Maximun allowed values
const int MAX_NAME_LENGTH = 50;
const float MAX_PRICE = 10000.0f;
const int MAX_QUANTITY = 1000;

class InventoryManager
{
private:
	Inventory inventory;
public:

	// ++++++++++++++++++++++++++++++++++
	// Core Functions
	// ++++++++++++++++++++++++++++++++++

	// display all items in the inventory
	void DisplayInventory();
	// sort inventory by attribute and order
	void SortInventory();

	// add item to inventory, user choose position (head, tail, or body)
	void AddItem();

	// edit item property (name, type, price, quantity)
	// can search by name or position
	// if not exist, display error message
	void EditItem();

	// delete item, user choose position (head, tail, or body) 
	// search by name or position
	// if not exist, display error message
	void DeleteItem();

	// load inventory from file (specific or default path)
	// if file not exist, display error message
	void LoadInventory();
	// save inventory to file (specific or default path)
	// if file not exist, display error message
	void SaveInventory();


	// ++++++++++++++++++++++++++++++++++
	// UI/Menu Functions
	// ++++++++++++++++++++++++++++++++++

	// clear screen
	void ClearScreen();

	// display file menu, specific file or default file
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
	
	// ++++++++++++++++++++++++++++++++++
	// Main program runner
	// ++++++++++++++++++++++++++++++++++
	
	// start and control the main program loop
	void Run();
};
