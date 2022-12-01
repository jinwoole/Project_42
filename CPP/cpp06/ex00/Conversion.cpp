#include "Conversion.hpp"

Conversion::Conversion()
{
}

Conversion& Conversion::operator=(const Conversion& other)
{
	this->string_input = other.string_input;
	this->input_value = other.input_value;
	this->input_end = other.input_end;
	this->char_value = other.char_value;
	this->int_value = other.int_value;
	this->float_value = other.float_value;
	this->type = other.type;

	return *this;
}

Conversion::Conversion(const Conversion& other)
{
	*this = other;
}

Conversion::Conversion(char *char_input)
{
	std::string input(char_input);
	bool vaild_check = false;

	if (input == "-inff" || input == "+inff" || input == "nanf" || input == "-inf" || input == "+inf" || input == "nan")
		vaild_check = true;
	if (input.length() == 1 && isprint(char_input[0]))
	{
		vaild_check = true;
		this->type = CHAR;
		this->char_value = char_input[0];
	}
	this->input_value = strtod(char_input, &this->input_end); //받아온 친구를 double로 저장. 드럽게 큰 자료형으로 받는게 좋지

	std::string end(input_end); //예외처리
	if ((vaild_check == false && isinf(input_value)) || (vaild_check == false && isinf(input_value) == 0 && !(end == "f" || end == "\0")))
	{
		std::cout << "Wrong Input" << std::endl;
		exit(1);
	}
	if (isinf(input_value) == 1)
	{
		if (input_end[0] == 'f' || input_end[0] == 'F')
		{
			this->float_value = static_cast<float>(input_value);
			type = INFF;
		}
		else
			type = INF;
		return ;
	}
	if ((vaild_check == false && input_value < INT_MAX && input_value > INT_MIN && (input.find('.') == std::string::npos)) || (type == CHAR && isdigit(char_value)))
	{
		type = INT;
		this->int_value = input_value;
	}
	else if (input_value < FLT_MAX && end == "f")
	{
		type = FLOAT;
		this->float_value = input_value;
	}
	else if (type == CHAR && vaild_check == false)
	{
		type = DOUBLE;
	}
	else if (isnan(input_value))
	{
		if (end == "f")
		{
			this->type = FLOAT;
			this->float_value = input_value;
		}
		else
		{
			this->type = DOUBLE;
		}
	}
}

Conversion::~Conversion()
{
}

void Conversion::print_char()
{
	std::cout << "char: ";
	if (isnan(input_value))
		std::cout << "impossible";
	else if (this->type == INFF || this->type == INF)
	{
		std::cout << "impossible";
	}
	else if (this->type == CHAR)
	{
		std::cout << char_value;
	}
	else if (this->type == INT)
	{
		if (isprint(int_value) == 0)
		{
			std::cout << "Non displayable" << std::endl;
			return ;
		}
		if (int_value < 0 || int_value > 127)
		{
			std::cout << "impossible" << std::endl;
			return ;
		}
		std::cout << static_cast<char>(int_value);
	}
	else if (this->type == FLOAT)
	{
		if (isprint(static_cast<char>(float_value)) == 0)
		{
			std::cout << "Non visiable" << std::endl;
			return ;
		}
		std::cout << static_cast<char>(float_value);
	}
	else if (this->type == DOUBLE)
	{
		if (isprint(static_cast<char>(input_value)) == 0)
		{
			std::cout << "Non visiable" << std::endl;
			return ;
		}
		std::cout << static_cast<char>(input_value);
	}
	std::cout << std::endl;
}

void Conversion::print_int()
{
    std::cout << "int: ";
	if (isnan(input_value) || input_value > INT_MAX || input_value < INT_MIN)
		std::cout << "impossible";
	else if (this->type == CHAR)
		std::cout << static_cast<int>(char_value);
	else if (this->type == FLOAT)
		std::cout << static_cast<int>(float_value);
	else if (this->type == DOUBLE)
		std::cout << static_cast<int>(input_value);
	else if (this->type == INT)
		std::cout << int_value;
	std::cout << std::endl;
}

void Conversion::print_float()
{
	std::cout << "float: ";
	if (this->type == INFF)
	{
		std::cout << static_cast<float>(input_value) << 'f';
	}
	else if (this->type == INF)
	{
		std::cout << "impossible";
	}
	else if (this->type == CHAR)
	{
		std::cout << static_cast<float>(char_value) << 'f';
	}
	else if (this->type == INT)
	{
		std::cout << static_cast<float>(int_value) << 'f';
	}
	else if (this->type == FLOAT)
		std::cout << float_value << 'f';
	else if (this->type == DOUBLE)
	{
		std::cout << static_cast<float>(input_value) << 'f';
	}
	std::cout << std::endl;
}

void Conversion::print_double()
{
	std::cout << "double: ";
	
	if (this->type == CHAR)
	{
		std::cout << static_cast<double>(char_value);
	}
	else if (this->type == INT)
    {
		std::cout << static_cast<double>(int_value);
	}
	else if (this->type == FLOAT)
    {
		std::cout << static_cast<double>(float_value);
	}
	else
		std::cout << input_value;
	std::cout << std::endl;
}