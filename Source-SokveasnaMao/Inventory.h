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

	void SwapNodes(ItemNode* a, ItemNode* b);
	bool CompareNode(const Item& a, const Item& b, int attribute, bool order);
	ItemNode* PartitionAccending(ItemNode* first, ItemNode* last, int attribute);
	ItemNode* PartitionDescending(ItemNode* first, ItemNode* last, int attribute);

	void QuickSortAccending(ItemNode* first, ItemNode* last, int attribute);
	void QuickSortDescending(ItemNode* first, ItemNode* last, int attribute);
	void QuickSort(int attribute, int order);

	int GetItemCount() const { return itemList->NumNodes(); };

	void LoadFromFile(const string& filename);
	void SaveToFile(const string& filename);
};

