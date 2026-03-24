#pragma once
#include "ItemList.h"
class Inventory
{
private:
	ItemList* list;
public:
	Inventory();
	~Inventory();

	void AddItem(const Item& item);
	bool DeleteItem(int id);

	ItemNode* SearchById(int id);
	ItemNode* SearchByName(string name);

	void SortById();
	void SortByName();
	void SortByPrice();
	void SortByQuantity();

	void Display() const;

	void LoadFromFile(const string& filename);
	void SaveToFile(const string& filename);
};

