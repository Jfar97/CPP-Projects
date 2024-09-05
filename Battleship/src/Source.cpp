#include<iostream>
#include<string>
#include<unordered_map>
#include<cstdlib>
#include<vector>

using namespace std;


// Macros
// N represents the board size on a side
#define N 10
// Other macros act as directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


// Maps for ship health and names
unordered_map<int, int> shipHealth = {
	{1, 5}, {2, 4}, {3, 3}, {4, 3}, {5, 2}
};
unordered_map<int, string> shipNames = {
	{1, "Carrier"}, {2, "Battleship"}, {3, "Cruiser"}, {4, "Submarine"}, {5, "Destroyer"}
};


// Gameboard
// 0 is empty water
// 1-5 are the five ships
// -1 is a miss
// 6 is a hit
int board[N][N];


// Battleship class
class Ship
{
public:
	Ship(int number, string name, int health)
	{
		shipNumber = number;
		this->name = name;
		this->health = health;
		sunk = false;
	}
	void setName(string name)
	{
		this->name = name;
	}
	string getName()
	{
		return this->name;
	}
	void setHealth(int health)
	{
		this->health = health;
	}
	void gotHit()
	{
		this->health--;
	}
	void checkHealth()
	{
		if (health == 0)
		{
			sunk = true;
			cout << "You sunk my battleship!" << endl;
			cout << name << " has been sunk" << endl << endl;
		}
	}
	int getHealth()
	{
		return this->health;
	}
	// Number is used to pick out the correlating health and name from the maps
	void setNumber(int number)
	{
		shipNumber = number;
	}
	int getNumber()
	{
		return shipNumber;
	}
	bool checkIfSunk()
	{
		return sunk;
	}
private:
	// The number that represents which ship it is in the unordered_maps
	int shipNumber;
	// Ship name and health are based upon the values in the unordered_maps corresponding to the shipNumber
	string name;
	int health;
	// Boolean state if the ship has been sunk - i.e. all squares of the ship have been hit
	bool sunk;
};


// Prints the gameboard from the perspective of what the player see
// This is the print method used in the game
void printPlayerGameBoard()
{
	// Prints column numbers
	cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
	// Prints row numbers at beginning of each row
	for (int i = 0; i < N; i++)
	{
		// Check to only print one space on row 10 to align row numbers
		if (i == 9)
		{
			cout << i + 1 << " ";
		}
		else
		{
			cout << i + 1 << "  ";
		}
		// Prints the game board row after the row number
		for (int j = 0; j < N; j++)
		{
			if (board[i][j] == 6)
			{
				cout << "H ";
			}
			else if (board[i][j] == -1)
			{
				cout << "m ";
			}
			else
			{
				cout << "~ ";
			}
		}
		cout << endl;
	}
}


// Prints the game board with the ships visible
// Used for debugging - this function is not used in the actual game
void printGameBoard()
{
	cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
	for (int i = 0; i < N; i++)
	{
		if (i == 9)
		{
			cout << i + 1 << " ";
		}
		else
		{
			cout << i + 1 << "  ";
		}
		for (int j = 0; j < N; j++)
		{
			if (board[i][j]==0)
			{
				cout << "~ ";
			}
			else if (board[i][j] > 0)
			{
				cout << "[]";
			}
		}
		cout << endl;
	}
}


// Prints the number values of each square of the game board
// Used for debugging - this function is not used in the actual game
void printGameBoardNums()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}


// Iterates over the gameboard and sets all int values to 0 for a new game
void setUpBoard()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			board[i][j] = 0;
		}
	}
}


// Generates a random column or row number within the range of macro N that the computer uses to place down the ships
int randRowCol()
{
	int rnd = 0 + (rand() % 10);
	return rnd;
}


// Generates a random direction that the computer uses to place down the ships
int randDirection()
{
	int rnd = 0 + (rand() % 4);
	return rnd;
}


