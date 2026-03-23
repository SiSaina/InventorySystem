#pragma once
#include "Item.h"
class ItemNode
{
private:
	int mKey;
	Item mItem;
	ItemNode* mNext;
	ItemNode* mPrev;
public:
	ItemNode(int key);
	~ItemNode();
	int Getkey() const;
	Item GetItem() const;
	ItemNode* GetNext() const;
	ItemNode* GetPrev() const;
	void SetKey(int key);
	void SetItem(Item Item);
	void SetNext(ItemNode* Next);
	void SetPrev(ItemNode* Prev);
};
