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
	Item(string name, ItemType type, float price, int quantity) {
		this->name = name;
		this->type = type;
		this->price = price;
		this->quantity = quantity;
	};
	string GetName() const { return name; };
	ItemType GetType() const { return type; };
	string GetTypeString() const {
		switch (type) {
		case Armor: return "Armor";
		case Consumable: return "Consumable";
		case Utility: return "Utility";
		case Weapon: return "Weapon";
		default: return "Unknown";
		}
	};
	float GetPrice() const { return price; };
	int GetQuantity() const { return quantity; };
	void SetName(string name) { this->name = name; };
	void SetType(ItemType type) { this->type = type; };
	void SetPrice(float price) { this->price = price; };
	void SetQuantity(int quantity) { this->quantity = quantity; };
};
