#include "vector_tester.hpp"

void testVector(int count) {

	testPushBack(count);
	testErase();
	testResize();
	testAssign();
	testCopy();
	testInsert();
	testBidirect();
	testIte();
	testIteArrow();
	testRelOp();
	testRiteConstruct();
	testRite();
	testRite2();
	testArrow();
}

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
std::string NumberToS (T Number) {
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

void testPushBack(int count) {
	ft::vector<std::string> str_vec;
	ft::vector<int> int_vec;
	ft::vector<Buffer> buffer_vec;

	ft::vector<int> int_vec2(10, 5);
	ft::vector<int> int_vec3(int_vec2.begin(), int_vec2.end());

	testMaxSize(buffer_vec, "buffer");
	testMaxSize(int_vec, "int");

	std::cout << "Push_back" << std::endl;
	for (int i = 0; i < count; i++)
	{
		//string
		char c = i + 'a';
		str_vec.push_back(NumberToS(c));
		//int
		int_vec.push_back(i * 10);
		//Buffer
		buffer_vec.push_back(Buffer());
	}
	printfComp("size", buffer_vec.size());
	printfComp("capacity", buffer_vec.capacity());

	for (int i = 0; i < count; i++)
	{
		const int idx = rand() % count;
		buffer_vec[idx].idx = 5;
	}

	printVec(buffer_vec, "buffer");
	printVec(str_vec, "string");
	printVec(int_vec, "int");
	std::cout << "Pop_back" << std::endl;
	testMaxSize(int_vec, "int");
	int_vec.pop_back();
	int_vec.pop_back();
	printVec(int_vec, "int");

	std::cout << "Clear" << std::endl;
	testMaxSize(int_vec, "int");
	std::cout << *int_vec.end() << std::endl;
	int_vec.clear();
	printVec(int_vec, "int");
	std::cout << "begin()" << *int_vec.begin() << std::endl;
	std::cout << "end()" << *int_vec.end() << std::endl;

	testMaxSize(int_vec, "int");
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
	printSize(vct);
	printSize(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(vct);
	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_four);

	vct_four.assign(6, 84);
	printSize(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	printSize(vct);
	printSize(vct_two);
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

void checkErase(ft::vector<std::string> const &vct,
				   ft::vector<std::string>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

void testErase(void)
{
	ft::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	checkErase(vct, vct.erase(vct.begin()));
	checkErase(vct, vct.erase(vct.end() - 1));

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));
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
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);
}

void testInsert() {
	ft::vector<int> vct(10);
	ft::vector<int> vct2;
	ft::vector<int> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	printSize(vct2);

	vct2.insert(vct2.end() - 2, 42);
	printSize(vct2);

	vct2.insert(vct2.end(), 2, 84); //segfault
	printSize(vct2);

	vct2.resize(4);
	printSize(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	printSize(vct2);

	printSize(vct);

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
	printSize(vct3);
}

void testBidirect() {
	std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	ft::vector<int> vct(lst.begin(), lst.end());
	printSize(vct);

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	printSize(vct);

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	printSize(vct);
}

void prepost_incdec(ft::vector<int> &vct) {
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

	printSize(vct);
}

void testIteArrow() {
	const int size = 5;
	ft::vector<foo<int> > vct(size);
	ft::vector<foo<int> >::iterator it(vct.begin());
	ft::vector<foo<int> >::const_iterator ite(vct.end());

	for (int i = 1; it != ite; ++i)
		*it++ = i;
	printSize(vct);

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
	printSize(vct);

	std::cout << (it_ == it.base()) << std::endl; //1
	std::cout << (it_ == (it + 3).base()) << std::endl; //0

	std::cout << *(it.base() + 1) << std::endl; //10
	std::cout << *(it - 3) << std::endl;//15
	std::cout << *(it - 3).base() << std::endl;//20
	it -= 3;
	std::cout << *it.base() << std::endl;//20

	std::cout << "TEST OFFSET" << std::endl;
	std::cout << *(it) << std::endl;//15
	std::cout << *(it).base() << std::endl;//20
	std::cout << *(it - 0) << std::endl;//15
	std::cout << *(it - 0).base() << std::endl;//20
	std::cout << *(it - 1).base() << std::endl;//25

	std::cout << "OK" << std::endl;
}

void testRite2() {
	const int size = 5;
	ft::vector<int> vct(size);
	ft::vector<int>::reverse_iterator it = vct.rbegin();
	ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	std::cout << *it << std::endl;
	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *it << std::endl;
	std::cout << *(it += 2) << std::endl; // 5
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	printSize(vct);
	std::cout << *it << std::endl;
}

void testArrow() {
	const int size = 5;
	ft::vector<foo<int> > vct(size);
	ft::vector<foo<int> >::reverse_iterator it(vct.rbegin());
	ft::vector<foo<int> >::const_reverse_iterator ite(vct.rend());

	for (int i = 1; it != ite; ++i)
		*it++ = (i * 7);
	printSize(vct);

	it = vct.rbegin();
	ite = vct.rbegin();

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
