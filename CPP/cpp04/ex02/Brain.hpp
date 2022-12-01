#ifndef BRAIN
#define BRAIN

#include <string>

class Brain
{
	private:
		std::string ideas[100];
	public:
		Brain();
		Brain(const Brain& other);
		Brain& operator=(const Brain& other);
		~Brain();
		std::string getFirstIdea();
		void setFirstIdea(const std::string& idea);
};

#endif