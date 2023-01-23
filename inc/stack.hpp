#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

	template<class T, class Container = ft::vector<T> >
	class stack {
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

	protected:
		container_type _c;

	public:
//	constructor

//		default
		explicit stack (const container_type& cont = container_type()) : _c(cont) {}

//		copy
		stack(const stack& src) { (*this) = src; }

//		operator=
		stack& operator=(const stack& rhs) {
			if (this != &rhs)
			{
				_c = rhs._c;
			}
			return (*this);
		}

//		destructor
		~stack() {}

//	Element access

//		accesses the top element
		reference top() { return (_c.back()); }
//		accesses the top element
		const_reference top() const { return (_c.back()); }

//	Capacity

//		checks whether the underlying container is empty
		bool empty() const { return (_c.empty()); }
//		returns the number of elements
		size_type size() const { return (_c.size()); }

//	Modifiers

//		inserts element at the top
		void push (const value_type& value) { _c.push_back(value); };
//		removes the top element
		void pop() { _c.pop_back(); }

		friend bool operator==( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
			return (lhs._c == rhs._c);
		}

		friend bool operator!=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
			return (lhs._c != rhs._c);
		}

		friend bool operator<( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
			return (lhs._c < rhs._c);
		}

		friend bool operator<=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
			return (lhs._c <= rhs._c);
		}

		friend bool operator>( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
			return (lhs._c > rhs._c);
		}

		friend bool operator>=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ) {
			return (lhs._c >= rhs._c);
		}

	};
}

#endif
