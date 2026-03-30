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

void Inventory::AddItem(const Item& item)
{
	itemList->InsertTail(item);
}

void Inventory::DeleteItem(ItemNode* item)
{
	int position = itemList->FindNodeByNode(item);
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

pair<ItemNode*, ItemNode*> Inventory::FindNodeToSwap(ItemNode*& head, int x, int y) {
	ItemNode* node1 = nullptr;
	ItemNode* node2 = nullptr;
	ItemNode* temp = head;

	int index = 0;

	while (temp != nullptr) {
		if (index == x) node1 = temp;
		if (index == y) node2 = temp;
		temp->GetNext();
	}
	return { node1, node2 };
}

void Inventory::SwapNodes(ItemNode* a, ItemNode* b) {
	if (!a || !b) throw "Invalid input";
	Item temp = a->GetItem();
	a->SetItem(b->GetItem());
	b->SetItem(temp);
}

int Inventory::PartitionByName(int low, int high) {
	ItemNode* pivotNode = itemList->GetNode(high);
	return low;
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

void Inventory::DisplayInventory() const
{
	itemList->DisplayList();
}

void Inventory::LoadFromFile(const string& filename)
{

	ifstream file(filename);

	if (!file.is_open())
	{
		cout << "Cannot open: " << filename << endl;
		return;
	}
	string line;

	getline(file, line);

	while(getline(file, line)) {
		if (line.empty()) continue;
		string name, typeStr, priceStr, quantityStr;
		
		stringstream ss(line);

		getline(ss, name, '/');
		ss.ignore(1);
		getline(ss, typeStr, '/');
		ss.ignore(1);
		getline(ss, priceStr, '/');
		ss.ignore(1);
		getline(ss, quantityStr, '/');

		name.erase(0, name.find_first_not_of(" "));
		name.erase(name.find_last_not_of(" ") + 1);
		typeStr.erase(remove(typeStr.begin(), typeStr.end(), ' '), typeStr.end());
		priceStr.erase(remove(priceStr.begin(), priceStr.end(), ' '), priceStr.end());
		quantityStr.erase(remove(quantityStr.begin(), quantityStr.end(), ' '), quantityStr.end());
		
		float price = stof(priceStr);
		int quantity = stoi(quantityStr);

		ItemType type;

		if (typeStr == "Armor") type = Armor;
		else if (typeStr == "Consumable") type = Consumable;
		else if (typeStr == "Utility") type = Utility;
		else if (typeStr == "Weapon") type = Weapon;
		else throw "Invalid item type";

		Item item(name, type, price, quantity);
		AddItem(item);
	};

	file.close();
	cout << "Loaded from " << filename << endl;;
}

void Inventory::SaveToFile(const string& filename)
{
	ofstream file(filename);

	if(!file.is_open()) {
		throw "Could not open file";
	}

	ItemNode* temp = itemList->GetNode(0);

	while (temp != nullptr)
	{
		Item item = temp->GetItem();

		file << item.GetName() << " "
			<< item.GetType() << " "
			<< item.GetPrice() << " "
			<< item.GetQuantity()
			<< endl;

		temp = temp->GetNext();
	}

	file.close();

	cout << "Saved to " << filename << endl;;
}
