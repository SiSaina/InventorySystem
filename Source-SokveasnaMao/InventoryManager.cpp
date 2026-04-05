#include "InventoryManager.h"

InventoryManager::InventoryManager() {
	inventory = new Inventory();
}

InventoryManager::~InventoryManager()
{
	delete inventory;
}

void InventoryManager::DisplayInventory()
{
	inventory->DisplayInventory();
}

void InventoryManager::SortInventory()
{
	DisplayAttributeMenu();

	//input attribute to sort
	int attribute = Validation::ValidateIntInput("Enter option: ", 0, 4);
	if (attribute == 0) return;
	cout << "1. Accending" << endl;
	cout << "2. Decending" << endl;
	cout << "0. Back" << endl;

	//input order to sort
	int order = Validation::ValidateIntInput("Enter option: ", 0, 2);
	if (order == 0) return;

	inventory->QuickSort(attribute, order);

	system("cls");
	DisplayInventory();
}

void InventoryManager::AddItem()
{
	string name = Validation::ValidateStringInput("Enter name: ");
	ItemType type = Validation::ValidateItemTypeInput("Enter type (Armor, Consumable, Utility, Weapon): ");
	float price = Validation::ValidateFloatInput("Enter price: ", 0.1f, 10000.0f);
	int quantity = Validation::ValidateIntInput("Enter quantity: ", 1, 1000);

	Item newItem(name, type, price, quantity);
	inventory->AddItem(newItem);
	
	cout << "Item added successfully" << endl;
}

void InventoryManager::EditItem()
{
	DisplaySearchMenu();
	int searchOption = Validation::ValidateIntInput("Enter choice: ", 0, 2);
	if (searchOption == 0) return;

	ItemNode* node = nullptr;

	if(searchOption == 1) {
		string name = Validation::ValidateStringInput("Enter name: ");
		node = inventory->SearchByName(name);
	}
	else if(searchOption == 2) {
		int position = Validation::ValidateIntInput("Enter position: ", 0, inventory->GetItemCount());
		node = inventory->SearchByPosition(position);
	}
	else {
		cout << "Invalid input" << endl;
		return;
	}

	DisplayAttributeMenu();
	int attributeOption = Validation::ValidateIntInput("Enter choice: ", 0, 4);
	if (attributeOption == 0) return;

	switch (attributeOption)
	{
	case 1: {
		node->GetItem().SetName(Validation::ValidateStringInput("Enter new name: "));
		break;
	}
	case 2: {
		node->GetItem().SetType(Validation::ValidateItemTypeInput("Enter new type (Armor, Consumable, Utility, Weapon): "));
		break;
	}
	case 3: {
		node->GetItem().SetPrice(Validation::ValidateFloatInput("Enter new price: ", 0.1f, 10000.0f));
		break;
	}
	case 4: {
		node->GetItem().SetQuantity(Validation::ValidateIntInput("Enter new quantity: ", 1, 1000));
		break;
	}
	default:
		cout << "Invalid input" << endl;
	}
}

void InventoryManager::DeleteItem()
{
	DisplaySearchMenu();
	int searchOption = Validation::ValidateIntInput("Enter choice: ", 0, 2);
	if (searchOption == 0) return;
	
	ItemNode* node = nullptr;

	if(searchOption == 1) {
		string name = Validation::ValidateStringInput("Enter name: ");
		node = inventory->SearchByName(name);
	}
	else if(searchOption == 2) {
		int position = Validation::ValidateIntInput("Enter position: ", 0, inventory->GetItemCount());
		node = inventory->SearchByPosition(position);
	}
	else {
		cout << "Invalid input" << endl;
		return;
	}
	inventory->DeleteItem(node);
}

void InventoryManager::LoadInventory()
{
	inventory->LoadFromFile("Inventory.txt");
}

void InventoryManager::SaveInventory()
{
	inventory->SaveToFile("Inventory.txt");
}

void InventoryManager::DisplaySearchMenu()
{
	cout << "Search by:" << endl;
	cout << "1. Name" << endl;
	cout << "2. Position" << endl;
	cout << "0. Back" << endl;
}

void InventoryManager::DisplayAttributeMenu()
{
	cout << "Attribute" << endl;
	cout << "1. Name" << endl;
	cout << "2. Type" << endl;
	cout << "3. Price" << endl;
	cout << "4. Quantity" << endl;
	cout << "0. Exit" << endl;
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
}

void InventoryManager::DisplayMDSHeader() {
	cout << "***********************************************************************\n\n";
	cout << "Bachelor of Software Engineering\n";
	cout << "Media Design School\n";
	cout << "Auckland,    New Zealand\n";
	cout << "(c) Year 1 Media Design School\n\n";
	cout << "Author                  :   Sokveasna Mao\n";
	cout << "Email                   :   maosokveasna48@gmail.com\n";
	cout << "Component code and name :   GD1P02 - Algorithms and Data Structures\n";
	cout << "Description             :   Inventory System and Sorting\n\n";
	cout << "**************************************************************************\n\n";
}

void InventoryManager::Run()
{
	int searchOption = -1;
	while (searchOption != 0) {
		DisplayMenu();

		searchOption = Validation::ValidateIntInput("Enter choice: ", 0, 7);
		system("cls");
		
		switch (searchOption) {
		case 1:
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
			cout << "Yameroe come back" << endl;
			exit(0);
		default:
			cout << "Invalid input. Please try again." << endl;
		}
	}
}
