#ifndef SET_TESTER_HPP
#define SET_TESTER_HPP

#ifndef STD
#define STD 0
#endif

#if STD //CREATE A REAL STL EXAMPLE
#include <set>
	namespace ft = std;
#else
#include "../inc/set.hpp"
#endif

#include <iostream>

void testSet();
void testInsertSet();

template <typename T_SET>
void printSize(T_SET const &st) {
	std::cout << "size: " << st.size() << std::endl;
	std::cout << "max_size: " << st.max_size() << std::endl;
	typename T_SET::const_iterator it = st.begin(), ite = st.end();
	std::cout << std::endl << "Content is:" << std::endl;
	for (; it != ite; ++it)
		std::cout << "- " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}

#endif
