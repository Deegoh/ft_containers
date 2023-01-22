#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {

	template <class T,
			class Category = bidirectional_iterator_tag,
			class Distance = std::ptrdiff_t,
			class Pointer = T*,
			class Reference = T&>
	class bidirectional_iterator : public iterator_traits<iterator<T, Category> > {

	public:
		typedef T			value_type;
		typedef Category	iterator_category;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;

	protected:
		pointer _root;
		pointer _current;
		pointer _nil;

	public:
		//CONSTRUCTOR
		bidirectional_iterator() : _root(NULL), _current(NULL), _nil(NULL) {}

		bidirectional_iterator(pointer root, pointer current, pointer nil) :
		_root(root), _current(current), _nil(nil) {}

		bidirectional_iterator(const bidirectional_iterator& src) {
			*this = src;
		}

		bidirectional_iterator& operator=(const bidirectional_iterator& rhs) {
			if (this != &rhs) {
				_root = rhs._root;
				_current = rhs._current;
				_nil = rhs._nil;
			}
			return (*this);
		}

		~bidirectional_iterator() {}

	public:


		//ACCESS
		operator bidirectional_iterator<const T>() const {
			return (bidirectional_iterator<const T>(_root, _current, _nil));
		}

		bool operator==(const bidirectional_iterator &rhs) const {
			return (_current == rhs._current);
		}
		bool operator!=(const bidirectional_iterator &rhs) const {
			return (_current != rhs._current);
		}

		reference operator*() const {
			if (_current == NULL)
				throw std::exception();
			return (_current->value);
		}

		reference operator*() {
			if (_current == NULL)
				throw std::exception();
			return (_current->value);
		}

		pointer operator->() {
			return (&_current->value);
		}
		pointer operator->() const {
			return (&_current->value);
		}

		//READ

		//WRITE

		//lifehack normal to const
		operator bidirectional_iterator<const T>() const {
			return (bidirectional_iterator<const T>(this->_ptr));
		}

		//ITERATE


		// COMPARE

		friend bool operator==(const bidirectional_iterator &lhs, const bidirectional_iterator &rhs) {
			return (lhs._ptr == rhs._ptr);
		}

		friend bool operator!=(const bidirectional_iterator &lhs, const bidirectional_iterator &rhs) {
			return (lhs._ptr != rhs._ptr);
		}

	};
}

#endif
