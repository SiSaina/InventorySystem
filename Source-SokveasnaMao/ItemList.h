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

	ItemNode* GetNodeByPosition(int position);
	ItemNode* GetNodeByName(string name);
	int GetNodeByNode(ItemNode* item);

	// get number of item nodes in the list
	int NumNodes() const;
	// display item list
	void DisplayList();

	// move current node to head, tail, and next node
	void MoveCurrentNodeToHead();
	void MoveCurrentNodeToTail();
	bool MoveCurrentNodeNext();
	bool MoveCurrentNodePrev();
};

