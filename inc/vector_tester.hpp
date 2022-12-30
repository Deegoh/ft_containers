#ifndef VECTOR_TESTER_HPP
# define VECTOR_TESTER_HPP

#include "vector.hpp"
#include "base.hpp"
#include <string>
#include <sstream>
#include <cstdlib>

#define BUFFER_SIZE 4096
#define COUNT (5)

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
void testErase(void);
void testCopy();
void testInsert();
void prepost_incdec(ft::vector<int> &vct);
void testBidirect();
void testIte();
void testIteArrow();
void testRelOp(void);
void testRiteConstruct();
void testRite();
void testRite2();
void testArrow();
void testVector();


#endif
