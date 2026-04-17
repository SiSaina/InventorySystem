#pragma once
#include "ItemList.h"
#include "Validation.h"
#include <fstream>
#include <sstream>
class Inventory
{
private:
	ItemList itemList;
public:
	// call function in itemlist to display inventory in table form
	void DisplayInventory();

	// add node to inventory at the head, tail, or body
	bool AddItemToHead(const Item& item);
	bool AddItemToTail(const Item& item);
	bool AddItemToBody(const Item& item, int position);

	// delete node from inventory at the head, tail, or body
	bool DeleteItemFromHead();
	bool DeleteItemFromTail();
	bool DeleteItemFromBody(int position);
	
	// search for a node by name or position, return the node if found, if not return nullptr
	// pass by reference to avoid copying string
	ItemNode* SearchByName(const string& name);
	ItemNode* SearchByPosition(int position);

	// find the position of a node, return position, if not return -1
	int GetNodePosition(ItemNode* node);

	// swap two nodes by their pointers
	void SwapNodes(ItemNode* a, ItemNode* b);
	// swap two nodes by values
	static void SwapNodesData(ItemNode* a, ItemNode* b);
	// compare two nodes by their attributes, return true if a should be before b, otherwise return false
	bool CompareNode(const Item a, const Item b, int attribute, bool order);

	// partition the list for quicksort
	// take first node, and last node
	// return the pivot node
	ItemNode* PartitionAscending(ItemNode* first, ItemNode* last, int attribute);
	ItemNode* PartitionDescending(ItemNode* first, ItemNode* last, int attribute);

	// quicksort the list by the given attribute and order, order = 1 for accending, 2 for decending
	void QuickSortAscending(ItemNode* first, ItemNode* last, int attribute);
	void QuickSortDescending(ItemNode* first, ItemNode* last, int attribute);
	// quicksort the list by the given attribute and order, return true if successful, otherwise return false
	bool QuickSort(int attribute, int order);

	// get the number of items in the inventory
	int GetItemCount() const;
	// clear all nodes in the inventory, used for loading from file
	void ClearAllNodes();

	// load inventory from file (specific or default), return true if successful, otherwise return false
	bool LoadFromFile(const string& filename);
	// save inventory to file (specific or default), return true if successful, otherwise return false
	bool SaveToFile(const string& filename);
};

