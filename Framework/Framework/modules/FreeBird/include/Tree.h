#pragma once
#include <string>

class Node
{
public:
	Node(int value, std::string data);
	Node(int value);

	std::string _data;
	int _value;

	Node* leftNode;
	Node* rightNode;
};


class Tree
{
public:
	Tree();
	Tree(Node*& item);

	~Tree()
	{
		Destroy();
	}

	void Destroy();

	void AddNode(int value, std::string data = " ");

	bool IsEmpty();

	void BFT();

	int GetHeight(Node* node);

private:

	void Destroy(Node*& p)
	{
		if (p != nullptr)
		{
			Destroy(p->_left);
			Destroy(p->_right);
			delete p;
			p = nullptr;
		}
	}

	Node* rootNode;

};