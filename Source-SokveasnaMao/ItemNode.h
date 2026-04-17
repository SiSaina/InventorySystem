#pragma once
#include "Item.h"
#include <iostream>
class ItemNode
{
private:
	Item item;
	ItemNode* next;
	ItemNode* prev;
public:
	ItemNode();
	~ItemNode();

	// use & to pass by reference, and directly modification
	Item& GetItem();
	// read-only access
	const Item& GetItem() const;
	ItemNode* GetNext() const;
	ItemNode* GetPrev() const;

	void SetItem(Item& item);
	void SetNext(ItemNode* next);
	void SetPrev(ItemNode* prev);

	void DisplayNode() const;
};
