#include <iostream>
#include <string>
#include "bst.hpp"

using std::string;


// Checks to see if the player wants to quit the game by entering q or Q, or if they game should continue otherwise
bool quitCheck()
{
	string input;
	// Check for empty input
	while (1)
	{
		std::cout << "Press q to quit or any other key to continue: \n";
		std::getline(std::cin, input);
		if (input.empty())
		{
			std::cout << "Empty input.";
			continue;
		}
		break;
	}
	if (input == "q" || input == "Q")
	{
		return true;
	}
	return false;
}


// Returns the string "y" for yes and "n" for no
string yesOrNo()
{
	string input;
	while (1)
	{
		std::cout << "Please enter y for yes or n for no: \n";
		std::getline(std::cin, input);
		// Check for empty input
		if (input.empty())
		{
			std::cout << "Empty input. ";
			continue;
		}
		if (input.length() > 1)
		{
			std::cout << "Invalid input. ";
			continue;
		}
		if ((input != "y" && input != "Y") && (input != "n" && input != "N"))
		{
			std::cout << "Invalid input. ";
			continue;
		}
		break;
	}
	return input;
}

// Returns 1 if the guess string is printed, and 0 if the question portion is printed
int printNode(Node* currentNode)
{
	if (currentNode->question.empty())
	{
		std::cout << std::endl << currentNode->guess << std::endl;
		return 1;
	}
	else
	{
		std::cout << std::endl << currentNode->question << std::endl;
		return 0;
	}
}


