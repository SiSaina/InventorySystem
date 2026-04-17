#include "InventoryManager.h"

void InventoryManager::DisplayInventory()
{
	try {
		// check if inventory is empty
		if (inventory.GetItemCount() == 0) {
			cout << "DisplayInventory: Inventory is empty" << endl;
			return;
		}
		inventory.DisplayInventory();
	}
	catch (exception& e) {
		cout << "Display Inventory Error: " << e.what() << endl;
		return;
	}
}

void InventoryManager::SortInventory()
{
	try {
		// check if inventory is empty
		if (inventory.GetItemCount() == 0) {
			cout << "SortInventory: No items to sort" << endl;
			return;
		}

		// display attribute menu (name, type, price, quantity)
		DisplayAttributeMenu();

		//input attribute to sort
		int attributeOption = Validation::ValidateIntInput("Enter option: ", 0, 4);
		if (attributeOption == 0) {
			ClearScreen();
			return;
		}
		// display order menu (accending, decending)
		cout << "1. Accending" << endl;
		cout << "2. Decending" << endl;
		cout << "0. Back" << endl;
		//input order to sort
		int orderOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
		if (orderOption == 0) {
			ClearScreen();
			return;
		}

		// perform the function quicksort
		inventory.QuickSort(attributeOption, orderOption);

		ClearScreen();
		DisplayInventory();
	}
	catch (exception& e) {
		cout << "Sort Inventory Error: " << e.what() << endl;
		return;
	}
}

void InventoryManager::AddItem()
{
	try {
		// Ask where to insert item (head, tail, body)
		DisplayItemPositionMenu();
		int positionOption = Validation::ValidateIntInput("Enter option: ", 0, 3);
		if (positionOption == 0) {
			ClearScreen();
			return;
		}

		// input item detail from user
		string name = Validation::ValidateStringInput("Enter name: ");
		DisplayItemTypeMenu();
		ItemType type = Validation::ValidateItemTypeInput("Enter type: ");
		float price = Validation::ValidateFloatInput("Enter price: ", MIN_PRICE, MAX_PRICE);
		int quantity = Validation::ValidateIntInput("Enter quantity: ", MIN_QUANTITY, MAX_QUANTITY);

		// create new item
		Item newItem(name, type, price, quantity);

		// add to head, tail or body by position, if position not exist, display error message
		if (positionOption == 1) inventory.AddItemToHead(newItem);
		else if (positionOption == 2) inventory.AddItemToTail(newItem);
		else {
			int positionChoice = Validation::ValidateIntInput("Enter position: ", 1, inventory.GetItemCount() + 1);
			// no need to check position exist since it is already checked in ValidateIntInput
			// positionChoice - 1 because the user interface start from 1
			// but the inventory is start from 0
			inventory.AddItemToBody(newItem, positionChoice - 1);
		}

		ClearScreen();
		cout << "Item added successfully" << endl;
	}
	catch (exception& e) {
		cout << "Add Item Error: " << e.what() << endl;
		return;
	}
}

void InventoryManager::EditItem()
{
	try {
		// check if inventory is empty
		if (inventory.GetItemCount() == 0) {
			cout << "EditItem: No items to edit" << endl;
			return;
		}

		// Choose search method
		DisplaySearchMenu();
		int searchOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
		if (searchOption == 0) {
			ClearScreen();
			return;
		}

		ItemNode* tempNode = nullptr;

		//search by name
		if (searchOption == 1) {
			string searchName = Validation::ValidateStringInput("Enter name: ");
			tempNode = inventory.SearchByName(searchName);
		}
		// search by position
		else {
			int positionOption = Validation::ValidateIntInput("Enter position: ", 1, inventory.GetItemCount() + 1);
			tempNode = inventory.SearchByPosition(positionOption - 1);
		}

		// if not found
		if (tempNode == nullptr) {
			ClearScreen();
			cout << "Item not found" << endl;
			return;
		}

		// Choose which attribute to edit
		DisplayAttributeMenu();
		int attributeOption = Validation::ValidateIntInput("Enter choice: ", 0, 4);
		if (attributeOption == 0) {
			ClearScreen();
			return;
		}

		tempNode->DisplayNode();
		// Update selected attribute
		switch (attributeOption)
		{
		case 1: { // edit name
			tempNode->GetItem().SetName(Validation::ValidateStringInput("Enter new name: "));
			break;
		}
		case 2: { // edit type
			DisplayItemTypeMenu();
			tempNode->GetItem().SetType(Validation::ValidateItemTypeInput("Enter new type: "));
			break;
		}
		case 3: { // edit price
			tempNode->GetItem().SetPrice(Validation::ValidateFloatInput("Enter new price: ", MIN_PRICE, MAX_PRICE));
			break;
		}
		case 4: { // edit quantity
			tempNode->GetItem().SetQuantity(Validation::ValidateIntInput("Enter new quantity: ", MIN_QUANTITY, MAX_QUANTITY));
			break;
		}
		default:
			cout << "EditItem: Invalid input" << endl;
			break;
		}
		ClearScreen();
		tempNode->DisplayNode();
		cout << "Item edited successfully" << endl;
	}
	catch (exception& e) {
		cout << "Edit Item Error: " << e.what() << endl;
		return;
	}
}

