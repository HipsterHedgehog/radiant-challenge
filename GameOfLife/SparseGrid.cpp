#include "SparseGrid.h"

void SparseGrid::add(const int64_t x, const int64_t y)
{
	grid.insert(std::pair<const int64_t, const int64_t>(x, y));
}

void SparseGrid::clear()
{
	grid.clear();
}

bool SparseGrid::get(const int64_t x, const int64_t y) {
	std::pair<const int64_t, const int64_t> el(x, y);
	auto setIter = grid.find(el);
	return setIter != grid.end();
}

bool SparseGrid::operator()(const int64_t x, const int64_t y) {
	return get(x, y);
}