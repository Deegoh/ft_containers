#ifndef MAIN_UTILS_HPP
# define MAIN_UTILS_HPP
#include <typeinfo>

template <class Tp>
struct NAlloc : public std::allocator<Tp>{
	typedef Tp					value_type;
	NAlloc() {};
	template <class T> NAlloc(const NAlloc<T>&) {}

	Tp* allocate(std::size_t n)
	{
		n *= sizeof(Tp);
		Tp* p = static_cast<Tp*>(::operator new(n));
//		std::cout << "allocating " << n << " bytes @ " << p << '\n';
		std::cout << "allocating " << n << " bytes" << std::endl;
		return p;
	}

	void construct(Tp* p, const Tp& val)
	{
		*p = val;
	}

	void destroy(Tp* p)
	{
		std::cout << "destroy " << sizeof(p) << " bytes" << "\n";
		if (std::string("NSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE").compare(typeid(*p).name()) == 0)
		{
			//*p = "";
		}
	}

	void deallocate(Tp* p, std::size_t n)
	{
//		std::cout << "deallocating " << n*sizeof*p << " bytes @ " << p << "\n\n";
		std::cout << "deallocating " << n*sizeof*p << " bytes" << std::endl;
		::operator delete(p);
	}
};
template <class T, class U>
bool operator==(const NAlloc<T>&, const NAlloc<U>&) { return true; }
template <class T, class U>
bool operator!=(const NAlloc<T>&, const NAlloc<U>&) { return false; }

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
	std::cout << "capacity: " << ((vec.size() <= vec.capacity()) ? "OK" : "KO") << std::endl;
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
	ft::vector<int> vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	vct2.assign(vct.begin(), vct.end());
	printVec(vct, "vct");
//	printVec(vct2, "vct2");
	vct.assign(2, 42);
	vct.assign(10, 42);
	printVec(vct, "vct");
	testMaxSize(vct, "");
}

void testResize() {
	const int start_size = 7;

	ft::vector<int> vct(start_size, 20);
	ft::vector<int> vct2;
	ft::vector<int>::iterator it = vct.begin();

	for (int i = 2; i < 7; ++i)
		it[i] = (7 - i) * 3;

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

//template <typename T>
void testErase() {
	ft::vector<int> c;
	c.push_back(0);
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	c.push_back(4);
	c.push_back(5);
	c.push_back(6);
	c.push_back(7);
	c.push_back(8);
	c.push_back(9);

	printVec(c, "erase1");
	std::cout << "resul1[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]" << std::endl;
//	0 1 2 3 4 5 6 7 8 9

	c.erase(c.begin());
	printVec(c, "erase2");
	std::cout << "resul2[1, 2, 3, 4, 5, 6, 7, 8, 9]" << std::endl;
//	1 2 3 4 5 6 7 8 9

	c.erase(c.begin() + 2, c.begin() + 5);
	printVec(c, "erase3");
	std::cout << "resul3[1, 2, 6, 7, 8, 9]" << std::endl;
//	1 2 6 7 8 9

//	// Erase all even numbers
	for (ft::vector<int>::iterator it = c.begin(); it != c.end();)
	{
	if (*it % 2 == 0)
	it = c.erase(it);
	else
	++it;
	}
	printVec(c, "erase");
	std::cout << "resul[1, 7, 9]" << std::endl;
//	1 7 9
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
	printTest(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printTest(vct);
	printTest(vct_range);
	printTest(vct_copy);
}

void insertTest() {
	ft::vector<int> c1(3, 100);
	printVec(c1, "1");

	ft::vector<int>::iterator it = c1.begin();
	it = c1.insert(it, 200);
	printVec(c1, "2");
//	c1.insert(it, 2, 300);
	printVec(c1, "3");
//	TODO finish test (https://en.cppreference.com/w/cpp/container/vector/insert)
}

#endif


