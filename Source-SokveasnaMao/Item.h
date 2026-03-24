#pragma once
#include <iostream>
#include <string>
#include "ItemType.h"
using namespace std;
class Item
{
private:
	string name;
	ItemType type;
	float price;
	int quantity;
public:
	Item() {
		name = "Unknown";
		type = Armor;
		price = 0.0f;
		quantity = 0;
	}
	Item(string name) {
		name = name;
		type = Armor;
		price = 0.0f;
		quantity = 0;
	};
	string GetName() const { return name; };
	ItemType GetType() const { return type; };
	float GetPrice() const { return price; };
	int GetQuantity() const { return quantity; };
	void SetName(string name) { name = name; };
	void SetType(ItemType type) { type = type; };
	void SetPrice(float price) { price = price; };
	void SetQuantity(int quantity) { quantity = quantity; };
};
