#pragma once
#include <utility>
#include <set>
#include <cstdint>
#include <numeric>

class SparseGrid {
private:
	std::set<std::pair<const int64_t, const int64_t>> grid;
public:
	// Rely on the default constructor automatically generated
	void add(const int64_t x, const int64_t y);
	void clear();
	bool get(const int64_t x, const int64_t y);
	bool operator()(const int64_t x, const int64_t y);
	template<class T, class Op> inline T reduce(T init, Op op);
};

template<class T, class Op>
inline T SparseGrid::reduce(T init, Op op) 
{
	return std::accumulate(grid.begin(), grid.end(), init, op);
}