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
	if (inventory->GetItemCount() == 0) {
		cout << "No items to sort" << endl;
		return;
	}
	DisplayAttributeMenu();

	//input attribute to sort
	int attributeOption = Validation::ValidateIntInput("Enter option: ", 0, 4);
	if (attributeOption == 0) return;
	cout << "1. Accending" << endl;
	cout << "2. Decending" << endl;
	cout << "0. Back" << endl;

	//input order to sort
	int orderOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
	if (orderOption == 0) return;

	inventory->QuickSort(attributeOption, orderOption);

	system("cls");
	DisplayInventory();
}

void InventoryManager::AddItem()
{
	DisplayItemPositionMenu();
	int positionOption = Validation::ValidateIntInput("Enter option: ", 0, 3);
	if (positionOption == 0) return;

	string name = Validation::ValidateStringInput("Enter name: ");
	DisplayItemTypeMenu();
	ItemType type = Validation::ValidateItemTypeInput("Enter type: ");
	float price = Validation::ValidateFloatInput("Enter price: ", MIN_PRICE, MAX_PRICE);
	int quantity = Validation::ValidateIntInput("Enter quantity: ", MIN_QUANTITY, MAX_QUANTITY);

	Item newItem(name, type, price, quantity);

	if(positionOption == 1) inventory->AddItemToHead(newItem);
	else if(positionOption == 2) inventory->AddItemToTail(newItem);
	else {
		int positionChoice = Validation::ValidateIntInput("Enter position: ", 0, inventory->GetItemCount());
		inventory->AddItemToBody(newItem, positionChoice);
	}

	cout << "Item added successfully" << endl;
}

void InventoryManager::EditItem()
{
	if(inventory->GetItemCount() == 0) {
		cout << "No items to edit" << endl;
		return;
	}
	DisplaySearchMenu();
	int searchOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
	if (searchOption == 0) return;

	ItemNode* tempNode = nullptr;

	if(searchOption == 1) {
		string searchName = Validation::ValidateStringInput("Enter name: ");
		tempNode = inventory->SearchByName(searchName);
	}
	else {
		int positionOption = Validation::ValidateIntInput("Enter position: ", 0, inventory->GetItemCount());
		tempNode = inventory->SearchByPosition(positionOption);
	}

	DisplayAttributeMenu();
	int attributeOption = Validation::ValidateIntInput("Enter choice: ", 0, 4);
	if (attributeOption == 0) return;

	switch (attributeOption)
	{
	case 1: {
		tempNode->GetItem().SetName(Validation::ValidateStringInput("Enter new name: "));
		break;
	}
	case 2: {
		DisplayItemTypeMenu();
		tempNode->GetItem().SetType(Validation::ValidateItemTypeInput("Enter new type: "));
		break;
	}
	case 3: {
		tempNode->GetItem().SetPrice(Validation::ValidateFloatInput("Enter new price: ", MIN_PRICE, MAX_PRICE));
		break;
	}
	case 4: {
		tempNode->GetItem().SetQuantity(Validation::ValidateIntInput("Enter new quantity: ", MIN_QUANTITY, MAX_QUANTITY));
		break;
	}
	default:
		cout << "Invalid input" << endl;
	}
}

void InventoryManager::DeleteItem()
{
	if (inventory->GetItemCount() == 0) {
		cout << "No items to delete" << endl;
		return;
	}
	DisplayItemPositionMenu();
	int positionOption = Validation::ValidateIntInput("Enter option: ", 0, 3);
	if (positionOption == 0) return;

	try {
		if (positionOption == 1) {
			inventory->DeleteItemFromHead();
			return;
		}
		else if (positionOption == 2) {
			inventory->DeleteItemFromTail();
			return;
		}
		
		DisplaySearchMenu();
		int searchOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
		if (searchOption == 0) return;

		ItemNode* tempNode = nullptr;
		int positionChoice = -1;

		if (searchOption == 1) {
			string searchName = Validation::ValidateStringInput("Enter name: ");
			tempNode = inventory->SearchByName(searchName);
			if (!tempNode) {
				cout << "No item found with name " << searchName << endl;
				return;
			}
			positionChoice = inventory->GetNodePosition(tempNode);
			inventory->DeleteItemFromBody(positionChoice);
		}
		else if (searchOption == 2) {
			// no need to check position exist since it is already checked in ValidateIntInput
			positionChoice = Validation::ValidateIntInput("Enter position: ", 0, inventory->GetItemCount());
			inventory->DeleteItemFromBody(positionChoice);
		}
	}
	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
		return;
	}
}

void InventoryManager::LoadInventory()
{
	DisplayFileMenu();
	int pathOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
	if (pathOption == 0) return;

	string filePath;

	if (pathOption == 1) {
		cout << "Enter file path to load inventory: ";
		getline(cin, filePath);
	}else if(pathOption == 2) {
		filePath = "Inventory.txt";
	}
	
	if(!Validation::ValidateFilePath(filePath)) {
		cout << "Invalid file. Only .txt allow" << endl;
		return;
	}
	if(!inventory->LoadFromFile(filePath)) {
		cout << "Failed to load inventory from " << filePath << endl;
		return;
	}
	cout << "Inventory loaded successfully from " << filePath << endl;
}

void InventoryManager::SaveInventory()
{
	DisplayFileMenu();
	int pathOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
	if (pathOption == 0) return;

	string filePath;

	if (pathOption == 1) {
		cout << "Enter file path to save inventory: ";
		getline(cin, filePath);
	}
	else if (pathOption == 2) {
		filePath = "Inventory.txt";
	}

	if (!Validation::ValidateFilePath(filePath)) {
		cout << "Invalid file. Only .txt allow" << endl;
		return;
	}
	if (!inventory->SaveToFile(filePath)) {
		cout << "Failed to save inventory from " << filePath << endl;
		return;
	}
	cout << "Inventory saved successfully from " << filePath << endl;
}

void InventoryManager::DisplayFileMenu()
{
	cout << "1. Specific path" << endl;
	cout << "2. Default" << endl;
	cout << "0. Back" << endl;
}

void InventoryManager::DisplayItemPositionMenu()
{
	cout << "Operate item by position" << endl;
	cout << "1. Head" << endl;
	cout << "2. Tail" << endl;
	cout << "3. Body" << endl;
	cout << "0. Back" << endl;
}

void InventoryManager::DisplayItemTypeMenu()
{
	cout << "Item type" << endl;
	cout << "1. Armor" << endl;
	cout << "2. Consumable" << endl;
	cout << "3. Utility" << endl;
	cout << "4. Weapon" << endl;
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
