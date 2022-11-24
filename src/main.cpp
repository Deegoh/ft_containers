//#include "iterator.hpp"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>

#ifndef STD
# define STD 0
#endif
#if STD //CREATE A REAL STL EXAMPLE
#include <map>
	# include <stack>
	# include <vector>
	namespace ft = std;
#else
//# include <map.hpp>
//# include <stack.hpp>
# include <vector.hpp>
#endif

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
void printVec(T &vec, std::string str) {
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
void printVec(ft::vector<Buffer> &vec, std::string str) {
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

template <typename T>
void printfComp(std::string str, T std_f) {
	std::cout << str <<": " << std_f << std::endl;
}

void testMaxSize() {
	ft::vector<int> vec;

	// set some content in the vector:
	for (int i=0; i<100; i++) vec.push_back(i);

	std::cout << "size: " << vec.size() << "\n";
	std::cout << "capacity: " << vec.capacity() << "\n";
	std::cout << "max_size: " << vec.max_size() << "\n";
}

int main() {
	#if STD //CREATE A REAL STL EXAMPLE
		std::cout << "STD" << std::endl;
	#else
		std::cout << "FT" << std::endl;
	#endif
	srand(10);
	std::cout << "hello container - seed: 10 - count: " << COUNT << std::endl;

	ft::vector<std::string> str_vec;
	ft::vector<int> int_vec;
	ft::vector<Buffer> buffer_vec;

	printfComp("capacity", buffer_vec.capacity());

	for (int i = 0; i < COUNT; i++)
	{
		//string
		char c = i + 'a';
		str_vec.push_back(NumberToS(c));
		//int
		int_vec.push_back(i * 10);
		//Buffer
		buffer_vec.push_back(Buffer());
	}
	printfComp("size", buffer_vec.size());
	printfComp("capacity", buffer_vec.capacity());

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		buffer_vec[idx].idx = 5;
	}

	printVec(buffer_vec, "buffer");
	printVec(str_vec, "string");
	printVec(int_vec, "int");

	testMaxSize();
	return (0);
}
