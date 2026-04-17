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

	// use & to pass by reference, and directly modification
	Item& GetItem() { return item; };
	// read-only access
	const Item& GetItem() const { return item; };

	ItemNode* GetNext() const { return next; };
	ItemNode* GetPrev() const { return prev; };

	void SetItem(Item& item) { this->item = item; };
	void SetNext(ItemNode* next) { this->next = next; };
	void SetPrev(ItemNode* prev) { this->prev = prev; };

	void DisplayNode() const {
		cout << "------------------------" << endl;
		cout << "Name     : " << item.GetName() << endl;
		cout << "Type     : " << item.GetTypeString() << endl;
		cout << "Price    : " << item.GetPrice() << endl;
		cout << "Quantity : " << item.GetQuantity() << endl;
		cout << "------------------------" << endl;
	}
};
