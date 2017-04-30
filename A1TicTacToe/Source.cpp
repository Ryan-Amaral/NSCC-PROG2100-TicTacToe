// This program is a tic tac toe game where the computer cannot possibly loose.

#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

// validation class
class Validation{

	public:
		// single character validation 'y' or 'n' upper or lower case
		static bool YNValidation(char input){
			bool isValid;
			if (input == 'Y' || input == 'y' || input == 'N' || input == 'n'){
				isValid = true;
			}
			else{
				isValid = false;
			}

			return isValid;
		}

		// single character validation, number 1-9
		static bool OneToNineValidation(char input){
			bool isValid = false;
			// accept only a digit
			if (isdigit(input)){
				// must be greater than 0
				if ((input - '0') > 0){
					isValid = true;
				}
			}

			return isValid;
		}
};

// 2d coordinates for tic tac toe board
class Coordinates2D{
	private:
		int x;
		int y;
	public:
		void Set(int x, int y){
			this -> x = x;
			this -> y = y;
		}
		
		int GetX(){
			return x;
		}

		int GetY(){
			return y;
		}
};

class TicTacToeLineSearcher{

	public:
		// checks if the current square is a 2 in a row for the specified symbol, to get to a three in a row.
		static bool CheckFor2InARow(int t3Board[3][3], Coordinates2D squareCoords, int xOrO){
			int totalInLine = 0; // stores the amount of 'X's or 'O's in a line
			// search vertical
			for (int i = 0; i < 3; i++){
				// add points to totalInLine if the right symbol 
				if (t3Board[i][squareCoords.GetY()] == xOrO){
					totalInLine++;
				}
				// if wrong symbol is in line, set to -1
				else if (t3Board[i][squareCoords.GetY()] == -xOrO){
					totalInLine = -1;
				}
			}

			// don't continue if totalInLine == 2
			if (totalInLine < 2){
				totalInLine = 0;
				// horizontal
				for (int i = 0; i < 3; i++){
					// add points to totalInLine if the right symbol
					if (t3Board[squareCoords.GetX()][i] == xOrO){
						totalInLine++;
					}
					// if wrong symbol is in line, set to -1
					else if (t3Board[squareCoords.GetX()][i] == -xOrO){
						totalInLine = -1;
					}
				}
			}

			if (totalInLine < 2){
				totalInLine = 0;
				// diagonal down right
				if (squareCoords.GetX() == squareCoords.GetY()){
					for (int i = 0; i < 3; i++){
						// add points to totalInLine if the right symbol
						if (t3Board[i][i] == xOrO){
							totalInLine++;
						}
						// if wrong symbol is in line, set to -1
						else if (t3Board[i][i] == -xOrO){
							totalInLine = -1;
						}
					}
				}
			}

			if (totalInLine < 2){
				totalInLine = 0;
				// diagonal down left
				if ((squareCoords.GetX() == 1 && squareCoords.GetY() == 1) ||
					(squareCoords.GetX() == 0 && squareCoords.GetY() == 2) ||
					(squareCoords.GetX() == 2 && squareCoords.GetY() == 0)){
					for (int x = 0; x < 3; x++){
						for (int y = 2; y >= 0; y--){
							// add points to totalInLine if the right symbol
							if (t3Board[x][y] == xOrO && y == (2 - x)){
								totalInLine++;
							}
							// if wrong symbol is in line, set to -1
							else if (t3Board[x][y] == -xOrO &&  y == (2 - x)){
								totalInLine = -1;
							}
						}
					}
				}
			}

			if (totalInLine == 2){
				return true;
			}
			else{
				return false;
			}
		}

