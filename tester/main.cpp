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
#endif

#include "test.hpp"
#include "vector_tester.hpp"

#define COUNT (5)

int main() {
#if STD //CREATE A REAL STL EXAMPLE
	std::cout << "STD" << std::endl;
#else
	std::cout << "FT" << std::endl;
#endif
	std::cout << "hello container - seed: 10 - count: " << COUNT << std::endl;
	srand(10);
//	testVector(COUNT);
}