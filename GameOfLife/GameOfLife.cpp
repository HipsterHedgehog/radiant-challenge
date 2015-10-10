#include "GameOfLife.h"
#include <functional>

GameOfLife::GameOfLife() : generation(0)
{
	// Use default constructors for buffer1 and buffer2
}

void GameOfLife::nextGeneration()
{
	// Apply the Game of Life function to each element

	// Determine the buffer that represents the current generation
	SparseGrid &currentGeneration = ((generation % 2) == 0) ? buffer1 : buffer2;
	SparseGrid &nextGeneration = ((generation % 2) == 1) ? buffer1 : buffer2;

	// Clear the buffer for the next generation
	nextGeneration.clear();

	// Using the current generation data, generate the next generation's data
	currentGeneration.reduce(
		nextGeneration,
		// Lambda to apply the game of life function to the current generation - must adhere to header SparseGrid(SparseGrid &, std::pair<const int64_t, const int64_t>)
		[&currentGeneration](auto nextGen, auto currentCell)
		{
			auto forEachNeighbor = [](std::pair<const int64_t, const int64_t> cell, std::function<void(const int64_t, const int64_t)> neighborOp)
			{
				for (int64_t x = cell.first - 1; x <= cell.first + 1; x++)
				{
					for (int64_t y = cell.second - 1; y <= cell.second + 1; y++)
					{
						if (x != 0 && y != 0)
						{
							neighborOp(x, y);
						}
					}
				}
			};

			auto countAliveNeighbors = [&currentGeneration, &forEachNeighbor](std::pair<const int64_t, const int64_t> cell)
			{
				short aliveNeighbors = 0;
				forEachNeighbor(cell, [&currentGeneration, &aliveNeighbors](auto x, auto y)
				{
					if (currentGeneration(x, y))
					{
						aliveNeighbors++;
					}
				});
				return aliveNeighbors;
			};

			// 1) For the current alive cell, apply the rules for under/stagnant/overpopulation
			short aliveNeighbors = countAliveNeighbors(currentCell);
			if (aliveNeighbors >= 2 && aliveNeighbors <= 3)
			{
				// Cell continues on to next generation
				nextGen.add(currentCell.first, currentCell.second);
			}
			// Under-population and over-population cases are implicitly handled since we cleared the next generation already

			// 2) For the each neihboring dead cell, apply the rules for reproduction
			forEachNeighbor(currentCell, [&currentGeneration, &nextGen, &countAliveNeighbors](auto x, auto y)
			{
				auto neighborCell = std::pair<const int64_t, const int64_t>(x, y);
				// Ensure a dead cell "reproduces"
				if (!currentGeneration(x, y) && countAliveNeighbors(neighborCell) == 3)
				{
					nextGen.add(x, y);
				}
			});

			return nextGen;
		}
	);
}
