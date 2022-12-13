#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {

	//	IS_INTEGRAL
	struct false_type {
		const static bool value = false;
		operator bool() const {return value;}
	};

	struct true_type {
		const static bool value = true;
		operator bool() const {return value;}
	};

	template<typename> struct is_integral: ft::false_type {};

	template<> struct is_integral<short> : ft::true_type {};
	template<> struct is_integral<bool> : ft::true_type {};
	template<> struct is_integral<char> : ft::true_type {};
	template<> struct is_integral<wchar_t> : ft::true_type {};
	template<> struct is_integral<signed char> : ft::true_type {};
	template<> struct is_integral<int> : ft::true_type {};
	template<> struct is_integral<long int> : ft::true_type {};
	template<> struct is_integral<unsigned char> : ft::true_type {};
	template<> struct is_integral<unsigned short int> : ft::true_type {};
	template<> struct is_integral<unsigned int> : ft::true_type {};
	template<> struct is_integral<unsigned long int> : ft::true_type {};

	//lexicographical_compare
	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}

		return (first1 == last1) && (first2 != last2);
	}

	//equal
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1,
			   InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) {
				return false;
			}
		}
		return true;
	}

	//enable_if<bool, T>
	template<bool B, class T = void>
	struct enable_if {};

	//enable_if<T>
	template<class T>
	struct enable_if<true, T> { typedef T type; };

}

#endif
