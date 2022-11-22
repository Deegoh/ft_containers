//#include "iterator.hpp"
#include <vector.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (5)
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))

int main(/*int argc, char** argv*/) {
//	if (argc != 2)
//	{
//		std::cerr << "Usage: ./test seed" << std::endl;
//		std::cerr << "Provide a seed please" << std::endl;
//		std::cerr << "Count value:" << COUNT << std::endl;
//		return (1);
//	}
//	(void)argv;

	srand(10);
	std::cout << "hello container - seed: 10 - count: " << COUNT << std::endl;
	std::vector<std::string> std_str_vector;
	ft::vector<std::string> ft_str_vector;

	std::vector<int> std_int_vector;
	ft::vector<int> ft_int_vector;

	std::vector<Buffer> std_vector_buffer;
	ft::vector<Buffer> ft_vector_buffer;
	std::cout << "std_capacity: " << std_vector_buffer.capacity() << std::endl;
	std::cout << "ft_capacity: " << ft_vector_buffer.capacity() << std::endl;

	for (int i = 0; i < COUNT; i++)
	{
		std_vector_buffer.push_back(Buffer());
//		ft_vector_buffer.push_back(Buffer());
	}
	std::cout << "std_size: " << std_vector_buffer.size() << std::endl;
	std::cout << "std_capacity: " << std_vector_buffer.capacity() << std::endl;
	std::cout << "ft_size: " << ft_vector_buffer.size() << std::endl;
	std::cout << "ft_capacity: " << ft_vector_buffer.capacity() << std::endl;

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		std_vector_buffer[idx].idx = 5;
	}

	for (int i = 0; i < 5; i++)
	{
		std::cout << std_vector_buffer[i].idx << std::endl;
	}
	return (0);
}
