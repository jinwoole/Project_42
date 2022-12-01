#ifndef ARRAY
#define ARRAY

# include <iostream>

template <typename T>
class Array
{
	protected:
		T* elements;
		unsigned int arr_size;
	public:
		Array();
		Array(unsigned int i); //할당하는 생성자
		~Array();
		Array(Array<T> const& other);
		Array<T>&		operator=(Array<T> const& other); //깊은복사 하자 동일 그것도 처리해야 한다.
		T&				operator[](unsigned int i) const; //오버로딩
		unsigned int	size() const; //변경x
};

template <typename T>
Array<T>::Array()
{
    elements = NULL;
	arr_size = 0;
}

template <typename T>
Array<T>::Array(unsigned int i)
{
	elements = new T[i];
    arr_size = i;
}

template <typename T>
Array<T>::~Array()
{
	if (elements)
		delete [] elements;
}

template <typename T>
Array<T>::Array(Array<T> const& other)
{
	elements = new T[other.size()];
	
	for (unsigned int i = 0; i < other.size(); i++)
	{
		elements[i] = other[i];
	}
    arr_size = other.size();
}

template <typename T>
Array<T>& Array<T>::operator=(Array<T> const& other)
{
	if (elements)
		delete [] elements;
	elements = new T[other.size()];
	for (unsigned int i = 0; i < other.size(); i++)
	{
		elements[i] = other[i];
	}
	arr_size = other.size();

	return *this;
}

template <typename T>
T& Array<T>::operator[](unsigned int i) const
{
	if (i > this->arr_size - 1)
		throw std::exception();
	return elements[i];
}

template <typename T>
unsigned int Array<T>::size() const
{
	return arr_size;
}

#endif