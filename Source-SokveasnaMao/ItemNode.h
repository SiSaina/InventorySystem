#pragma once
#include "Item.h"
class ItemNode
{
private:
	int key;
	Item item;
	ItemNode* next;
	ItemNode* prev;
public:
	ItemNode(int key) {
		this->key = key;
		item = Item("Unknown");
		next = nullptr;
		prev = nullptr;
	};
	~ItemNode() {
		delete next;
		delete prev;
	};
	int GetKey() const { return key; };
	Item GetItem() const { return item; };
	ItemNode* GetNext() const { return next; };
	ItemNode* GetPrev() const { return prev; };
	void SetKey(int key) { this->key = key; };
	void SetItem(Item item) { this->item = item; };
	void SetNext(ItemNode* next) { this->next = next; };
	void SetPrev(ItemNode* prev) { this->prev = prev; };
};
