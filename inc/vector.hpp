#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <cstddef>
# include <stdexcept>


# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "random_access_iterator.hpp"
# include "comparators.hpp"

namespace ft {
	template <typename T, class Allocator = std::allocator<T> >
	class vector {
	public:
		// types
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef ft::random_access_iterator<value_type>			iterator;
		typedef ft::random_access_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	protected:
		allocator_type _alloc;
		value_type *_c;
		size_type _size;
		size_type _capacity;

		//		Destroy and deallocate
		void cleanPointer() {
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_c + i);
			}
			_alloc.deallocate(_c, _capacity);
		}

	public:

//		Constructor

//		default
		explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
			_capacity = 0;
			_size = 0;
			_c = NULL;
		}

//		fill
		explicit vector(size_type n, const value_type& value = value_type(),
						const allocator_type& alloc = allocator_type()) : _alloc(alloc) {
			_c = _alloc.allocate(n);
			std::uninitialized_fill_n(_c, n, value);
			_size = n;
			_capacity = n;
		}

//		range
		template<class InputIt>
		vector(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
			   InputIt last, const allocator_type& alloc = allocator_type() ) : _alloc (alloc) {
			size_type n = ft::distance(first, last);
			if (n < 0)
			{
				_size = 0;
				_capacity = 0;
				_c = NULL;
				return;
			}
			_c = _alloc.allocate(n);
			std::uninitialized_copy(first, last, _c);
			_size = n;
			_capacity = n;
		}

//		copy
		vector(const vector& src) : _alloc() {
			_capacity = 0;
			_size = 0;
			_c = NULL;
			(*this) = src;
		};

//		destructor
		~vector() {
			if (_c)
				cleanPointer();
		};

//		operator=
		vector& operator=(const vector& rhs) {
			if (&rhs == this)
				return (*this);
			if (rhs.size() > this->capacity()) {
				cleanPointer();
				_capacity = rhs._capacity;
				this->_c = _alloc.allocate(_capacity);
				std::uninitialized_copy(rhs.begin(), rhs.end(), _c);
			} else/*if (this->size() >= rhs.size())*/ {
				std::uninitialized_copy(rhs.begin(), rhs.end(), _c);
				for (size_type i = rhs.size() - 1; i < this->size(); ++i) {
					_alloc.destroy(_c + i);
				}
			}
			_size = rhs._size;
			return (*this);
		};

//		assigns values to the container
		void assign(size_type count, const value_type & value) {
			if (count > capacity())
				reserve(count);
			std::uninitialized_fill_n(_c , count, value);
			_size = count;
		}

//		assigns values to the container
		template<class InputIt>
		void assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last) {
			size_type diff = ft::distance(first, last);
			if (diff > capacity())
				reserve(diff);
			for (size_type i = 0; first != last ; first++, i++) {
				_c[i] = *first;
			}
			_size = diff;
		}

//		returns the associated allocator
		allocator_type get_allocator() const {
			return (_alloc);
		}

//		Element access

//		access specified element with bounds checking
		reference at(size_type pos) {
			if (pos >= size())
				throw std::out_of_range("out_of_range exception");
			return (*(_c + pos));
		}
		const_reference at(size_type pos) const {
			if (pos >= size())
				throw std::out_of_range("out_of_range exception");
			return (*(_c + pos));
		}

//		access specified element
		T& operator[](size_type index) {
			return (_c[index]);
		};
		const T& operator[](size_type index) const {
			return (_c[index]);
		};

//		access the first element
		reference front() {
			return (*_c);
		}
		const_reference front() const {
			return (*_c);
		}

//		access the last element
		reference back() {
			return (*(_c + size() - 1));
		}
		const_reference back() const {
			return (*(_c + size() - 1));
		}

//		Iterators
//		returns an iterator to the beginning
		iterator begin() {return iterator(_c);}
//		returns an const iterator to the beginning
		const_iterator begin() const {return const_iterator(_c);}
//		returns an iterator to the end
		iterator end() {return iterator(_c + _size);}
//		returns an const iterator to the end
		const_iterator end() const {return const_iterator(_c + _size);}

//		returns a reverse iterator to the beginning
		reverse_iterator rbegin() {return reverse_iterator(_c + _size);}
//		returns a reverse iterator to the beginning
		const_reverse_iterator rbegin() const {return const_reverse_iterator(_c + _size);}
//		returns a reverse iterator to the end
		reverse_iterator rend() {return reverse_iterator(_c);}
//		returns a reverse iterator to the end
		const_reverse_iterator rend() const {return const_reverse_iterator(_c);}

//		Capacity
//		checks whether the container is empty (public member function)
		bool empty() const {
			return (_size == 0);
		}

//		Return size (public member function)
		size_type size() const {
			return (ft::distance(begin(), end()));
		}

//		returns the maximum possible number of elements (public member function)
		size_type max_size() const {return _alloc.max_size();}

