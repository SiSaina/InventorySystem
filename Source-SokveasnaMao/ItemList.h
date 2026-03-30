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

	void InsertHead(Item item);
	void InsertTail(Item item);
	void InsertBody(int position, Item item);
	void DeleteHead();
	void DeleteTail();
	void DeleteBody(int position);

	ItemNode* GetNode(int position) const;
	int FindNodeByNode(ItemNode* item);
	ItemNode* FindNodeByPosition(int position);
	ItemNode* FindNodeByName(string name);
	int NumNodes() const;
	bool NodeExistsByPosition(int position);

	void DisplayList();

	void MoveToHead();
	void MoveToTail();
	bool MoveNext();
	bool MovePrev();
	ItemNode* GetCurrent() const;
	bool IsHead() const;
	bool IsTail() const;
	void ResetCurrent();
};

