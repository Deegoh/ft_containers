#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "random_access_iterator.hpp"
#include "iterator.hpp"

namespace ft {

	template <class RandomIt>
	class reverse_iterator {
	public:
		typedef RandomIt									iterator_type;
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::pointer				pointer;
		typedef typename iterator_type::reference			reference;
		typedef typename iterator_type::iterator_category	iterator_category;

	protected:
		iterator_type _randIt;

	public:
//		Default constructor
		reverse_iterator() : _randIt() {}
//		Constructor by random iterator
		explicit reverse_iterator(const iterator_type& randIt) : _randIt(randIt) {}
//		Copy constructor
		template <class Type>
		explicit reverse_iterator(const reverse_iterator<Type> &src) {
			_randIt = src.base();
		}
//		assigns another iterator adaptor
		reverse_iterator &operator=(const reverse_iterator &rhs) {
			if (&rhs != this)
				_randIt = rhs._randIt;
			return (*this);
		}
//		Destructor
		~reverse_iterator() {}

//		hack
		operator reverse_iterator<ft::random_access_iterator<const value_type> >() const {
			return (reverse_iterator<ft::random_access_iterator<const value_type> >(this->base()));
		}

//		accesses the underlying iterator
		iterator_type base() const {
			return _randIt;
		}

//		accesses the pointed-to element
		reference operator*() const {
			iterator_type tmp = _randIt;
			return (*(--tmp));
		}
//		accesses the pointed-to element
		pointer operator->() const {
			return &(operator*());
		}
//		accesses an element by index
		reference operator[](difference_type diff) const {
			return (*(_randIt - diff - 1));
		}

//		Pre-increments or pre-decrements by one respectively.
		reverse_iterator& operator++() {
			_randIt--;
			return (*this);
		}
//		Post-increments or post-decrements by one respectively.
		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			_randIt--;
			return (tmp);
		}
//		Pre-increments or pre-decrements by one respectively.
		reverse_iterator& operator--() {
			_randIt++;
			return (*this);
		}
//		Post-increments or post-decrements by one respectively.
		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			_randIt++;
			return (tmp);
		}
//		Returns an iterator which is advanced by n or -n positions respectively.
		reverse_iterator operator+(difference_type diff) const {
			return (reverse_iterator(_randIt - diff));
		}
//		Advances the iterator by n or -n positions respectively.
		reverse_iterator& operator+=(difference_type diff) {
			_randIt = _randIt - diff;
			return (*this);
		}
//		Returns an iterator which is advanced by n or -n positions respectively.
		const reverse_iterator operator-(difference_type diff) const {
			return (reverse_iterator(_randIt + diff));
		}
//		Advances the iterator by n or -n positions respectively.
		reverse_iterator& operator-=(difference_type diff) {
			_randIt = _randIt + diff;
			return (*this);
		}

	// Non member function overloads https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator_cmp
	public:
//		iterator adaptors to compare
		friend bool operator==(const reverse_iterator<RandomIt> &lhs, const reverse_iterator<RandomIt> &rhs) {
			return (lhs.base() == rhs.base());
		}
		friend bool operator!=(const reverse_iterator<RandomIt> &lhs, const reverse_iterator<RandomIt> &rhs) {
			return !(lhs.base() == rhs.base());
		}
		friend bool operator<(const reverse_iterator<RandomIt> &lhs, const reverse_iterator<RandomIt> &rhs) {
			return (rhs.base() < lhs.base());
		}
		friend bool operator<=(const reverse_iterator<RandomIt> &lhs, const reverse_iterator<RandomIt> &rhs) {
			return !(rhs < lhs);
		}
		friend bool operator>(const reverse_iterator<RandomIt> &lhs, const reverse_iterator<RandomIt> &rhs) {
			return (rhs < lhs);
		}
		friend bool operator>=(const reverse_iterator<RandomIt> &lhs, const reverse_iterator<RandomIt> &rhs) {
			return !(lhs < rhs);
		}

//		Returns the distance between two iterator adaptors.
		friend difference_type operator-(const reverse_iterator<RandomIt> &lhs, const reverse_iterator<RandomIt> &rhs) {
			return (rhs.base() - lhs.base());
		}
//		Returns the iterator it incremented by n.
		friend reverse_iterator<RandomIt> operator+(difference_type diff, const reverse_iterator<RandomIt> &rhs) {
			return (reverse_iterator(rhs.base() - diff));
		}
	};

}

#endif
