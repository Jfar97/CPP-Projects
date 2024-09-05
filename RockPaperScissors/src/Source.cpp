#include <iostream>
#include <string>
#include <cstdlib>

using std::string;


// Gets the player's input move using r, p, and s, and also allows the player to quit by using q.
// This method still needs reworking to properly handle inputs with spaces between characters or strings
char getPlayerMove()
{
	string input;
	char playerMove;
	while (1)
	{
		std::cout << "Press q to quit or please select your move: r for rock, p for paper, s for scissors\n";
		std::getline(std::cin, input);
		// Check for empty input
		if (input.empty())
		{
			std::cout << "\nEmpty input.\n";
			continue;
		}
		// Ensure the player has entered a single and valid character
		if (input.length() > 1)
		{
			std::cout << "\nInvalid input.\n";
			continue;
		}
		playerMove = input[0];
		// Ensure the input is one of the four valid options
		if (playerMove != 'r' && playerMove != 'p' && playerMove != 's' && playerMove != 'q')
		{
			std::cout << "\nInvalid selection.\n";
			continue;
		}
		break;
	}
	return playerMove;
}


// Generates the computer's move by generating a random number of either 1, 2, or 3
char getCompMove()
{
	int rnd = 0 + (rand() % 3);
	if (rnd == 1)
	{
		return 'r';
	}
	else if (rnd == 2)
	{
		return 'p';
	}
	else
	{
		return 's';
	}
}


// Checks both the user input and the generated computer move and compares them to see who wins, returns 1 for a player win, -1 for a computer win, and 0 for a draw
void winnerCheck(char player, char computer)
{
	// Player chose rock
	if (player == 'r')
	{
		std::cout << "Player's move: Rock\n";
		if (computer == 's')
		{
			std::cout << "Computer's move: Scissors\n";
			std::cout << "You win!\n";
		}
		else if (computer == 'p')
		{
			std::cout << "Computer's move: Paper\n";
			std::cout << "Computer wins!\n";
		}
		else
		{
			std::cout << "Computer's move: Rock\n";
			std::cout << "Tie!\n";
		}
	}
	// Player chose paper
	else if (player == 'p')
	{
		std::cout << "Player's move: Paper\n";
		if (computer == 'r')
		{
			std::cout << "Computer's move: Rock\n";
			std::cout << "You win!\n";
		}
		else if (computer == 's')
		{
			std::cout << "Computer's move: Scissors\n";
			std::cout << "Computer wins!\n";
		}
		else
		{
			std::cout << "Computer's move: Paper\n";
			std::cout << "Tie!\n";
		}
	}
	// Player chose scissors
	else
	{
		std::cout << "Player's move: Scissors\n";
		if (computer == 'p')
		{
			std::cout << "Computer's move: Paper\n";
			std::cout << "You win!\n";
		}
		else if (computer == 'r')
		{
			std::cout << "Computer's move: Rock\n";
			std::cout << "Computer wins!\n";
		}
		else
		{
			std::cout << "Computer's move: Scissors\n";
			std::cout << "Tie!\n";
		}
	}
}


// Plays the actual rock paper scissors game by checking the user's input, generating a computer move if the game continues, and then checking who won in a loop
void playRockPaperScissors()
{
	char playerCheck;
	char compCheck;
	std::cout << "Welcome to Rock Paper Scissors! ";
	while (1)
	{
		playerCheck = getPlayerMove();
		if (playerCheck == 'q')
		{
			break;
		}
		compCheck = getCompMove();
		winnerCheck(playerCheck, compCheck);
		std::cout << std::endl;
	}
	std::cout << "Thank you for playing!\n";
}

// Seed the time for the random number generator and then plays the game loop
int main()
{
	srand(time(0));
	playRockPaperScissors();
	return 0;
}