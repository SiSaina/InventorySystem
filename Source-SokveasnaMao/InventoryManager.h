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
	InventoryManager();
	~InventoryManager();

	void DisplayInventory();
	void SortInventory();
	void AddItem();
	void EditItem();
	void DeleteItem();
	void LoadInventory();
	void SaveInventory();

	void DisplayItemPositionMenu();
	void DisplayItemTypeMenu();
	void DisplaySearchMenu();
	void DisplayAttributeMenu();
	void DisplayMenu();
	void DisplayMDSHeader();
	
	void Run();
};
