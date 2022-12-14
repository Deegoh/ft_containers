#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "random_access_iterator.hpp"
#include "iterator.hpp"

namespace ft {

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

	template <class T, class Category = random_access_iterator_tag>
	class reverse_iterator : public random_access_iterator<T, Category> {
	public:
		typedef random_access_iterator<T, Category>						iterator_type;
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::pointer				pointer;
		typedef typename iterator_type::reference			reference;
		typedef typename iterator_type::iterator_category	iterator_category;

	protected:
		pointer _ptr;

	public:
		reverse_iterator() : _ptr(NULL) {}
		reverse_iterator(pointer ptr) : _ptr(ptr) {}
		reverse_iterator(iterator_type ptr) : _ptr(reverse_iterator(ptr)) {}
		~reverse_iterator() {}
		reverse_iterator(const reverse_iterator &src) {
			(*this) = src;
		}
		reverse_iterator &operator=(const reverse_iterator &rhs) {
			if (&rhs != this)
				_ptr = rhs._ptr;
			return (*this);
		}

		operator reverse_iterator<const T>() const {
			return (reverse_iterator<const T>(this->_ptr));
		}

		reference operator*() const {
			return (*_ptr);
		}
		pointer operator->() const {
			return (_ptr);
		}

		reference operator[](difference_type diff) const {
			return (*(_ptr + diff));
		}

		reverse_iterator& operator++() {
			_ptr--;
			return (*_ptr);
		}

		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			(*this)--;
			return (*tmp);
		}
		reverse_iterator& operator--() {
			_ptr++;
			return (*_ptr);
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			(*this)++;
			return (*tmp);
		}
		reverse_iterator& operator+=(difference_type diff) {
			_ptr -= diff;
			return (*this);
		}
		reverse_iterator operator+(difference_type diff) const
		{
			return (_ptr - diff);
		}
		reverse_iterator& operator-=(difference_type diff) {
			_ptr += diff;
			return (*this);
		}
		reverse_iterator operator-(difference_type diff) const {
			return (_ptr - diff);
		}
	};

//	https://www.ibm.com/docs/en/zos/2.2.0?topic=ri-synopsis
//	template<class RanIt>
//	class reverse_iterator : public iterator<
//			typename iterator_traits<RanIt>::iterator_category,
//			typename iterator_traits<RanIt>::value_type,
//			typename iterator_traits<RanIt>::difference_type,
//			typename iterator_traits<RanIt>::pointer,
//			typename iterator_traits<RanIt>::reference> {
//		typedef typename iterator_traits<RanIt>::difference_type
//				Dist;
//		typedef typename iterator_traits<RanIt>::pointer
//				Ptr;
//		typedef typename iterator_traits<RanIt>::reference
//				Ref;
//	public:
//		typedef RanIt iterator_type;
//		reverse_iterator();
//		explicit reverse_iterator(RanIt x);
//		template<class U>
//		reverse_iterator(const reverse_iterator<U>& x);
//		RanIt base() const;
//		Ref operator*() const;
//		Ptr operator->() const;
//		reverse_iterator& operator++();
//		reverse_iterator operator++(int);
//		reverse_iterator& operator--();
//		reverse_iterator operator--();
//		reverse_iterator& operator+=(Dist n);
//		reverse_iterator operator+(Dist n) const;
//		reverse_iterator& operator-=(Dist n);
//		reverse_iterator operator-(Dist n) const;
//		Ref operator[](Dist n) const;
//	protected:
//		RanIt current;
//	};

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