		// checks for a 3 in a row for the specified symbol.
		static bool CheckFor3InARow(int t3Board[3][3], Coordinates2D squareCoords, int xOrO){
			int totalInLine = 0; // stores the amount of 'X's or 'O's in a line
			// search vertical
			for (int i = 0; i < 3; i++){
				// add points to totalInLine if the right symbol 
				if (t3Board[i][squareCoords.GetY()] == xOrO){
					totalInLine++;
				}
			}

			// don't continue if totalInLine == 3
			if (totalInLine < 3){
				totalInLine = 0;
				// horizontal
				for (int i = 0; i < 3; i++){
					// add points to totalInLine if the right symbol
					if (t3Board[squareCoords.GetX()][i] == xOrO){
						totalInLine++;
					}
				}
			}

			if (totalInLine < 3){
				totalInLine = 0;
				// diagonal down right
				if (squareCoords.GetX() == squareCoords.GetY()){
					for (int i = 0; i < 3; i++){
							// add points to totalInLine if the right symbol
							if (t3Board[i][i] == xOrO){
								totalInLine++;
							}
					}
				}
			}

			if (totalInLine < 3){
				totalInLine = 0;
				// diagonal down left
				if ((squareCoords.GetX() == 1 && squareCoords.GetY() == 1) ||
					(squareCoords.GetX() == 0 && squareCoords.GetY() == 2) ||
					(squareCoords.GetX() == 2 && squareCoords.GetY() == 0)){
					for (int x = 0; x < 3; x++){
						for (int y = 2; y >= 0; y--){
							// add points to totalInLine if the right symbol
							if (t3Board[x][y] == xOrO && y == (2 - x)){
								totalInLine++;
							}
						}
					}
				}
			}

			if (totalInLine == 3){
				return true;
			}
			else{
				return false;
			}
		}

		// Searches all possible tripple lines to find the total amount of points a square has,
		// for use for the ai class. 'O's are worth -1, and 'X's are worth +1.
		static int FindPointsOnSquare(int t3Board[3][3], Coordinates2D squareCoords){
			int totalPoints = 0; // track the points as we go through

			// search vertical and horizontal lines for all coordinates
			// vertical
			for (int i = 0; i < 3; i++){
				totalPoints += t3Board[i][squareCoords.GetY()];
			}
			// horizontal
			for (int i = 0; i < 3; i++){
				totalPoints += t3Board[squareCoords.GetX()][i];
			}

			// search diagonal lines for coordinates where x and y are equal or when one is 0 and the other is 2
			// diagonal down right
			if (squareCoords.GetX() == squareCoords.GetY()){
				for (int x = 0; x < 3; x++){
					for (int y = 0; y < 3; y++){
						totalPoints += t3Board[x][y];
					}
				}
			}
			// diagonal down left
			if ((squareCoords.GetX() == 1 && squareCoords.GetY() == 1) ||
					(squareCoords.GetX() == 0 && squareCoords.GetY() == 2) ||
					(squareCoords.GetX() == 2 && squareCoords.GetY() == 0)){
				for (int x = 0; x < 3; x++){
					for (int y = 2; y >= 0; y--){
						totalPoints += t3Board[x][y];
					}
				}
			}
			
			return totalPoints;
		}
};

// the values for each tic tac toe square
enum BoxValue : int { EMPTY = 0, X = 1, O = -1 };

// the computer's method for determining a move
class TicTacToeAi{
	
	private:
		bool didPlayerStart; // did the player make the first move

		Coordinates2D FindBestPoints(int t3Board[3][3], bool searchForHighest){
			Coordinates2D currentCoordinates; // temp value
			Coordinates2D selectedCoordinates; // store the best value
			int currentBestValue = 999; // obsolete value as a sort of flag
			int tempPoints; // stores points so repeated acces of the method is not needed
			for (int x = 0; x < 3; x++){
				for (int y = 0; y < 3; y++){
					if (t3Board[x][y] == BoxValue::EMPTY){
						currentCoordinates.Set(x, y); // set the coords to current
						tempPoints = TicTacToeLineSearcher::FindPointsOnSquare(t3Board, currentCoordinates);
						// if first time set initial value
						if (currentBestValue == 999){
							currentBestValue = tempPoints;
							selectedCoordinates.Set(x, y);
						}
						// search for high
						else if (searchForHighest){
							if (tempPoints > currentBestValue){
								currentBestValue = tempPoints;
								selectedCoordinates.Set(x, y);
							}
						}
						// search for low
						else{
							if (tempPoints < currentBestValue){
								currentBestValue = tempPoints;
								selectedCoordinates.Set(x, y);
							}
						}
					}
				}
			}

			return selectedCoordinates;
		}

