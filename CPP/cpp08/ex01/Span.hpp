#ifndef SPAN
#define SPAN

#include <exception>
#include <vector>
#include <iostream>


class Span
{
private:
	unsigned int _size;
	std::vector<int> storage;
public:
	Span(unsigned int size);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void addNumber(int number);
	unsigned int shortestSpan();
	unsigned int longestSpan();

	class SpanOverflowError : public std::exception
	{
		public:
			const char *what() const throw();
	};
	class SpanNotEnoughElementsError : public std::exception
	{
		public:
			const char *what() const throw();
	};
};

#endif