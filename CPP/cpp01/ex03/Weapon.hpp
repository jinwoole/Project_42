#ifndef WEAPON_CPP
#define WEAPON_CPP

#include <string>

class Weapon {
	private:
		std::string type;
	public:
		Weapon(std::string type);
		const std::string& getType();
		void setType(std::string type);
		~Weapon();
};

#endif
