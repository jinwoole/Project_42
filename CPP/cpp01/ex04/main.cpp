#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "Wrong argument numbers" << std::endl;
		return 1;
	}

	std::string file_name(argv[1]);
	std::string origin_str(argv[2]);
	std::string new_str(argv[3]);

	std::ifstream read_file(file_name);
	if (read_file.fail())
	{
		std::cout << "That file seems like cursed one" << std::endl;
		return 1;
	}
	std::ofstream write_file(file_name + ".replace"); 
	if (write_file.fail())
	{
		std::cout << "Something wrong happened during making output stream" << std::endl;
		return 1;
	}
	//파일이 생성되었다. 이걸로 독자적인 stream을 만드는 것 같다.
	//readfile과 write파일이 있으니 readfile을 한줄씩 읽으면서 대체한 스트림을
	//write파일에 갖다넣는 식으로 readfile을 eof까지 반복하면 된다.

	std::string	buffer;
	size_t		index;
	std::string temp_buffer;

	while (!std::getline(read_file, buffer).eof())
	{
		index = buffer.find(origin_str);
		if (index != std::string::npos) //찾는게 없으면 npos return
		{
			while (index != std::string::npos)
			{
				temp_buffer = buffer.substr(0, index);
				write_file << temp_buffer;
				write_file << new_str;
				buffer = buffer.substr(index + origin_str.length(), buffer.length());
				index = buffer.find(origin_str);
			}
			write_file << buffer;
		}
		else
		{
			write_file << buffer;
		}
		write_file << std::endl;
	}
	index = buffer.find(origin_str);
	if (index != std::string::npos) //찾는게 없으면 npos return
	{
		while (index != std::string::npos)
		{
			temp_buffer = buffer.substr(0, index);
			write_file << temp_buffer;
			write_file << new_str;
			buffer = buffer.substr(index + origin_str.length(), buffer.length());
			index = buffer.find(origin_str);
		}
		write_file << buffer;
	}
	else
	{
		write_file << buffer;
	}
	write_file << std::endl;
	
	//이거 하고보니 마지막줄엔 멈추네. 마지막 만나면 true그냥 되는것같다 그래서 여기 있어야한다.
	//write_file스트림 안에 집어넣으면 된다. 이제 이걸 수정해서 집어넣을 방법만 찾으면 된다.


	return 0;
}