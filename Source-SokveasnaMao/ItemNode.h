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
	ItemNode(int key);
	~ItemNode();
	int GetKey() const;
	Item GetItem() const;
	ItemNode* GetNext() const;
	ItemNode* GetPrev() const;
	void SetKey(int key);
	void SetItem(Item item);
	void SetNext(ItemNode* next);
	void SetPrev(ItemNode* prev);
};
