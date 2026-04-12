#include "Inventory.h"
#include <fstream>
#include <sstream>
#include <filesystem>

Inventory::Inventory()
{
	itemList = new ItemList();
}

Inventory::~Inventory()
{
	delete itemList;
}

bool Inventory::AddItemToHead(const Item& item)
{
	if (!itemList) throw "item list not initialized";
	itemList->InsertHead(item);
	return true;
}

bool Inventory::AddItemToTail(const Item& item)
{
	if (!itemList) throw "item list not initialized";
	itemList->InsertTail(item);
	return true;
}

bool Inventory::AddItemToBody(const Item& item, int position)
{
	if (!itemList) throw "item list not initialized";
	itemList->InsertBody(item, position);
	return true;
}

bool Inventory::DeleteItemFromHead()
{
	if (!itemList) throw "item list not initialized";
	if (itemList->NumNodes() == 0) {
		cout << "DeleteItemFromHead: no items to delete" << endl;
		return false;
	}
	itemList->DeleteHead();
	return true;
}

bool Inventory::DeleteItemFromTail()
{
	if (!itemList) throw "item list not initialized";
	if (itemList->NumNodes() == 0) {
		cout << "DeleteItemFromTail: no items to delete" << endl;
		return false;
	}
	itemList->DeleteTail();
	return true;
}

bool Inventory::DeleteItemFromBody(int position)
{
	if (!itemList) throw "item list not initialized";
	if (itemList->NumNodes() == 0) {
		cout << "DeleteItemFromBody: no items to delete" << endl;
		return false;
	}
	itemList->DeleteBody(position);
	return true;
}

ItemNode* Inventory::SearchByName(string name)
{
	if (itemList->NumNodes() == 0) {
		cout << "SearchByName: no items to search" << endl;
		return nullptr;
	}
	return itemList->GetNodeByName(name);
}

ItemNode* Inventory::SearchByPosition(int position)
{
	if (itemList->NumNodes() == 0) {
		cout << "SearchByPosition: no items to search" << endl;
		return nullptr;
	}
	return itemList->GetNodeByPosition(position);
}

int Inventory::GetNodePosition(ItemNode* node) const
{
	if (!itemList) throw "item list not initialized";
	return itemList->GetNodeByNode(node);
}

pair<ItemNode*, ItemNode*> Inventory::FindNode(ItemNode*& head, Item* X, Item* Y)
{
	ItemNode* N1 = NULL;
	ItemNode* N2 = NULL;
	ItemNode* temp = head;

	// Traversing the list
	while (temp != NULL) {
		if (temp->GetItem().GetName() == X->GetName())
			N1 = temp;
		else if (temp->GetItem().GetName() == Y->GetName())
			N2 = temp;
		temp = temp->GetNext();
	}
	return make_pair(N1, N2);
}

