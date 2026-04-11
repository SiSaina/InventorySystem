#include "ItemList.h"
#include <iomanip>
ItemList::ItemList() {
	itemHead = nullptr;
	itemCurrent = nullptr;
	itemTail = nullptr;
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
	itemTail = nullptr;
}
bool ItemList::InsertHead(Item item)
{
	ItemNode* newNode = new ItemNode();

	newNode->SetItem(item);
	newNode->SetNext(itemHead);
	newNode->SetPrev(nullptr);
	// if there's list, set the prevNode old head to new head
	if (itemHead != nullptr) itemHead->SetPrev(newNode);
	itemHead = newNode;
	itemCurrent = newNode;
	itemSize++;

	return true;
}
bool ItemList::InsertTail(Item item)
{
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
		MoveCurrentNodeToTail();
		newNode->SetPrev(itemCurrent);
		itemCurrent->SetNext(newNode);
	}
	itemCurrent = newNode;
	itemSize++;

	return true;
}

bool ItemList::InsertBody(Item item, int position)
{
	if (position < 0 || position > itemSize) {
		cout << "InsertBody: invalid position" << endl;
		return false; 
	}
	if (position == 0) { 
		InsertHead(item); 
		return false; 
	}
	if (position == itemSize) { 
		InsertTail(item); 
		return false; 
	}

	ItemNode* newNode = new ItemNode();
	newNode->SetItem(item);

	// move current node to second last correct position (if 10, current would be 9)
	MoveCurrentNodeToHead();
	for (int i = 0;i < position - 1;i++) MoveCurrentNodeNext();

	ItemNode* prev = itemCurrent;
	ItemNode* next = itemCurrent->GetNext();

	newNode->SetNext(next);
	newNode->SetPrev(prev);
	prev->SetNext(newNode);

	//if last node is not null
	if(next != nullptr) next->SetPrev(newNode);

	itemCurrent = newNode;
	itemSize++;

	return true;
}

bool ItemList::DeleteHead()
{
	if (itemHead == nullptr) {
		cout << "DeleteHead: list is empty" << endl;
		return false;
	}

	ItemNode* temp = itemHead;
	itemHead = itemHead->GetNext();

	if (itemHead != nullptr) itemHead->SetPrev(nullptr);
	if (itemCurrent == temp) itemCurrent = itemHead;

	delete temp;
	itemSize--;

	return true;
}

bool ItemList::DeleteTail()
{
	if (itemHead == nullptr) {
		cout << "DeleteTail: list is empty" << endl;
		return false;
	}
	if (itemSize == 1) {
		delete itemHead;
		itemHead = nullptr;
		itemCurrent = nullptr;
		itemSize--;
		return true;
	}

	MoveCurrentNodeToTail();
	ItemNode* tail = itemCurrent;
	ItemNode* prev = tail->GetPrev();

	prev->SetNext(nullptr);
	itemCurrent = prev;

	delete tail;
	itemSize--;
	return true;
}

bool ItemList::DeleteBody(int position)
{
	// no list
	if (itemHead == nullptr) {
		cout << "DeleteBody: list is empty" << endl;
		return false;
	}
	// user enter out of range position
	if (position < 0 || position >= itemSize) {
		cout << "DeleteBody: invalid input" << endl;
		return false;
	}
	if (itemSize == 1) { 
		DeleteHead();
		return false;
	}
	if (position == 0) { 
		DeleteHead(); 
		return false; 
	}
	if (position == itemSize - 1) { 
		DeleteTail(); 
		return false; 
	}

	MoveCurrentNodeToHead();
	for (int i = 0;i < position;i++) MoveCurrentNodeNext();

	ItemNode* curr = itemCurrent;
	ItemNode* next = curr->GetNext();
	ItemNode* prev = curr->GetPrev();

	prev->SetNext(next);
	next->SetPrev(prev);
	itemCurrent = next;

	delete curr;
	itemSize--;

	return true;
}

ItemNode* ItemList::GetNodeByPosition(int position)
{
	// move current node to next until match with position
	if (position < 0 || position >= itemSize) {
		cout << "FindNodeByPosition: invalid input" << endl;
		return nullptr;
	}

	if (position < itemSize / 2) {
		MoveCurrentNodeToHead();
		for (int i = 0;i < position;i++) MoveCurrentNodeNext();
	} else {
		MoveCurrentNodeToTail();
		for (int i = itemSize - 1;i > position;i--) MoveCurrentNodePrev();
	}
	return itemCurrent;
}

ItemNode* ItemList::GetNodeByName(string name) {
	MoveCurrentNodeToHead();
	do {
		if (itemCurrent->GetItem().GetName() == name) return itemCurrent;
	} while (MoveCurrentNodeNext());
	return nullptr;
}

int ItemList::GetNodeByNode(ItemNode* item)
{
	MoveCurrentNodeToHead();
	int index = 0;

	while (itemCurrent != nullptr) {
		if (item == itemCurrent) return index;
		index++;
		MoveCurrentNodeNext();
	}
	return -1;
}
int ItemList::NumNodes() const { return itemSize; };

void ItemList::DisplayList() {
	MoveCurrentNodeToHead();
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
		MoveCurrentNodeNext();
	}
}

void ItemList::MoveCurrentNodeToHead()
{
	if (itemHead == nullptr) throw "no list";
	itemCurrent = itemHead;
}

void ItemList::MoveCurrentNodeToTail()
{
	if (itemHead == nullptr) throw "no list";
	itemCurrent = itemHead;
	while (itemCurrent->GetNext() != nullptr) itemCurrent = itemCurrent->GetNext();
}

bool ItemList::MoveCurrentNodeNext()
{
	if (itemCurrent == nullptr) return false;

	itemCurrent = itemCurrent->GetNext();
	return true;
}
bool ItemList::MoveCurrentNodePrev() {
	if (itemCurrent) return false;

	itemCurrent = itemCurrent->GetPrev();
	return true;
}