// Creates a BinarySearchTree pointer that contains the nodes with the questions and guesses for the twenty questions game
BinarySearchTree* createGameTree()
{
	BinarySearchTree* tree = new BinarySearchTree();
	Node* root = nullptr;

	//root node
	root = tree->insertNode(root, 40, "Is it a vegetable?", "");

	//Vegetable Half

	//Salad Green branch
	root = tree->insertNode(root, 8, "Is it commonly used as salad greens?", "");
	root = tree->insertNode(root, 2, "Does it contain a high amount of iron?", "");
	root = tree->insertNode(root, 1, "", "Is it Spinach?");
	root = tree->insertNode(root, 4, "Is it always eaten raw?", "");
	root = tree->insertNode(root, 3, "", "Is it Lettuce?");
	root = tree->insertNode(root, 6, "Is it put in coleslaw?", "");
	root = tree->insertNode(root, 5, "", "Is it Cabbage?");
	root = tree->insertNode(root, 7, "", "Is it Kale?");

	//Starchy Vegetable branch
	root = tree->insertNode(root, 14, "Is it a starchy vegetable?", "");
	root = tree->insertNode(root, 12, "Is it served mashed commonly?", "");
	root = tree->insertNode(root, 10, "Is it served candied commonly?", "");
	root = tree->insertNode(root, 13, "", "Is it Beans?");
	root = tree->insertNode(root, 9, "", "Is it Yams?");
	root = tree->insertNode(root, 11, "", "Is it Potatoes?");

	//Seasoning branch
	root = tree->insertNode(root, 22, "Is it used in cooking to season food?", "");
	root = tree->insertNode(root, 16, "Does it help keep away vampires?", "");
	root = tree->insertNode(root, 15, "", "Is it Garlic?");
	root = tree->insertNode(root, 18, "Is it commonly put on burgers?", "");
	root = tree->insertNode(root, 17, "", "Is it an Onion?");
	root = tree->insertNode(root, 20, "Is it a type of onion?", "");
	root = tree->insertNode(root, 19, "", "Is it a Shallot?");
	root = tree->insertNode(root, 21, "", "Is it Chives?");

	//Grows Underground branch
	root = tree->insertNode(root, 28, "Does it grow underground?", "");
	root = tree->insertNode(root, 24, "Is it orange?", "");
	root = tree->insertNode(root, 23, "", "Is it a Carrot?");
	root = tree->insertNode(root, 26, "Is it usually red?", "");
	root = tree->insertNode(root, 25, "", "Is it a Radish?");
	root = tree->insertNode(root, 27, "", "Is it a Turnip?");

	//Green branch
	root = tree->insertNode(root, 34, "Is it green?", "");
	root = tree->insertNode(root, 30, "Is it farmed as long stalks?", "");
	root = tree->insertNode(root, 29, "", "Is it Asparagus?");
	root = tree->insertNode(root, 32, "Is it spherical?", "");
	root = tree->insertNode(root, 31, "", "Is it a Brussel Sprout?");
	root = tree->insertNode(root, 33, "", "Is it Broccoli?");

	//Different Kinds branch
	root = tree->insertNode(root, 36, "Are there a large variety of it?", "");
	root = tree->insertNode(root, 35, "", "Is it a Mushroom?");
	root = tree->insertNode(root, 37, "", "Is it Cauliflower?");

	//Fruit Half
	//Mistaken for Vegetable branch
	root = tree->insertNode(root, 60, "Is it commonly mistaken for a vegetable?", "");
	root = tree->insertNode(root, 44, "Is it commonly put on burgers?", "");
	root = tree->insertNode(root, 42, "Is it red?", "");
	root = tree->insertNode(root, 46, "Can it be spicy?", "");
	root = tree->insertNode(root, 41, "", "Is it a Tomato?");
	root = tree->insertNode(root, 43, "", "Is it a Pickle?");
	root = tree->insertNode(root, 45, "", "Is it a Pepper?");
	root = tree->insertNode(root, 50, "Is it commonly eaten as a side?", "");
	root = tree->insertNode(root, 48, "Is it yellow?", "");
	root = tree->insertNode(root, 47, "", "Is it Corn?");
	root = tree->insertNode(root, 49, "", "Is it Peas?");
	root = tree->insertNode(root, 52, "Is it used in martinis?", "");
	root = tree->insertNode(root, 51, "", "Is it an Olive?");
	root = tree->insertNode(root, 56, "Is it a type of squash?", "");
	root = tree->insertNode(root, 54, "Is it orange?", "");
	root = tree->insertNode(root, 53, "", "Is it a Pumpkin?");
	root = tree->insertNode(root, 55, "", "Is it a Zucchini?");
	root = tree->insertNode(root, 58, "Is it purple?", "");
	root = tree->insertNode(root, 57, "", "Is it an Eggplant?");
	root = tree->insertNode(root, 59, "", "Is it a Cucumber?");

	//Berry in Name branch
	root = tree->insertNode(root, 70, "Is 'berry' in the name?", "");
	root = tree->insertNode(root, 66, "Is it red?", "");
	root = tree->insertNode(root, 62, "Is it spherical?", "");
	root = tree->insertNode(root, 61, "", "Is it a Cranberry?");
	root = tree->insertNode(root, 64, "Is it commonly covered in chocolate and given as a gift?", "");
	root = tree->insertNode(root, 63, "", "Is it a Strawberry?");
	root = tree->insertNode(root, 65, "", "Is it a Raspberry?");
	root = tree->insertNode(root, 68, "Is it spherical?", "");
	root = tree->insertNode(root, 67, "", "Is it a Blueberry?");
	root = tree->insertNode(root, 69, "", "Is it a Blackberry?");

	//Citrus branch
	root = tree->insertNode(root, 78, "Is it a citrus fruit?", "");
	root = tree->insertNode(root, 76, "Do people drink it as a juice commonly?", "");
	root = tree->insertNode(root, 72, "Is it yellow?", "");
	root = tree->insertNode(root, 71, "", "Is it a Lemon?");
	root = tree->insertNode(root, 74, "Is it orange on the inside?", "");
	root = tree->insertNode(root, 73, "", "Is it an Orange?");
	root = tree->insertNode(root, 75, "", "Is it a Grapefruit?");
	root = tree->insertNode(root, 77, "", "Is it a Lime?");

	//Grows on Tree branch
	root = tree->insertNode(root, 100, "Does it grow on a tree?", "");
	root = tree->insertNode(root, 82, "Does it have a shell?", "");
	root = tree->insertNode(root, 80, "Is the shell spiky?", "");
	root = tree->insertNode(root, 79, "", "Is it a Durian?");
	root = tree->insertNode(root, 81, "", "Is it a Coconut?");
	root = tree->insertNode(root, 96, "Does it have a pit?", "");
	root = tree->insertNode(root, 88, "Is it orange?", "");
	root = tree->insertNode(root, 86, "Is it spherical?", "");
	root = tree->insertNode(root, 84, "Is there a Nintendo character named after it?", "");
	root = tree->insertNode(root, 83, "", "Is it a Peach?");
	root = tree->insertNode(root, 85, "", "Is it an Apricot?");
	root = tree->insertNode(root, 87, "", "Is it a Mango?");
	root = tree->insertNode(root, 90, "Is it used in guacamole?", "");
	root = tree->insertNode(root, 89, "", "Is it an Avocado?");
	root = tree->insertNode(root, 94, "Is it purple?", "");
	root = tree->insertNode(root, 92, "Is it spherical?", "");
	root = tree->insertNode(root, 91, "", "Is it a Plum?");
	root = tree->insertNode(root, 93, "", "Is it a Fig?");
	root = tree->insertNode(root, 95, "", "Is it a Cherry?");
	root = tree->insertNode(root, 98, "Is it spherical?", "");
	root = tree->insertNode(root, 97, "", "Is it an Apple?");
	root = tree->insertNode(root, 99, "", "Is it a Pear?");

	//Does not Grow on Tree branch
	root = tree->insertNode(root, 104, "Does it grow on vines?", "");
	root = tree->insertNode(root, 102, "Is it used to make wine?", "");
	root = tree->insertNode(root, 101, "", "Is it a Grape?");
	root = tree->insertNode(root, 103, "", "Is it a Kiwi?");
	root = tree->insertNode(root, 106, "Is it commonly drank as a juice?", "");
	root = tree->insertNode(root, 105, "", "Is it a Pineapple?");
	root = tree->insertNode(root, 108, "Is it yellow?", "");
	root = tree->insertNode(root, 107, "", "Is it a Banana?");
	root = tree->insertNode(root, 109, "", "Is it a Watermelon?");

	return tree;
}