//		reserves storage (public member function)
		void reserve(size_type n) {
			if (n > max_size())
				throw std::length_error("Size error");
			if (n == 0)
				n = 1;
			if (_capacity < n) {
				value_type *tmp = _alloc.allocate(n);
				std::uninitialized_copy(this->begin(), this->end(), tmp);
				cleanPointer();
				_capacity = n;
				_c = tmp;
			}
			else // should i do ?
			{
				reserve(_capacity * 2);
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

//		inserts elements (single element)
		iterator insert(iterator pos, const value_type& val) {
			size_type diff = ft::distance(begin(), pos);

			size_type newCapacity;
			size_type n = 1;

			newCapacity = _capacity;
			if (_size + n > _capacity * 2 || _capacity == 0)
				newCapacity = _size + n;
			else if (_size + n > _capacity)
				newCapacity = _capacity * 2;

			if (_capacity < newCapacity)
			{
				value_type *tmp = _alloc.allocate(newCapacity);
				std::uninitialized_copy(begin(), pos, tmp);
				*(tmp + diff) = val;
				std::uninitialized_copy(begin() + diff, end(), tmp + diff + 1);
				cleanPointer();
				_c = tmp;
			}
			else
			{
				for (iterator ite = end(); ite != pos ; ite--) {
					*ite = *(ite - 1);
				}
				*(_c + diff) = val;
			}

			_size++;
			_capacity = newCapacity;
			return (iterator(_c + diff));
		}

//		inserts elements (fill)
		void insert(iterator pos, size_type n, const value_type& val) {
			if (n == 0)
				return;

			size_type diff = ft::distance(begin(), pos);
			size_type newCapacity;

			newCapacity = _capacity;
			if (_size + n > _capacity * 2 || _capacity == 0)
				newCapacity = _size + n;
			else if (_size + n > _capacity)
				newCapacity = _capacity * 2;

			if (_capacity < newCapacity)
			{
				value_type *tmp = _alloc.allocate(newCapacity);
				std::uninitialized_copy(begin(), pos, tmp);
				std::uninitialized_fill_n(tmp + diff, n,val);
				std::uninitialized_copy(pos, end(), tmp + diff + n);
				cleanPointer();
				_c = tmp;
			}
			else
			{
				std::copy_backward(_c, _c + _size, _c + _size + n);
				std::uninitialized_fill_n(_c + diff, n,val);
			}

			_size += n;
			_capacity = newCapacity;
		}

//		inserts elements (range)
		template <class InputIt>
		void insert(iterator pos, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last) {
			size_type diff = ft::distance(first, last);
			size_type diffCpy = ft::distance(begin(), pos);
			size_type newCapacity;

			newCapacity = _capacity;
			if (_size + diff > _capacity * 2 || _capacity == 0)
				newCapacity = _size + diff;
			else if (_size + diff > _capacity)
				newCapacity = _capacity * 2;

			if (_capacity < newCapacity) {
				value_type *tmp = _alloc.allocate(newCapacity);
				std::uninitialized_copy(begin(), pos, tmp);
				std::uninitialized_copy(first, last, tmp + diffCpy);
				std::uninitialized_copy(pos, end(), tmp + diff + diffCpy);
				cleanPointer();
				_c = tmp;
			}
			else
			{
				std::uninitialized_copy(begin(), pos, _c);
				std::uninitialized_copy(first, last, _c + diffCpy);
				std::uninitialized_copy(pos, end(), _c + diff + diffCpy);
			}
			_size += diff;
			_capacity = newCapacity;
		}

//		erases elements
		iterator erase(iterator pos) {
			if (pos == end())
				return (pos);
			if (pos + 1 != end())
				std::copy(pos + 1, end(), pos);
			_size--;
			_alloc.destroy(_c + _size);
			return (pos);
		}

//		erases elements
		iterator erase(iterator first, iterator last) {
			if (first == last)
				return (last);
			size_t diff = ft::distance(first, last);
			iterator it = std::copy(last, end(), first);
			for (; it != end() ; it++) {
				_alloc.destroy(_c + (it - begin()));
			}
			_size = _size - diff;
			return (last - diff);
		}

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
				int oldSize = _size;
				reserve(count);
				std::uninitialized_fill_n(_c + oldSize, count - oldSize, value);
				_size = count;
			}
			else if (count < _size)
			{
				erase(_c + count, end());
				_size = count;
			}
		}

//		swaps the contents
		void swap(vector &other) {
			allocator_type alloc = other._alloc;
			value_type *c = other._c;
			size_type size = other._size;
			size_type capacity = other._capacity;

			other._alloc = this->_alloc;
			other._c = this->_c;
			other._size = this->_size;
			other._capacity = this->_capacity;

			this->_alloc = alloc;
			this->_c = c;
			this->_size = size;
			this->_capacity = capacity;
		}

//		relational operators
		friend bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
			if (lhs._size != rhs._size)
				return (lhs._size == rhs._size);
			for (size_type i = 0; i < lhs._size; i++) {
				if (lhs.at(i) != rhs.at(i))
					return false;
			}
			return true;
		}

		friend bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
			return !(lhs == rhs);
		}
		friend bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		friend bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
			return (rhs < lhs);
		}
		friend bool operator>= (const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
			return !(lhs < rhs);
		}
		friend bool operator<= (const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
			return !(rhs < lhs);
		}

		friend void swap(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
			lhs.swap(rhs);
		}

	};
}

#endif
