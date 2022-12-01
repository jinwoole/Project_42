#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed()
{
    fixed_point_nbr = 0;
    std::cout << "Default constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& src)
{
    std::cout << "Copy assignment operator called" << std::endl;
    fixed_point_nbr = src.fixed_point_nbr;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Fixed& num)
{
    out << num.toFloat();
    return out;
}

Fixed::Fixed(const Fixed &origin)
{
    std::cout << "Copy constructor called" << std::endl;
    fixed_point_nbr = origin.fixed_point_nbr;
}

Fixed::Fixed(const int i)
{
    std::cout << "Int constructor called" << std::endl;
    fixed_point_nbr = i << fractional_bits;
}

Fixed::Fixed(const float f)
{
    std::cout << "Float constructor called" << std::endl;
    fixed_point_nbr = roundf(f * (1 << fractional_bits));
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return fixed_point_nbr;
}

void Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    fixed_point_nbr = raw;
}

float Fixed::toFloat(void) const
{
    return ((float)fixed_point_nbr / (1 << fractional_bits));
}

int Fixed::toInt(void) const
{
    return (fixed_point_nbr >> fractional_bits);
}

