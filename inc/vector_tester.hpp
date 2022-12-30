#ifndef VECTOR_TESTER_HPP
# define VECTOR_TESTER_HPP

#ifndef STD
	#define STD 0
#endif

#if STD //CREATE A REAL STL EXAMPLE
	#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

#include "base.hpp"

#include <string>
#include <sstream>
#include <cstdlib>

#define BUFFER_SIZE 4096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

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
