#ifndef MAIN_UTILS_HPP
# define MAIN_UTILS_HPP
#include <typeinfo>

template<typename T>
void printVec(ft::vector<T> &vec, std::string str) {
	std::cout << str << "[";
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i];
		if (i < vec.size() - 1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}

template<>
void printVec(ft::vector<Buffer> &vec, std::string str) {
	std::cout << str << "[";
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i].idx;
		if (i < vec.size() - 1)
			std::cout << ", ";
	}
	std::cout << "]" << std::endl;
}

template <typename T>
std::string NumberToS ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
void printfComp(std::string str, T std_f) {
	std::cout << str <<": " << std_f << std::endl;
}

template <typename T>
void testMaxSize(T &vec, std::string str) {
	std::cout << str << "\n";
	std::cout << "size: " << vec.size() << "\n";
	std::cout << "capacity: " << vec.capacity() << "\n";
	std::cout << "max_size: " << vec.max_size() << "\n";
}

template <typename T>
void printTest(T &vec) {
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << " " << ((vec.size() <= vec.capacity()) ? "OK" : "KO") << std::endl;
	std::cout << "max_size: " << vec.max_size() << std::endl;
	std::cout << std::endl;
	std::cout << "Content is:" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "- " << vec[i] << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void testAssign() {
	ft::vector<int> vct(7);
	ft::vector<int> vct_two(4);
	ft::vector<int> vct_three;
	ft::vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	printTest(vct);
	printTest(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printTest(vct);
	printTest(vct_two);
	printTest(vct_three);
	printTest(vct_four);

	vct_four.assign(6, 84);
	printTest(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	printTest(vct);
	printTest(vct_two);
}

void testResize() {
	const int start_size = 7;

	ft::vector<int> vct(start_size, 20);
	ft::vector<int> vct2;

	for (int i = 2; i < 7; ++i)
		vct[i] = (7 - i) * 3;

	printVec(vct, "vct");

	vct.resize(10, 42);
	printVec(vct, "vct");

	vct.resize(18, 43);
	printVec(vct, "vct");
	vct.resize(10);
	printVec(vct, "vct");
	vct.resize(23, 44);
	printVec(vct, "vct");
	vct.resize(5);
	printVec(vct, "vct");
	vct.reserve(5);
	vct.reserve(3);
	printVec(vct, "vct");
	vct.resize(87);
	vct.resize(5);
	printVec(vct, "vct");

	std::cout << "vct2 is empty " << vct2.empty() << std::endl;
	vct2 = vct;
	std::cout << "vct2 is empty " << vct2.empty() << std::endl;
	vct.reserve(vct.capacity() + 1);
	printVec(vct, "vct");
	printVec(vct2, "vct2");

	vct2.resize(0);
	std::cout << "vct2 is empty " << vct2.empty() << std::endl;
	printVec(vct2, "vct2");
}

void	checkErase(ft::vector<std::string> const &vct,
				   ft::vector<std::string>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printTest(vct);
}

void	testErase(void)
{
	ft::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printTest(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	printTest(vct);
	ft::vector<std::string>::iterator it = vct.erase(vct.begin(), vct.begin() + 3);
	std::cout << *it << std::endl;
	printTest(vct);

//	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
//	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));
//
//	vct.push_back("Hello");
//	vct.push_back("Hi there");
//	printTest(vct);
//	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));
//
//	vct.push_back("ONE");
//	vct.push_back("TWO");
//	vct.push_back("THREE");
//	vct.push_back("FOUR");
//	printTest(vct);
//	checkErase(vct, vct.erase(vct.begin(), vct.end()));
}

void testCopy() {
	ft::vector<int> vct(5);
	ft::vector<int>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	ft::vector<int> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	ft::vector<int> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	printTest(vct);
	printTest(vct_range);
//	printTest(vct_copy);
//
//	vct = vct_copy;
//	vct_copy = vct_range;
//	vct_range.clear();
//
//	std::cout << "\t-- PART TWO --" << std::endl;
//	printTest(vct);
//	printTest(vct_range);
//	printTest(vct_copy);
}

void testInsert() {
	ft::vector<int> vct(10);
	ft::vector<int> vct2;
	ft::vector<int> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	printTest(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	printTest(vct2);

	vct2.insert(vct2.end() - 2, 42);
	printTest(vct2);

	vct2.insert(vct2.end(), 2, 84); //segfault
	printTest(vct2);

	vct2.resize(4);
	printTest(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	printTest(vct2);

	printTest(vct);

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
	printTest(vct3);
}

//#include <list>
//
//void testBidirect() {
//	std::list<int> lst;
//	std::list<int>::iterator lst_it;
//	for (int i = 1; i < 5; ++i)
//		lst.push_back(i * 3);
//
//	ft::vector<int> vct(lst.begin(), lst.end());
//	printTest(vct);
//
//	lst_it = lst.begin();
//	for (int i = 1; lst_it != lst.end(); ++i)
//		*lst_it++ = i * 5;
//	vct.assign(lst.begin(), lst.end());
//	printTest(vct);
//
//	vct.insert(vct.end(), lst.rbegin(), lst.rend());
//	printTest(vct);
//}

void	prepost_incdec(ft::vector<int> &vct)
{
	ft::vector<int>::iterator it = vct.begin();
	ft::vector<int>::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}


void testIte() {
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::iterator it = vct.begin();
	ft::vector<int>::const_iterator ite = vct.begin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;
	prepost_incdec(vct);

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
	std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	printTest(vct);
}

#include "base.hpp"

void testIteArrow() {
	const int size = 5;
	ft::vector<foo<int> > vct(size);
	ft::vector<foo<int> >::iterator it(vct.begin());
	ft::vector<foo<int> >::const_iterator ite(vct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
	printTest(vct);

	it = vct.begin();
	ite = vct.begin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	it->m();
	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	(*it).m();
	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;
}

void	testRiteEqOpe()
{
//	const int size = 5;
//	ft::vector<foo<int> > vct(size);
//	ft::vector<foo<int> >::reverse_iterator it_0(vct.rbegin());
//	ft::vector<foo<int> >::reverse_iterator it_1(vct.rend());
//	ft::vector<foo<int> >::reverse_iterator it_mid;
//
//	ft::vector<foo<int> >::const_reverse_iterator cit_0 = vct.rbegin();
//	ft::vector<foo<int> >::const_reverse_iterator cit_1;
//	ft::vector<foo<int> >::const_reverse_iterator cit_mid;
//
//	for (int i = size; it_0 != it_1; --i)
//		*it_0++ = i;
//	printSize(vct, 1);
//	it_0 = vct.rbegin();
//	cit_1 = vct.rend();
//	it_mid = it_0 + 3;
//	cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;
//
//	std::cout << std::boolalpha;
//	std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;
//
//	std::cout << "\t\tft_eq_ope:" << std::endl;
//	// regular it
//	ft_eq_ope(it_0 + 3, it_mid);
//	ft_eq_ope(it_0, it_1);
//	ft_eq_ope(it_1 - 3, it_mid);
//	// const it
//	ft_eq_ope(cit_0 + 3, cit_mid);
//	ft_eq_ope(cit_0, cit_1);
//	ft_eq_ope(cit_1 - 3, cit_mid);
//	// both it
//	ft_eq_ope(it_0 + 3, cit_mid);
//	ft_eq_ope(it_mid, cit_0 + 3);
//	ft_eq_ope(it_0, cit_1);
//	ft_eq_ope(it_1, cit_0);
//	ft_eq_ope(it_1 - 3, cit_mid);
//	ft_eq_ope(it_mid, cit_1 - 3);

}

template <class T, class Alloc>
void	cmp(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

void testRelOp(void)
{
	ft::vector<int> vct(4);
	ft::vector<int> vct2(4);

	cmp(vct, vct);  // 0
	cmp(vct, vct2); // 1

	vct2.resize(10);

	cmp(vct, vct2); // 2
	cmp(vct2, vct); // 3

	vct[2] = 42;

	cmp(vct, vct2); // 4
	cmp(vct2, vct); // 5

	swap(vct, vct2);

	cmp(vct, vct2); // 6
	cmp(vct2, vct); // 7

}

void testRiteConstruct() {
	ft::vector<int> vct;
	ft::vector<int>::iterator it = vct.begin();
	ft::vector<int>::const_iterator cit = vct.begin();

	ft::vector<int>::reverse_iterator rit(it);

	ft::vector<int>::const_reverse_iterator crit(rit);
	ft::vector<int>::const_reverse_iterator crit_(it);
	ft::vector<int>::const_reverse_iterator crit_2(cit);

	/* error expected
	ft::vector<int>::reverse_iterator rit_(crit);
	ft::vector<int>::reverse_iterator rit2(cit);
	ft::vector<int>::iterator it2(rit);
	ft::vector<int>::const_iterator cit2(crit);
		*/

	std::cout << "OK" << std::endl;
}

void testRite() {
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::iterator it_ = vct.begin();
	ft::vector<int>::reverse_iterator it(it_);

	for (int i = 0; i < size; ++i)
		vct[i] = (i + 1) * 5;
	printTest(vct);

	std::cout << (it_ == it.base()) << std::endl; //1
	std::cout << (it_ == (it + 3).base()) << std::endl; //0

	std::cout << *(it.base() + 1) << std::endl; //10
	std::cout << *(it - 3) << std::endl;//15
	std::cout << *(it - 3).base() << std::endl;//20
	it -= 3;
	std::cout << *it.base() << std::endl;//20

	std::cout << "TEST OFFSET" << std::endl;
	std::cout << *(it) << std::endl;
	std::cout << *(it).base() << std::endl;
	std::cout << *(it - 0) << std::endl;
	std::cout << *(it - 0).base() << std::endl;
	std::cout << *(it - 1).base() << std::endl;

	std::cout << "OK" << std::endl;
}

void testRite2() {
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::reverse_iterator it = vct.rbegin();
//	ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
//	std::cout << *(it -= 1) << std::endl;
//
//	*(it -= 2) = 42;
//	*(it += 2) = 21;
//
//	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;
//
//	std::cout << "(it == const_it): " << (ite == it) << std::endl;
//	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
//	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
//
//	printTest(vct);
//	std::cout << *it << std::endl;
}


#endif


