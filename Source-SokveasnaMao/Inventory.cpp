#include "Inventory.h"

void Inventory::DisplayInventory()
{
	itemList.DisplayList();
}

// +++++++++++++++++++
// Add node function
// +++++++++++++++++++
bool Inventory::AddItemToHead(const Item& item)
{
	return itemList.InsertHead(item);
}
bool Inventory::AddItemToTail(const Item& item)
{
	return itemList.InsertTail(item);
}
bool Inventory::AddItemToBody(const Item& item, int position)
{
	return itemList.InsertBody(item, position);
}

// +++++++++++++++++++
// Delete node function
// +++++++++++++++++++
bool Inventory::DeleteItemFromHead()
{
	if (itemList.NumNodes() == 0) {
		cout << "DeleteItemFromHead: no items to delete" << endl;
		return false;
	}
	return itemList.DeleteHead();
}
bool Inventory::DeleteItemFromTail()
{
	if (itemList.NumNodes() == 0) {
		cout << "DeleteItemFromTail: no items to delete" << endl;
		return false;
	}
	return itemList.DeleteTail();
}
bool Inventory::DeleteItemFromBody(int position)
{
	if (itemList.NumNodes() == 0) {
		cout << "DeleteItemFromBody: no items to delete" << endl;
		return false;
	}
	return itemList.DeleteBody(position);
}

// +++++++++++++++++++
// search function
// +++++++++++++++++++
ItemNode* Inventory::SearchByName(const string& name)
{
	if (itemList.NumNodes() == 0) {
		cout << "SearchByName: no items to search" << endl;
		return nullptr;
	}
	return itemList.GetNodeByName(name);
}
ItemNode* Inventory::SearchByPosition(int position)
{
	if (itemList.NumNodes() == 0) {
		cout << "SearchByPosition: no items to search" << endl;
		return nullptr;
	}
	return itemList.GetNodeByPosition(position);
}
int Inventory::GetNodePosition(ItemNode* node)
{
	return itemList.GetNodeByNode(node);
}

