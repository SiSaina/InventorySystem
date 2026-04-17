#include "Item.h"

Item::Item()
{
	name = "Unknown";
	type = Armor;
	price = 0.0f;
	quantity = 0;
}
Item::Item(string name, ItemType type, float price, int quantity)
{
	this->name = name;
	this->type = type;
	this->price = price;
	this->quantity = quantity;
}
string Item::GetName() const
{
	return name;
}
ItemType Item::GetType() const
{
	return type;
}
string Item::GetTypeString() const
{
	switch (type)
	{
	case Armor: return "Armor";
	case Consumable: return "Consumable";
	case Utility: return "Utility";
	case Weapon: return "Weapon";
	default: return "Unknown";
	}
}
float Item::GetPrice() const
{
	return price;
}
int Item::GetQuantity() const
{
	return quantity;
}
void Item::SetName(string name)
{
	this->name = name;
}
void Item::SetType(ItemType type)
{
	this->type = type;
}
void Item::SetPrice(float price)
{
	this->price = price;
}
void Item::SetQuantity(int quantity)
{
	this->quantity = quantity;
}