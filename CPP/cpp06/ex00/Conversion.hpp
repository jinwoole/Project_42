#ifndef CONVERSION
#define CONVERSION

#include <iostream>
#include <string>
#include <cmath>
#include <cfloat>
#include <float.h>

typedef enum		types
{
	CHAR, INT, FLOAT, DOUBLE, INF, INFF
}					type_t;

class Conversion
{
	private:
		std::string string_input;
		double input_value;
		char *input_end;
		char char_value;
		int int_value;
        float float_value;
		type_t type;

	public:
        Conversion();
		Conversion(const Conversion &other);
		Conversion& operator=(const Conversion &other);
        Conversion(char *char_input);
		~Conversion();

		void print_char();
		void print_int();
		void print_float();
        void print_double();
};


#endif