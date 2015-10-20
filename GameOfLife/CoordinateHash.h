#pragma once
#include <utility>
#include <cstdint>

class CoordinateHash
{
private:
	std::hash<int64_t> hasher;
public:
	size_t operator()(const std::pair<const int64_t, const int64_t> &coord) const;
};

