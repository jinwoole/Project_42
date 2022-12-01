#ifndef FINAL
#define FINAL

#include <algorithm>

template <typename T>
typename T::const_iterator easyfind(const T& container, const int v)
{
	return std::find(container.begin(), container.end(), v);
}

#endif