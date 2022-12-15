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
		RandomIt _randIt;

	public:
		reverse_iterator() : _randIt(NULL) {}
		~reverse_iterator() {}

		explicit reverse_iterator(const iterator_type& randIt) : _randIt(randIt) {}

		template <class Type>
		explicit reverse_iterator(const reverse_iterator<Type> &src) {
			(*this) = src;
		}

		reverse_iterator &operator=(const reverse_iterator &rhs) {
			if (&rhs != this)
				_randIt = rhs._randIt;
			return (*this);
		}

		operator reverse_iterator<ft::random_access_iterator<const value_type> >() const {
			return (reverse_iterator<ft::random_access_iterator<const value_type> >(this->base()));
		}

		iterator_type base() const {
			return _randIt;
		}

		reference operator*() const {
			RandomIt tmp = _randIt;
			return *(--tmp);
		}

		pointer operator->() const {
			return (_randIt);
		}

		reference operator[](difference_type diff) const {
			return (*(_randIt + diff));
		}

		reverse_iterator& operator++() {
			_randIt--;
			return (*_randIt);
		}

		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			(*this)--;
			return (*tmp);
		}
		reverse_iterator& operator--() {
			_randIt++;
			return (*_randIt);
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			(*this)++;
			return (*tmp);
		}
		reverse_iterator& operator+=(difference_type diff) {
			_randIt -= diff;
			return (*this);
		}
		const reverse_iterator operator+(difference_type diff) const {
			return (reverse_iterator(_randIt - diff));
		}
		reverse_iterator& operator-=(difference_type diff) {
			_randIt += diff;
			return (*this);
		}
		const reverse_iterator operator-(difference_type diff) const {
			return (reverse_iterator(_randIt + diff));
		}

		// Non member function overloads
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
		friend reverse_iterator<RandomIt> operator+(difference_type diff, const reverse_iterator<RandomIt> &rhs) {
			return (reverse_iterator(rhs._randIt - diff));
		}
		friend reverse_iterator<RandomIt> operator+(difference_type diff, reverse_iterator<RandomIt> &rhs) {
			return (reverse_iterator(rhs._randIt - diff));
		}
		friend difference_type operator-(const reverse_iterator<RandomIt> &lhs, const reverse_iterator<RandomIt> &rhs) {
			return (rhs._randIt - lhs._randIt);
		}
	};

// template code

//	template <class RandomAccessIterator,
//			  class T,
//			  class Reference,
//			  class Distance>
//	// Reference = T&
//	// Distance = ptrdiff_t
//
//	class reverse_iterator : public random_access_iterator<T, Distance> {
//		typedef reverse_iterator<RandomAccessIterator, T, Reference, Distance>
//				self;
//		friend bool operator==(const self& x, const self& y);
//		friend bool operator<(const self& x, const self& y);
//		friend Distance operator-(const self& x, const self& y);
//		friend self operator+(Distance n, const self& x);
//	protected:
//		RandomAccessIterator current;
//	public:
//		reverse_iterator() {}
//		reverse_iterator(RandomAccessIterator x) : current(x) {}
//		RandomAccessIterator base() { return current; }
//		Reference operator*() const { return *(current - 1); }
//		self& operator++() {
//			--current;
//			return *this;
//		}
//		self operator++(int) {
//			self tmp = *this;
//			--current;
//			return tmp;
//		}
//		self& operator--() {
//			++current;
//			return *this;
//		}
//		self operator--(int) {
//			self tmp = *this;
//			++current;
//			return tmp;
//		}
//		self operator+(Distance n) const {
//			return self(current - n);
//		}
//		self& operator+=(Distance n) {
//			current -= n;
//			return *this;
//		}
//		self operator-(Distance n) const {
//			return self(current + n);
//		}
//		self& operator-=(Distance n) {
//			current += n;
//			return *this;
//		}
//		Reference operator[](Distance n) { return *(*this + n); }
//	};
//
//	template <class RandomAccessIterator, class T, class Reference, class Distance>
//	inline bool operator==(const reverse_iterator<RandomAccessIterator, T,
//			Reference, Distance> &x,
//						   const reverse_iterator<RandomAccessIterator, T,
//								   Reference, Distance> &y) {
//		return x.current == y.current;
//	}
//
//	template <class RandomAccessIterator, class T, class Reference, class Distance>
//	inline bool operator<(const reverse_iterator<RandomAccessIterator, T,
//			Reference, Distance> &x,
//						  const reverse_iterator<RandomAccessIterator, T,
//								  Reference, Distance> &y) {
//		return y.current < x.current;
//	}
//
//	template <class RandomAccessIterator, class T, class Reference, class Distance>
//	inline Distance operator-(const reverse_iterator<RandomAccessIterator, T,
//			Reference, Distance> &x,
//							  const reverse_iterator<RandomAccessIterator, T,
//									  Reference, Distance> &y) {
//		return y.current - x.current;
//	}
//
//	template <class RandomAccessIterator, class T, class Reference, class Distance>
//	inline reverse_iterator<RandomAccessIterator, T, Reference, Distance>
//	operator+(Distance n,
//			  const reverse_iterator<RandomAccessIterator, T, Reference,
//					  Distance> &x) {
//		return reverse_iterator<RandomAccessIterator, T, Reference, Distance>
//				(x.current - n);
//	}
}

#endif
