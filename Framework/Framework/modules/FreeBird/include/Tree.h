#pragma once
#include <string>

class Node
{
public:
	Node(int data);

	int _data;

	Node* leftNode;
	Node* rightNode;
};


class Tree
{
public:
	Tree();
	Tree(int data) : rootNode(new Node(data)) {}

	~Tree()
	{
		Destroy();
	}

	void Destroy();

	void AddNode(int data);

	bool IsEmpty();

	void BFT();

	int GetHeight(Node* node);

	Node* GetRootNode();

private:

	void Destroy(Node*& p)
	{
		if (p != nullptr)
		{
			Destroy(p->leftNode);
			Destroy(p->rightNode);
			delete p;
			p = nullptr;
		}
	}

	Node* rootNode;

};