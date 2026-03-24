#pragma once
#include "ItemNode.h"
class ItemList
{
private:
	ItemNode* itemNode;
	ItemNode* itemCurrent;
	int itemSize;
public:
	ItemList();
	~ItemList();
	void InsertHead(int key, Item item);
	void InsertTail(int key, Item item);
	void InsertBody(int position, int key, Item item);
	void DeleteHead();
	void DeleteTail();
	void DeleteBody(int position);
	ItemNode* GetNode(int position) const;
	ItemNode* FindNode(int key);
	int NumNodes() const;
	bool NodeExists(int key);

	void MoveToHead();
	void MoveToTail();
	bool MoveNext();
	bool MovePrev();
	ItemNode* GetCurrent() const;
	bool IsHead() const;
	bool IsTail() const;
	void ResetCurrent();
};

