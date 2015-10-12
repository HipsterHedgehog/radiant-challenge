#include "GameOfLife.h"
#include <regex>
#include <sstream>
#include <iostream>

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
	
	// Output each generation to the console in (x, y) pair format
	for (unsigned short i = 0; i < 20; i++)
	{
		stringstream outputString;
		outputString << "Generation " << (i+1) << ":\t";
		gameOfLife.forEachLiveCell([&outputString](auto liveCell)
		{
			outputString << "(" << liveCell.first << ", " << liveCell.second << ") ";
		});
		cout << outputString.str() << endl;
		gameOfLife.nextGeneration();
	}

	return 0;
}