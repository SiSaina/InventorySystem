#pragma once
#include "ItemList.h"
class Inventory
{
private:
	ItemList* itemList;
public:
	Inventory();
	~Inventory();

	void DisplayInventory() const;
	void AddItem(const Item& item);
	bool DeleteItem(int id);

	ItemNode* SearchById(int id);
	ItemNode* SearchByName(string name);

	static pair<ItemNode*, ItemNode*> FindNodeToSwap(ItemNode*& head, int x, int y);
	void SwapNodes(ItemNode* a, ItemNode* b);

	int PartitionByName(int low, int high);
	void QuickSortByName();
	void QuickSortByPrice();
	void QuickSortByQuantity();

	void LoadFromFile(const string& filename);
	void SaveToFile(const string& filename);
};

