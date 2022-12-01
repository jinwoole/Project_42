#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed()
{
    fixed_point_nbr = 0;
}

Fixed& Fixed::operator=(const Fixed& src)
{
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
    fixed_point_nbr = origin.fixed_point_nbr;
}

Fixed::Fixed(const int i)
{
    fixed_point_nbr = i << fractional_bits;
}

Fixed::Fixed(const float f)
{
    fixed_point_nbr = roundf(f * (1 << fractional_bits));
}

Fixed::~Fixed()
{
}

int Fixed::getRawBits(void) const
{
    return fixed_point_nbr;
}

void Fixed::setRawBits(int const raw)
{
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

bool Fixed::operator>(const Fixed& target)
{
    if (toFloat() > target.toFloat())
        return 1;
    return 0;
}

bool Fixed::operator<(const Fixed& target)
{
    if (toFloat() < target.toFloat())
        return 1;
    return 0;
}

bool Fixed::operator>=(const Fixed& target)
{
    if (toFloat() >= target.toFloat())
        return 1;
    return 0;
}

bool Fixed::operator<=(const Fixed& target)
{
    if (toFloat() <= target.toFloat())
        return 1;
    return 0;
}

bool Fixed::operator==(const Fixed& target)
{
    if (toFloat() == target.toFloat())
        return 1;
    return 0;
}

bool Fixed::operator!=(const Fixed& target)
{
    if (toFloat() != target.toFloat())
        return 1;
    return 0;
}

float     Fixed::operator+(const Fixed& target)
{
    return (toFloat() + target.toFloat());
}

float     Fixed::operator-(const Fixed& target)
{
    return (toFloat() - target.toFloat());
}

float     Fixed::operator*(const Fixed& target)
{
    return (toFloat() * target.toFloat());
}

float     Fixed::operator/(const Fixed& target)
{
    return (toFloat() / target.toFloat());
}

Fixed & Fixed::operator++(void)
{
    this->fixed_point_nbr++;
    return (*this);
}

Fixed	Fixed::operator++(int)
{
    Fixed	prv(*this);

    this->fixed_point_nbr++;
    return (prv);
}

Fixed& Fixed::operator--(void)
{
    this->fixed_point_nbr--;
    return (*this);
}

Fixed	Fixed::operator--(int)
{
    Fixed	prv(*this); //복사연산자를 통해 코드 실행 이전의 값을 반환함으로써 연산은 미리시키고 값은 증가

    this->fixed_point_nbr--;
    return (prv);
}

Fixed& Fixed::min(Fixed& tar1, Fixed& tar2)
{
    if (tar1.toFloat() <= tar2.toFloat())
    {
        return tar1;
    }
    return tar2;
}

const Fixed& Fixed::min(const Fixed& tar1, const Fixed& tar2)
{
    if (tar1.toFloat() <= tar2.toFloat())
    {
        return tar1;
    }
    return tar2;
}

Fixed& Fixed::max(Fixed& tar1, Fixed& tar2)
{
    if (tar1.toFloat() >= tar2.toFloat())
    {
        return tar1;
    }
    return tar2;
}

const Fixed& Fixed::max(const Fixed& tar1, const Fixed& tar2)
{
    if (tar1.toFloat() >= tar2.toFloat())
    {
        return tar1;
    }
    return tar2;
}