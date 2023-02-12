#ifndef STACK_TESTER_HPP
#define STACK_TESTER_HPP

#ifndef STD
# define STD 0
#endif

#if STD //CREATE A REAL STL EXAMPLE
# include <stack>
	namespace ft = std;
#else
# include "../inc/stack.hpp"
#endif


#include <iostream>

template <typename T_STACK>
void	printSize(T_STACK &stck, bool print_content = 1)
{
	std::cout << "size: " << stck.size() << std::endl;
	if (print_content)
	{
		std::cout << std::endl << "Content was:" << std::endl;
		while (stck.size() != 0) {
			std::cout << "- " << stck.top() << std::endl;
			stck.pop();
		}
	}
	std::cout << "###############################################" << std::endl;
}

void testStack();

#endif