// swaping item by pointer
void Inventory::SwapNodes(ItemNode* a, ItemNode* b) {
	// check if a and b are not null and not the same node
	if (!a || !b) throw "SwapNodes: null node";
	if (a == b) return;

	// store surrounding nodes of a and b
	ItemNode* prevA = a->GetPrev();
	ItemNode* nextA = a->GetNext();
	ItemNode* prevB = b->GetPrev();
	ItemNode* nextB = b->GetNext();

	// case 1: if a is directly before b
	// then we only need to update the next and prev of a and b, and the surrounding nodes of a and b
	if(nextA == b) {
		// if prevA is not null, set its next to b
		if (prevA) prevA->SetNext(b);
		// if nextB is not null, set its prev to a
		if (nextB) nextB->SetPrev(a);
		
		a->SetNext(nextB);
		a->SetPrev(b);
		b->SetNext(a);
		b->SetPrev(prevA);
	}
	// case 2: if b is directly before a
	// then we only need to update the next and prev of a and b, and the surrounding nodes of a and b
	else if (nextB == a) {
		// if prevB is not null, set its next to a
		if (prevB) prevB->SetNext(a);
		// if nextA is not null, set its prev to b
		if (nextA) nextA->SetPrev(b);
		b->SetNext(nextA);
		b->SetPrev(a);
		a->SetNext(b);
		a->SetPrev(prevB);
	}
	// case 3: if a and b are not adjacent
	// then we need to update the next and prev of a and b, and the surrounding nodes of a and b
	else {
		// if prevA is not null, set its next to b
		if (prevA) prevA->SetNext(b);
		// if nextA is not null, set its prev to b
		if (nextA) nextA->SetPrev(b);
		// if prevB is not null, set its next to a
		if (prevB) prevB->SetNext(a);
		// if nextB is not null, set its prev to a
		if (nextB) nextB->SetPrev(a);

		a->SetNext(nextB);
		a->SetPrev(prevB);
		b->SetNext(nextA);
		b->SetPrev(prevA);
	}
	// update head of the list if a or b is the head
	if(itemList->GetHead() == a) itemList->SetHead(b);
	else if (itemList->GetHead() == b) itemList->SetHead(a);
	
	// update tail
	if (itemList->GetTail() == a) itemList->SetTail(b);
	else if (itemList->GetTail() == b) itemList->SetTail(a);

	// fix boundaries
	if (itemList->GetHead()) itemList->GetHead()->SetPrev(nullptr);

	if (itemList->GetTail()) itemList->GetTail()->SetNext(nullptr);
}
void Inventory::SwapNodesByRelinking(ItemNode* n1, ItemNode* n2)
{
	if (!n1 || !n2 || n1 == n2) return;

	// Save neighbors
	ItemNode* n1Prev = n1->GetPrev();
	ItemNode* n1Next = n1->GetNext();
	ItemNode* n2Prev = n2->GetPrev();
	ItemNode* n2Next = n2->GetNext();
	// Case: n1 directly before n2
	if (n1->GetNext() == n2)
	{
		ItemNode* prev = n1->GetPrev();
		ItemNode* next = n2->GetNext();

		if (prev) prev->SetNext(n2);
		else itemList->SetHead(n2);

		if (next) next->SetPrev(n1);
		else itemList->SetTail(n1);

		n2->SetPrev(prev);
		n2->SetNext(n1);

		n1->SetPrev(n2);
		n1->SetNext(next);

		return;
	}

	// Case: n2 directly before n1
	if (n2->GetNext() == n1)
	{
		ItemNode* prev = n2->GetPrev();
		ItemNode* next = n1->GetNext();

		if (prev) prev->SetNext(n1);
		else itemList->SetHead(n1);

		if (next) next->SetPrev(n2);
		else itemList->SetTail(n2);

		n1->SetPrev(prev);
		n1->SetNext(n2);

		n2->SetPrev(n1);
		n2->SetNext(next);

		return;
	}
	// --- DETACH n1 ---
	if (n1Prev) n1Prev->SetNext(n1Next);
	else itemList->SetHead(n1Next);

	if (n1Next) n1Next->SetPrev(n1Prev);
	else itemList->SetTail(n1Prev);

	// --- DETACH n2 ---
	if (n2Prev) n2Prev->SetNext(n2Next);
	else itemList->SetHead(n2Next);

	if (n2Next) n2Next->SetPrev(n2Prev);
	else itemList->SetTail(n2Prev);

	// --- INSERT n1 into n2's original position ---
	n1->SetPrev(n2Prev);
	n1->SetNext(n2Next);

	if (n2Prev) n2Prev->SetNext(n1);
	else itemList->SetHead(n1);

	if (n2Next) n2Next->SetPrev(n1);
	else itemList->SetTail(n1);

	// --- INSERT n2 into n1's original position ---
	n2->SetPrev(n1Prev);
	n2->SetNext(n1Next);

	if (n1Prev) n1Prev->SetNext(n2);
	else itemList->SetHead(n2);

	if (n1Next) n1Next->SetPrev(n2);
	else itemList->SetTail(n2);
}
void Inventory::SwapNodesByPointer(ItemNode*& a, ItemNode*& b, Item* X, Item* Y)
{
	// check if a and b are not null and not the same node
	if (!a || !b) throw "SwapNodesByPointer: null node";
	if (a == b) return;
	if (a == NULL || a->GetNext() == NULL || X == Y) return;

	pair<ItemNode*, ItemNode*> nodes = FindNode(a, X, Y);

	ItemNode* node1 = nodes.first;
	ItemNode* node2 = nodes.second;

	if(node1 == a) a = node2;
	else if (node2 == a) a = node1;
	if(node1 == b) b = node2;
	else if (node2 == b) b = node1;

	ItemNode* temp;
	temp = node1->GetNext();
	node1->SetNext(node2->GetNext());
	node2->SetNext(temp);

	if (node1->GetNext() != NULL)
		node1->GetNext()->SetPrev(node1);
	if (node2->GetNext() != NULL)
		node2->GetNext()->SetPrev(node2);

	temp = node1->GetPrev();
	node1->SetPrev(node2->GetPrev());
	node2->SetPrev(temp);
	if (node1->GetPrev() != NULL)
		node1->GetPrev()->SetNext(node1);
	if (node2->GetPrev() != NULL)
		node2->GetPrev()->SetNext(node2);
}

