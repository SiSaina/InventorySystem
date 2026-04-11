#pragma once
#include "ItemNode.h"
class ItemList
{
private:
	ItemNode* itemHead;
	ItemNode* itemCurrent;
	ItemNode* itemTail;
	int itemSize;
	int nextId;
public:
	ItemList();
	~ItemList();

	// get item head and current node
	ItemNode* GetHead() const { return itemHead; };
	ItemNode* GetCurrentNode() const { return itemCurrent; };

	// set item head node
	void SetHead(ItemNode* head) { itemHead = head; };

	// insert doubly linked list node, head, tail, and body
	bool InsertHead(Item item);
	bool InsertTail(Item item);
	bool InsertBody(Item item, int position);

	// delete doubly linked list node, head, tail, and body
	bool DeleteHead();
	bool DeleteTail();
	bool DeleteBody(int position);

	// get item node by position, return the node, return nullptr if position not exist
	ItemNode* GetNode(int position) const;
	// find item node by node, return the position of the node, return -1 if node not exist
	int FindNodeByNode(ItemNode* item);

	// check if item node exists by position, return the node if exists, nullptr otherwise
	ItemNode* FindNodeByPosition(int position);
	// check if item node exists by name, return the node if exists, nullptr otherwise
	ItemNode* FindNodeByName(string name);
	// get number of item nodes in the list
	int NumNodes() const;
	// display item list
	void DisplayList();

	// move current node to head, tail, and next node
	void MoveCurrentNodeToHead();
	void MoveCurrentNodeToTail();
	bool MoveCurrentNodeNext();
	bool MoveCurrentNodePrev();
	// get current item node, return nullptr if current node is nullptr
	ItemNode* GetCurrent() const;
};

