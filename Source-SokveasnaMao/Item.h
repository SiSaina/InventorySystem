#pragma once
#include <iostream>
#include <string>
#include "ItemType.h"
using namespace std;
class Item
{
private:
	string Name;
	ItemType Type;
	float Price;
	int Quantity;
public:
	Item() {
		Name = "Unknown";
		Type = Armor;
		Price = 0.0f;
		Quantity = 0;
	}
	Item(string name) {
		Name = name;
		Type = Armor;
		Price = 0.0f;
		Quantity = 0;
	};
	string GetName() const { return Name; };
	ItemType GetType() const { return Type; };
	float GetPrice() const { return Price; };
	int GetQuantity() const { return Quantity; };
	void SetName(string name) { Name = name; };
	void SetType(ItemType type) { Type = type; };
	void SetPrice(float price) { Price = price; };
	void SetQuantity(int quantity) { Quantity = quantity; };
};
