#ifndef VECTOR_TESTER_HPP
# define VECTOR_TESTER_HPP

#ifndef STD
	#define STD 0
#endif

#if STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	namespace ft = std;
#else
	#include "../inc/vector.hpp"
#endif

#include <list>
#include "../inc/base.hpp"
#include "test.hpp"

#include <string>
#include <sstream>
#include <cstdlib>

#define T_SIZE_TYPE typename ft::vector<T>::size_type

template <typename T>
void	printSize(ft::vector<T> const &vct, bool print_content = true) {
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;

	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template<typename T>
void printVec(ft::vector<T> &vec, std::string str);

template<>
void printVec(ft::vector<Buffer> &vec, std::string str);

template <typename T>
std::string NumberToS (T Number);

template <typename T>
void printfComp(std::string str, T std_f);

template <typename T>
void testMaxSize(T &vec, std::string str);

template <typename T>
void printTest(T &vec);

void testAssign();
void testResize();
void testErase();
void testCopy();
void testInsert();
void prepost_incdec(ft::vector<int> &vct);
void testBidirect();
void testIte();
void testIteArrow();
void testRelOp();
void testRiteConstruct();
void testRite();
void testRite2();
void testArrow();
void testVector(int count);


#endif
