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
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
//# include <map.hpp>
//# include <stack.hpp>
	#include <vector.hpp>
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

#include "tester.hpp"

int main() {
	#if STD //CREATE A REAL STL EXAMPLE
		std::cout << "STD" << std::endl;
	#else
		std::cout << "FT" << std::endl;
	#endif
	srand(10);
	std::cout << "hello container - seed: 10 - count: " << COUNT << std::endl;

//	ft::vector<std::string> str_vec;
//	ft::vector<int> int_vec;
//	ft::vector<Buffer> buffer_vec;
//
//	ft::vector<int> int_vec2(10, 5);
//	ft::vector<int> int_vec3(int_vec2.begin(), int_vec2.end());

//	testMaxSize(buffer_vec, "buffer");
//	testMaxSize(int_vec, "int");
//
//	std::cout << "Push_back" << std::endl;
//	for (int i = 0; i < COUNT; i++)
//	{
//		//string
//		char c = i + 'a';
//		str_vec.push_back(NumberToS(c));
//		//int
//		int_vec.push_back(i * 10);
//		//Buffer
//		buffer_vec.push_back(Buffer());
//	}
//	printfComp("size", buffer_vec.size());
//	printfComp("capacity", buffer_vec.capacity());
//
//	for (int i = 0; i < COUNT; i++)
//	{
//		const int idx = rand() % COUNT;
//		buffer_vec[idx].idx = 5;
//	}
//
//	printVec(buffer_vec, "buffer");
//	printVec(str_vec, "string");
//	printVec(int_vec, "int");
//	std::cout << "Pop_back" << std::endl;
//	testMaxSize(int_vec, "int");
//	int_vec.pop_back();
//	int_vec.pop_back();
//	printVec(int_vec, "int");
//
//	std::cout << "Clear" << std::endl;
//	testMaxSize(int_vec, "int");
//	std::cout << *int_vec.end() << std::endl;
//	int_vec.clear();
//	printVec(int_vec, "int");
//	std::cout << "begin()" << *int_vec.begin() << std::endl;
//	std::cout << "end()" << *int_vec.end() << std::endl;

//	testMaxSize(int_vec, "int");
	testErase();
//	testResize();
//	testAssign();
//	testCopy();
//	testInsert();
//	testBidirect();
//	testIte();
//	testIteArrow();
//	testRelOp();
//	testRiteConstruct();
//	testRite();
//	testRite2();
//	testArrow();
}
