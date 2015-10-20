#include "CoordinateHash.h"
#include <functional>

size_t CoordinateHash::operator()(const std::pair<const int64_t, const int64_t> &coord) const
{
	// Borrowed from http://www.boost.org/doc/libs/1_37_0/doc/html/hash/reference.html#boost.hash_combine
	auto seed = hasher(coord.first);
	return seed + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}