	public:
		// find where the ai will move
		Coordinates2D FindBestCoordinates(int t3Board[3][3], int playersMoves, int computersMoves){
			// where the coordinates will go
			Coordinates2D selectedCoordinates;
			bool foundBestSquare = false;

			// pre script first move for center or a corner
			if (computersMoves == 0){
				// computer has first move
				if (playersMoves == 0){
					// always start in center
					selectedCoordinates.Set(1, 1);
				}
				// player had first move
				else{
					//start in center if player is not in center
					if (t3Board[1][1] == BoxValue::EMPTY){
						selectedCoordinates.Set(1, 1);
					}
					// otherwise start on bottom right corner
					else{
						selectedCoordinates.Set(2, 2);
					}
				}
			}
			// special situation thats needs to be taken accounted for on fourth turn when user goes first
			else if (playersMoves == 2 && computersMoves == 1 && 
					((t3Board[2][1] == BoxValue::O && t3Board[1][2] == BoxValue::O) || 
					(t3Board[1][2] == BoxValue::O && t3Board[0][1] == BoxValue::O) || 
					(t3Board[0][1] == BoxValue::O && t3Board[1][0] == BoxValue::O) || 
					(t3Board[1][0] == BoxValue::O && t3Board[2][1] == BoxValue::O))){
				selectedCoordinates = FindBestPoints(t3Board, false);
				foundBestSquare = true;
			}
			// special situation thats needs to be taken accounted for on fourth turn when user goes first
			else if (playersMoves == 2 && computersMoves == 1 &&
					t3Board[1][1] == BoxValue::O && t3Board[0][0] == BoxValue::O){
						// our move must be to a corner
						selectedCoordinates.Set(0, 2);
						foundBestSquare = true;
			}
			// not first move so actual decision making needed
			else{
				Coordinates2D currentCoordinates; // the current coordinates to look at in each itteration

				//fist, search for computer existing 2 in a rows for imediate win
				for (int x = 0; x < 3; x++){
					for (int y = 0; y < 3; y++){
						currentCoordinates.Set(x, y); // set the coords to current
						if (TicTacToeLineSearcher::CheckFor2InARow(t3Board, currentCoordinates, BoxValue::X) && 
								t3Board[x][y] == BoxValue::EMPTY){
							selectedCoordinates.Set(x, y); // possible three in a row, computer wins
							foundBestSquare = true;
							break;
						}
					}
					if (foundBestSquare){
						break;
					}
				}
				
				// second, search for user 2 in a rows to stop enemy win
				if (!foundBestSquare){
					for (int x = 0; x < 3; x++){
						for (int y = 0; y < 3; y++){
							currentCoordinates.Set(x, y); // set the coords to current
							if (TicTacToeLineSearcher::CheckFor2InARow(t3Board, currentCoordinates, BoxValue::O) && 
									t3Board[x][y] == BoxValue::EMPTY){
								selectedCoordinates.Set(x, y); // possible three in a row for user, stop them
								foundBestSquare = true;
								break;
							}
						}
						if (foundBestSquare){
							break;
						}
					}
				}
				// find the square with the optimal amount of points.
				// searching for highest points if user goes first, lowest if computer started
				if (!foundBestSquare){
					selectedCoordinates = FindBestPoints(t3Board, didPlayerStart);
				}
			}

			return selectedCoordinates;
		}

		void SetDidPlayerStart(bool didPlayerStart){
			this->didPlayerStart = didPlayerStart;
		}
};

// the integer values for match outcomes
enum RoundWinner : int {PLAYER_WON, COMPUTER_WON, TIE};

class TicTacToeVisual{

	public:
		static void PrintBoard(int board[3][3]){
			cout << "\n";
			int squareNum = 1; // keep track of number of the square
			for (int x = 0; x < 3; x++){
				cout << "\n--------------------\n\n";
				for (int y = 0; y < 3; y++){
					switch (board[x][y])
					{
						case BoxValue::EMPTY:
							cout << " | " << squareNum << " | ";
							break;
						case BoxValue::O:
							cout << " | " << 'O' << " | ";
							break;
						case BoxValue::X:
							cout << " | " << 'X' << " | ";
							break;
						default:
							cout << "fdhsf";
							break;
					}
					squareNum++;
				}
				cout << "\n";
			}
			cout << "--------------------\n";
		}
};

