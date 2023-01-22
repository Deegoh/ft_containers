#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {

	template <class T,
			  class Category = random_access_iterator_tag,
			  class Distance = std::ptrdiff_t,
			  class Pointer = T*,
			  class Reference = T&>
	class random_access_iterator : public iterator_traits<iterator<T, Category> > {
	protected:
		Pointer _ptr;

	public:
		typedef T			value_type;
		typedef Category	iterator_category;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

		//CONSTRUCTOR
		random_access_iterator() : _ptr(NULL) {}

		random_access_iterator(Pointer ptr) : _ptr(ptr) {}

		~random_access_iterator() {}

		random_access_iterator(const random_access_iterator &src) {
			(*this) = src;
		}

		random_access_iterator &operator=(const random_access_iterator &rhs) {
			if (&rhs != this)
			{
				_ptr = rhs._ptr;
			}
			return (*this);
		}

		//ACCESS
		Pointer operator->() {
			return (_ptr);
		}
		Reference operator*() const {
			return (*_ptr);
		}

		Reference operator[](size_t index) {
			return (*(_ptr + index));
		}

		//READ

		//WRITE

		//lifehack normal to const
		operator random_access_iterator<const T>() const {
			return (random_access_iterator<const T>(this->_ptr));
		}

		//ITERATE
		const random_access_iterator operator-(size_t index) const {
			return (_ptr - index);
		}

		friend difference_type operator-(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr - rhs._ptr);
		}

		const random_access_iterator operator+(size_t index) const {
			return (_ptr + index);
		}

		friend difference_type operator+(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr + rhs._ptr);
		}

//		friend difference_type operator+(random_access_iterator &lhs, random_access_iterator &rhs) {
//			return (lhs._ptr + rhs._ptr);
//		}

		friend random_access_iterator operator+(size_t lhs, random_access_iterator rhs) {
			return (rhs + lhs);
		}
//		Distance operator+(const random_access_iterator &rhs) {
//			return (_ptr + rhs._ptr);
//		}

		random_access_iterator &operator++() {
			_ptr++;
			return (*this);
		}
		random_access_iterator operator++(int) {
			random_access_iterator tmp = *this;
			++(*this);
			return (tmp);
		}
		random_access_iterator &operator--() {
			_ptr--;
			return (*this);
		}

//		const random_access_iterator operator--(int) {
//			const random_access_iterator tmp = *this;
//			--(*this);
//			return (tmp);
//		}
		random_access_iterator operator--(int) {
			random_access_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		random_access_iterator &operator+=(difference_type diff) {
			_ptr = _ptr + diff;
			return (*this);
		}

		random_access_iterator &operator-=(difference_type diff) {
			_ptr = _ptr - diff;
			return (*this);
		}

		// COMPARE

		friend bool operator<(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr < rhs._ptr);
		}

		friend bool operator>(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr > rhs._ptr);
		}

		friend bool operator<=(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr <= rhs._ptr);
		}

		friend bool operator>=(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr >= rhs._ptr);
		}

		friend bool operator==(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr == rhs._ptr);
		}

		friend bool operator!=(const random_access_iterator &lhs, const random_access_iterator &rhs) {
			return (lhs._ptr != rhs._ptr);
		}

	};
}

#endif
