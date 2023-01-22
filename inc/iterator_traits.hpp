#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

//+---------------+-------------------------------------------------------------------------+
//|               |                      PROPERTIES                                         |
//|   ITERATOR    +------------+------+-------+----------------------+----------------------+
//|               | ACCESS     | READ | WRITE | ITERATE              | COMPARE              |
//+---------------+------------+------+-------+----------------------+----------------------+
//| Input         | ->         | =*i  |       | ++                   | ==, !=               |
//| Output        |            |      | *i=   | ++                   |                      |
//| Forward       | ->         | =*i  | *i=   | ++                   | ==, !=               |
//| Bidirectional |            | =*i  | *i=   | ++, --               | ==, !=               |
//| Random-Access | ->, []     | =*i  | *i=   | ++, --, +=, -=, +, - | ==, !=, <, >, <=, >= |
//+---------------+------------+------+-------+----------------------+----------------------+

namespace ft {

	//TAG_ITERATORS
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag: public input_iterator_tag { };
	struct bidirectional_iterator_tag: public forward_iterator_tag { };
	struct random_access_iterator_tag: public bidirectional_iterator_tag { };
	struct contiguous_iterator_tag: public random_access_iterator_tag { };

	//ITERATOR
	template<	class T,
				class Category,
				class Distance = ptrdiff_t,
				class Pointer = T*,
				class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Category	iterator_category;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	//ITERATOR_TRAITS
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	//ITERATOR_TRAITS<T*>
	template<class T>
	struct iterator_traits<T*>
	{
		typedef T							value_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//ITERATOR_TRAITS<const T *>
	template<class T>
	struct iterator_traits<const T*> {
		typedef T							value_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	template<class It>
	typename ft::iterator_traits<It>::difference_type
	distance(It first, It last)
	{
		typename ft::iterator_traits<It>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

}

#endif
