#pragma once
#include "ItemList.h"
#include "Validation.h"
class Inventory
{
private:
	ItemList* itemList;
public:
	Inventory();
	~Inventory();

	void DisplayInventory() const;
	void AddItem(const Item& item);
	void DeleteItem(ItemNode* item);

	ItemNode* SearchByName(string name);
	ItemNode* SearchByPosition(int position);

	static pair<ItemNode*, ItemNode*> FindNodeToSwap(ItemNode*& head, int x, int y);
	void SwapNodes(ItemNode* a, ItemNode* b);

	int PartitionByName(int low, int high);
	void QuickSortByName();
	void QuickSortByPrice();
	void QuickSortByQuantity();

	int GetItemCount() const { return itemList->NumNodes(); };

	void LoadFromFile(const string& filename);
	void SaveToFile(const string& filename);
};