void InventoryManager::DeleteItem()
{
	try {
		// check if inventory is empty
		if (inventory.GetItemCount() == 0) {
			cout << "DeleteItem: No items to delete" << endl;
			return;
		}

		// choose delete position (head, tail, or body)
		DisplayItemPositionMenu();
		int positionOption = Validation::ValidateIntInput("Enter option: ", 0, 3);
		if (positionOption == 0) {
			ClearScreen();
			return;
		}

		// delete from head
		if (positionOption == 1) {
			inventory.DeleteItemFromHead();
			ClearScreen();
			cout << "Item Delete successfully" << endl;
			return;
		}
		// delete from tail
		else if (positionOption == 2) {
			inventory.DeleteItemFromTail();
			ClearScreen();
			cout << "Item Delete successfully" << endl;
			return;
		}

		// delete from body (need search)
		DisplaySearchMenu();
		int searchOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
		if (searchOption == 0) {
			ClearScreen();
			return;
		}

		ItemNode* tempNode = nullptr;
		int positionChoice = -1;

		// search by name
		if (searchOption == 1) {
			string searchName = Validation::ValidateStringInput("Enter name: ");
			tempNode = inventory.SearchByName(searchName);
			if (!tempNode) {
				cout << "DeleteItem: No item found with name " << searchName << endl;
				return;
			}
			// convert node to position
			positionChoice = inventory.GetNodePosition(tempNode);
			inventory.DeleteItemFromBody(positionChoice);
		}
		// search by position
		else if (searchOption == 2) {
			// no need to check position exist since it is already checked in ValidateIntInput
			positionChoice = Validation::ValidateIntInput("Enter position: ", 1, inventory.GetItemCount() + 1);
			tempNode = inventory.SearchByPosition(positionChoice - 1);
			if (!tempNode) {
				cout << "DeleteItem: No item found at position " << positionChoice << endl;
				return;
			}
			// positionChoice - 1 because the user interface start from 1
			// but the inventory is start from 0
			inventory.DeleteItemFromBody(positionChoice - 1);
		}
		ClearScreen();
		cout << "Item delete successfully" << endl;
	}
	catch (exception& e) {
		cout << "Delete Item Error: " << e.what() << endl;
		return;
	}
}

void InventoryManager::LoadInventory()
{
	try {
		// display specific or default file menu
		DisplayFileMenu();
		int pathOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
		if (pathOption == 0) {
			ClearScreen();
			return;
		}

		string filePath;

		// custom file path
		if (pathOption == 1) {
			cout << "Enter file path to load inventory: ";
			getline(cin, filePath);
		}
		// default file path
		else if (pathOption == 2) {
			filePath = "Inventory.txt";
		}

		// validate file type
		if (!Validation::ValidateFilePath(filePath)) {
			cout << "LoadInventory: Invalid file. Only .txt allow" << endl;
			return;
		}
		// load data
		if (!inventory.LoadFromFile(filePath)) {
			cout << "LoadInventory: Failed to load inventory from " << filePath << endl;
			return;
		}
		ClearScreen();
		cout << "Inventory loaded successfully from " << filePath << endl;
	}
	catch (exception& e) {
		cout << "Load Inventory Error: " << e.what() << endl;
		return;
	}
}

void InventoryManager::SaveInventory()
{
	try {
		// check if inventory is empty
		if (inventory.GetItemCount() == 0) {
			cout << "SaveInventory: No items to save" << endl;
			return;
		}

		DisplayFileMenu();
		int pathOption = Validation::ValidateIntInput("Enter option: ", 0, 2);
		if (pathOption == 0) {
			ClearScreen();
			return;
		}

		string filePath;

		// custom file path
		if (pathOption == 1) {
			cout << "Enter file path to save inventory: ";
			getline(cin, filePath);
		}
		// default file path
		else if (pathOption == 2) {
			filePath = "Inventory.txt";
		}

		// validate file type
		if (!Validation::ValidateFilePath(filePath)) {
			cout << "SaveInventory: Invalid file. Only .txt allow" << endl;
			return;
		}
		// save data
		if (!inventory.SaveToFile(filePath)) {
			cout << "SaveInventory: Failed to save inventory to " << filePath << endl;
			return;
		}
		ClearScreen();
		cout << "Inventory saved successfully from " << filePath << endl;
	}
	catch (exception& e) {
		cout << "Save Inventory Error: " << e.what() << endl;
		return;
	}
}

void InventoryManager::ClearScreen()
{
	system("cls");
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
	try {
		int searchOption = -1;
		while (searchOption != 0) {
			DisplayMenu();

			searchOption = Validation::ValidateIntInput("Enter choice: ", 0, 7);
			ClearScreen();

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
				cout << "Exiting program..." << endl;
				exit(0);
			default:
				cout << "Invalid input. Please try again." << endl;
			}
		}
	}
	catch (exception& e) {
		cout << "Run Function Error: " << e.what() << endl;
		return;
	}
}
