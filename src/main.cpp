#include <iostream>

#ifndef STD
# define STD 0
#endif
#if STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
//# include <stack.hpp>
	#include <vector.hpp>
#endif

#include "vector_tester.hpp"

#define COUNT (5)
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))

int main() {
	#if STD //CREATE A REAL STL EXAMPLE
		std::cout << "STD" << std::endl;
	#else
		std::cout << "FT" << std::endl;
	#endif
	std::cout << "hello container - seed: 10 - count: " << COUNT << std::endl;
	testVector();
}
