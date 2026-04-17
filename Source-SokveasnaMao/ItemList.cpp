#include "ItemList.h"

// constructor
ItemList::ItemList() {
	itemHead = nullptr;
	itemCurrent = nullptr;
	itemTail = nullptr;
	itemSize = 0;
}
// destructor
ItemList::~ItemList() {
	// start delete from the head
	ItemNode* remove = itemHead;
	ItemNode* next = nullptr;
	while (remove != nullptr) {

		// store next node before delete the current node, repeat until delete all
		next = remove->GetNext();
		delete remove;
		remove = next;
	}

	// after delete all node, reset pointers
	itemHead = nullptr;
	itemCurrent = nullptr;
	itemTail = nullptr;
	itemSize = 0;
}

int ItemList::NumNodes() const { return itemSize; };

void ItemList::DisplayList() {
	// start from head node
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
		// iterate until the last node
		MoveCurrentNodeNext();
	}
}

// +++++++++++++++++++
// Getter function
// +++++++++++++++++++
ItemNode* ItemList::GetHead() const
{
	return itemHead;
}
ItemNode* ItemList::GetCurrentNode() const
{
	return itemCurrent;
}
ItemNode* ItemList::GetTail() const
{
	return itemTail;
}

// +++++++++++++++++++
// Setter function
// +++++++++++++++++++
void ItemList::SetHead(ItemNode* head)
{
	itemHead = head;
}
void ItemList::SetCurrentNode(ItemNode* current)
{
	itemCurrent = current;
}
void ItemList::SetTail(ItemNode* tail)
{
	itemTail = tail;
}

// +++++++++++++++++++
// Insert node functions
// +++++++++++++++++++
bool ItemList::InsertHead(Item item)
{
	ItemNode* newNode = new ItemNode();

	// assign item data
	newNode->SetItem(item);
	// new node next point to old head
	newNode->SetNext(itemHead);
	// new node prev point to nullptr, since it is head node
	newNode->SetPrev(nullptr);

	// if there's list, set the prevNode old head to new head
	if (itemHead != nullptr) itemHead->SetPrev(newNode);
	// if list is empty, new node is also tail node
	else itemTail = newNode;
	
	// update head and current node to new node
	itemHead = newNode;
	itemCurrent = newNode;
	itemSize++;

	return true;
}
bool ItemList::InsertTail(Item item)
{
	ItemNode* newNode = new ItemNode();

	newNode->SetItem(item);
	// tail node have no next node
	newNode->SetNext(nullptr);

	// if list is empty
	if (itemHead == nullptr) {
		// new node has no prev node
		newNode->SetPrev(nullptr);
		// head and tail become new node
		itemHead = newNode;
		itemTail = newNode;
	}
	// if list
	else {
		// set current node to tail
		MoveCurrentNodeToTail();
		// link new node to old node
		newNode->SetPrev(itemCurrent);
		// link old node to new node
		itemCurrent->SetNext(newNode);
		itemTail = newNode;
	}
	itemCurrent = newNode;
	itemSize++;

	return true;
}
bool ItemList::InsertBody(Item item, int position)
{
	// check out of range position
	if (position < 0 || position > itemSize) {
		cout << "InsertBody: invalid position" << endl;
		return false; 
	}
	// position = 0 is insert head
	if (position == 0) return InsertHead(item);
	// position = itemsize is insert tail
	if (position == itemSize) return InsertTail(item);

	ItemNode* newNode = new ItemNode();
	newNode->SetItem(item);

	// move current node to second last correct position (if 10, current would be 9)
	MoveCurrentNodeToHead();
	for (int i = 0;i < position - 1;i++) MoveCurrentNodeNext();

	// save prev and next node
	ItemNode* prev = itemCurrent;
	ItemNode* next = itemCurrent->GetNext();

	// link new node in between the save node
	newNode->SetNext(next);
	newNode->SetPrev(prev);
	prev->SetNext(newNode);

	// if last node is not null
	if (next != nullptr) next->SetPrev(newNode);
	// if inserting at end, update tail
	else itemTail = newNode;

	itemCurrent = newNode;
	itemSize++;

	return true;
}

