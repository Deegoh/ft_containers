#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <cstddef>


//# include "iterator.hpp"
# include "Random_access_iterator.hpp"
//# include "utils.hpp"

//test
//# include "iterator94.hpp"
//# include <vector>
//endTest

namespace ft {
	template <typename T, class Allocator = std::allocator<T> >
	class vector {
	public:
		// types
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef Random_access_iterator<value_type>			iterator;
		typedef Random_access_iterator<const value_type>	const_iterator;
//		typedef ft::reverse_iterator<iterator>				reverse_iterator;
//		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	protected:
		allocator_type _alloc;
		value_type *_c;
		size_type _size;
		size_type _capacity;

	public:
		void reAlloc(size_type newCapacity) {
			if (newCapacity == 0)
				newCapacity = 1;
			T* newBlock = _alloc.allocate(newCapacity);
			if (newCapacity < _size)
				_size = newCapacity;
			for (size_type i = 0; i < _size; ++i) {
				newBlock[i] = _c[i];
			}
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_c + i);
			}
			if (_c)
				_alloc.deallocate(_c, _capacity);
			_c = newBlock;
			_capacity = newCapacity;
		}

//		Constructor
		vector() : _alloc() {
			_capacity = 0;
			_size = 0;
			_c = NULL;
		};

		vector(size_type n, const T& value = T()) : _alloc() {
			_c = _alloc.allocate(n);
			std::uninitialized_fill_n(_c, n, value);
			_size = n;
			_capacity = n;
		}

		vector(const vector& src) {(*this) = src;};

		~vector() {
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_c + i);
			}
			if (_c)
				_alloc.deallocate(_c, _capacity);
		};

		vector& operator=(const vector& rhs) {
			if (&rhs != this)
			{
				_size = rhs._size;
				_alloc = rhs._alloc;
				_capacity = rhs._capacity;
				_c = rhs._c;
			}
			return (*this);
		};

//		iterator overload

		T& operator[](size_type index) {
			if (index >= _size)
			{
				// throw error ?
				return (_c[0]);
			}
			return (_c[index]);
		};
		const T& operator[](size_type index) const {
			if (index >= _size)
			{
				// throw error ?
				return (_c[0]);
			}
			return (_c[index]);
		};

//		Iterators
//		returns an iterator to the beginning
		iterator begin() {return iterator(_c);}
//		returns an iterator to the beginning
		const_iterator begin() const {return const_iterator(_c);}
//		returns an iterator to the end
		iterator end() {return iterator(_c + _size);}
//		returns an iterator to the end
		const_iterator end() const {return const_iterator(_c + _size);}

//		Capacity
//		checks whether the container is empty (public member function)
		bool empty() const {
			return (begin() == end());
		}

//		Return size (public member function)
//		std::distance(begin(), end())
		size_type size() const {
//			std::distance(begin(), end());
			return (_size);
		}

//		returns the maximum possible number of elements (public member function)
		size_type max_size() const {return _alloc.max_size();}

//		reserves storage (public member function)
		void reserve(size_type n) {
			if (n == 0)
				n = 1;
			if (_capacity < n) {
				value_type *tmp = _alloc.allocate(n);
				std::uninitialized_copy(this->begin(), this->end(), tmp);
				for (size_type i = 0; i < _size; ++i) {
					_alloc.destroy(_c + i);
				}
				_alloc.deallocate(_c, _capacity);
				_c = tmp;
				_capacity = n;
			}
		}

//		returns the number of elements that can be held in currently allocated storage (public member function)
		size_type capacity() const {return (_capacity);}

//		Modifiers
//		Clear content (public member function)
		void clear() {
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_c + i);
			}
			_size = 0;
		}
		//TODO insert
//		inserts elements (single element)
//		iterator insert (iterator position, const_iterator first, const_iterator last);
//		inserts elements (fill)
//		void insert (iterator position, size_type n, const value_type& x);
//		inserts elements (range)
//		template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator last);
		//TODO erase
//		erases elements
		iterator erase(iterator position)
		{
			if (position + 1 != end())
				std::copy(position + 1, end(), position);
			_size--;
			_alloc.destroy(_c + _size);
			return (iterator(_c + _size));
		}
//		iterator erase( const_iterator pos );
//		erases elements
		iterator erase(iterator first, iterator last)
		{
			iterator it = std::copy(last, end(), first);
			for (; it != end() ; it++) {
				_alloc.destroy(_c + (it - begin()));
			}
			_size = _size - (last - first);
			return (iterator(_c + _size));
		}
//		iterator erase( const_iterator first, const_iterator last );

//		Add element at the end (public member function)
		void push_back(const value_type& value) {
			if (_size >= _capacity) {
				reserve(_capacity * 2);
			}
			_alloc.construct(_c + _size, value);
			_size++;
		}
//		removes the last element (public member function)
		void pop_back() {
			if (_size > 0)
			{
				_size--;
				_alloc.destroy(_c + _size);
			}
		}
//		Change size (public member function)
		void resize(size_type count, T value = T()) {
			if (count > _size)
			{
				if (_capacity < count)
					reserve(_capacity * 2);
				std::uninitialized_fill_n(_c + _size, count - _size, value);
				_size = count;
			}
			else if (count < _size)
			{
				erase(_c + count, end());
				_size = count;
			}
		}
		//TODO swap
//		swaps the contents
//		void swap(vector& other);
	};
}

#endif
