#include "GameOfLife.h"

int main(int argc, char* argv[])
{
	GameOfLife gameOfLife;
	gameOfLife.addLiveCell(0, 0);
	gameOfLife.addLiveCell(1, 0);
	gameOfLife.addLiveCell(2, 0);
	gameOfLife.addLiveCell(-1, -1);
	gameOfLife.addLiveCell(0, -1);
	gameOfLife.addLiveCell(1, -1);

	for (unsigned short i = 0; i < 10; i++)
	{
		gameOfLife.nextGeneration();
	}

	return 0;
}