// Checks to see if a ship can be placed in a direction from a starting point without intersection any other ships
bool checkIntersection(int direction, int shipNum, int row, int col)
{
	// Remove the square of the ship take up by the starting position
	int shipLength = shipHealth[shipNum]-1;
	while (shipLength > 0)
	{
		// Moves across the board based up the direction parameter given
		switch (direction) {
			case NORTH:	// North moves up by reducing row number
				row--;
				break;
			case EAST:	// East moves right by increasing column number
				col++;
				break;
			case SOUTH:	// South moves down by increasing row number
				row++;
				break;
			case WEST:	// West moves left by decreasing column number
				col--;
				break;
		}
		// If the new position moved to on the board is not 0, then it is occupied and true is returned to indicate there is an intersection
		if (board[row][col]!=0)
		{
			return true;
		}
		// Reduce shipLength since a new square was placed down successfully
		shipLength--;
	}
	return false;
}


// Checks to see which direction a ship can be placed where it will not run off the game board and will not intersect with another ship
int checkAvailableDirections(int ship, int row, int col)
{
	int direction=-1;
	// Reduce ship length due to the first square of the ship being placed at the starting position
	int shipLength = shipHealth[ship]-1;
	while(direction==-1)
	{
		// Gets a random direction to try and place the ship
		direction = randDirection();
		// Switch statement checks if the ship will fit on the board if it is placed in the selected direction from the starting row and column
		switch (direction) {
			case NORTH:
				if (shipLength > row)
				{
					direction = -1;
				}
				break;
			case EAST:
				if (shipLength + col > 9)
				{
					direction = -1;
				}
				break;
			case SOUTH:
				if (shipLength + row > 9)
				{
					direction = -1;
				}
				break;
			case WEST:
				if (shipLength > col)
				{
					direction = -1;
				}
				break;
		}
		// Call function above to check for ships intersecting with one another
		if (checkIntersection(direction, ship, row, col) == true)
		{
			direction = -1;
		}
	}
	// Once a valid direction passes all the tests, it is returnted as the direction to place the next ship
	return direction;
}


// Places a given ship down on the game board
void placeShip(int direction, int shipNum, int row, int col)
{
	// Remove square that is placed at starting position
	int shipLeft = shipHealth[shipNum] - 1;
	while (shipLeft>0)
	{
		// Places the ship down based upon the direction
		switch (direction) {
			case NORTH:
				row--;
				break;
			case EAST:
				col++;
				break;
			case SOUTH:
				row++;
				break;
			case WEST:
				col--;
				break;
		}
		// Place down ship by changing square number and decrease ship length by 1
		board[row][col] = shipNum;
		shipLeft--;
	}
}


// Iterates over all 5 ships and places them down so they fit on the board and do not intersect one another
void generateShips()
{
	int row;
	int col;
	int shipNum = 1;
	// Iterates over the 5 ships in the unordered_maps
	while (shipNum < 6)
	{
		// Creates a random starting position
		row = randRowCol();
		col = randRowCol();
		// Initial check to see if the spot is empty
		if (board[row][col] == 0)
		{
			// Places the ship down and then finds a direction for the ship to finish being placed down
			board[row][col] = shipNum;
			int shipDirection = checkAvailableDirections(shipNum, row, col);
			placeShip(shipDirection, shipNum, row, col);
			shipNum++;
		}
	}
	
}


// Gets a valid row input from the user
int getRow()
{
	string rawInput;
	int row;
	while (1)
	{
		cout << "Choose a row between 1 and 10: ";
		getline(cin, rawInput);
		// Check for empty input
		if (rawInput.empty())
		{
			cout << "Empty input. Please enter a number. ";
			continue;
		}
		// Only numbers check
		if (rawInput.find_first_not_of("0123456789") != string::npos)
		{
			cout << "Invalid input. Please only enter numbers. ";
			continue;
		}
		// Valid int number check
		try {
			row = stoi(rawInput);
		}
		catch (const out_of_range&) {
			cout << "Number is too large. ";
			continue;
		}
		// Valid range check
		if (row >= 1 && row <= 10)
		{
			break;
		}
		else
		{
			cout << "Invalid row selection. ";
		}
	}
	return row;
}


