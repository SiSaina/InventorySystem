#include "ItemList.h"
ItemList::ItemList() {
	itemNode = nullptr;
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
}
void ItemList::InsertHead(int key, Item item)
{
	ItemNode* newNode = new ItemNode(key);
	newNode->SetItem(item);
	newNode->SetNext(itemNode);
	itemNode != nullptr ? itemNode->SetPrev(itemNode) : itemNode->SetPrev(nullptr);
	itemNode = newNode;
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
		newNode->SetPrev(nullptr);
		itemNode = newNode;
	}
	itemSize++;
}

void ItemList::InsertBody(int position, int key, Item item)
{
	if (position < 0 || position > itemSize) { throw "Invalid position"; }
	if (position == 0) { InsertHead(key, item); return; }
	if (position == itemSize) { InsertTail(key, item); return; }
	ItemNode* newNode = new ItemNode(key);
	newNode->SetItem(item);

	ItemNode* prev = GetNode(position - 1);
	ItemNode* next = GetNode(position);

	newNode->SetNext(next);
	newNode->SetPrev(prev);
	prev->SetNext(newNode);
	next->SetPrev(newNode);

	itemSize++;
}

void ItemList::DeleteHead()
{
	if (itemNode == nullptr) throw "No list";
	ItemNode* temp = itemNode;
	itemNode = itemNode->GetNext();
	if (itemNode != nullptr) itemNode->SetPrev(nullptr);
	delete temp;
	itemSize--;
}

void ItemList::DeleteTail()
{
	if (itemNode == nullptr) throw "No list";
	if (itemSize == 1) {
		delete itemNode;
		itemNode = nullptr;
		itemSize--;
		return;
	}
	ItemNode* curr = itemNode;
	while (curr->GetNext() != nullptr) {
		curr = curr->GetNext();
	}
	ItemNode* prev = curr->GetPrev();
	prev->SetNext(nullptr);
	delete curr;
	itemSize--;
}

void ItemList::DeleteBody(int position)
{
	if (itemNode == nullptr) throw "no list";
	if (position < 0 || position >= itemSize) throw "invalid input";
	if (position == 0) { DeleteHead(); return; }
	if (position == itemSize - 1) { DeleteTail(); return; }

	ItemNode* prev = GetNode(position - 1);
	ItemNode* curr = prev->GetNext();
	ItemNode* next = curr->GetNext();

	prev->SetNext(next);
	next->SetNext(prev);
	delete curr;
	itemSize--;
}

ItemNode* ItemList::GetNode(int position) const
{
	if (position < 0 || position >= itemSize) throw "Invalid input";
	ItemNode* newNode = itemNode;
	int size = 0;
	while (size != position) {
		newNode = newNode->GetNext();
		size++;
	}
	return newNode;
}

ItemNode* ItemList::FindNode(int key)
{
	ItemNode* newNode = itemNode;
	int size = 0;
	while (newNode != nullptr) {
		if (newNode->GetKey() == key) return newNode;
		newNode = newNode->GetNext();
		size++;
	}
	throw "Not found";
}

int ItemList::NumNodes() const { return itemSize; };

bool ItemList::NodeExists(int key)
{
	ItemNode* newNode = itemNode;
	int size = 0;
	while (newNode != nullptr) {
		if (newNode->GetKey() == key) return true;
		newNode = newNode->GetNext();
		size++;
	}
	return false;
}
