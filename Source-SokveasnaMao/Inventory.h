#pragma once
#include "ItemList.h"
#include "Validation.h"
#include <iostream>
class Inventory
{
private:
	ItemList* itemList;
public:
	Inventory();
	~Inventory();

	void DisplayInventory() const;

	void AddItemToHead(const Item& item);
	void AddItemToTail(const Item& item);
	void AddItemToBody(const Item& item, int position);

	void DeleteItemFromHead();
	void DeleteItemFromTail();
	void DeleteItemFromBody(int position);

	ItemNode* SearchByName(string name);
	ItemNode* SearchByPosition(int position);

	int GetNodePosition(ItemNode* node) const;
	bool FindExistNodeByPosition(int position) const;

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

