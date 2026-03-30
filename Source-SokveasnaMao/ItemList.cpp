#include "ItemList.h"
#include <iomanip>
ItemList::ItemList() {
	itemHead = nullptr;
	itemCurrent = nullptr;
	itemSize = 0;
	nextId = 1;
}
ItemList::~ItemList() {
	ItemNode* remove = itemHead;
	ItemNode* next = nullptr;
	while (remove != nullptr) {
		next = remove->GetNext();
		delete remove;
		remove = next;
	}
	itemCurrent = nullptr;
}
void ItemList::InsertHead(Item item)
{
	//int id = nextId;
	//nextId++;
	ItemNode* newNode = new ItemNode();
	newNode->SetItem(item);
	newNode->SetNext(itemHead);
	newNode->SetPrev(nullptr);
	// if there's list, set the prevNode old head to new head
	if (itemHead != nullptr) itemHead->SetPrev(newNode);
	itemHead = newNode;
	itemCurrent = newNode;
	itemSize++;
}
void ItemList::InsertTail(Item item)
{
	//int id = nextId;
	//nextId++;
	ItemNode* newNode = new ItemNode();
	newNode->SetItem(item);
	newNode->SetNext(nullptr);
	// no list
	if (itemHead == nullptr) {
		newNode->SetPrev(nullptr);
		itemHead = newNode;
	}
	else {
		// if list, set current node to tail
		MoveToTail();
		newNode->SetPrev(itemCurrent);
		itemCurrent->SetNext(newNode);
	}
	itemCurrent = newNode;
	itemSize++;
}

void ItemList::InsertBody(int position, Item item)
{
	if (position < 0 || position > itemSize) { throw "Invalid position"; }
	if (position == 0) { InsertHead(item); return; }
	if (position == itemSize) { InsertTail(item); return; }

	//int id = nextId;
	//nextId++;

	ItemNode* newNode = new ItemNode();
	newNode->SetItem(item);

	// move current node to second last correct position (if 10, current would be 9)
	MoveToHead();
	for (int i = 0;i < position - 1;i++) MoveNext();

	ItemNode* prev = itemCurrent;
	ItemNode* next = itemCurrent->GetNext();

	newNode->SetNext(next);
	newNode->SetPrev(prev);
	prev->SetNext(newNode);

	//if last node is not null
	if(next != nullptr) next->SetPrev(newNode);

	itemCurrent = newNode;
	itemSize++;
}

void ItemList::DeleteHead()
{
	if (itemHead == nullptr) throw "No list";

	ItemNode* temp = itemHead;
	itemHead = itemHead->GetNext();

	if (itemHead != nullptr) itemHead->SetPrev(nullptr);
	if (itemCurrent == temp) itemCurrent = itemHead;

	delete temp;
	itemSize--;
}

void ItemList::DeleteTail()
{
	if (itemHead == nullptr) throw "No list";
	if (itemSize == 1) {
		delete itemHead;
		itemHead = nullptr;
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
	// no list
	if (itemHead == nullptr) throw "no list";
	// user enter out of range position
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
	ItemNode* newNode = itemHead;
	for (int i = 0;i < position;i++) newNode = newNode->GetNext();
	return newNode;
}

int ItemList::FindNodeByNode(ItemNode* item) 
{
	MoveToHead();
	int index = 0;
	do {
		if (item == GetNode(index)) return index;
		index++;
	} while (MoveNext());
	throw "Not found";
}

ItemNode* ItemList::FindNodeByPosition(int position)
{
	// move current node to next until match with position
	MoveToHead();
	do {
		if (itemCurrent == GetNode(position)) return itemCurrent;
	} while (MoveNext());
	throw "Not found";
}

ItemNode* ItemList::FindNodeByName(string name) {
	MoveToHead();
	do {
		if (itemCurrent->GetItem().GetName() == name) return itemCurrent;
	} while (MoveNext());
	throw "Not found";
}

int ItemList::NumNodes() const { return itemSize; };

//bool ItemList::NodeExists(int id)
//{
//	MoveToHead();
//	do {
//		if (itemCurrent->GetId() == id) return true;
//	} while (MoveNext());
//	return false;
//}

bool ItemList::NodeExistsByPosition(int position)
{
	do {
		if (itemCurrent == GetNode(position)) return true;
	} while (MoveNext());
	return true;
}

void ItemList::DisplayList() {
	MoveToHead();
	// set width for each column and left align
	cout << left << setw(25) << "Name" << setw(20) << "Type" << setw(12) << "Price" << setw(12) << "Quantity" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	while (itemCurrent != nullptr) {
		// set width for each column and left align
		cout << left
			<< setw(25) << itemCurrent->GetItem().GetName()
			<< setw(20) << itemCurrent->GetItem().GetTypeString()
			<< setw(12) << itemCurrent->GetItem().GetPrice()
			<< setw(12) << itemCurrent->GetItem().GetQuantity()
			<< endl;
		MoveNext();
	}
}

void ItemList::MoveToHead()
{
	if (itemHead == nullptr) throw "no list";
	itemCurrent = itemHead;
}

void ItemList::MoveToTail()
{
	if (itemHead == nullptr) throw "no list";
	itemCurrent = itemHead;
	while (itemCurrent->GetNext() != nullptr) itemCurrent = itemCurrent->GetNext();
}

bool ItemList::MoveNext()
{
	if (itemCurrent == nullptr) throw "current not set";
	if (itemCurrent->GetNext() == nullptr) {
		itemCurrent = nullptr;
		return false;
	}
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