// +++++++++++++++++++
// delete node function
// +++++++++++++++++++
bool ItemList::DeleteHead()
{
	if (itemHead == nullptr) {
		cout << "DeleteHead: list is empty" << endl;
		return false;
	}

	// store old head, and move head forward
	ItemNode* temp = itemHead;
	itemHead = itemHead->GetNext();

	// if new head exist, remove backward link
	if (itemHead != nullptr) itemHead->SetPrev(nullptr);

	// if current node is old head, update to new head
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
	// if node only 1, delete single node and reset pointer
	if (itemSize == 1) {
		delete itemHead;
		itemHead = nullptr;
		itemCurrent = nullptr;
		itemTail = nullptr;
		itemSize--;
		return true;
	}

	// move to last node, get last node
	MoveCurrentNodeToTail();
	ItemNode* tail = itemCurrent;
	
	// set prev to second last node
	ItemNode* prev = tail->GetPrev();

	// remove tail link
	prev->SetNext(nullptr);

	// move current backward to second last node
	itemCurrent = prev;

	delete tail;
	itemSize--;
	return true;
}
bool ItemList::DeleteBody(int position)
{
	if (itemHead == nullptr) {
		cout << "DeleteBody: list is empty" << endl;
		return false;
	}
	// user input out of range position
	if (position < 0 || position >= itemSize) {
		cout << "DeleteBody: invalid input" << endl;
		return false;
	}

	// if only 1 node or position 0, delete head
	if (itemSize == 1) return DeleteHead();
	if (position == 0) return DeleteHead();
	// if last position, delete tail
	if (position == itemSize - 1) return DeleteTail();

	MoveCurrentNodeToHead();
	for (int i = 0; i < position; i++) MoveCurrentNodeNext();

	// get current node, next node, prev node
	ItemNode* curr = itemCurrent;
	ItemNode* next = curr->GetNext();
	ItemNode* prev = curr->GetPrev();

	// redirect the link
	prev->SetNext(next);
	next->SetPrev(prev);
	itemCurrent = next;

	delete curr;
	itemSize--;

	return true;
}

// +++++++++++++++++++
// search function
// +++++++++++++++++++
ItemNode* ItemList::GetNodeByPosition(int position)
{
	// user input out of range
	if (position < 0 || position >= itemSize) {
		cout << "FindNodeByPosition: invalid input" << endl;
		return nullptr;
	}

	// choose direction based on position
	if (position < itemSize / 2) {
		// move forward until reach position
		MoveCurrentNodeToHead();
		for (int i = 0;i < position;i++) MoveCurrentNodeNext();
	} else {
		// move backward until reach position
		MoveCurrentNodeToTail();
		for (int i = itemSize - 1;i > position;i--) MoveCurrentNodePrev();
	}
	return itemCurrent;
}

ItemNode* ItemList::GetNodeByName(string name) {
	// iterate all node and check matching name, return node, if not return nullptr
	MoveCurrentNodeToHead();
	while (itemCurrent != nullptr) {
		if (Validation::ToLower(itemCurrent->GetItem().GetName()) == Validation::ToLower(name)) return itemCurrent;
		MoveCurrentNodeNext();
	}
	return nullptr;
}

int ItemList::GetNodeByNode(ItemNode* item)
{
	// iterate all node and check matching name, return index, if not return -1
	MoveCurrentNodeToHead();
	int index = 0;
	while (itemCurrent != nullptr) {
		if (item == itemCurrent) return index;
		index++;
		MoveCurrentNodeNext();
	}
	return -1;
}

// +++++++++++++++++++
// traversal functions
// +++++++++++++++++++
void ItemList::MoveCurrentNodeToHead()
{
	if (itemHead == nullptr) throw "no list";
	itemCurrent = itemHead;
}

void ItemList::MoveCurrentNodeToTail()
{
	if (itemHead == nullptr) throw "no list";
	// start from head
	itemCurrent = itemHead;
	// iterate until last node
	while (itemCurrent->GetNext() != nullptr) itemCurrent = itemCurrent->GetNext();
}

bool ItemList::MoveCurrentNodeNext()
{
	if (itemCurrent == nullptr) return false;
	
	// if already at last node
	if (itemCurrent->GetNext() == nullptr) {
		itemCurrent = nullptr;
		return true;
	}
	itemCurrent = itemCurrent->GetNext();
	return true;
}
bool ItemList::MoveCurrentNodePrev() {
	if (itemCurrent == nullptr) return false;

	// if already at first node
	if(itemCurrent->GetPrev() == nullptr) {
		itemCurrent = nullptr;
		return true;
	}
	itemCurrent = itemCurrent->GetPrev();
	return true;
}
