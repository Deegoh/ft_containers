#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

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

//	template<typename T> struct is_integral: is_integral_base<std::remove_cv_t<T> > {};

	//TAG_ITERATORS
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag: public input_iterator_tag { };
	struct bidirectional_iterator_tag: public forward_iterator_tag { };
	struct random_access_iterator_tag: public bidirectional_iterator_tag { };
	struct contiguous_iterator_tag: public random_access_iterator_tag { };

	//ITERATOR
	template<	class Category,
				class T,
				class Distance = ptrdiff_t,
				class Pointer = T*,
				class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	//ITERATOR_TRAITS
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	//ITERATOR_TRAITS<T*>
	template<class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//ITERATOR_TRAITS<const T *>
	template<class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

}

#endif
