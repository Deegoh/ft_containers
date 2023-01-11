// Map implementation -*- C++ -*-

// Copyright (C) 2001, 2002, 2004 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.	This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.	If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.	Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.	This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.	Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.	It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.	Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.	It is provided "as is" without express or implied warranty.
 */

/** @file stl_map.h
 *	This is an internal header file, included by other library headers.
 *	You should not attempt to use it directly.
 */

#ifndef _MAP_H
#define _MAP_H 1

//#include <bits/concept_check.h>


#include "utility.hpp"
#include <functional>
//#include "test_tree.h"
#include "tree_hajar.hpp"
//#include <concept_check.h>

namespace ft
{
/**
 *	@brief A standard container made up of (key,value) pairs, which can be
 *	retrieved based on a key, in logarithmic time.
 *
 *	@ingroup Containers
 *	@ingroup Assoc_containers
 *
 *	Meets the requirements of a <a href="tables.html#65">container</a>, a
 *	<a href="tables.html#66">reversible container</a>, and an
 *	<a href="tables.html#69">associative container</a> (using unique keys).
 *	For a @c map<Key,T> the key_type is Key, the mapped_type is T, and the
 *	value_type is std::pair<const Key,T>.
 *
 *	Maps support bidirectional iterators.
 *
 *	@if maint
 *	The private tree data is declared exactly the same way for map and
 *	multimap; the distinction is made entirely in how the tree functions are
 *	called (*_unique versus *_equal, same as the standard).
 *	@endif
*/
	template <typename Key, typename Tp, typename Compare = std::less<Key>,
						typename Alloc = std::allocator<pair<const Key, Tp> > >
	class map
		{
			// concept requirements
//			__glibcxx_class_requires(Tp, _SGIAssignableConcept)
//			__glibcxx_class_requires4(Compare, bool, Key, Key,
//								_BinaryFunctionConcept)

		public:
			typedef Key					key_type;
			typedef Tp					mapped_type;
			typedef pair<const Key, Tp>	value_type;
			typedef Compare			keyCompare;

			class valueCompare
				: public std::binary_function<value_type, value_type, bool>
			{
		friend class map<Key,Tp,Compare,Alloc>;
			protected:
		Compare comp;

		explicit valueCompare(Compare _c)
		: comp(_c) { }

			public:
		bool operator()(const value_type& x, const value_type& y) const {
			return comp(x.first, y.first); }
		};

		private:
			/// @if maint	This turns a red-black tree into a [multi]map.	@endif
			typedef Tree<key_type> rep_type;
			/// @if maint	The actual tree structure.	@endif
			rep_type _tree;

		public:
			// many of these are specified differently in ISO, but the following are
			// "functionally equivalent"
			typedef typename Alloc::pointer									 pointer;
			typedef typename Alloc::const_pointer						 const_pointer;
			typedef typename Alloc::reference								 reference;
			typedef typename Alloc::const_reference					 const_reference;
			typedef typename rep_type::allocator_type				 allocator_type;
			typedef typename ft::TreeIterators<value_type, keyCompare>		iterator;
			typedef typename ft::TreeIterators<value_type, keyCompare, true>	const_iterator;
//			typedef typename ft::TreeIterators<value_type, keyCompare>::reverse_iterator	reverse_iterator;
//			typedef typename ft::TreeIterators<value_type, keyCompare, true>::const_reverse_iterator const_reverse_iterator;

			// [23.3.1.1] construct/copy/destroy
			// (getAllocator() is normally listed in this section, but seems to have
			// been accidentally omitted in the printed standard)
			/**
			 *	@brief	Default constructor creates no elements.
			 */
			map()
			: _tree() { }

			// for some reason this was made a separate function
			/**
			 *	@brief	Default constructor creates no elements.
			 */
//			explicit
//			map(const Compare& comp, const allocator_type& alloc = allocator_type())
//			: _tree(comp, alloc) { }

			/**
			 *	@brief	Map copy constructor.
			 *	@param	x	A %map of identical element and allocator types.
			 *
			 *	The newly-created %map uses a copy of the allocation object used
			 *	by @a x.
			 */
			map(const map& x)
			: _tree(x._tree) { }