// Gets a valid column input from the user
int getCol()
{
	string rawInput;
	int col;
	while (1)
	{
		cout << "Choose a column between 1 and 10: ";
		getline(cin, rawInput);
		// Check for empty input
		if (rawInput.empty())
		{
			cout << "Empty input. Please enter a number. ";
			continue;
		}
		// Only numbers check
		if (rawInput.find_first_not_of("0123456789") != string::npos)
		{
			cout << "Invalid input. Please only enter numbers. ";
			continue;
		}
		// Valid int check
		try {
			col = stoi(rawInput);
		}
		catch(const out_of_range&) {
			cout << "Number is too large. ";
			continue;
		}
		// Valid range check
		if (col >= 1 && col <= 10)
		{
			break;
		}
		else
		{
			cout << "Invalid column selection. ";
		}
	}
	return col;
}


// Iterates through a vector containing the ships on the board and checks to see if all the ships have been sunk indicating the game is over
bool checkAllSunk(vector<Ship> ships)
{
	for (int i = 0;i < ships.size();i++)
	{
		if (ships[i].checkIfSunk() == false)
		{
			return false;
		}
	}
	return true;
}


// Performs all parts of the players move, and returns the number of the hit ship or 0 for a miss
int playerMove()
{
	int row;
	int col;
	// Ensures the player picks a spot that has not already been selected
	while (1)
	{
		row = getRow() - 1;
		col = getCol() - 1;
		if (board[row][col] == -1 || board[row][col] == 6)
		{
			cout << endl << "Spot has already been fired upon, make another selection" << endl;
		}
		else
		{
			break;
		}
	}
	// Changes the board value to a miss or hit depening if the spot was occupied
	if (board[row][col] == 0)
	{
		board[row][col] = -1;
		cout << endl << "Miss" << endl << endl;
		return 0;
	}
	else
	{
		int shipHit = board[row][col];
		board[row][col] = 6;
		cout << endl << "Hit!" << endl << endl;
		return shipHit;
	}
}


// Plays the battleship game using the ships given inside the vector parameter
void playBattleship(vector<Ship> ships)
{
	setUpBoard();
	generateShips();
	bool gameOver = false;
	int hit=0;
	printPlayerGameBoard();
	while (!gameOver)
	{
		// Performs the player move and checks if the ship was hit
		hit = playerMove();
		if (hit != 0)
		{
			// Subtract one from hit since C++ arrays start at 0 not 1
			ships[hit - 1].gotHit();
			ships[hit - 1].checkHealth();
		}
		printPlayerGameBoard();
		// Check if the game is over
		if (checkAllSunk(ships) == true)
		{
			cout << endl;
			cout << "~~~~~~~~~~~~~~" << endl;
			cout << "~ Game Over! ~" << endl;
			cout << "~~~~~~~~~~~~~~" << endl;
			gameOver = true;
		}
	}
}


int main()
{
	// Seed time for random num generation and set up the ship vector for the game
	srand(time(0));
	vector<Ship> enemyShips;
	for (int i = 1; i < 6; i++)
	{
		Ship newShip = Ship(i, shipNames[i], shipHealth[i]);
		enemyShips.push_back(newShip);
	}
	/*
	for (int i = 1; i < 6; i++)
	{
		cout << enemyShips[i - 1].getName() << endl;
		cout << enemyShips[i - 1].getNumber() << endl;
		cout << enemyShips[i - 1].getHealth() << endl;
	}
	*/

	playBattleship(enemyShips);
	/*
	setUpBoard();
	generateShips();
	printGameBoard();
	*/
	return 0;
}