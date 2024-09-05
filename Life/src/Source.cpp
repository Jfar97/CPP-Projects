#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono>

using std::string;
using std::vector;

// Board Macros - Defines the board to be 5x5 and the last cell to be number 24
const int BOARD_SIZE = 5;
const int MAX_CELL = BOARD_SIZE * BOARD_SIZE - 1; // Have to subtract 1 since arrays all start at 0


// Takes in a 2D int vector and sets all values to 0 to reset the board
void ResetBoard(vector<vector<int>>& board)
{
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			board[row][col] = 0;
		}
	}
}


// Check if the player wishes to quit by entering the single character q or Q
bool quitCheck()
{
	string input;
	std::cout << "Press q to quit or any other key to continue: \n";
	std::getline(std::cin, input);
	if (input == "q" || input == "Q")
	{
		return true;
	}
	return false;
}


// Gets a user input and parses out the valid inputs on the board and then returns them in a vector
vector<int> GetStartingPositions()
{
	string rawInput;
    vector<int> validInputs;

    while (1)
    {
		// Takes in the raw input as a string
        std::cout << "Enter the integer positions of the cells starting at 0 and ending at " << MAX_CELL << ": \n";
        std::getline(std::cin, rawInput);

		// Input is not empty check
		if (rawInput.empty())
		{
			continue;
		}

		// Only numbers check and commas
		if (rawInput.find_first_not_of("0123456789,") != string::npos)
		{
			std::cout << "Invalid input. Please only enter numbers. ";
			continue;
		}

		// Creates a string stream object from the input so that it can be parsed through
        std::stringstream ss(rawInput);
        string nextItem;		
        validInputs.clear();	// Reset input array on each loop
        bool valid = true;

		// Loops through each line, parsing into the nextItem string until a comma is found
        while (std::getline(ss, nextItem, ','))
        {
			// Removes white space to avoid input issues
            nextItem.erase(0, nextItem.find_first_not_of(" \t"));
            nextItem.erase(nextItem.find_last_not_of(" \t") + 1);

            try
            {
				// Attempts to turned the parsed string section into a number and add it to the input array if it is valid
                int nextNumber = std::stoi(nextItem);
                if (nextNumber >= 0 && nextNumber <= MAX_CELL)
                {
                    validInputs.push_back(nextNumber);
                }
                else
                {
                    std::cout << nextNumber << " was removed for being out of range\n";
                }
            }
            catch (const std::exception&)
            {
                std::cout << "Invalid input: " << nextItem << ". Skipping.\n";
                valid = false;
            }
        }
		
		std::cout << std::endl;
		for (int i = 0; i < validInputs.size(); i++)
		{
			std::cout << validInputs[i] << " is a given input\n";
		}
		std::cout << std::endl;
		
		// Makes sure the input was valid (only valid ints) and the input array isn't empty
        if (valid && !validInputs.empty())
        {
            return validInputs;
        }
        else if (validInputs.empty())
        {
            std::cout << "No valid inputs given, please try again\n\n";
        }
    }
}

// Prints the current generation of the 2D int vector board parameter, representing living cells with *
void PrintBoard(const vector<vector<int>>& board)
{
	for (int i = 0; i < 13; i++)
	{
		std::cout << "-";
	}
	std::cout << "\n|";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << i+1 << " ";
	}
	std::cout << "|\n";
	for (int i = 0; i < BOARD_SIZE+8; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		std::cout << "|";
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			if (board[row][col] == 1)
			{
				std::cout << "* ";
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << "|" << std::endl;
	}
	for (int i = 0; i < BOARD_SIZE + 8; i++)
	{
		std::cout << "-";
	}
	std::cout << "\n\n\n";
}


// Iterates over the board and calculates how many neighbors each cell has and posts the amount to the neighborGrid
void CountNeighbors(const vector<vector<int>>& board, vector<vector<int>>& neighborGrid)
{
	// First nested set of for loops iterates over each cell of the board
	for (int row = 0; row < BOARD_SIZE; row++)
	{
		for (int col = 0; col < BOARD_SIZE; col++)
		{
			int currentNeighbors = 0;
			// Second nested set of for loops iterates over the eight surrounding cells of each cell
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					// Same cell as first loop check
					if (i == 0 && j == 0)
					{
						continue;
					}
					// Update position of neighbor cell being examined
					int rowCheck = row + i;
					int colCheck = col + j;
					// Checks if the cell positions are valid and contain a living cell
					if ((rowCheck >= 0 && rowCheck < BOARD_SIZE) && (colCheck >= 0 && colCheck < BOARD_SIZE))
					{
						currentNeighbors += board[rowCheck][colCheck];
					}
				}
			}
			neighborGrid[row][col] = currentNeighbors;
		}
	}
}


// Calculates which cells will be alive and dead in the next generation for the first 2D int board vector based upon the second 2D int vector neighborGrid
void NextGeneration(vector<vector<int>>& board, const vector<vector<int>>& neighborGrid)
{
	for (int row = 0; row < BOARD_SIZE; ++row)
	{
		for (int col = 0; col < BOARD_SIZE; ++col)
		{
			// If a cell has 3 alive neighbors it will be alive next gen
			if (neighborGrid[row][col] == 3)
			{
				board[row][col] = 1;
			}
			// If a cell has two neighbors and is alive already it remains alive next gen
			else if (neighborGrid[row][col] == 2 && board[row][col] == 1)
			{
				board[row][col] = 1;
			}
			// Otherwise cell dies
			else
			{
				board[row][col] = 0;
			}
		}
	}
}


// Function that plays the game of life
void PlayGameOfLife()
{
	// lifeBoard is the actual board that the game occurs on
	vector<vector<int>> lifeBoard(BOARD_SIZE, vector<int>(BOARD_SIZE));
	// neighborGrid tracks the number of neighbors for each cell
	vector<vector<int>> neighborGrid(BOARD_SIZE, vector<int>(BOARD_SIZE));

	while (1)
	{
		// Gets the starting positions and set those board values to 1
		vector<int> startingPositions = GetStartingPositions();
		for (int i = 0; i < startingPositions.size(); i++)
		{
			int pos = startingPositions[i];
			int posRow = pos / BOARD_SIZE;
			int posCol = pos % BOARD_SIZE;
			if ((posRow < BOARD_SIZE && posRow >= 0) && (posCol < BOARD_SIZE && posCol >= 0))
			{
				lifeBoard[posRow][posCol] = 1;
			}
		}

		// Prints the generations starting at the set up with generation 0 and then pritns the next 10 generations
		for (int generation = 0; generation < 11; generation++)
		{
			std::cout << "Generation " << generation << ": \n";
			PrintBoard(lifeBoard);
			CountNeighbors(lifeBoard, neighborGrid);
			NextGeneration(lifeBoard, neighborGrid);
			// Added delay between generations to increase visual clarity
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		// Check if the use wishes to quit the game or play again
		if (quitCheck() == true)
		{
			break;
		}
		ResetBoard(lifeBoard);
	}
	std::cout << "Thank you for playing!\n";
}


int main()
{
	PlayGameOfLife();
	return 0;
}