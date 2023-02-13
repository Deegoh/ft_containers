#include <iostream>
#include <string>
#include <deque>

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
	#include "../inc/map.hpp"
	#include "../inc/stack.hpp"
	#include "../inc/vector.hpp"
	#include "../inc/set.hpp"
#endif

#include "vector_tester.hpp"
#include "map_tester.hpp"
#include "stack_tester.hpp"
#include "set_tester.hpp"

#define COUNT (5)

int main() {
#if STD //CREATE A REAL STL EXAMPLE
	std::cout << "STD" << std::endl;
#else
	std::cout << "FT" << std::endl;
#endif
	std::cout << "hello container - seed: 10 - count: " << COUNT << std::endl;
	std::cout << "Vector tester" << std::endl;
	testVector(COUNT);
	std::cout << "Map tester" << std::endl;
	testMap(COUNT);
	std::cout << "Stack tester" << std::endl;
	testStack();
	std::cout << "Set tester" << std::endl;
	testSet();

}