#ifndef CPP_FIXED_HPP
#define CPP_FIXED_HPP

#include <iostream>

class Fixed {
private:
    int fixed_point_nbr;
    static const int fractional_bits = 8;
public:
    Fixed();
    Fixed(const int i);
    Fixed(const float f);
    Fixed(const Fixed& origin);
    Fixed& operator=(const Fixed& src); //연산자 오버로딩. 레퍼런스로 안하면 src의 생성자와 소멸자가 작동해서 슬프다
    ~Fixed();

    int     getRawBits(void) const;
    void    setRawBits(int const raw);
    float   toFloat(void) const;
    int     toInt(void) const;

    bool    operator>(const Fixed& target);
    bool    operator<(const Fixed& target);
    bool    operator>=(const Fixed& target);
    bool    operator<=(const Fixed& target);
    bool    operator==(const Fixed& target);
    bool    operator!=(const Fixed& target);
    float   operator+(const Fixed& target);
    float   operator-(const Fixed& target);
    float   operator*(const Fixed& target);
    float   operator/(const Fixed& target);
    Fixed&  operator++(void);
    Fixed   operator++(int);
    Fixed&  operator--(void);
    Fixed   operator--(int);


    static Fixed& min(Fixed& tar1, Fixed& tar2);
    static const Fixed& min(const Fixed& tar1, const Fixed& tar2);
    static Fixed& max(Fixed& tar1, Fixed& tar2);
    static const Fixed& max(const Fixed& tar1, const Fixed& tar2);
};

std::ostream& operator<<(std::ostream& out, const Fixed& num);
//member function으로 하고 싶다면, friend 키워드를 붙여야 한다.


#endif
