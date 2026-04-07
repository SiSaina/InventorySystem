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

void Inventory::AddItemToHead(const Item& item)
{
	itemList->InsertHead(item);
}

void Inventory::AddItemToTail(const Item& item)
{
	itemList->InsertTail(item);
}

void Inventory::AddItemToBody(const Item& item, int position)
{
	itemList->InsertBody(item, position);
}

void Inventory::DeleteItemFromHead(ItemNode* item)
{
	itemList->DeleteHead();
}

void Inventory::DeleteItemFromTail(ItemNode* item)
{
	itemList->DeleteTail();
}

void Inventory::DeleteItemFromBody(ItemNode* item, int position)
{
	itemList->DeleteBody(position);
}

ItemNode* Inventory::SearchByName(string name)
{
	return itemList->FindNodeByName(name);
}

ItemNode* Inventory::SearchByPosition(int position)
{
	return itemList->FindNodeByPosition(position);
}

// swaping item by pointer
void Inventory::SwapNodes(ItemNode* a, ItemNode* b) {
	if (!a || !b) throw "Invalid node";

	// store surrounding nodes of a and b
	ItemNode* prevA = a->GetPrev();
	ItemNode* nextA = a->GetNext();
	
	ItemNode* prevB = b->GetPrev();
	ItemNode* nextB = b->GetNext();

	// case 1: if a is directly before b
	if(nextA == b) {
		a->SetNext(nextB);
		a->SetPrev(b);
		b->SetNext(a);
		b->SetPrev(prevA);
		if (prevA) prevA->SetNext(b);
		if (nextB) nextB->SetPrev(a);
	}
	// case 2: if b is directly before a
	else if (nextB == a) {
		b->SetNext(nextA);
		b->SetPrev(a);
		a->SetNext(b);
		a->SetPrev(prevB);
		if (prevB) prevB->SetNext(a);
		if (nextA) nextA->SetPrev(b);
	}
	// case 3: if a and b are not adjacent
	else {
		a->SetNext(nextB);
		a->SetPrev(prevB);
		b->SetNext(nextA);
		b->SetPrev(prevA);
		if (prevA) prevA->SetNext(b);
		if (nextA) nextA->SetPrev(b);
		if (prevB) prevB->SetNext(a);
		if (nextB) nextB->SetPrev(a);
	}
	if(itemList->GetHead() == a) itemList->SetHead(b);
	else if (itemList->GetHead() == b) itemList->SetHead(a);
}
bool Inventory::CompareNode(const Item& a, const Item& b, int attribute, bool order) {
	// order = true for accending, false for decending
	// attribute: 1 for name, 2 for type, 3 for price, 4 for quantity
	switch (attribute) {
	case 1: 
		return order ? a.GetName() > b.GetName() 
					 : a.GetName() < b.GetName();
	case 2:
		return order ? a.GetType() > b.GetType() 
					 : a.GetType() < b.GetType();
	case 3:
		return order ? a.GetPrice() > b.GetPrice() 
					 : a.GetPrice() < b.GetPrice();
	case 4:
		return order ? a.GetQuantity() > b.GetQuantity() 
					 : a.GetQuantity() < b.GetQuantity();
	default:
		throw "Invalid attribute";
	}
}
ItemNode* Inventory::PartitionAccending(ItemNode* first, ItemNode* last, int attribute)
{
	// set pivot as last element
	Item pivot = last->GetItem();
	// index of first element, it is nullptr
	ItemNode* i = first->GetPrev();

	for(ItemNode* j = first; j != last; j = j->GetNext()) {
		if (CompareNode(j->GetItem(), pivot, attribute, true)) {
			// move i to the next position and swap it with j
			i = (i == nullptr) ? first : i->GetNext();
			SwapNodes(i, j);
		}
	}

	// move i to the current pivot position and swap it with the pivot
	i = (i == nullptr) ? first : i->GetNext();

	SwapNodes(i, last);
	return i;
}

ItemNode* Inventory::PartitionDescending(ItemNode* first, ItemNode* last, int attribute)
{
	Item pivot = last->GetItem();
	ItemNode* i = first->GetPrev();

	for (ItemNode* j = first; j != last; j = j->GetNext()) {
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
	QuickSortAccending(first, pivot->GetPrev(), attribute);
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

void Inventory::QuickSort(int attribute, int order)
{
	if (itemList == nullptr) throw "no item";

	ItemNode* first = itemList->GetNode(0);
	ItemNode* last = itemList->GetNode(itemList->NumNodes() - 1);

	if(order == 1) QuickSortAccending(first, last, attribute);
	else QuickSortDescending(first, last, attribute);
	cout << endl;
}

void Inventory::DisplayInventory() const
{
	itemList->DisplayList();
}

void Inventory::LoadFromFile(const string& filename)
{
	// open file for reading
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Cannot open: " << filename << endl;
		return;
	}
	// read first line and ignore it since it is the header
	string line;
	getline(file, line);

	// read each line and parse it into an item, then add it to the inventory
	while(getline(file, line)) {
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
		else throw "Invalid item type";

		// create item and add it to inventory
		Item item(name, type, price, quantity);
		AddItemToTail(item);
	};

	file.close();
	cout << "Loaded from " << filename << endl;;
}

void Inventory::SaveToFile(const string& filename)
{
	// open file for writing, if it doesn't exist, create it, if it does exist, overwrite it
	ofstream file(filename);

	// check if file is open, if not, throw an error
	if(!file.is_open()) {
		throw "Could not open file";
	}

	// write header
	file << "NAME // TYPE // PRICE // QUANTITY" << endl;
	ItemNode* temp = itemList->GetNode(0);
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

	cout << "Saved to " << filename << endl;;
}