// +++++++++++++++++++++++++++++++++++++++
// quicksort and quicksort helper function
// +++++++++++++++++++++++++++++++++++++++
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
	if(itemList.GetHead() == a) itemList.SetHead(b);
	else if (itemList.GetHead() == b) itemList.SetHead(a);
	
	// update tail
	if (itemList.GetTail() == a) itemList.SetTail(b);
	else if (itemList.GetTail() == b) itemList.SetTail(a);

	// fix boundaries
	if (itemList.GetHead()) itemList.GetHead()->SetPrev(nullptr);
	if (itemList.GetTail()) itemList.GetTail()->SetNext(nullptr);
}
void Inventory::SwapNodesData(ItemNode* a, ItemNode* b)
{
	Item temp = a->GetItem();
	a->SetItem(b->GetItem());
	b->SetItem(temp);
}
bool Inventory::CompareNode(const Item a, const Item b, int attribute, bool order) {
	// order = true for ascending, false for decending
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
ItemNode* Inventory::PartitionAscending(ItemNode* first, ItemNode* last, int attribute)
{
	// check if first and last are not null
	if (!first || !last) throw "Partition: null node";

	try {
		// set pivot as last element
		Item pivot = last->GetItem();
		// set 'i' the index of first element, it is nullptr
		ItemNode* i = first->GetPrev();

		// loop through the list from first to last
		// if the current element is smaller than or equal to the pivot
		for(ItemNode* j = first; j != last; ) {
			// save next node before swapping
			ItemNode* nextJ = j->GetNext();

			// if current element is <= pivot (for ascending order)
			if (CompareNode(j->GetItem(), pivot, attribute, true)) {
				// move i to the next position and swap it with j
				i = (i == nullptr) ? first : i->GetNext();

				SwapNodesData(i, j);
			}
			j = nextJ;
		}

		// move i to the current pivot position and swap it with the pivot
		i = (i == nullptr) ? first : i->GetNext();
		SwapNodesData(i, last);
		return i;
	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
		return nullptr;
	}
}
ItemNode* Inventory::PartitionDescending(ItemNode* first, ItemNode* last, int attribute)
{	
	if (!first || !last) throw "Partition: null node";

	try {
		Item pivot = last->GetItem();
		ItemNode* i = first->GetPrev();

		for (ItemNode* j = first; j != last; ) {
			ItemNode* nextJ = j->GetNext();
			// if current element is >= pivot (for descending order)
			if (CompareNode(j->GetItem(), pivot, attribute, false)) {
				i = (i == nullptr) ? first : i->GetNext();
				SwapNodesData(i, j);
			}
			j = nextJ;
		}

		i = (i == nullptr) ? first : i->GetNext();

		SwapNodesData(i, last);
		return i;
	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
		return nullptr;
	}
}
void Inventory::QuickSortAscending(ItemNode* first, ItemNode* last, int attribute)
{
	// stop quicksort if the list is empty
	// or only one element
	if (first == nullptr || last == nullptr) return;
	if (first == last || first == last->GetNext()) return;

	try {
		// partition list and get pivot position
		ItemNode* pivot = PartitionAscending(first, last, attribute);

		// recursive sort left side of pivot
		QuickSortAscending(first, pivot->GetPrev(), attribute);
		//recursive sort right side of pivot
		QuickSortAscending(pivot->GetNext(), last, attribute);
	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
	}
}
void Inventory::QuickSortDescending(ItemNode* first, ItemNode* last, int attribute)
{
	if (first == nullptr || last == nullptr) return;
	if (first == last || first == last->GetNext()) return;

	try {
		ItemNode* pivot = PartitionDescending(first, last, attribute);

		QuickSortDescending(first, pivot->GetPrev(), attribute);
		QuickSortDescending(pivot->GetNext(), last, attribute);
	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
	}
}
bool Inventory::QuickSort(int attribute, int order)
{
	if (itemList.NumNodes() == 0) {
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

	ItemNode* first = itemList.GetHead();
	ItemNode* last = itemList.GetTail();

	if (order == 1) QuickSortAscending(first, last, attribute);
	else QuickSortDescending(first, last, attribute);

	return true;
}

int Inventory::GetItemCount() const
{
	return itemList.NumNodes();
}

void Inventory::ClearAllNodes()
{
	// delete all nodes one by one from head
	while (itemList.NumNodes() > 0) {
		itemList.DeleteHead();
	}
}

bool Inventory::LoadFromFile(const string& filename)
{
	// clear current inventory before loading new data
	ClearAllNodes();

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

			// use stringstream to break the line into parts
			stringstream ss(line);

			// extract values separated by "//"
			getline(ss, name, '/');
			ss.ignore(1);
			getline(ss, typeStr, '/');
			ss.ignore(1);
			getline(ss, priceStr, '/');
			ss.ignore(1);
			getline(ss, quantityStr, '/');

			// trim whitespace from name
			name.erase(0, name.find_first_not_of(" "));
			name.erase(name.find_last_not_of(" ") + 1);
			// remove all spaces from typeStr, priceStr, and quantityStr
			typeStr.erase(remove(typeStr.begin(), typeStr.end(), ' '), typeStr.end());
			priceStr.erase(remove(priceStr.begin(), priceStr.end(), ' '), priceStr.end());
			quantityStr.erase(remove(quantityStr.begin(), quantityStr.end(), ' '), quantityStr.end());
		
			// convert string price to float and string quantity to int
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

			Item item(name, type, price, quantity);
			AddItemToTail(item);
		}
		catch (exception& e) {
			cout << "Error parsing line: " << line << endl;
			cout << "Error message: " << e.what() << endl;
		}
	};
	// close file
	file.close();
	return true;
}

bool Inventory::SaveToFile(const string& filename)
{
	// open file for writing
	// if it doesn't exist, create it, if it does exist, overwrite it
	ofstream file(filename);

	if(!file.is_open()) {
		cout << "Could not open file" << endl;
		return false;
	}

	file << "NAME // TYPE // PRICE // QUANTITY" << endl;
	ItemNode* temp = itemList.GetHead();
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

	// close file
	file.close();
	return true;
}