			/**
			 *	@brief	Builds a %map from a range.
			 *	@param	first	An input iterator.
			 *	@param	last	An input iterator.
			 *
			 *	Create a %map consisting of copies of the elements from [first,last).
			 *	This is linear in N if the range is already sorted, and NlogN
			 *	otherwise (where N is distance(first,last)).
			 */
			template <typename InputIt>
			map(InputIt first, InputIt last)
			: _tree() {
				_tree.insert_unique(first, last);
			}

			/**
			 *	@brief	Builds a %map from a range.
			 *	@param	first	An input iterator.
			 *	@param	last	An input iterator.
			 *	@param	comp	A comparison functor.
			 *	@param	a	An allocator object.
			 *
			 *	Create a %map consisting of copies of the elements from [first,last).
			 *	This is linear in N if the range is already sorted, and NlogN
			 *	otherwise (where N is distance(first,last)).
			 */
			template <typename InputIt>
				map(InputIt first, InputIt last,
				const Compare& comp, const allocator_type& alloc = allocator_type())
		: _tree()
				{ _tree.insert_unique(first, last); }

			// FIXME There is no dtor declared, but we should have something generated
			// by Doxygen.	I don't know what tags to add to this paragraph to make
			// that happen:
			/**
			 *	The dtor only erases the elements, and note that if the elements
			 *	themselves are pointers, the pointed-to memory is not touched in any
			 *	way.	Managing the pointer is the user's responsibilty.
			 */

			/**
			 *	@brief	Map assignment operator.
			 *	@param	x	A %map of identical element and allocator types.
			 *
			 *	All the elements of @a x are copied, but unlike the copy constructor,
			 *	the allocator object is not copied.
			 */
			map&
			operator=(const map& x)
			{
		_tree = x._tree;
		return *this;
			}

			/// Get a copy of the memory allocation object.
			allocator_type
			getAllocator() const
			{ return _tree.getAllocator(); }

			// iterators
			/**
			 *	Returns a read/write iterator that points to the first pair in the
			 *	%map.
			 *	Iteration is done in ascending order according to the keys.
			 */
			iterator
			begin()
			{ return _tree.begin(); }

			/**
			 *	Returns a read-only (constant) iterator that points to the first pair
			 *	in the %map.	Iteration is done in ascending order according to the
			 *	keys.
			 */
			const_iterator
			begin() const
			{ return _tree.begin(); }

			/**
			 *	Returns a read/write iterator that points one past the last pair in
			 *	the %map.	Iteration is done in ascending order according to the keys.
			 */
			iterator
			end()
			{ return _tree.end(); }

			/**
			 *	Returns a read-only (constant) iterator that points one past the last
			 *	pair in the %map.	Iteration is done in ascending order according to
			 *	the keys.
			 */
			const_iterator
			end() const
			{ return _tree.end(); }

			/**
			 *	Returns a read/write reverse iterator that points to the last pair in
			 *	the %map.	Iteration is done in descending order according to the
			 *	keys.
			 */
//			reverse_iterator
//			rbegin()
//			{ return _tree.rbegin(); }

			/**
			 *	Returns a read-only (constant) reverse iterator that points to the
			 *	last pair in the %map.	Iteration is done in descending order
			 *	according to the keys.
			 */
//			const_reverse_iterator
//			rbegin() const
//			{ return _tree.rbegin(); }

			/**
			 *	Returns a read/write reverse iterator that points to one before the
			 *	first pair in the %map.	Iteration is done in descending order
			 *	according to the keys.
			 */
//			reverse_iterator
//			rend()
//			{ return _tree.rend(); }

			/**
			 *	Returns a read-only (constant) reverse iterator that points to one
			 *	before the first pair in the %map.	Iteration is done in descending
			 *	order according to the keys.
			 */
//			const_reverse_iterator
//			rend() const
//			{ return _tree.rend(); }

			// capacity
			/** Returns true if the %map is empty.	(Thus begin() would equal
			 *	end().)
			*/
			bool
			empty() const
			{ return _tree.empty(); }

			/** Returns the size of the %map.	*/
			size_t size() const
			{ return _tree.size(); }

			/** Returns the maximum size of the %map.	*/
			size_t
			max_size() const
			{ return _tree.max_size(); }

