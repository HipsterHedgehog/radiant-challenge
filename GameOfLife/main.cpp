#include "GameOfLife.h"
#include "GameOfLifeOutput.h"
#include <regex>
#include <sstream>
#include <iostream>
#include <conio.h>

int main(int argc, char* argv[])
{
	using namespace std;

	GameOfLife gameOfLife;

	// Add any pairs that match a standard coordinate style - e.g. (+10, -100)
	regex coordMatcher("\\(([\\+|-]?[0-9]+),[ ]*([\\+|-]?[0-9]+)\\)");
	for (int i = 1; i < argc; i++)
	{
		string coords = string(argv[i]);
		smatch matchResults;

		// Add a match 
		if (regex_match(coords, matchResults, coordMatcher))
		{
			int64_t x = stoll(matchResults[1]);
			int64_t y = stoll(matchResults[2]);
			gameOfLife.addLiveCell(x, y);
		}
	}

	// Helper class to generate output from the Game of Life simulation
	GameOfLifeOutput<15, 15> gameOfLifeOutput(gameOfLife);
	
	// Output each live cell to the console
	int input = '\0';
	stringstream firstGen;
	gameOfLifeOutput.output(firstGen);
	cout << firstGen.str();
	while (input != 27 /* ESC */ && input != EOF)
	{
		input = _getch();
		int direction = 0;
		stringstream outputString;

		// Clear the terminal for the next generation
		system("cls");

		switch (input)
		{
		// Handle arrow keys
		case 0: // Num-lock off arrows
		case 224: // Keyboard arrows
			direction = _getch();
			switch (direction)
			{
			case 72: // Up-Arrow
				gameOfLifeOutput.moveUp(outputString);
				break;
			case 75: //Left-Arrow
				gameOfLifeOutput.moveLeft(outputString);
				break;
			case 77: //Right-Arrow
				gameOfLifeOutput.moveRight(outputString);
				break;
			case 80: //Down-Arror
				gameOfLifeOutput.moveDown(outputString);
				break;
			}
			cout << outputString.str();
			break;
		// Handle continue generation
		case '\r': // Enter
		case '\n': // Enter
		case 32: // Space bar
			gameOfLife.nextGeneration();
			gameOfLifeOutput.output(outputString);
			cout << outputString.str();
			break;
		}
		cin.clear();
	}
	return 0;
}