void Inventory::SwapNodesData(ItemNode* a, ItemNode* b)
{
	Item temp = a->GetItem();
	a->SetItem(b->GetItem());
	b->SetItem(temp);
}

bool Inventory::CompareNode(const Item a, const Item b, int attribute, bool order) {
	// order = true for accending, false for decending
	// attribute: 1 for name, 2 for type, 3 for price, 4 for quantity
	switch (attribute) {
	case 1: 
		return order ? a.GetName() < b.GetName() 
					 : a.GetName() > b.GetName();
	case 2:
		return order ? a.GetType() < b.GetType() 
					 : a.GetType() > b.GetType();
	case 3:
		return order ? a.GetPrice() < b.GetPrice() 
					 : a.GetPrice() > b.GetPrice();
	case 4:
		return order ? a.GetQuantity() < b.GetQuantity() 
					 : a.GetQuantity() > b.GetQuantity();
	default:
		throw "invalid attribute for comparison";
	}
}
ItemNode* Inventory::PartitionAccending(ItemNode* first, ItemNode* last, int attribute)
{
	// check if first and last are not null
	if (!first || !last) throw "Partition: null node";

	// set pivot as last element
	Item pivot = last->GetItem();
	// index of first element, it is nullptr
	ItemNode* i = first->GetPrev();

	// loop through the list from first to last
	// if the current element is smaller than or equal to the pivot
	// move the index of smaller element and swap it with the current element
	for(ItemNode* j = first; j != last; j = j->GetNext()) {
		// store next node of j since it might be swapped with i and lose the reference to the next node
		if (CompareNode(j->GetItem(), pivot, attribute, true)) {
			// move i to the next position and swap it with j
			i = (i == nullptr) ? first : i->GetNext();

			SwapNodesByPointer(i, j, &i->GetItem(), &j->GetItem());
		}
	}

	// move i to the current pivot position and swap it with the pivot
	i = (i == nullptr) ? first : i->GetNext();

	SwapNodesByPointer(i, last, &i->GetItem(), &last->GetItem());

	return i;
}

ItemNode* Inventory::PartitionDescending(ItemNode* first, ItemNode* last, int attribute)
{	
	if (!first || !last) throw "Partition: null node";
	Item pivot = last->GetItem();
	ItemNode* i = first->GetPrev();

	for (ItemNode* j = first; j != last; j = j->GetNext()) {
		if (!j) throw "Partition: null node in loop";
		if (CompareNode(j->GetItem(), pivot, attribute, false)) {
			i = (i == nullptr) ? first : i->GetNext();
			SwapNodes(i, j);
		}
	}

	i = (i == nullptr) ? first : i->GetNext();

	SwapNodes(i, last);
	return i;
}

void Inventory::QuickSortAccending(ItemNode* first, ItemNode* last, int attribute)
{
	// check if there are nodes to sort
	// check if first and last are not the same and if they are not adjacent
	// if they are adjacent, if there is only one element, then it is already sorted
	if (first == nullptr || last == nullptr) return;
	if (first == last || first == last->GetNext()) return;

	ItemNode* pivot = PartitionAccending(first, last, attribute);

	// recursively sort the left pivot
	QuickSortAccending(first, pivot->GetPrev(), attribute);
	// recursively sort the right pivot
	QuickSortAccending(pivot->GetNext(), last, attribute);
}

