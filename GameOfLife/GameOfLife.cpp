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
	SparseGrid &currentGeneration = getCurrentGeneration();
	SparseGrid &futureGeneration = ((generation % 2) == 1) ? buffer1 : buffer2;

	// Clear the buffer for the next generation
	futureGeneration.clear();

	// Using the current generation data, generate the next generation's data
	currentGeneration.forEach(
		// Lambda to apply the game of life function to the current generation - must adhere to header void(SparseGrid &, std::pair<const int64_t, const int64_t>)
		[&currentGeneration, &futureGeneration](auto currentCell) mutable
		{
			auto forEachNeighbor = [](std::pair<const int64_t, const int64_t> cell, std::function<void(const int64_t, const int64_t)> neighborOp)
			{
				for (int64_t x = cell.first - 1; x <= cell.first + 1; x++)
				{
					for (int64_t y = cell.second - 1; y <= cell.second + 1; y++)
					{
						if (!(x == cell.first && y == cell.second))
						{
							neighborOp(x, y);
						}
					}
				}
			};

			auto countAliveNeighbors = [&currentGeneration, &forEachNeighbor](auto cell)
			{
				short aliveNeighbors = 0;
				forEachNeighbor(cell, [&currentGeneration, &aliveNeighbors](auto x, auto y) mutable
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
				futureGeneration.add(currentCell.first, currentCell.second);
			}
			// Under-population and over-population cases are implicitly handled since we cleared the next generation already

			// 2) For the each neihboring dead cell, apply the rules for reproduction
			forEachNeighbor(currentCell, [&currentGeneration, &futureGeneration, &countAliveNeighbors](auto x, auto y) mutable
			{
				auto neighborCell = std::pair<const int64_t, const int64_t>(x, y);
				// Ensure a dead cell "reproduces"
				if (!currentGeneration(x, y) && countAliveNeighbors(neighborCell) == 3)
				{
					futureGeneration.add(x, y);
				}
			});
		}
	);

	generation++;
}

void GameOfLife::addLiveCell(int64_t x, int64_t y)
{
	getCurrentGeneration().add(x, y);
}

SparseGrid &GameOfLife::getCurrentGeneration()
{
	return ((generation % 2) == 0) ? buffer1 : buffer2;
}

const SparseGrid &GameOfLife::getCurrentGeneration() const
{
	return ((generation % 2) == 0) ? buffer1 : buffer2;
}