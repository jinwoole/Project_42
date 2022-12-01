#include "Harl.hpp"

void Harl::debug(void)
{
    std::cout << "[ DEBUG ]" << std::endl;
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special- ketchup burger. I really do!" << std::endl;
}

void Harl::info(void)
{
    std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void)
{
    std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. " << std::endl;
    std::cout << "I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error(void)
{
    std::cout << "[ ERROR ]" << std::endl;
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level)
{
	void (Harl::*func[4])(void) = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    int idx = std::find(levels, levels + 4, level) - levels;
    //find로 찾으면 단어 일부만 입력해도 찾아버린다. compare로 비교해야 한다.

    switch (idx)
    {
        case 0:
            (this->*(func[idx]))();
            idx++;
        case 1:
            (this->*(func[idx]))();
            idx++;
        case 2:
            (this->*(func[idx]))();
            idx++;
        case 3:
            (this->*(func[idx]))();
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
            break;
    }
}
