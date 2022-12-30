#include <iostream>
#include <cstdlib>

#ifndef STD
# define STD 0
#endif
#if STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>

	#include <functional>
	#include <utility>
	namespace ft = std;
#else
	#include <map.hpp>
//# include <stack.hpp>
	#include <vector.hpp>
#endif
#include "vector_tester.hpp"

#define COUNT (5)
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))

void testMap(int count) {
	ft::map<int, int> map_int;

	for (int i = 0; i < count; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < count; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	for(ft::map<int, int>::iterator it = map_int.begin(); it != map_int.end(); ++it)
	{
		std::cout << it->first << "\n";
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
		for(ft::map<int, int>::iterator it = copy.begin(); it != copy.end(); ++it)
		{
			std::cout << it->first << "\n";
		}
	}
}

int main() {
	#if STD //CREATE A REAL STL EXAMPLE
		std::cout << "STD" << std::endl;
	#else
		std::cout << "FT" << std::endl;
	#endif
	std::cout << "hello container - seed: 10 - count: " << COUNT << std::endl;
	srand(10);
//	testVector(COUNT);
	testMap(COUNT);
}
