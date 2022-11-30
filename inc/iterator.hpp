#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft {

//	struct false_type {
//		const static bool value = false;
//		operator bool() const { return value; }
//		// There is more here, but it doesn't really matter for your question
//	};
//
//	struct true_type {
//		const static bool value = true;
//		operator bool() const { return value; }
//		// There is more here, but it doesn't really matter for your question
//	};
//
//	template<class T, T v>
//	struct integral_constant {
//		static T value = v;
//		typedef T					value_type;
//		typedef integral_constant	type; // using injected-class-name
//		operator value_type() const { return value; }
//		value_type operator()() const { return value; } // since c++14
//	};
//
//	template< class T >
//	struct is_integral
//	{
//		static const bool value /* = true if T is integral, false otherwise */;
//		typedef ft::integral_constant<bool, value> type;
//	};

//	template<typename>
//	struct is_integral
//			: public false_type { };
//
//	template<>
//	struct __is_integral_helper<bool>
//			: public true_type { };
//
//	template<>
//	struct __is_integral_helper<char>
//			: public true_type { };
//
//	template<>
//	struct __is_integral_helper<signed char>
//			: public true_type { };
//
//	template<>
//	struct __is_integral_helper<unsigned char>
//			: public true_type { };

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
