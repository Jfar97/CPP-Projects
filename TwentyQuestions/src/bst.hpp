#ifndef bst_hpp
#define bst_hpp

#include <iostream>
#include <cstdlib>
#include <string>

using std::string;

// Struct definition for the node component that will be used to build out the binary search tree
struct Node
{
	// Data is used to determine the position of the node when inserting it into the tree
	int data;
	// Question and guess store the data for the twenty question game
	string question;
	string guess;
	// left and right are node branches that allow further branching in the tree
	Node* left;
	Node* right;
	// Constructor
	Node(int value, const string& question, const string& guess) : data(value), question(question), guess(guess), left(nullptr), right(nullptr) {}
};

// Class definition of the BinarySearchTree used to create the twenty question tree model, defined inside bst.cpp
class BinarySearchTree
{
public:
	BinarySearchTree();
	Node* insertNode(Node* rootNode, int value, const string& question, const string& guess);
	Node* getRootNode();
	void printTree(Node* treeRootNode);
private:
	// Root node is the first node of the tree from which all other nodes will branch from
	Node* rootNode;
};


#endif 