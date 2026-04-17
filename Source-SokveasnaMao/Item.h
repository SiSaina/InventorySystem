#pragma once
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
	Item();
	Item(string name, ItemType type, float price, int quantity);

	// Getters
	string GetName() const;
	ItemType GetType() const;
	string GetTypeString() const;
	float GetPrice() const;
	int GetQuantity() const;

	// Setters
	void SetName(string name);
	void SetType(ItemType type);
	void SetPrice(float price);
	void SetQuantity(int quantity);
};
