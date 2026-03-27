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
		getline(ss, name, '/');
		getline(ss, typeStr, '/');
		getline(ss, typeStr, '/');
		getline(ss, priceStr, '/');
		getline(ss, priceStr, '/');
		getline(ss, quantityStr, '/');
		
		name.erase(remove(name.begin(), name.end(), ' '), name.end());
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

		file << temp->GetId() << " "
			<< item.GetName() << " "
			<< item.GetType() << " "
			<< item.GetPrice() << " "
			<< item.GetQuantity()
			<< endl;

		temp = temp->GetNext();
	}

	file.close();

	cout << "Saved to " << filename << endl;;
}