			// [23.3.1.2] element access
			/**
			 *	@brief	Subscript ( @c [] ) access to %map data.
			 *	@param	k	The key for which data should be retrieved.
			 *	@return	A reference to the data of the (key,data) %pair.
			 *
			 *	Allows for easy lookup with the subscript ( @c [] ) operator.	Returns
			 *	data associated with the key specified in subscript.	If the key does
			 *	not exist, a pair with that key is created using default values, which
			 *	is then returned.
			 *
			 *	Lookup requires logarithmic time.
			 */
			mapped_type&
			operator[](const key_type& k)
			{
		// concept requirements
//		__glibcxx_function_requires(_DefaultConstructibleConcept<mapped_type>)

		iterator it = lower_bound(k);
		// it->first is greater than or equivalent to k.
		if (it == end() || keycomp()(k, (*it).first))
					it = insert(it, value_type(k, mapped_type()));
		return (*it).second;
			}

			// modifiers
			/**
			 *	@brief Attempts to insert a std::pair into the %map.
			 *	@param	x	Pair to be inserted (see std::make_pair for easy creation of
			 *						 pairs).
			 *	@return	A pair, of which the first element is an iterator that points
			 *					 to the possibly inserted pair, and the second is a bool that
			 *					 is true if the pair was actually inserted.
			 *
			 *	This function attempts to insert a (key, value) %pair into the %map.
			 *	A %map relies on unique keys and thus a %pair is only inserted if its
			 *	first element (the key) is not already present in the %map.
			 *
			 *	Insertion requires logarithmic time.
			 */
			pair<iterator,bool>
			insert(const value_type& x)
			{ return _tree.insert_unique(x); }

			/**
			 *	@brief Attempts to insert a std::pair into the %map.
			 *	@param	position	An iterator that serves as a hint as to where the
			 *										pair should be inserted.
			 *	@param	x	Pair to be inserted (see std::make_pair for easy creation of
			 *						 pairs).
			 *	@return	An iterator that points to the element with key of @a x (may
			 *					 or may not be the %pair passed in).
			 *
			 *	This function is not concerned about whether the insertion took place,
			 *	and thus does not return a boolean like the single-argument
			 *	insert() does.	Note that the first parameter is only a hint and can
			 *	potentially improve the performance of the insertion process.	A bad
			 *	hint would cause no gains in efficiency.
			 *
			 *	See http://gcc.gnu.org/onlinedocs/libstdc++/23_containers/howto.html#4
			 *	for more on "hinting".
			 *
			 *	Insertion requires logarithmic time (if the hint is not taken).
			 */
			iterator
			insert(iterator position, const value_type& x)
			{ return _tree.insert_unique(position, x); }

			/**
			 *	@brief A template function that attemps to insert a range of elements.
			 *	@param	first	Iterator pointing to the start of the range to be
			 *								 inserted.
			 *	@param	last	Iterator pointing to the end of the range.
			 *
			 *	Complexity similar to that of the range constructor.
			 */
			template <typename InputIt>
				void
				insert(InputIt first, InputIt last)
				{ _tree.insert_unique(first, last); }

			/**
			 *	@brief Erases an element from a %map.
			 *	@param	position	An iterator pointing to the element to be erased.
			 *
			 *	This function erases an element, pointed to by the given iterator,
			 *	from a %map.	Note that this function only erases the element, and
			 *	that if the element is itself a pointer, the pointed-to memory is not
			 *	touched in any way.	Managing the pointer is the user's responsibilty.
			 */
			void
			erase(iterator position)
			{ _tree.erase(position); }

			/**
			 *	@brief Erases elements according to the provided key.
			 *	@param	x	Key of element to be erased.
			 *	@return	The number of elements erased.
			 *
			 *	This function erases all the elements located by the given key from
			 *	a %map.
			 *	Note that this function only erases the element, and that if
			 *	the element is itself a pointer, the pointed-to memory is not touched
			 *	in any way.	Managing the pointer is the user's responsibilty.
			 */
			size_t
			erase(const key_type& x)
			{ return _tree.erase(x); }

			/**
			 *	@brief Erases a [first,last) range of elements from a %map.
			 *	@param	first	Iterator pointing to the start of the range to be
			 *								 erased.
			 *	@param	last	Iterator pointing to the end of the range to be erased.
			 *
			 *	This function erases a sequence of elements from a %map.
			 *	Note that this function only erases the element, and that if
			 *	the element is itself a pointer, the pointed-to memory is not touched
			 *	in any way.	Managing the pointer is the user's responsibilty.
			 */
			void
			erase(iterator first, iterator last)
			{ _tree.erase(first, last); }

