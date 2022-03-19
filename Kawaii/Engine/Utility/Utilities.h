#pragma once

// Set these flags to 1 to use STL vector and deque
// Set these flags to 0 to use custom implementeation of those containers
#define USE_STL_VECTOR 1
#define USE_STL_DEQUE 1

#if USE_STL_VECTOR
#include <vector>
namespace Kawaii::Utils
{
	template<typename T>
	using vector = std::vector<T>;
}
#else
#include "Vector.h"
#endif

#if USE_STL_DEQUE
#include <deque>
namespace Kawaii::Utils
{
	template<typename T>
	using deque = std::deque<T>;
}
#endif