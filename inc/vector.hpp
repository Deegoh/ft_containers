#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <cstddef>

//# include "iterator.hpp"
# include "Random_access_iterator.hpp"
//# include "utils.hpp"

namespace ft {
	template <typename T, class Allocator = std::allocator<T> >
	class vector {
	public: //test delete after
		void reAllocTest() {
			size_type size = 5;
			T *block = _alloc.allocate(size);
			std::cout << "alloc[";
			for (size_type i = 0; i < size; ++i) {
				block[i] = _c[i];
				std::cout << block[i];
				if (i < 5 -1)
					std::cout << ", ";
			}
			std::cout << "]" << std::endl;
//			std::cout << &block << std::endl;
//			std::cout << &block[0] << std::endl;
//			// destroy space _c
			for (size_type i = 0; i < size; ++i) {
				_alloc.destroy(block + i);
			}
//			// deallocate space _c
			_alloc.deallocate(block, size);
		}
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
		iterator _start;
		iterator _end;

//		https://web.archive.org/web/20160304114243/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/VECTOR.H
//		void reserve(size_type n) {
//			if (capacity() < n) {
//				iterator tmp = static_allocator.allocate(n);
//				uninitialized_copy(begin(), end(), tmp);
//				destroy(start, finish);
//				static_allocator.deallocate(start);
//				finish = tmp + size();
//				start = tmp;
//				end_of_storage = begin() + n;
//			}
//		}
	public:
//		1. alloc a new block of memory
//		2. copy / move old elems into new block
//		3. delete
		void reAlloc(size_type newCapacity) {
			if (newCapacity == 0)
				newCapacity = 1;
			T* newBlock = _alloc.allocate(newCapacity);
//			downsize space
			if (newCapacity < _size)
				_size = newCapacity;
//			cpy value
			for (size_type i = 0; i < _size; ++i) {
				newBlock[i] = _c[i];
			}
//			destroy content _c
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_c + i);
			}
//			deallocate space _c
			if (_c)
				_alloc.deallocate(_c, _capacity);
//			cpy
			_c = newBlock;
			_start = _c;
			_end = _c + _size;
			_capacity = newCapacity;
		}

