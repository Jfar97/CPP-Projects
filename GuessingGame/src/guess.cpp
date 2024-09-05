#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>


using namespace std;


//Player class represents the player object who is playing the game
class Player
{
public:
	//Constructor for nonexistent player
	Player()
	{
		this->name = "(No Name)";
		this->guesses = -1;
	}
	//Constructor for creating a new plyer to play the game
	Player(string name)
	{
		this->name = name;
		this->guesses = 0;
	}
	//Constructor for reading players from the leader file
	Player(string name, int guesses)
	{
		this->name = name;
		this->guesses = guesses;
	}
	//Getter for the string player name
	string getName()
	{
		return this->name;
	}
	//Setter that increments the player guesses by one
	void makeGuess()
	{
		this->guesses++;
	}
	//Getter for the number of guesses made by the player
	int getGuesses()
	{
		return this->guesses;
	}
private:
	string name;
	int guesses;
};


//LeaderBoard class for the list of the top 5 leaders
class LeaderBoard
{
public:
	//Constructor that fills a new leader board with "empty" players
	LeaderBoard() 
	{
		for (int i = 0; i < 5; ++i) 
		{
			leaders[i] = Player();
		}
	}
	//Reads the leaderboard from the leader file
	void readBoardFromFile()
	{
		//Opens the leader file, or creates a new leader file if none exists
		ifstream leaderList("leaders.txt");
		if (!leaderList)
		{
			ofstream newLeaderList("leaders.txt");
			newLeaderList.close();
			return;
		}
		//Reads the values from the files into local variables that are used to fill the leader member array with players
		string name;
		int guesses;
		int index = 0;
		while (leaderList >> name >> guesses && index < 5)
		{
			leaders[index] = Player(name, guesses);
			index++;
		}
		leaderList.close();
	}
	//Puts a player on the leader list if there is an appropriate spot based upon their number of guesses
	void setSpot(Player player)
	{
		for (int spot = 0; spot < 5; spot++)
		{
			if (leaders[spot].getGuesses() == -1)
			{
				leaders[spot] = player;
				break;
			}
			else if(leaders[spot].getGuesses() > player.getGuesses())
			{
				for (int i = 4; i > spot; i--)
				{
					if (leaders[i - 1].getGuesses() != -1)
					{
						leaders[i] = leaders[i - 1];
					}
				}
				leaders[spot] = player;
				break;
			}
		}
	}
	//Prints out the contents of the leader array
	void printList()
	{
		for (int i = 0; i < 5; ++i) {
			if (leaders[i].getGuesses() > 0) 
			{
				if (leaders[i].getGuesses() == 1)
				{
					cout << "Player " << i + 1 << ": " << leaders[i].getName() << " - " << leaders[i].getGuesses() << " guess" << endl;
				}
				else
				{
					cout << "Player " << i + 1 << ": " << leaders[i].getName() << " - " << leaders[i].getGuesses() << " guesses" << endl;
				}
			}
			else 
			{
				// Handle the case where the player name is empty
				cout << "Player " << i + 1 << ": (No Name)" << endl;
			}
		}
	}
	//Getter for the address of a player object from the leader array at a given index
	Player& getPlayer(int index)
	{
		return leaders[index];
	}
private:
	//The leader list of the 5 players with the lowest number of guesses
	Player leaders[5];
};


//Returns 1 if the user inputs 'q', and returns 0 otherwise
int QuitGameCheck()
{
	string input;
	cout << "Press 'q' to quit or any other key to continue:" << endl;
	getline(cin, input);

	if (input.size() == 1 && input[0] == 'q')
	{
		cout << "Bye Bye!" << endl;
		return 1;
	}

	return 0;
}


//Gets a user input between 10 and 100
int GetGuess()
{
	int guess;

	cout << "Guess a value between 10 and 100: ";

	while (!(cin>>guess) || guess < 10 || guess > 100)
	{
		cout << "Please make sure your guess is between 10 and 100: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return guess;
}


//Writes the leader array from a leaderboard object reference and prints it to a file
void WriteToFile(LeaderBoard& leaders)
{
	ofstream leaderList("leaders.txt");

	if (!leaderList.is_open())
	{
		cout << "Error opening file" << endl;
		return;
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			leaderList << leaders.getPlayer(i).getName() << '\t';
			leaderList << leaders.getPlayer(i).getGuesses() << endl;
		}
		leaderList.close();
	}
}


//Plays the guessing game, checks for quit, and reads/writes the leader list file
void PlayGuessingGame()
{
	while (1)
	{
		//Quit game check
		if (QuitGameCheck() == 1)
		{
			break;
		}

		//Reads the leaderboard
		LeaderBoard leaders;
		leaders.readBoardFromFile();

		//create new player object for game
		string name;
		cout << "Please enter your name to start: ";
		cin >> name;
		Player newPlayer(name);

		//Generate random number
		srand(static_cast<unsigned int>(time(nullptr)));  //Need to seed current time
		int guessNum = rand() % 91 + 10;
		double sqrtGuessNum = sqrt(guessNum);
		cout << fixed << setprecision(5) << sqrtGuessNum << " is the square root of what number?" << endl;

		//Guessing game loop
		while (1)
		{
			int guess = GetGuess();
			newPlayer.makeGuess();
			if (guess < guessNum)
			{
				cout << "Too low, guess again: ";
			}
			else if (guess > guessNum)
			{
				cout << "Too high, guess again: ";
			}
			else
			{
				break;
			}
		}

		//Places and prints current player and then writes the leader list to the file
		leaders.setSpot(newPlayer);
		cout << "You made " << newPlayer.getGuesses() << " guesses, " << newPlayer.getName() << endl;
		cout << "You got it, baby!" << endl;
		leaders.printList();
		cout << endl;
		WriteToFile(leaders);
	}
}



int main()
{
	PlayGuessingGame();

	return 0; 
} 