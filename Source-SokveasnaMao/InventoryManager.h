#pragma once
#include "Inventory.h"
#include "validation.h"

class InventoryManager
{
private:
	Inventory* inventory;
	int option;
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
