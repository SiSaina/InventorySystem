#pragma once
#include "ItemNode.h"
class ItemList
{
private:
	ItemNode* itemHead;
	ItemNode* itemCurrent;
	int itemSize;
	int nextId;
public:
	ItemList();
	~ItemList();

	// get item head and current node
	ItemNode* GetHead() const { return itemHead; };
	ItemNode* GetCurrentNode() const { return itemCurrent; };

	// set item head and current node
	void SetHead(ItemNode* head) { itemHead = head; };
	void SetCurrentNode(ItemNode* current) { itemCurrent = current; };

	// insert item node, head, tail, and body
	void InsertHead(Item item);
	void InsertTail(Item item);
	void InsertBody(Item item, int position);

	// delete item node, head, tail, and body
	void DeleteHead();
	void DeleteTail();
	void DeleteBody(int position);

	// search item node by name and position
	ItemNode* GetNode(int position) const;
	int FindNodeByNode(ItemNode* item);
	bool FindExistNodeByPosition(int position);
	ItemNode* FindNodeByPosition(int position);
	ItemNode* FindNodeByName(string name);
	int NumNodes() const;
	void DisplayList();

	void MoveToHead();
	void MoveToTail();
	bool MoveNext();
	ItemNode* GetCurrent() const;
};

