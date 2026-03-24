#include "ItemList.h"
ItemList::ItemList() {
	itemNode = nullptr;
	itemCurrent = nullptr;
	itemSize = 0;
}
ItemList::~ItemList() {
	ItemNode* remove = itemNode;
	ItemNode* next = nullptr;
	while (remove != nullptr) {
		next = remove->GetNext();
		delete remove;
		remove = next;
	}
	itemCurrent = nullptr;
}
void ItemList::InsertHead(int key, Item item)
{
	ItemNode* newNode = new ItemNode(key);
	newNode->SetItem(item);
	newNode->SetNext(itemNode);
	itemNode != nullptr ? itemNode->SetPrev(itemNode) : itemNode->SetPrev(nullptr);
	itemNode = newNode;
	itemCurrent = newNode;
	itemSize++;
}
void ItemList::InsertTail(int key, Item item)
{
	ItemNode* newNode = new ItemNode(key);
	newNode->SetItem(item);
	if (itemNode != nullptr) {
		ItemNode* temp = itemNode;
		while (temp->GetNext() != nullptr) {
			temp = temp->GetNext();
		}
		temp->SetNext(newNode);
		newNode->SetPrev(temp);
	}
	else {
		MoveToTail();
		newNode->SetPrev(itemCurrent);
		itemCurrent->SetNext(newNode);
	}
	itemCurrent = newNode;
	itemSize++;
}

void ItemList::InsertBody(int position, int key, Item item)
{
	if (position < 0 || position > itemSize) { throw "Invalid position"; }
	if (position == 0) { InsertHead(key, item); return; }
	if (position == itemSize) { InsertTail(key, item); return; }

	ItemNode* newNode = new ItemNode(key);
	newNode->SetItem(item);

	MoveToHead();
	for (int i = 0;i < position - 1;i++)MoveNext();

	ItemNode* prev = itemCurrent;
	ItemNode* next = itemCurrent->GetNext();

	newNode->SetNext(next);
	newNode->SetPrev(prev);
	prev->SetNext(newNode);
	if(next != nullptr) next->SetPrev(newNode);

	itemCurrent = newNode;
	itemSize++;
}

void ItemList::DeleteHead()
{
	if (itemNode == nullptr) throw "No list";
	ItemNode* temp = itemNode;
	itemNode = itemNode->GetNext();
	if (itemNode != nullptr) itemNode->SetPrev(nullptr);
	if (itemCurrent == temp) itemCurrent = itemNode;
	delete temp;
	itemSize--;
}

void ItemList::DeleteTail()
{
	if (itemNode == nullptr) throw "No list";
	if (itemSize == 1) {
		delete itemNode;
		itemNode = nullptr;
		itemCurrent = nullptr;
		itemSize--;
		return;
	}

	MoveToTail();
	ItemNode* tail = itemCurrent;
	ItemNode* prev = tail->GetPrev();

	prev->SetNext(nullptr);
	itemCurrent = prev;

	delete tail;
	itemSize--;
}

void ItemList::DeleteBody(int position)
{
	if (itemNode == nullptr) throw "no list";
	if (position < 0 || position >= itemSize) throw "invalid input";
	if (itemSize == 1) { DeleteHead(); return; }
	if (position == 0) { DeleteHead(); return; }
	if (position == itemSize - 1) { DeleteTail(); return; }

	MoveToHead();
	for (int i = 0;i < position;i++) MoveNext();

	ItemNode* curr = itemCurrent;
	ItemNode* next = curr->GetNext();
	ItemNode* prev = curr->GetPrev();

	prev->SetNext(next);
	next->SetPrev(prev);
	itemCurrent = next;

	delete curr;
	itemSize--;
}

ItemNode* ItemList::GetNode(int position) const
{
	if (position < 0 || position >= itemSize) throw "Invalid input";
	ItemNode* newNode = itemNode;
	for (int i = 0;i < position;i++) newNode = newNode->GetNext();
	return newNode;
}

ItemNode* ItemList::FindNode(int key)
{
	MoveToHead();
	do {
		if (itemCurrent->GetKey() == key) return itemCurrent;
	} while (MoveNext());
	throw "Not found";
}

int ItemList::NumNodes() const { return itemSize; };

bool ItemList::NodeExists(int key)
{
	MoveToHead();
	do {
		if (itemCurrent->GetKey() == key) return true;
	} while (MoveNext());
	return false;
}

void ItemList::MoveToHead()
{
	if (itemNode == nullptr) throw "no list";
	itemCurrent = itemNode;
}

void ItemList::MoveToTail()
{
	if (itemNode == nullptr) throw "no list";
	itemCurrent = itemNode;
	while (itemCurrent->GetNext() != nullptr) itemCurrent = itemCurrent->GetNext();
}

bool ItemList::MoveNext()
{
	if (itemCurrent == nullptr) throw "current not set";
	if (itemCurrent->GetNext() == nullptr) return false;
	itemCurrent = itemCurrent->GetNext();
	return true;
}

bool ItemList::MovePrev() {
	if (itemCurrent == nullptr) throw "current not set";
	if (itemCurrent->GetPrev() == nullptr) return false;
	itemCurrent = itemCurrent->GetPrev();
	return true;
}

ItemNode* ItemList::GetCurrent() const
{
	if (itemCurrent == nullptr) throw "current not set";
	return itemCurrent;
}

bool ItemList::IsHead() const 
{
	if (itemCurrent == nullptr) return true;
	return (itemCurrent->GetPrev() == nullptr);
}

bool ItemList::IsTail() const
{
	if (itemCurrent == nullptr) return true;
	return (itemCurrent->GetNext() == nullptr);
}

void ItemList::ResetCurrent() { itemCurrent = nullptr; }