			/**
			 *	@brief	Swaps data with another %map.
			 *	@param	x	A %map of the same element and allocator types.
			 *
			 *	This exchanges the elements between two maps in constant time.
			 *	(It is only swapping a pointer, an integer, and an instance of
			 *	the @c Compare type (which itself is often stateless and empty), so it
			 *	should be quite fast.)
			 *	Note that the global std::swap() function is specialized such that
			 *	std::swap(m1,m2) will feed to this function.
			 */
			void
			swap(map& x)
			{ _tree.swap(x._tree); }

			/**
			 *	Erases all elements in a %map.	Note that this function only erases
			 *	the elements, and that if the elements themselves are pointers, the
			 *	pointed-to memory is not touched in any way.	Managing the pointer is
			 *	the user's responsibilty.
			 */
			void
			clear()
			{ _tree.clear(); }

			// observers
			/**
			 *	Returns the key comparison object out of which the %map was
			 *	constructed.
			 */
			keyCompare
			keycomp() const
			{ return _tree.keycomp(); }

			/**
			 *	Returns a value comparison object, built from the key comparison
			 *	object out of which the %map was constructed.
			 */
			valueCompare
			valuecomp() const
			{ return valueCompare(_tree.keycomp()); }

			// [23.3.1.3] map operations
			/**
			 *	@brief Tries to locate an element in a %map.
			 *	@param	x	Key of (key, value) %pair to be located.
			 *	@return	Iterator pointing to sought-after element, or end() if not
			 *					 found.
			 *
			 *	This function takes a key and tries to locate the element with which
			 *	the key matches.	If successful the function returns an iterator
			 *	pointing to the sought after %pair.	If unsuccessful it returns the
			 *	past-the-end ( @c end() ) iterator.
			 */
			iterator
			find(const key_type& x)
			{ return _tree.find(x); }

			/**
			 *	@brief Tries to locate an element in a %map.
			 *	@param	x	Key of (key, value) %pair to be located.
			 *	@return	Read-only (constant) iterator pointing to sought-after
			 *					 element, or end() if not found.
			 *
			 *	This function takes a key and tries to locate the element with which
			 *	the key matches.	If successful the function returns a constant
			 *	iterator pointing to the sought after %pair. If unsuccessful it
			 *	returns the past-the-end ( @c end() ) iterator.
			 */
			const_iterator
			find(const key_type& x) const
			{ return _tree.find(x); }

			/**
			 *	@brief	Finds the number of elements with given key.
			 *	@param	x	Key of (key, value) pairs to be located.
			 *	@return	Number of elements with specified key.
			 *
			 *	This function only makes sense for multimaps; for map the result will
			 *	either be 0 (not present) or 1 (present).
			 */
			size_t
			count(const key_type& x) const
			{ return _tree.find(x) == _tree.end() ? 0 : 1; }

			/**
			 *	@brief Finds the beginning of a subsequence matching given key.
			 *	@param	x	Key of (key, value) pair to be located.
			 *	@return	Iterator pointing to first element equal to or greater
			 *					 than key, or end().
			 *
			 *	This function returns the first element of a subsequence of elements
			 *	that matches the given key.	If unsuccessful it returns an iterator
			 *	pointing to the first element that has a greater value than given key
			 *	or end() if no such element exists.
			 */
			iterator
			lower_bound(const key_type& x)
			{ return _tree.lower_bound(x); }

			/**
			 *	@brief Finds the beginning of a subsequence matching given key.
			 *	@param	x	Key of (key, value) pair to be located.
			 *	@return	Read-only (constant) iterator pointing to first element
			 *					 equal to or greater than key, or end().
			 *
			 *	This function returns the first element of a subsequence of elements
			 *	that matches the given key.	If unsuccessful it returns an iterator
			 *	pointing to the first element that has a greater value than given key
			 *	or end() if no such element exists.
			 */
			const_iterator
			lower_bound(const key_type& x) const
			{ return _tree.lower_bound(x); }

			/**
			 *	@brief Finds the end of a subsequence matching given key.
			 *	@param	x	Key of (key, value) pair to be located.
			 *	@return Iterator pointing to the first element
			 *					greater than key, or end().
			 */
			iterator
			upper_bound(const key_type& x)
			{ return _tree.upper_bound(x); }

