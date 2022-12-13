#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft {

	template <class T,
			  class Category = random_access_iterator_tag,
			  class Distance = std::ptrdiff_t,
			  class Pointer = T*,
			  class Reference = T&>
	class reverse_iterator : public iterator<T, Category> {
	protected:
		Pointer _ptr;

	public:
		typedef T			value_type;
		typedef Category	iterator_category;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;


		reverse_iterator() : _ptr(NULL) {}
		reverse_iterator(Pointer ptr) : _ptr(ptr) {}
		~reverse_iterator() {}
		reverse_iterator(const reverse_iterator &src) {
			(*this) = src;
		}
		reverse_iterator &operator=(const reverse_iterator &rhs) {
			if (&rhs != this)
				_ptr = rhs._ptr;
			return (*this);
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
//			Reference, Distance>& x,
//						   const reverse_iterator<RandomAccessIterator, T,
//								   Reference, Distance>& y) {
//		return x.current == y.current;
//	}
//
//	template <class RandomAccessIterator, class T, class Reference, class Distance>
//	inline bool operator<(const reverse_iterator<RandomAccessIterator, T,
//			Reference, Distance>& x,
//						  const reverse_iterator<RandomAccessIterator, T,
//								  Reference, Distance>& y) {
//		return y.current < x.current;
//	}
//
//	template <class RandomAccessIterator, class T, class Reference, class Distance>
//	inline Distance operator-(const reverse_iterator<RandomAccessIterator, T,
//			Reference, Distance>& x,
//							  const reverse_iterator<RandomAccessIterator, T,
//									  Reference, Distance>& y) {
//		return y.current - x.current;
//	}
//
//	template <class RandomAccessIterator, class T, class Reference, class Distance>
//	inline reverse_iterator<RandomAccessIterator, T, Reference, Distance>
//	operator+(Distance n,
//			  const reverse_iterator<RandomAccessIterator, T, Reference,
//					  Distance>& x) {
//		return reverse_iterator<RandomAccessIterator, T, Reference, Distance>
//				(x.current - n);
//	}
}

#endif
