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
//	#include <test_map.h>
//# include <stack.hpp>
	#include <vector.hpp>
#endif
#include "vector_tester.hpp"
#include <list>

#define COUNT (5)
//#define COUNT (MAX_RAM / (int)sizeof(Buffer))


//template <typename T>
//std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
//{
//	o << "key: " << iterator->first << " | value: " << iterator->second;
//	if (nl)
//		o << std::endl;
//	return ("");
//}
//
//template<typename T_MAP>
//void	printSize(T_MAP const &mp, bool print_content = 1)
//{
//	std::cout << "size: " << mp.size() << std::endl;
//	std::cout << "max_size: " << mp.max_size() << std::endl;
//	if (print_content)
//	{
//		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
//		std::cout << std::endl << "Content is:" << std::endl;
//		for (; it != ite; ++it)
//			std::cout << "- " << printPair(it, false) << std::endl;
//	}
//	std::cout << "###############################################" << std::endl;
//}
//
//void testCopyMap() {
//
//		std::list<ft::pair<const int, int> > lst;
//		unsigned int lst_size = 7;
//		for (unsigned int i = 0; i < lst_size; ++i)
//			lst.push_back(ft::pair<const int, int>(lst_size - i, i));
//		ft::map<const int, int> mp(lst.begin(), lst.end());
//		ft::map<const int, int>::iterator it = mp.begin(), ite = mp.end();
//
//		ft::map<const int, int> mp_range(it, --(--ite));
//		for (int i = 0; it != ite; ++it)
//			it->second = ++i * 5;
//
//		it = mp.begin(); ite = --(--mp.end());
//		ft::map<const int, int> mp_copy(mp);
//		for (int i = 0; it != ite; ++it)
//			it->second = ++i * 7;
//
//		std::cout << "\t-- PART ONE --" << std::endl;
//		printSize(mp);
//		printSize(mp_range);
//		printSize(mp_copy);
//
//		mp = mp_copy;
//		mp_copy = mp_range;
//		mp_range.clear();
//
//		std::cout << "\t-- PART TWO --" << std::endl;
//		printSize(mp);
//		printSize(mp_range);
//		printSize(mp_copy);
//}

void testMap(int count) {
//	testCopyMap();
	ft::map<int, int> map_int;
	ft::map<int, int>::iterator it;
//
	for (int i = 0; i < count; ++i)
	{
//		template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
//		pair<typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator, bool>
//		_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::_M_insert_unique(const _Val& __v) {
//			typedef pair<iterator, bool> _Res;
//			pair<_Base_ptr, _Base_ptr> __res = _M_get_insert_unique_pos(_KeyOfValue()(__v));
//			if (__res.second)
//			{
//				_Alloc_node __an(*this);
//				return _Res(_M_insert_(__res.first, __res.second,
//									   _GLIBCXX_FORWARD(_Arg, __v), __an),
//							true);
//			}
//			return _Res(iterator(__res.first), false);
//		}


//		std::pair<iterator, bool>
//		insert(const value_type& __x)
//		{ return _M_t._M_insert_unique(__x); }
		map_int.insert(ft::make_pair(i, i * count));
//		map_int.insert(std::make_pair(i, i * count));
	}
//
//	for(it = map_int.begin(); it != map_int.end(); ++it)
//	{
//		std::cout << "first[" << it->first << "] second[" << it->second << "]" << "\n";
//	}
//
//	int sum = 0;
//	for (int i = 0; i < count; i++)
//	{
//		int access = rand();
//		sum += map_int[access];
//	}
//	for(ft::map<int, int>::iterator it = map_int.begin(); it != map_int.end(); ++it)
//	{
//		std::cout << it->first << "\n";
//	}
//	std::cout << "should be constant with the same seed: " << sum << std::endl;
//
//	{
//		ft::map<int, int> copy = map_int;
//		for(ft::map<int, int>::iterator it = copy.begin(); it != copy.end(); ++it)
//		{
//			std::cout << it->first << "\n";
//		}
//	}
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
//	ft::rb_tree<std::string, int> test;
//	test._root->value = 10;
//	std::cout << test._root->value << std::endl;

//	ft::rb_tree<std::string, int> tree;
//	tree = test;

//	std::cout << tree._root->value << std::endl;
}
