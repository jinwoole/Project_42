#ifndef DOG
#define DOG

#include <string>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain *dogBrain;
	public:
		Dog();
		Dog(Dog& other);
		Dog& operator=(Dog& other);
		~Dog();
		void makeSound() const;
		std::string getIdea();
		void setIdea(const std::string& idea);
		Brain* getBrain();
};

#endif