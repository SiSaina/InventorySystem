#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(const Item& item)
{
}

bool Inventory::DeleteItem(int id)
{
	return false;
}

ItemNode* Inventory::SearchById(int id)
{
	return nullptr;
}

ItemNode* Inventory::SearchByName(string name)
{
	return nullptr;
}

void Inventory::SortById()
{
}

void Inventory::SortByName()
{
}

void Inventory::SortByPrice()
{
}

void Inventory::SortByQuantity()
{
}

void Inventory::Display() const
{
}

void Inventory::LoadFromFile(const string& filename)
{
}

void Inventory::SaveToFile(const string& filename)
{
}
