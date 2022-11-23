//#include "iterator.hpp"
#include <vector.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (5)
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
void printVec(T vec, std::string str) {
	std::cout << str << "[";
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i];
		if (i < COUNT -1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}

template<>
void printVec(std::vector<Buffer> vec, std::string str) {
	std::cout << str << "[";
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i].idx;
		if (i < COUNT -1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}

//TODO why it's segfault
template<>
void printVec(ft::vector<Buffer> vec, std::string str) {
	std::cout << str << "[";
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i].idx;
		if (i < COUNT -1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}

template <typename T>
std::string NumberToS ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

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
	std::cout << "std_capacity: " << std_vector_buffer.capacity() << " = 0" << std::endl;
	std::cout << "ft_capacity: " << ft_vector_buffer.capacity() << " = " << std_vector_buffer.capacity() << std::endl;

	for (int i = 0; i < COUNT; i++)
	{
		//string
		char c = i + 'a';
		std_str_vector.push_back(NumberToS(c));
		ft_str_vector.push_back(NumberToS(c));
		//int
		std_int_vector.push_back(i * 10);
		ft_int_vector.push_back(i * 10);
		//Buffer
		std_vector_buffer.push_back(Buffer());
		ft_vector_buffer.push_back(Buffer());
	}
	std::cout << "std_size: " << std_vector_buffer.size() << " = " << COUNT << std::endl;
	std::cout << "std_capacity: " << std_vector_buffer.capacity() << " = " << std_vector_buffer.capacity() << std::endl;
	std::cout << "ft_size: " << ft_vector_buffer.size() << " = " << std_vector_buffer.size() << std::endl;
	std::cout << "ft_capacity: " << ft_vector_buffer.capacity() << " = " << std_vector_buffer.capacity() << std::endl;

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		std_vector_buffer[idx].idx = 5;
		ft_vector_buffer[idx].idx = 5;
	}

	printVec(std_vector_buffer, "std buffer");
//	printVec(ft_vector_buffer, "ft buffer");

	std::cout << "ft buffer" << "[";
	for (int i = 0; i < COUNT; i++)
	{
		std::cout << ft_vector_buffer[i].idx;
		if (i < COUNT -1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;

	printVec(std_str_vector, "std str");

	std::cout << "ft str" << "[";
	for (int i = 0; i < COUNT; i++)
	{
		std::cout << ft_str_vector[i];
		if (i < COUNT -1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;

	printVec(std_int_vector, "std int");

	std::cout << "ft int" << "[";
	for (int i = 0; i < COUNT; i++)
	{
		std::cout << ft_int_vector[i];
		if (i < COUNT -1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	return (0);
}
