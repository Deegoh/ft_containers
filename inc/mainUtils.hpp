#ifndef MAIN_UTILS_HPP
# define MAIN_UTILS_HPP

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
void testMaxSize(T &vec) {
	std::cout << "size: " << vec.size() << "\n";
	std::cout << "capacity: " << vec.capacity() << "\n";
	std::cout << "max_size: " << vec.max_size() << "\n";
}

#endif


