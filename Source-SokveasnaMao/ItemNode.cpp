#include "ItemNode.h"

ItemNode::ItemNode()
{
	item = Item();
	next = nullptr;
	prev = nullptr;
}
ItemNode::~ItemNode()
{
	next = nullptr;
	prev = nullptr;
}
Item& ItemNode::GetItem()
{
	return item;
}
const Item& ItemNode::GetItem() const
{
	return item;
}
ItemNode* ItemNode::GetNext() const
{
	return next;
}
ItemNode* ItemNode::GetPrev() const
{
	return prev;
}
void ItemNode::SetItem(Item& item)
{
	this->item = item;
}
void ItemNode::SetNext(ItemNode* next)
{
	this->next = next;
}
void ItemNode::SetPrev(ItemNode* prev)
{
	this->prev = prev;
}
void ItemNode::DisplayNode() const
{
	cout << "------------------------" << endl;
	cout << "Name     : " << item.GetName() << endl;
	cout << "Type     : " << item.GetTypeString() << endl;
	cout << "Price    : " << item.GetPrice() << endl;
	cout << "Quantity : " << item.GetQuantity() << endl;
	cout << "------------------------" << endl;
}