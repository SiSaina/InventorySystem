#pragma once
#include "ItemList.h"
class Inventory
{
private:
	ItemList* itemList;
public:
	Inventory();
	~Inventory();

	void AddItem(const Item& item);
	bool DeleteItem(int id);

	ItemNode* SearchById(int id);
	ItemNode* SearchByName(string name);

	static pair<ItemNode*, ItemNode*> FindNodeToSwap(ItemNode*& head, int x, int y);
	void SwapNode(ItemNode* head, ItemNode* tail, int x, int y);

	void QuickSortById();
	void QuickSortByName();
	void QuickSortByPrice();
	void QuickSortByQuantity();

	void Display() const;

	void LoadFromFile(const string& filename);
	void SaveToFile(const string& filename);
};

