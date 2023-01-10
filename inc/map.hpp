#ifndef MAP_HPP
# define MAP_HPP
//#include <function.h>

//https://web.archive.org/web/20160731194845/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/MAP.H
//https://cs.brown.edu/people/jwicks/libstdc++/html_user/stl__map_8h-source.html

# include "pair.hpp"
# include "rb_tree.hpp"
//#include "test_map.h"
//#include "test_tree.h"
# include <functional>
//# include <utility>

namespace ft {

	template<
				class Key,//map::key_type
				class T,//map::mapped_type
				class Compare = std::less<Key>,//map::key_compare
				class Allocator = std::allocator<ft::pair<const Key, T> >//map::allocator_type>
			>
	class map {
	public:
//
//// typedefs:
//
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator alloc_type;
//		typedef typename alloc_type::reference reference;
//		typedef typename alloc_type::const_reference const_reference;
//		typedef typename alloc_type::pointer pointer;
//		typedef typename alloc_type::const_pointer const_pointer;
		typedef ft::random_access_iterator<value_type> iterator;
////		typedef ft::random_access_iterator<const value_type> const_iterator;
//////		typedef ft::bidirectional_iterator<value_type>			iterator;
//////		typedef ft::bidirectional_iterator<const value_type>	const_iterator;
////		typedef ft::reverse_iterator<iterator> reverse_iterator;
////		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
////		typedef typename allocator_type::difference_type difference_type;
////		typedef typename allocator_type::size_type size_type;
//
////		typedef typename rep_type::pointer					pointer;
////		typedef typename rep_type::reference				reference;
////		typedef typename rep_type::const_reference			const_reference;
		typedef ft::rb_tree<key_type, mapped_type , key_compare , alloc_type> tree_type;
//
//		typedef typename rep_type::iterator					iterator;
//		typedef typename rep_type::const_iterator			const_iterator;
//		typedef typename rep_type::reverse_iterator			reverse_iterator;
//		typedef typename rep_type::const_reverse_iterator	const_reverse_iterator;
//		typedef typename rep_type::size_type				size_type;
//		typedef typename rep_type::difference_type			difference_type;
//
//
////		compares objects of type value_type (class)
//		class value_compare : public std::binary_function<value_type, value_type, bool> {
//			friend class map<Key, T, Compare>;
//
//		protected:
//			Compare comp;
//
//			value_compare(Compare c) : comp(c) {}
//
//		public:
//			bool operator()(const value_type &x, const value_type &y) const {
//				return comp(x.first, y.first);
//			}
//		};
//
	private:
		tree_type _tree;
		key_compare _comp;
		alloc_type _alloc;
//
	public:

//	copilien

//		empty container constructor (default constructor)
		explicit map(const Compare &comp = Compare(),
					 const alloc_type& alloc = alloc_type()) :
					 _tree(),
					 _comp(comp),
					 _alloc(alloc)
					 {}
//
////		range constructor
//		template <class InputIt>
//		map(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last,
//			const Compare &comp = Compare(),
//			const allocator_type& alloc = allocator_type()) :
//			_tree(comp, false), _alloc(alloc) {
////			_tree(first, last, comp, false), _alloc(alloc) {
//			_tree.insert(first, last);
//		}
//
////		copy constructor
//		explicit map(const map<Key, T, Compare> &x) : _tree(x.t, false), _alloc() {}
//
////		destructor
		~map() {}
//
//		map<Key, T, Compare, Allocator> &operator=(const map<Key, T, Compare> &rhs) {
//			if (&rhs != this)
//				_tree = rhs._tree;
//			return *this;
//		}
//
////		returns the associated allocator
//		allocator_type get_allocator() const {
//			return (_alloc);
//		}
//
////	Element access:
//
////		access specified element with bounds checking
//		mapped_type& at(const Key& key) {
//			(void)key;
////			TODO find if key exist
//			throw std::out_of_range("out_of_range exception");
//		}
//
////		access specified element with bounds checking
//		const mapped_type& at(const Key& key) const {
//			(void)key;
////			TODO find if key exist
//			throw std::out_of_range("out_of_range exception");
//		}
//
////		access or insert specified element
////		mapped_type& operator[](const Key& key) {
////			return(*((this->insert(make_pair(key,mapped_type()))).first));
////		}
//
//		reference operator[](const key_type& k) {
//			return (*((insert(value_type(k, T()))).first)).second;
//		}
//
////	Iterators:
//
//		Return iterator to beginning
		iterator begin() { return _tree.begin(); }
////		Return const iterator to beginning
//		const_iterator begin() const { return _tree.begin(); }
//
//		Return iterator to end
		iterator end() { return _tree.end(); }
////		Return const iterator to end
//		const_iterator end() const { return _tree.end(); }
//
////		Returns a reverse iterator to the beginning
//		reverse_iterator rbegin() { return _tree.rbegin(); }
////		Returns a const reverse iterator to the beginning
//		const_reverse_iterator rbegin() const { return _tree.rbegin(); }
//
////		Return reverse iterator to reverse end
//		reverse_iterator rend() { return _tree.rend(); }
////		Return const reverse iterator to reverse end
//		const_reverse_iterator rend() const { return _tree.rend(); }
//
////	Capacity:
//
////		checks whether the container is empty
//		bool empty() const { return _tree.empty(); }
////		returns the number of elements
//		size_type size() const { return _tree.size(); }
////		returns the maximum possible number of elements
//		size_type max_size() const { return _tree.max_size(); }
//
//		void swap(map<Key, T, Compare>& x) {
//			_tree.swap(x.t);
//		}
//
////	Modifiers:
//
////		Erases all elements from the container. After this call, size() returns zero.
////		clears the contents
//		void clear() {}
//
//
		typedef ft::pair<iterator, bool> pair_iterator_bool;
//		// typedef done to get around compiler bug

//		insert a single elemen
		pair_iterator_bool insert(const value_type& val) {
			return _tree.insert(val);
		}
//		insert a single elemen with hint
//		iterator insert(iterator position, const value_type& x) {
//			return _tree.insert(position, x);
//		}
//		insert a range
//		void insert(const value_type* first, const value_type* last) {
//			_tree.insert(first, last);
//		}

