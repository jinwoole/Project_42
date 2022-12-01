#include <iostream>

using namespace std;

class CustomException : public std::exception
{
	public:
		const char* what(void) const throw()
		{
			return ("CustomException");
		}
};

void Divide(int n1, int n2)
{
	if (n2 == 0)
		throw (CustomException()); //divide내에서 catch
	cout << "몫 : " << n1 / n2 << endl;
	cout << "나머지 : " << n1 % n2 << endl;
}

int main(void)
{
	int n1, n2;
	cout << "수 입력 : ";
	cin >> n1 >> n2;
    
	try
	{
		Divide(n1, n2);
		cout << "나눗셈 종료" << endl;
	}
	catch (std::exception& e)
	{
		cerr << e.what() << endl;
	}
	return 0;
}