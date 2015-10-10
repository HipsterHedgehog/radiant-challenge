#pragma once
#include <utility>
#include <set>
#include <cstdint>
#include <functional>
#include <algorithm>

class SparseGrid {
private:
	std::set<std::pair<const int64_t, const int64_t>> grid;
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