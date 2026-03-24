#pragma once
#include "Item.h"
class ItemNode
{
private:
	int id;
	Item item;
	ItemNode* next;
	ItemNode* prev;
public:
	ItemNode(int id) {
		this->id = id;
		item = Item();
		next = nullptr;
		prev = nullptr;
	};
	~ItemNode() {
		delete next;
		delete prev;
	};
	int GetId() const { return id; };
	Item GetItem() const { return item; };
	ItemNode* GetNext() const { return next; };
	ItemNode* GetPrev() const { return prev; };
	void Setid(int id) { this->id = id; };
	void SetItem(Item item) { this->item = item; };
	void SetNext(ItemNode* next) { this->next = next; };
	void SetPrev(ItemNode* prev) { this->prev = prev; };
};
