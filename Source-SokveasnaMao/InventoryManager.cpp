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
	inventory->DisplayInventory();
}

void InventoryManager::SortInventory()
{
	DisplayAttributeMenu();
	option = Validation::ValidateIntInput("Enter option: ", 0, 5);
	cout << "1. Accending" << endl;
	cout << "2. Decending" << endl;
	cout << "0. Back" << endl;
	int order = Validation::ValidateIntInput("Enter option: ", 0, 2);
	switch (option)
	{
	case 1:
		if(order == 1) inventory->QuickSortByName();
		else inventory->QuickSortByName();
		break;
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
	option = Validation::ValidateIntInput("Enter choice: ", 0, 2);
	switch (option) {
	case 1: {
		string name = Validation::ValidateStringInput("Enter name: ");
		ItemNode* node = inventory->SearchByName(name);
		DisplayAttributeMenu();
		option = Validation::ValidateIntInput("Enter choice: ", 0, 4);
		switch (option)
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
		case 0: return;
		default:
			cout << "Invalid input" << endl;
			break;
		}
		break;
	}
	case 2: {
		int position = Validation::ValidateIntInput("Enter position: ", 0, inventory->GetItemCount());
		ItemNode* node = inventory->SearchByPosition(position);
		DisplayAttributeMenu();
		option = Validation::ValidateIntInput("Enter choice: ", 0, 4);
		switch (option)
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
		case 0: return;
		default:
			cout << "Invalid input" << endl;
			break;
		}
		break;
	}
	case 0: return;
	default:
		cout << "Invalid input" << endl;
		break;
	}
}

void InventoryManager::DeleteItem()
{
	DisplaySearchMenu();
	option = Validation::ValidateIntInput("Enter choice: ", 0, 2);
	switch (option) {
	case 1: {
		ItemNode* node = inventory->SearchByName(Validation::ValidateStringInput("Enter name: "));
		inventory->DeleteItem(node);
		break;
	}
	case 2: {
		ItemNode* node = inventory->SearchByPosition(Validation::ValidateIntInput("Enter position: ", 0, inventory->GetItemCount()));
		inventory->DeleteItem(node);
		break;
	}
	case 0: return;
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
		option = Validation::ValidateIntInput("Enter choice: ", 0, 7);
		switch (option) {
		case 1:
			system("cls");
			DisplayInventory();
			break;
		case 2:
			system("cls");
			SortInventory();
			break;
		case 3:
			system("cls");
			cin.ignore();
			AddItem();
			break;
		case 4:
			system("cls");
			EditItem();
			break;
		case 5:
			system("cls");
			DeleteItem();
			break;
		case 6:
			system("cls");
			LoadInventory();
			break;
		case 7:
			system("cls");
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