			/**
			 *	@brief Finds the end of a subsequence matching given key.
			 *	@param	x	Key of (key, value) pair to be located.
			 *	@return	Read-only (constant) iterator pointing to first iterator
			 *					 greater than key, or end().
			 */
			const_iterator
			upper_bound(const key_type& x) const
			{ return _tree.upper_bound(x); }

			/**
			 *	@brief Finds a subsequence matching given key.
			 *	@param	x	Key of (key, value) pairs to be located.
			 *	@return	Pair of iterators that possibly points to the subsequence
			 *					 matching given key.
			 *
			 *	This function is equivalent to
			 *	@code
			 *		std::make_pair(c.lower_bound(val),
			 *									 c.upper_bound(val))
			 *	@endcode
			 *	(but is faster than making the calls separately).
			 *
			 *	This function probably only makes sense for multimaps.
			 */
			pair<iterator,iterator>
			equal_range(const key_type& x)
			{ return _tree.equal_range(x); }

			/**
			 *	@brief Finds a subsequence matching given key.
			 *	@param	x	Key of (key, value) pairs to be located.
			 *	@return	Pair of read-only (constant) iterators that possibly points
			 *					 to the subsequence matching given key.
			 *
			 *	This function is equivalent to
			 *	@code
			 *		std::make_pair(c.lower_bound(val),
			 *									 c.upper_bound(val))
			 *	@endcode
			 *	(but is faster than making the calls separately).
			 *
			 *	This function probably only makes sense for multimaps.
			 */
			pair<const_iterator,const_iterator>
			equal_range(const key_type& x) const
			{ return _tree.equal_range(x); }

			template <typename K1, typename T1, typename C1, typename A1>
				friend bool
				operator== (const map<K1,T1,C1,A1>&,
						const map<K1,T1,C1,A1>&);

			template <typename K1, typename T1, typename C1, typename A1>
				friend bool
				operator< (const map<K1,T1,C1,A1>&,
					 const map<K1,T1,C1,A1>&);
		};

	/**
	 *	@brief	Map equality comparison.
	 *	@param	x	A %map.
	 *	@param	y	A %map of the same type as @a x.
	 *	@return	True iff the size and elements of the maps are equal.
	 *
	 *	This is an equivalence relation.	It is linear in the size of the
	 *	maps.	Maps are considered equivalent if their sizes are equal,
	 *	and if corresponding elements compare equal.
	*/
	template <typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator==(const map<Key,Tp,Compare,Alloc>& x,
							 const map<Key,Tp,Compare,Alloc>& y)
		{ return x._tree == y._tree; }

	/**
	 *	@brief	Map ordering relation.
	 *	@param	x	A %map.
	 *	@param	y	A %map of the same type as @a x.
	 *	@return	True iff @a x is lexicographically less than @a y.
	 *
	 *	This is a total ordering relation.	It is linear in the size of the
	 *	maps.	The elements must be comparable with @c <.
	 *
	 *	See std::lexicographicalCompare() for how the determination is made.
	*/
	template <typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator<(const map<Key,Tp,Compare,Alloc>& x,
							const map<Key,Tp,Compare,Alloc>& y)
		{ return x._tree < y._tree; }

	/// Based on operator==
	template <typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator!=(const map<Key,Tp,Compare,Alloc>& x,
							 const map<Key,Tp,Compare,Alloc>& y)
		{ return !(x == y); }

	/// Based on operator<
	template <typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator>(const map<Key,Tp,Compare,Alloc>& x,
							const map<Key,Tp,Compare,Alloc>& y)
		{ return y < x; }

	/// Based on operator<
	template <typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator<=(const map<Key,Tp,Compare,Alloc>& x,
							 const map<Key,Tp,Compare,Alloc>& y)
		{ return !(y < x); }

	/// Based on operator<
	template <typename Key, typename Tp, typename Compare, typename Alloc>
		inline bool
		operator>=(const map<Key,Tp,Compare,Alloc>& x,
							 const map<Key,Tp,Compare,Alloc>& y)
		{ return !(x < y); }

	/// See std::map::swap().
	template <typename Key, typename Tp, typename Compare, typename Alloc>
		inline void
		swap(map<Key,Tp,Compare,Alloc>& x, map<Key,Tp,Compare,Alloc>& y)
		{ x.swap(y); }
} // namespace std

#endif /* _MAP_H */
