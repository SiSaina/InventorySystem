#pragma once
#include "Inventory.h"
#include "validation.h"
#include <iostream>

using namespace std;

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

	void DisplaySearchMenu();
	void DisplayAttributeMenu();
	void DisplayMenu();
	void DisplayMDSHeader();
	
	void Run();
};
