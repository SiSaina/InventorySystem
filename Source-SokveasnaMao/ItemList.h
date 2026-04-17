#pragma once
#include "ItemNode.h"
#include "Validation.h"
#include <iomanip>
#include <iostream>
class ItemList
{
private:
	ItemNode* itemHead;
	ItemNode* itemCurrent;
	ItemNode* itemTail;
	int itemSize;
public:
	ItemList();
	~ItemList();

	// get number of item nodes in the list
	int NumNodes() const;

	// display item list
	// Name   Type   Price   Quantity
	// ------------------------------
	// Sword  Weapon 100     2
	void DisplayList();

	// get item head, current and tail node
	ItemNode* GetHead() const;
	ItemNode* GetCurrentNode() const;
	ItemNode* GetTail() const;

	// set item head, current and tail node
	void SetHead(ItemNode* head);
	void SetCurrentNode(ItemNode* current);
	void SetTail(ItemNode* tail);

	// insert doubly linked list node, head, tail, and body
	bool InsertHead(Item item);
	bool InsertTail(Item item);
	bool InsertBody(Item item, int position);

	// delete doubly linked list node, head, tail, and body
	bool DeleteHead();
	bool DeleteTail();
	bool DeleteBody(int position);

	// get node, take position, return node
	ItemNode* GetNodeByPosition(int position);
	// get node, take name, return node
	ItemNode* GetNodeByName(string name);
	// get node position, take node, return position
	int GetNodeByNode(ItemNode* item);

	// move current node to head, tail, next node, and prev node
	void MoveCurrentNodeToHead();
	void MoveCurrentNodeToTail();
	bool MoveCurrentNodeNext();
	bool MoveCurrentNodePrev();
};

