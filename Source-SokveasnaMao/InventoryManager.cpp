#include "InventoryManager.h"

InventoryManager::InventoryManager() {
	inventory = new Inventory();
	option = -1;
}

InventoryManager::~InventoryManager()
{
	delete inventory;
}

void InventoryManager::DisplayInventory()
{
	inventory->DisplayList();
}

void InventoryManager::SortInventory()
{
	int choice;
	cout << "Sort by:" << endl;
	cout << "1. Id" << endl;
	cout << "2. Name" << endl;
	cout << "3. Price" << endl;
	cout << "4. Quantity" << endl;
	cout << "0. Back" << endl;
	cin >> choice;

	switch (choice)
	{
	case 1:
		//inventory->SortById();
		cout << "Inventory sorted successfully" << endl;
	case 2:
		//inventory->SortByName();
		cout << "Inventory sorted successfully" << endl;
		break;
	case 3:
		//inventory->SortByPrice();
		cout << "Inventory sorted successfully" << endl;
		break;
	case 4:
		//inventory->SortByQuantity();
		cout << "Inventory sorted successfully" << endl;
		break;
	case 0:
		return;
	default:
		cout << "Invalid input." << endl;
		break;
	}
}

void InventoryManager::AddItem()
{
	string name;
	int typeInput;
	float price;
	int quantity;
	
	cout << "Enter item name: ";
	getline(cin, name);
	cout << "Enter item type (0 = Armor, 1 = Consumable, 2 = Utilities, 3 = Weapon): ";
	cin >> typeInput;
	ItemType type = static_cast<ItemType>(typeInput);

	cout << "Enter price: ";
	cin >> price;
	cout << "Enter quantity: ";
	cin >> quantity;
	Item newItem(name, type, price, quantity);

	inventory->AddItem(newItem);
	
	cout << "Item added successfully" << endl;
}

void InventoryManager::EditItem()
{
	int choice = -1;
	cout << "What kind of search" << endl;
	cout << "1. Id" << endl;
	cout << "2. Name" << endl;
	cout << "0. Back" << endl;
	cin >> choice;
	switch (choice) {
	case 1: {
		int key = -1;
		cout << "Enter id: ";
		cin >> key;
		ItemNode* node = inventory->SearchById(key);


	}
	case 2: {
		int key = -1;
		cout << "Enter id: ";
		cin >> key;
		ItemNode* node = inventory->SearchById(key);


	}

	case 3:
	default:
		cout << "Invalid input" << endl;
		break;
	}
}

void InventoryManager::DeleteItem()
{
	int choice = -1;
	cout << "What kind of search" << endl;
	cout << "1. Id" << endl;
	cout << "2. Name" << endl;
	cout << "0. Back" << endl;
	cin >> choice;
	switch (choice) {
	case 1:
	case 2:
	case 3:
	default:
		cout << "Invalid input" << endl;
		break;
	}
}

void InventoryManager::LoadInventory()
{
	inventory->LoadFromFile("Inventory.txt");
}

void InventoryManager::SaveInventory()
{
	inventory->SaveToFile("Inventory2.txt");
}

void InventoryManager::DisplayMenu()
{
	DisplayMDSHeader();
	cout << "1. Display Inventory" << endl;
	cout << "2. Sort Inventory" << endl;
	cout << "3. Add Item" << endl;
	cout << "4. Edit Item" << endl;
	cout << "5. Delete Item" << endl;
	cout << "6. Load Inventory from File" << endl;
	cout << "7. Saved Inventory to File" << endl;
	cout << "0. Exit" << endl;
	cout << "Enter option: ";
}

void InventoryManager::DisplayMDSHeader() {
	cout << "***********************************************************************" << endl;
	cout << endl;
	cout << "Bachelor of Software Engineering" << endl;
	cout << "Media Design School" << endl;
	cout << "Auckland,    New Zealand" << endl;
	cout << "(c) Year 1 Media Design School" << endl;
	cout << endl;
	cout << "Author                  :   Sokveasna Mao" << endl;
	cout << "Email                   :   maosokveasna48@gmail.com" << endl;
	cout << "Component code and name :   GD1P02 - Algorithms and Data Structures" << endl;
	cout << "Description             :   Inventory System and Sorting" << endl;
	cout << endl;
	cout << "**************************************************************************" << endl;
	cout << endl;
}

void InventoryManager::Run()
{
	while (option != 0) {
		DisplayMenu();
		cin >> option;
		switch (option) {
		case 1:
			system("cls");
			DisplayInventory();
			break;
		case 2:
			SortInventory();
			break;
		case 3:
			cin.ignore();
			AddItem();
			break;
		case 4:
			EditItem();
			break;
		case 5:
			DeleteItem();
			break;
		case 6:
			LoadInventory();
			break;
		case 7:
			SaveInventory();
			break;
		case 0:
			system("cls");
			cout << "Yameroe come back" << endl;
			exit(0);
		default:
			cout << "Invalid input. Please try again." << endl;
			break;
		}
	}
}
