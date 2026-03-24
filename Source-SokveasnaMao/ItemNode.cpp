#include "ItemNode.h"
ItemNode::ItemNode(int key) {
	this->key = key;
	item = Item("Unknown");
	next = nullptr;
	prev = nullptr;
}
ItemNode::~ItemNode(){
	delete next;
	delete prev;
}

int ItemNode::GetKey() const { return key; };
Item ItemNode::GetItem() const { return item; };
ItemNode* ItemNode::GetNext() const { return next; };
ItemNode* ItemNode::GetPrev() const { return prev; };

void ItemNode::SetKey(int key) { this->key = key; };
void ItemNode::SetItem(Item item) { item = item; };
void ItemNode::SetNext(ItemNode* next) { next = next; };
void ItemNode::SetPrev(ItemNode* prev) { prev = prev; };
