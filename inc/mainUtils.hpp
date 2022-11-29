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
void printVec(T &vec, std::string str) {
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
//	for (ft::vector<int>::iterator it = c.begin(); it != c.end();)
//	{
//	if (*it % 2 == 0)
//	it = c.erase(it);
//	else
//	++it;
//	}
//	printVec(c, "erase");
//	std::cout << "resul[1, 7, 9]" << std::endl;
//	1 7 9
}

#endif


