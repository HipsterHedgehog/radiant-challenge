#pragma once
#include "SparseGrid.h"

class GameOfLife {
private:
	int64_t generation;
	// These two variables will be used to represent the current and next generation
	SparseGrid buffer1;
	SparseGrid buffer2;
public:
	GameOfLife();
	void nextGeneration();
};