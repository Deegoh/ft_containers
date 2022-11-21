#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
//# include <iterator>

namespace ft {
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
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	//ITERATOR_TRAITS<T*>
	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	//TAG_ITERATORS
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag: public input_iterator_tag { };
	struct bidirectional_iterator_tag: public forward_iterator_tag { };
	struct random_access_iterator_tag: public bidirectional_iterator_tag { };
	struct contiguous_iterator_tag: public random_access_iterator_tag { };
}

#endif
