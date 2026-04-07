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

	ItemNode* GetHead() const { return itemHead; };
	ItemNode* GetCurrentNode() const { return itemCurrent; };

	void SetHead(ItemNode* head) { itemHead = head; };
	void SetCurrentNode(ItemNode* current) { itemCurrent = current; };

	void InsertHead(Item item);
	void InsertTail(Item item);
	void InsertBody(Item item, int position);
	void DeleteHead();
	void DeleteTail();
	void DeleteBody(int position);

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

