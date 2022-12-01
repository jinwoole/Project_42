#include "Span.hpp"

Span::Span(unsigned int n)
{
	this->_size = n;
}

Span::Span(const Span& other)
{
	this->_size = other._size;
	this->storage = other.storage;
}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		this->_size = other._size;
		this->storage = other.storage;
	}
	return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
	if (storage.size() >= this->_size)
	{
		throw(SpanOverflowError());
	}
	else
	{
		storage.push_back(number);
	}
}

unsigned int Span::shortestSpan()
{
	if (storage.size() < 2)
	{
		throw(SpanNotEnoughElementsError());
	}


	std::vector<int> tmp = storage;
	std::sort(tmp.begin(), tmp.end());

	std::vector<int>::iterator iter = tmp.begin();
	unsigned int shortest;
	unsigned int diff;
	bool first_diff = false;

	for (iter = tmp.begin(); iter != tmp.end(); iter++)
	{
		std::vector<int>::iterator iNext = iter;
		iNext++;
		diff = *iNext - *iter;
		if (first_diff == false)
		{
			shortest = diff;
            first_diff = true;
		}
		if (diff < shortest)
		{
			shortest = diff;
		}
	}
	return shortest;
}

unsigned int Span::longestSpan()
{
	if (storage.size() < 2)
	{
		throw(SpanNotEnoughElementsError());
	}
	std::vector<int> tmp = storage;
	std::sort(tmp.begin(), tmp.end());

	return (tmp.back() - tmp.front());
}


const char* Span::SpanOverflowError::what() const throw()
{
	return "Error : Span Overflow!";
}

const char* Span::SpanNotEnoughElementsError::what() const throw()
{
	return "Error : Span does not have enough elements";
}