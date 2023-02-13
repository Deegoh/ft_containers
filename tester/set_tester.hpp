#ifndef SET_TESTER_HPP
#define SET_TESTER_HPP

#ifndef STD
#define STD 0
#endif

#if STD //CREATE A REAL STL EXAMPLE
#include <set>
	namespace ft = std;
#else
# include "../inc/set.hpp"
#endif

#include <iostream>
#include <list>

void testSet();
void testInsertSet();
void testCopySet();
void testEraseSet();
void ft_comp(const ft::set<char> &st, const ft::set<char>::const_iterator &it1, const ft::set<char>::const_iterator &it2);

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

template <typename SET, typename U>
void	ft_erase(SET &st, U param) {
	st.erase(param);
	printSize(st);
}

template <typename SET, typename U, typename V>
void	ft_erase(SET &st, U param, V param2) {
	st.erase(param, param2);
	printSize(st);
}

#endif
