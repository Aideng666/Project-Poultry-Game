#include "Tree.h"
#include <iostream>
#include <queue>

Node::Node(int data)
{
	_data = data;
	leftNode = nullptr;
	rightNode = nullptr;
}

Tree::Tree()
{
	rootNode = nullptr;
}

void Tree::Destroy()
{
	Destroy(rootNode);
}

void Tree::AddNode(int  data)
{
	Node* newNode = new Node(data);

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

Node* Tree::GetRootNode()
{
	return rootNode;
}
