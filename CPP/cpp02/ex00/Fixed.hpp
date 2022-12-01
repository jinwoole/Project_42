#ifndef CPP_FIXED_HPP
#define CPP_FIXED_HPP

#include <iostream>

class Fixed {
private:
    int fixed_point_nbr;
    static const int fractional_bits = 8;
public:
    Fixed();
    Fixed(const Fixed& origin);
    Fixed& operator=(const Fixed& src);
    ~Fixed();
    int getRawBits(void) const;
    void setRawBits(int const raw);
};

#endif
