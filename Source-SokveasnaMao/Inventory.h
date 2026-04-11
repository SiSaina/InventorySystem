#pragma once
#include "ItemList.h"
#include "Validation.h"
#include <iostream>
class Inventory
{
	// function header is a header that tell what the function is used for and what parameters it takes, and the result
private:
	ItemList* itemList;
public:
	// constructor and destructor
	Inventory();
	~Inventory();

	// display inventory
	void DisplayInventory() const;

	// add doublely linked list node to inventory at the head, tail, or body
	void AddItemToHead(const Item& item);
	void AddItemToTail(const Item& item);
	void AddItemToBody(const Item& item, int position);

	// delete doublely linked list node from inventory at the head, tail, or body
	void DeleteItemFromHead();
	void DeleteItemFromTail();
	void DeleteItemFromBody(int position);
	
	// search for a node by name or position, return the node if found, otherwise return nullptr
	ItemNode* SearchByName(string name);
	ItemNode* SearchByPosition(int position);

	// find the position of a node, return position, and -1 if not found
	int GetNodePosition(ItemNode* node) const;

	// swap two whole nodes by their pointers, not by their values
	void SwapNodes(ItemNode* a, ItemNode* b);

	// compare two nodes by their attributes, return true if a should be before b, otherwise return false
	bool CompareNode(const Item& a, const Item& b, int attribute, bool order);

	// partition the list for quicksort, return the pivot node
	ItemNode* PartitionAccending(ItemNode* first, ItemNode* last, int attribute);
	ItemNode* PartitionDescending(ItemNode* first, ItemNode* last, int attribute);

	// quicksort the list by the given attribute and order, order = 1 for accending, 2 for decending
	void QuickSortAccending(ItemNode* first, ItemNode* last, int attribute);
	void QuickSortDescending(ItemNode* first, ItemNode* last, int attribute);
	void QuickSort(int attribute, int order);

	// get the number of items in the inventory
	int GetItemCount() const { return itemList->NumNodes(); };
	// clear all nodes in the inventory, used for loading from file
	void ClearAllNodes();

	// load inventory from file (specific or default), return true if successful, otherwise return false
	bool LoadFromFile(const string& filename);
	// save inventory to file (specific or default), return true if successful, otherwise return false
	bool SaveToFile(const string& filename);
};