		//
//		pair<iterator, bool> insert(const value_type& val) {
//			int isNew = 0;
//			iterator temp = _tree.insert(val, isNew);
//			if (!isNew)
//				return (ft::make_pair<iterator, bool>(temp, false));
//			_size++;
////            pair<iterator, bool> t1 = ft::make_pair<iterator, bool>(temp, true);
//			return (ft::make_pair<iterator, bool>(temp, true));
//		}
//
//		template <class InputIterator>
//		void insert (InputIterator first, InputIterator last) {
//			InputIterator it = first;
//			int isNew = 0;
//			for (; it != last; it++) {
//				_tree.insert(*it, isNew);
//				if (isNew)
//					_size++;
//				isNew = 0;
//			}
//		}
//
//		iterator insert(iterator position, const value_type& val) {
//			(void)position;
//			int isNew = 0;
//			iterator temp = _tree.insert(val, isNew);
//			if (temp == _tree.end())
//				return (temp);
//			_size++;
//			return (temp);
//		}
		//




//		void erase(iterator position) { _tree.erase(position); }
//		size_type erase(const key_type& x) { return _tree.erase(x); }
//		void erase(iterator first, iterator last) { _tree.erase(first, last); }
//
//	// map operations:
//
//		iterator find(const key_type& x) { return _tree.find(x); }
//		const_iterator find(const key_type& x) const { return _tree.find(x); }
//		size_type count(const key_type& x) const { return _tree.count(x); }
//		iterator lower_bound(const key_type& x) {return _tree.lower_bound(x); }
//		const_iterator lower_bound(const key_type& x) const {
//			return _tree.lower_bound(x);
//		}
//		iterator upper_bound(const key_type& x) {return _tree.upper_bound(x); }
//		const_iterator upper_bound(const key_type& x) const {
//			return _tree.upper_bound(x);
//		}
////		typedef pair<iterator, iterator> pair_iterator_iterator;
//		// typedef done to get around compiler bug
//		pair<iterator, iterator> equal_range(const key_type& x) {
//			return _tree.equal_range(x);
//		}
////		typedef pair<const_iterator, const_iterator> pair_citerator_citerator;
//		// typedef done to get around compiler bug
//		pair<const_iterator, const_iterator> equal_range(const key_type& x) const {
//			return _tree.equal_range(x);
//		}
//
//
////	Observers:
////		returns the function that compares keys
//		key_compare key_comp() const { return _tree.key_comp(); }
////		returns the function that compares keys in objects of type value_type
//		value_compare value_comp() const { return value_compare(_tree.key_comp()); }
	};
//
//	template <class Key, class T, class Compare>
//	bool operator==(const map<Key, T, Compare>& x, const map<Key, T, Compare>& y) {
//		return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
//	}
//
//	template <class Key, class T, class Compare>
//	bool operator<(const map<Key, T, Compare>& x, const map<Key, T, Compare>& y) {
//		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
//	}

}

#endif
