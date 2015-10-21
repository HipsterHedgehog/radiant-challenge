#pragma once
#include <utility>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include "CoordinateHash.h"

class SparseGrid {
private:
	std::unordered_set<std::pair<const int64_t, const int64_t>, CoordinateHash> grid;
public:
	// Rely on the default constructor automatically generated
	void add(const int64_t x, const int64_t y);
	void clear();
	bool get(const int64_t x, const int64_t y) const;
	bool operator()(const int64_t x, const int64_t y) const;
	template <class Op> inline void forEach(Op op) const;
};

template <class Op> 
inline void SparseGrid::forEach(Op op) const
{
	std::for_each(grid.begin(), grid.end(), op);
}