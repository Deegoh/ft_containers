#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
//# include "iterator.hpp"
//INSIDE ITERATOR
# include <cstddef>

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
//		typedef implementation-defined <T>					iterator;
//		typedef implementation-defined <T>					const_iterator;
//		typedef ft::reverse_iterator<iterator>			reverse_iterator;
//		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		value_type *_c;
		size_type _size;
		size_type _capacity;

//		1. alloc a new block of memory
//		2. copy / move old elems into new block
//		3. delete
		void reAlloc(size_type newCapacity) {
			//TODO Change to allocator
			if (newCapacity == 0)
				newCapacity = 1;
			T* newBlock = new T[newCapacity];

			//downsize space
			if (newCapacity < _size)
				_size = newCapacity;

			//upsize space
			for (size_type i = 0; i < _size; ++i) {
				newBlock[i] = _c[i];
			}
			delete[] _c;
			_c = newBlock;
			_capacity = newCapacity;

//			// allocator for string values
//			allocator<T> myAllocator;
//
//			// allocate space for three strings
//			T* = myAllocator.allocate(newCapacity);
//
//			// construct these 3 strings
//			myAllocator.construct(str, "Geeks");
//			myAllocator.construct(str + 1, "for");
//			myAllocator.construct(str + 2, "Geeks");
//
//			cout << str[0] << str[1] << str[2];
//
//			// destroy these 3 strings
//			myAllocator.destroy(str);
//			myAllocator.destroy(str + 1);
//			myAllocator.destroy(str + 2);
//
//			// deallocate space for 3 strings
//			myAllocator.deallocate(str, 3);
		}

	public:
		vector() {
			_capacity = 0;
			_size = 0;
			_c = NULL;
		};

		vector(const vector& src) {(*this) = src;};

		~vector() {};

		vector& operator=(const vector& rhs) {
			if (&rhs != this)
				(*this) = rhs;
			return (*this);
		};

		//iterator functions

		T& operator[](size_type index) {
			if (index >= _size)
			{
				// throw error ?
				return (_c[_size - 1]);
			}
			return (_c[index]);
		};
		const T& operator[](size_type index) const {
			if (index >= _size)
			{
				// throw error ?
				return (_c[_size - 1]);
			}
			return (_c[index]);
		};

//		std::distance(begin(), end())
//		return size
		size_type size() const {return (_size);}
//		return allocated space
		size_type capacity() const {return (_capacity);}


		void push_back(const value_type& value) {
			if (_size >= _capacity)
				reAlloc(_capacity * 2);
			_c[_size] = value;
			_size++;
		}
//		void push_back(value_type &&value);
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
