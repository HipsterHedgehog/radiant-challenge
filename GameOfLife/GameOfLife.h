#pragma once
#include "SparseGrid.h"

class GameOfLife {
private:
	int64_t generation;
	// These two variables will be used to represent the current and next generation
	SparseGrid buffer1;
	SparseGrid buffer2;
	SparseGrid &getCurrentGeneration();
public:
	GameOfLife();
	void nextGeneration();
	void addLiveCell(int64_t x, int64_t y);
	const SparseGrid &getCurrentGeneration() const;
};