// Plays the twenty question game based upon the binary search tree with questions and guesses inside of the tree
void playTwentyQuestions(BinarySearchTree* tree)
{
	bool keepPlaying = true;
	// Get the starting root or question
	Node* current = tree->getRootNode();

	// Game loop
	while (keepPlaying)
	{
		// Quit check
		if (quitCheck() == true)
		{
			keepPlaying = false;
		}
		std::cout << "You think of a fruit or vegetable and I will try to guess it!\n";
		printNode(current);
		// Inner loop iterates over tree
		while (1)
		{
			string answer = yesOrNo();
			// Answer is yes - move left
			if (answer == "y" || answer == "Y")
			{
				// Navigate to next node to get the next question or guess
				current = current->left;
				// Guess printed - reached leaf
				if (printNode(current) == 1) 
				{
					answer = yesOrNo();
					if (answer == "y" || answer == "Y")
					{
						std::cout << "I win!\n";
						break;
					}
					else
					{
						std::cout << "You win!\n";
						break;
					}
				}
			}
			// Answer is no - move right
			else
			{
				// Navigate to next node to get the next question or guess
				current = current->right;
				// Guess printed - leaf reached
				if (printNode(current) == 1)
				{
					answer = yesOrNo();
					if (answer == "y" || answer == "Y")
					{
						std::cout << "I win!";
						break;
					}
					else
					{
						std::cout << "You win!";
						break;
					}
				}
			}
		}
		std::cout << "\n\n\n";
		// Reset tree
		current = tree->getRootNode();
	}
}



int main()
{
	BinarySearchTree* gameTree = createGameTree();
	playTwentyQuestions(gameTree);
	//gameTree->printTree(gameTree->getRootNode());
	return 0;
}