//		Constructor
		vector() : _alloc(), _start(NULL), _end(NULL) {
			_capacity = 0;
			_size = 0;
			_c = NULL;
//			_alloc = allocator_type();
		};

		vector(const vector& src) {(*this) = src;};

		~vector() {
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_c + i);
			}
			if (_c)
				_alloc.deallocate(_c, _capacity);
		};

		vector& operator=(const vector& rhs) {
//			if (&rhs != this)
//				(*this) = rhs;
			(void)rhs;
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
		iterator begin() {return iterator(_start);}
		const_iterator begin() const {return const_iterator(_start);}

		iterator end() {return iterator(_end);}
//		const_iterator end() const {return iterator(_end);}

//		Capacity
//		checks whether the container is empty (public member function)
		bool empty() const {
			return (begin() == end());
		}

//		Return size (public member function)
//		std::distance(begin(), end())
		size_type size() const {
			return (_size);
		}

//		returns the maximum possible number of elements (public member function)
		size_type max_size() const {return _alloc.max_size();}

//		reserves storage (public member function)
		void reserve(size_type n) {
			if (capacity() < n) {
				iterator tmp = _alloc.allocate(n);
				uninitialized_copy(begin(), end(), tmp);
				destroy(_start, _end);
				_alloc.deallocate(_start);
				_end = tmp + size();
				_start = tmp;
				_size = begin() + n;
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

//		Add element at the end (public member function)
		void push_back(const value_type& value) {
			if (_size >= _capacity) {
				reAlloc(_capacity * 2);
			}
			_alloc.construct(_c + _size, value);
			_size++;
			_end++;
		}
//		removes the last element (public member function)
		void pop_back() {
			if (_size > 0)
			{
				_size--;
				_end--;
				_alloc.destroy(_c + _size);
			}
		}

//		Change size (public member function)
		void resize (size_type count) {
			//1 reAlloc
			//2 move
			return count;
		}
	};
}

//template <class _Tp, class _Allocator>
//class __vector_base
//		: protected __vector_base_common<true>
//{
//public:
//typedef _Allocator                               allocator_type;
//typedef allocator_traits<allocator_type>         __alloc_traits;
//typedef typename __alloc_traits::size_type       size_type;
//protected:
//typedef _Tp                                      value_type;
//typedef value_type&                              reference;
//typedef const value_type&                        const_reference;
//typedef typename __alloc_traits::difference_type difference_type;
//typedef typename __alloc_traits::pointer         pointer;
//typedef typename __alloc_traits::const_pointer   const_pointer;
//typedef pointer                                  iterator;
//typedef const_pointer                            const_iterator;
//
//pointer                                         __begin_;
//pointer                                         __end_;
//__compressed_pair<pointer, allocator_type> __end_cap_;


//	template <class T, class Allocator = std::allocator<T> >
//	class vector {
//	public:
//		typedef T                                        value_type;
//		typedef Allocator                                allocator_type;
//		typedef typename allocator_type::reference       reference;
//		typedef typename allocator_type::const_reference const_reference;
//		typedef implementation-defined                   iterator;
//		typedef implementation-defined                   const_iterator;
//		typedef typename allocator_type::size_type       size_type;
//		typedef typename allocator_type::difference_type difference_type;
//		typedef typename allocator_type::pointer         pointer;
//		typedef typename allocator_type::const_pointer   const_pointer;
//		typedef std::reverse_iterator<iterator>          reverse_iterator;
//		typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
//
//		vector();
//		explicit vector(const allocator_type&);
//		explicit vector(size_type n);
//		vector(size_type n, const value_type& value, const allocator_type& = allocator_type());
//		template <class InputIterator>
//		vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type());
//		vector(const vector& x);
//		vector(vector&& x);
//		vector(initializer_list<value_type> il);
//		vector(initializer_list<value_type> il, const allocator_type& a);
//		~vector();
//		vector& operator=(const vector& x);
//		vector& operator=(initializer_list<value_type> il);
//		template <class InputIterator>
//		void assign(InputIterator first, InputIterator last);
//		void assign(size_type n, const value_type& u);
//		void assign(initializer_list<value_type> il);
//
//		allocator_type get_allocator() const;
//
//		iterator               begin();
//		const_iterator         begin()   const;
//		iterator               end();
//		const_iterator         end()     const;
//
//		reverse_iterator       rbegin();
//		const_reverse_iterator rbegin()  const;
//		reverse_iterator       rend();
//		const_reverse_iterator rend()    const;
//
//		const_iterator         cbegin()  const;
//		const_iterator         cend()    const;
//		const_reverse_iterator crbegin() const;
//		const_reverse_iterator crend()   const;
//
//		size_type size() const;
//		size_type max_size() const;
//		size_type capacity() const;
//		bool empty() const;
//		void reserve(size_type n);
//		void shrink_to_fit();
//
//		reference       operator[](size_type n);
//		const_reference operator[](size_type n) const;
//		reference       at(size_type n);
//		const_reference at(size_type n) const;
//
//		reference       front();
//		const_reference front() const;
//		reference       back();
//		const_reference back() const;
//
//		value_type*       data();
//		const value_type* data() const;
//
//		void push_back(const value_type& x);
//		void push_back(value_type&& x);
//		template <class... Args>
//		void pop_back();
//
//		template <class... Args> iterator emplace(const_iterator position, Args&&... args);
//		iterator insert(const_iterator position, const value_type& x);
//		iterator insert(const_iterator position, value_type&& x);
//		iterator insert(const_iterator position, size_type n, const value_type& x);
//		template <class InputIterator>
//		iterator insert(const_iterator position, InputIterator first, InputIterator last);
//		iterator insert(const_iterator position, initializer_list<value_type> il);
//
//		iterator erase(const_iterator position);
//		iterator erase(const_iterator first, const_iterator last);
//
//		void clear();
//
//		void resize(size_type sz);
//		void resize(size_type sz, const value_type& c);
//
//		void swap(vector&);
//
//		bool __invariants() const;
//	};
//
//}

#endif
