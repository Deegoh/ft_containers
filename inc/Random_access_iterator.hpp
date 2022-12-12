#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"

namespace ft {
	template <class T,
			class Category = random_access_iterator_tag,
			class Distance = std::ptrdiff_t,
			class Pointer = T*,
			class Reference = T&>
	class Random_access_iterator : public iterator<T, Category> {
	public:

//		typedef typename iterator<T, Category>::value_type			value_type;
//		typedef typename iterator<T, Category>::difference_type		difference_type;
//		typedef typename iterator<T, Category>::pointer				pointer;
//		typedef typename iterator<T, Category>::reference			reference;
//		typedef typename iterator<T, Category>::iterator_category	iterator_category;

		typedef T			value_type;

		typedef Category	iterator_category;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

		Random_access_iterator() : _ptr(NULL) {}

		Random_access_iterator(Pointer ptr) : _ptr(ptr) {}

		~Random_access_iterator() {}

		Random_access_iterator(const Random_access_iterator &src) {
			(*this) = src;
		}

		const Random_access_iterator operator-(int index) const {
			return (_ptr - index);
		}

		Distance operator-(const Random_access_iterator &rhs) {
			return (std::distance(rhs._ptr, _ptr));
		}

		Random_access_iterator operator+(int index) {
			return (_ptr + index);
		}

		Distance operator+(const Random_access_iterator &rhs) {
			return (std::distance(_ptr, rhs._ptr));
		}

		Random_access_iterator &operator=(const Random_access_iterator &rhs) {
			if (&rhs != this)
			{
				_ptr = rhs._ptr;
			}
			return (*this);
		}
		Random_access_iterator &operator++() {
			_ptr++;
			return (*this);
		}
		Random_access_iterator operator++(int) {
			Random_access_iterator it = *this;
			++(*this);
			return (it);
		}
		Random_access_iterator &operator--() {
			_ptr--;
			return (*this);
		}
		Random_access_iterator operator--(int) {
			Random_access_iterator it = *this;
			--(*this);
			return (it);
		}
		Reference operator[](size_t index) {
			return (*(_ptr + index));
		}

		Reference operator*() const {
			return (*_ptr);
		}

		Pointer operator->() {
			return (_ptr);
		}
		bool operator==(const Random_access_iterator &rhs) const {
			return (_ptr == rhs._ptr);
		}
		bool operator!=(const Random_access_iterator &rhs) const {
			return !(*this == rhs);
		}
//		Random_access_iterator &operator=(const Random_access_iterator &rhs) {
//			if (&rhs != this)
//			{
//				_ptr = rhs._ptr;
//			}
//			return (*this);
//		}
	private:
		Pointer _ptr;
	};
}

#endif
