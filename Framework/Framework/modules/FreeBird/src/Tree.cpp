#include "Tree.h"
#include <iostream>
#include <queue>

Node::Node(int value, std::string data)
{
	_value = value;
	_data = data;
	leftNode = nullptr;
	rightNode = nullptr;
}

Node::Node(int value)
{
	_value = value;
	_data = " ";
	leftNode = nullptr;
	rightNode = nullptr;
}

Tree::Tree()
{
	rootNode = nullptr;
}

Tree::Tree(Node*& item)
{
	rootNode = item;
}

void Tree::Destroy()
{
	Destroy(rootNode);
}

void Tree::AddNode(int value, std::string data)
{
	Node* newNode = new Node(value, data);

	if (rootNode == nullptr)
	{
		rootNode = newNode;
	}
	else
	{
		std::queue<Node*> q;
		Node* current = nullptr;

		q.push(rootNode);

		while (!q.empty())
		{
			current = q.front();
			q.pop();

			if (current->leftNode != nullptr)
			{
				q.push(current->leftNode);
			}
			else
			{
				current->leftNode = newNode;
				break;
			}

			if (current->rightNode != nullptr)
			{
				q.push(current->rightNode);
			}
			else
			{
				current->rightNode = newNode;
				break;
			}
		}
	}
}

bool Tree::IsEmpty()
{
	if (rootNode == nullptr)
		return true;
	else
		return false;
}

void Tree::BFT()
{
	std::cout << "BFT:" << std::endl;

	if (rootNode != nullptr)
	{

		std::queue <Node*> q;
		Node* current = nullptr;

		q.push(rootNode);

		while (!q.empty())
		{
			current = q.front();
			q.pop();

			std::cout << current->_data << std::endl;

			if (current->leftNode != nullptr)
			{
				q.push(current->leftNode);
			}

			if (current->rightNode != nullptr)
			{
				q.push(current->rightNode);
			}
		}
	}
	else
	{
		std::cout << "No Root Node!" << std::endl;
	}
}

int Tree::GetHeight(Node* node)
{
	if (node == nullptr)
		return 0;
	else
		return 1 + std::max(GetHeight(node->leftNode), GetHeight(node->rightNode));
}
