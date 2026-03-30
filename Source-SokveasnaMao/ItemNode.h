#pragma once
#include "Item.h"
class ItemNode
{
private:
	Item item;
	ItemNode* next;
	ItemNode* prev;
public:
	ItemNode() {
		item = Item();
		next = nullptr;
		prev = nullptr;
	};
	~ItemNode() {
		next = nullptr;
		prev = nullptr;
	};

	// use & to pass by reference
	Item& GetItem() { return item; };
	// read-only
	const Item& GetItem() const { return item; };

	ItemNode* GetNext() const { return next; };
	ItemNode* GetPrev() const { return prev; };

	void SetItem(Item item) { this->item = item; };
	void SetNext(ItemNode* next) { this->next = next; };
	void SetPrev(ItemNode* prev) { this->prev = prev; };
};