// loops through the game, multiple times if the player wants to
void GameCycle(){
	char input; // char to be recycled for each of the users inputs
	bool usersTurn; // true if it is currently the players turn
	bool userWantsQuit = false; // turns true when player wants to stop, exits app
	bool gameComplete = false; // turns true when the current game is over
	bool computerWon = false; // used after each round to check if computer won
	TicTacToeAi t3Ai; // the object for the computers planning
	bool threeInRow; // flag for game completion
	Coordinates2D tempCoords; // temporary coordinates needed for any square searching

	// the main game loop
	while (!userWantsQuit){
		threeInRow = false;

		// loop through untill input is valid
		do{
			cout << "\nDo you wish to make the first move? ('y'/'n'): ";
			input = _getch();
			_putch(input);
		} while (!Validation::YNValidation(input));
		cout << "\n";

		// assign first move to player if player wanted
		if (input == 'Y' || input == 'y'){
			usersTurn = true;
		}
		else{
			usersTurn = false;
		}
		t3Ai.SetDidPlayerStart(usersTurn); // the flag on the ai for player starting

		// setup game board, default to zero
		int ticTacToeBoard[3][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

		// display the board
		TicTacToeVisual::PrintBoard(ticTacToeBoard);

		// track turns to know when tied when total is 9
		int userTurnsTaken = 0;
		int computerTurnsTaken = 0;

		gameComplete = false;
		// inner game loop
		while (!gameComplete){
			// users turn, user is always 'O'
			if (usersTurn){
				// remind player that they are always 'O'
				cout << "\nYour turn! Remember, you the human are always O.\n";
				do{
					do{
						cout << "Please select a square (1-9): ";
						input = _getch();
						_putch(input);
						cout << "\n";
					} while (!Validation::OneToNineValidation(input));
				} while (ticTacToeBoard[((input - '0') - 1) / 3][((input - '0') - 1) % 3] != 
						BoxValue::EMPTY); // extra loop to check if square is empty

				// place 'O' on the right square, convert from number to coordinates
				ticTacToeBoard[((input - '0') - 1) / 3][((input - '0') - 1) % 3] = BoxValue::O;
				userTurnsTaken++;
			}
			// otherwise computers turn, computer is always 'X'
			else{ 
				// place 'X' in right spot
				Coordinates2D selectedCoordinates = t3Ai.FindBestCoordinates(ticTacToeBoard, userTurnsTaken, computerTurnsTaken);
				ticTacToeBoard[selectedCoordinates.GetX()][selectedCoordinates.GetY()] = BoxValue::X;
				computerTurnsTaken++;
				cout << "\nComputer placed an 'X' in square " << selectedCoordinates.GetX() * 3 + 1 + selectedCoordinates.GetY() << "!";
			}

			// display the board
			TicTacToeVisual::PrintBoard(ticTacToeBoard);

			// search for a three in a row of 'X's (because 'O' is impossible to win)
			for (int x = 0; x < 3; x++){
				for (int y = 0; y < 3; y++){
					tempCoords.Set(x, y);
					if (TicTacToeLineSearcher::CheckFor3InARow(ticTacToeBoard, tempCoords, BoxValue::X)){
						gameComplete = true;
						computerWon = true;
					}
				}
			}

			// determine if board is full or there is 3 in a row
			if ((userTurnsTaken + computerTurnsTaken == 9) || threeInRow)
				gameComplete = true;

			// determine winner if there is one
			if (gameComplete){
				cout << "\n\n"; // give some extra lines

				// if computer won got 3 in a row
				if (computerWon){
					cout << "Three 'X's in a row! The computer wins!!!!!!!!!!";
				}

				// if no three in a row it is a tie
				if(!computerWon){
					cout << "You tied the computer!!!!!!!";
				}

				computerWon = false;

				// loop through untill input is valid
				do{
					cout << "\nDo you want to play again? ('y'/'n'): ";
					input = _getch();
					_putch(input);
				} while (!Validation::YNValidation(input));
				cout << "\n";
				// change if want play again
				if (input == 'Y' || input == 'y'){
					userWantsQuit = false;
				}
				else{
					userWantsQuit = true;
				}
			}

			usersTurn = !usersTurn; // switch turn
		}
	}
}

int main(){
	cout << "Welcome to Tic Tac Toe!\n";
	GameCycle(); // start the game

	return 0;
}