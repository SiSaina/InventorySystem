#include "Inventory.h"

Inventory::Inventory()
{
	itemList = new ItemList();
}

Inventory::~Inventory()
{
	delete itemList;
}

void Inventory::AddItem(const Item& item)
{
	itemList->InsertTail(item);
}

bool Inventory::DeleteItem(int id)
{
	return false;
}

ItemNode* Inventory::SearchById(int id)
{
	return itemList->FindNodeById(id);
}

ItemNode* Inventory::SearchByName(string name)
{
	return itemList->FindNodeByName(name);
}

pair<ItemNode*, ItemNode*> Inventory::FindNodeToSwap(ItemNode*& head, int x, int y) {
	ItemNode* node1 = nullptr;
	ItemNode* node2 = nullptr;
	ItemNode* temp = head;

	while (temp != nullptr) {
		if (temp->GetId() == x) node1 = temp;
		if (temp->GetId() == y) node2 = temp;
		temp->GetNext();
	}
	return pair<ItemNode*, ItemNode*>();
}

void Inventory::SwapNode(ItemNode* head, ItemNode* tail, int x, int y) {
	if (head == nullptr || head->GetNext() == nullptr || x == y) return;



}

void Inventory::QuickSortById()
{
}

void Inventory::QuickSortByName()
{
	if (itemList == nullptr) throw "no item";

}

void Inventory::QuickSortByPrice()
{
}

void Inventory::QuickSortByQuantity()
{
}

void Inventory::Display() const
{
}

void Inventory::LoadFromFile(const string& filename)
{
}

void Inventory::SaveToFile(const string& filename)
{
}
