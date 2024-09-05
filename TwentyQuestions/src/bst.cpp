#include <iostream>
#include <string>
#include "bst.hpp"

// Constructor definition
BinarySearchTree::BinarySearchTree()
{
	// Initialize the root node to null on tree creation
	rootNode = nullptr;
}


// Inserts a new node into the tree based upon the value of the node being inserted
Node* BinarySearchTree::insertNode(Node* rootNode, int value, const string& question, const string& guess)
{
	// A node, either the main root or a branch root that has been navigated too recursively, that is null has the new node placed into its position
	if (rootNode == nullptr)
	{
		Node* newNode = new Node(value, question, guess);
		if (this->rootNode == nullptr)
			this->rootNode = newNode;  // Update the class's rootNode if it's null
		return newNode;
	}
	// Otherwise navigates down the tree based upon the node data
	else if (rootNode->data > value)
	{
		rootNode->left = insertNode(rootNode->left, value, question, guess);
	}
	else // (rootNode->data < value)
	{
		rootNode->right = insertNode(rootNode->right, value, question, guess);
	}
	return rootNode;
}


// Returns the rootnode of a binary search tree object
Node* BinarySearchTree::getRootNode()
{
	return this->rootNode;
}


// Prints the tree out from left to right to ensure the nodes are ordered properly
void BinarySearchTree::printTree(Node* treeRootNode)
{
	if (treeRootNode != NULL)
	{
		printTree(treeRootNode->left);
		std::cout << treeRootNode->data << " ";
		printTree(treeRootNode->right);
	}
}