void Inventory::QuickSortDescending(ItemNode* first, ItemNode* last, int attribute)
{
	if (first == nullptr || last == nullptr) return;
	if (first == last || first == last->GetNext()) return;

	ItemNode* pivot = PartitionDescending(first, last, attribute);
	QuickSortDescending(first, pivot->GetPrev(), attribute);
	QuickSortDescending(pivot->GetNext(), last, attribute);
}

bool Inventory::QuickSort(int attribute, int order)
{
	if (!itemList) throw "item list not initialized";
	if (itemList->NumNodes() == 0) {
		cout << "QuickSort: no items to sort" << endl;
		return false;
	}
	if (attribute < 1 || attribute > 4) {
		cout << "QuickSort: invalid attribute" << endl;
		return false;
	}
	if (order != 1 && order != 2) {
		cout << "QuickSort: invalid order" << endl;
		return false;
	}

	ItemNode* first = itemList->GetNodeByPosition(0);
	ItemNode* last = itemList->GetNodeByPosition(itemList->NumNodes() - 1);

	if(order == 1) QuickSortAccending(first, last, attribute);
	else QuickSortDescending(first, last, attribute);
}

void Inventory::DisplayInventory() const
{
	itemList->DisplayList();
}

int Inventory::GetItemCount() const
{
	return itemList->NumNodes();
}

void Inventory::ClearAllNodes()
{
	while (itemList->NumNodes() > 0) {
		itemList->DeleteHead();
	}
}

bool Inventory::LoadFromFile(const string& filename)
{
	ClearAllNodes();
	// open file for reading
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Cannot open file: " << filename << endl;
		return false;
	}
	// read first line and ignore it since it is the header
	string line;
	getline(file, line);

	// read each line and parse it into an item, then add it to the inventory
	while(getline(file, line)) {
		try {
			if (line.empty()) continue;
			string name, typeStr, priceStr, quantityStr;

			// use stringstream to parse the line, separate by // and space
			stringstream ss(line);
			// use getline to read until // and ignore the space after it
			getline(ss, name, '/');
			ss.ignore(1);
			getline(ss, typeStr, '/');
			ss.ignore(1);
			getline(ss, priceStr, '/');
			ss.ignore(1);
			getline(ss, quantityStr, '/');

			// trim whitespace from name
			// remove all spaces from typeStr, priceStr, and quantityStr
			name.erase(0, name.find_first_not_of(" "));
			name.erase(name.find_last_not_of(" ") + 1);
			typeStr.erase(remove(typeStr.begin(), typeStr.end(), ' '), typeStr.end());
			priceStr.erase(remove(priceStr.begin(), priceStr.end(), ' '), priceStr.end());
			quantityStr.erase(remove(quantityStr.begin(), quantityStr.end(), ' '), quantityStr.end());
		
			// convert string price to float and stirng quantity to int
			float price = stof(priceStr);
			int quantity = stoi(quantityStr);
		
			// convert string type to ItemType enum
			ItemType type;
			if (typeStr == "Armor") type = Armor;
			else if (typeStr == "Consumable") type = Consumable;
			else if (typeStr == "Utility") type = Utility;
			else if (typeStr == "Weapon") type = Weapon;
			else { 
				cout << "Warning: Invalid item type in line " << line << ", defaulting to Utility" << endl;
				type = Utility;
			}

			// create item and add it to inventory
			Item item(name, type, price, quantity);
			AddItemToTail(item);
		}
		catch (exception& e) {
			cout << "Error parsing line: " << line << endl;
			cout << "Error message: " << e.what() << endl;
		}
	};
	file.close();
	return true;
}

bool Inventory::SaveToFile(const string& filename)
{
	// open file for writing
	// if it doesn't exist, create it, if it does exist, overwrite it
	ofstream file(filename);

	// check if file is open, if not, throw an error
	if(!file.is_open()) {
		cout << "Could not open file" << endl;
		return false;
	}

	// write header
	file << "NAME // TYPE // PRICE // QUANTITY" << endl;
	ItemNode* temp = itemList->GetNodeByPosition(0);
	// write each item to file, separate by // and space
	while (temp != nullptr)
	{
		Item item = temp->GetItem();

		file << item.GetName() << " // "
			<< item.GetTypeString() << " // "
			<< item.GetPrice() << " // "
			<< item.GetQuantity()
			<< endl;
		temp = temp->GetNext();
	}

	file.close();
	return true;
}
