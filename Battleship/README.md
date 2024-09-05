**Battleship**

A C++ program that implements a simpler version of the classic battleship board game. The computer generates a board of the five ships and the player must sink all the ships by selecting positions on the board.

Features:
- Ship class used to manage the states of the different ships and their properties on the board
- Robust algorithms used to ensure proper placement of the ships entirely on the board with no overlap
- Unordered maps used for mapping ship data
- User input validation handles all possible invalid input cases

Running the Project:
1. Download the project files from GitHub
2. Navigate to the project directory
3. Compile using desired C++ compiler such as g++
4. Run the compiled program

Future Improvements:
- Implement the full battleship game with a player board they place ships on that the computer tries to guess the positions of
- Implement the ship class in a seperate header file and associated .cpp definition file
- Add a player class to implement for features for the player and better data tracking
- Add player data persistence using file I/O
