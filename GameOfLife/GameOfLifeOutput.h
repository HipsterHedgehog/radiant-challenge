#pragma once
#include "GameOfLife.h"
#include <utility>


template <short Width, short Height>
class GameOfLifeOutput
{
private:
	const GameOfLife &gameOfLife;
	unsigned char gridOutput[Height][Width];
	std::pair<int64_t, int64_t> cursor;
	
	inline void move(int64_t xDirection, int64_t yDirection, std::stringstream &outputStream);
	void clear();
public:
	GameOfLifeOutput(const GameOfLife &grid);
	
	void output(std::stringstream &outputStream);
	inline void moveLeft(std::stringstream &outputStream);
	inline void moveRight(std::stringstream &outputStream);
	inline void moveUp(std::stringstream &outputStream);
	inline void moveDown(std::stringstream &outputStream);
};

template <short Width, short Height>
GameOfLifeOutput<Width, Height>::GameOfLifeOutput(const GameOfLife &gameOfLife) :
	gameOfLife(gameOfLife)
{
	clear();
}

template <short Width, short Height>
void GameOfLifeOutput<Width, Height>::clear()
{
	for (short i = 0; i < Height; i++)
	{
		for (short j = 0; j < Width; j++)
		{
			// Fill dead cells with an "empty" block
			gridOutput[i][j] = 176;
		}
	}
}

template <short Width, short Height>
void GameOfLifeOutput<Width, Height>::output(std::stringstream &outputStream)
{
	// Fill the output buffer with dead cells
	clear();

	gameOfLife.forEachLiveCell([this](auto liveCell)
	{
		// Create the offset in the grid for each live cell
		auto offsetX = liveCell.first + (cursor.first + (Width / 2) + 1);
		auto offsetY = liveCell.second + (cursor.second + (Height / 2) + 1);

		if (offsetX >= 0 && offsetX < Width && offsetY >= 0 && offsetY < Height)
		{
			// Fill live cells with a block
			gridOutput[(short)offsetY][(short)offsetX] = 219;
		}
	});

	// Flip the y-axis
	for (short y = Height-1; y >= 0; y--)
	{
		for (short x = 0; x < Width; x++)
		{
			// Fill the output stream row with each column
			outputStream << gridOutput[y][x];
		}
		// Start a new row
		outputStream << std::endl;
	}
}
template <short Width, short Height>
inline void GameOfLifeOutput<Width, Height>::move(int64_t xDirection, int64_t yDirection, std::stringstream &outputStream)
{
	cursor = std::pair<int64_t, int64_t>(cursor.first + xDirection, cursor.second + yDirection);
	output(outputStream);
}

template <short Width, short Height>
inline void GameOfLifeOutput<Width, Height>::moveLeft(std::stringstream &outputStream)
{
	move(1, 0, outputStream);
}

template <short Width, short Height>
inline void GameOfLifeOutput<Width, Height>::moveRight(std::stringstream &outputStream)
{
	move(-1, 0, outputStream);
}

template <short Width, short Height>
inline void GameOfLifeOutput<Width, Height>::moveUp(std::stringstream &outputStream)
{
	move(0, -1, outputStream);
}

template <short Width, short Height>
inline void GameOfLifeOutput<Width, Height>::moveDown(std::stringstream &outputStream)
{
	move(0, 1, outputStream);
}