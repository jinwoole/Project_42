#include "Fixed.hpp"

Fixed::Fixed()
{
    fixed_point_nbr = 0;
    std::cout << "Default constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& src)
{
    std::cout << "Copy assignment operator called" << std::endl;
    fixed_point_nbr = src.getRawBits();
    return *this;
}

Fixed::Fixed(const Fixed &origin)
{
    std::cout << "Copy assignment operator called" << std::endl;
    fixed_point_nbr = origin.fixed_point_nbr;
}

Fixed::~Fixed() {
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