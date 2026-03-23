#include "ItemNode.h"
ItemNode::ItemNode(int key) {
	mKey = key;
	mItem = Item("Unknown");
	mNext = nullptr;
	mPrev = nullptr;
}
ItemNode::~ItemNode(){
	delete mNext;
	delete mPrev;
}

int ItemNode::Getkey() const { return mKey; };

Item ItemNode::GetItem() const { return mItem; };

ItemNode* ItemNode::GetNext() const { return mNext; };

ItemNode* ItemNode::GetPrev() const { return mPrev; };

void ItemNode::SetKey(int key) { mKey = key; };
void ItemNode::SetItem(Item Item) { mItem = Item; };
void ItemNode::SetNext(ItemNode* Next) { mNext = Next; };
void ItemNode::SetPrev(ItemNode* Prev) { mPrev = Prev; };
