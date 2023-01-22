#ifndef MAP_HPP
# define MAP_HPP

//https://web.archive.org/web/20160731194845/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/MAP.H
//https://cs.brown.edu/people/jwicks/libstdc++/html_user/stl__map_8h-source.html

# include "utility.hpp"
# include "rb_tree.hpp"
# include <functional>
# include <utility>

namespace ft {

	template<
				class Key,//map::key_type
				class T,//map::mapped_type
				class Compare = std::less<Key>,//map::key_compare
				class Allocator = std::allocator<ft::pair<Key, T> >//map::allocator_type>
			>
	class map {
	public:

// typedefs:

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const Key, T>						value_type;
		typedef Compare										key_compare;
		typedef Allocator									alloc_type;
		typedef typename alloc_type::reference				reference;
		typedef typename alloc_type::const_reference		const_reference;
		typedef typename alloc_type::pointer				pointer;
		typedef typename alloc_type::const_pointer			const_pointer;
		typedef ft::rb_tree<value_type, key_type, Compare>	tree_type;

		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename tree_type::size_type				size_type;
		typedef typename std::ptrdiff_t						difference_type;
		typedef typename tree_type::node_pointer			node_pointer;



	private:
//		compares objects of type value_type (class)
		class value_compare : public std::binary_function<value_type, value_type, bool> {
		protected:
			Compare comp;

		public:
			value_compare() {};
			explicit value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		key_compare _key_comp;
		value_compare _value_comp;
		tree_type _tree;
		alloc_type _alloc;

	public:

//	copilien

//		empty container constructor (default constructor)
		explicit map(const key_compare &comp = key_compare(),
					 const alloc_type& alloc = alloc_type()) :
					 _key_comp(comp),
					 _value_comp(comp),
					 _tree(),
					 _alloc(alloc)
					 {}

//		range constructor
		template <class InputIt>
		map(InputIt first, InputIt last,
			const Compare &comp = Compare(),
			const alloc_type& alloc = alloc_type()) :
			_key_comp(comp),
			_value_comp(comp),
			_tree(),
			_alloc(alloc) {
				insert(first, last);
		}

//		copy constructor
		map(const map &src) {
			*this = src;
		}

//		destructor
		~map() {}

		map<Key, T, Compare, Allocator> &operator=(const map &rhs) {
			if (&rhs != this)
			{
				_key_comp = rhs._key_comp;
				_value_comp = rhs._value_comp;
				_alloc = rhs._alloc;
				if (this->_tree.get_root() != this->_tree.get_nil())
					clear();
				insert(rhs.begin(), rhs.end());
			}
			return (*this);
		}

//	Allocator:

//		returns the associated allocator
		alloc_type get_allocator() const {
			return (_alloc);
		}

//	Iterators:

//		Return iterator to beginning
		iterator begin() { return _tree.begin(); }
//		Return const iterator to beginning
		const_iterator begin() const { return _tree.begin(); }
//
//		Return iterator to end
		iterator end() { return _tree.end(); }
//		Return const iterator to end
		const_iterator end() const { return _tree.end(); }

//		Returns a reverse iterator to the beginning
		reverse_iterator rbegin() { return _tree.rbegin(); }
//		Returns a const reverse iterator to the beginning
		const_reverse_iterator rbegin() const { return _tree.rbegin(); }

//		Return reverse iterator to reverse end
		reverse_iterator rend() { return _tree.rend(); }
//		Return const reverse iterator to reverse end
		const_reverse_iterator rend() const { return _tree.rend(); }

//	Capacity:

//		checks whether the container is empty
		bool empty() const { return _tree.empty(); }
//		returns the number of elements
		size_type size() const { return _tree.size(); }
//		returns the maximum possible number of elements
		size_type max_size() const { return _tree.max_size(); }

//	Element access:

//		access or insert specified element
		mapped_type& operator[](const key_type& key) {
			return((*((insert(ft::make_pair(key, T()))).first)).second);
		}

		node_pointer get_root() {
			return (_tree.get_root());
		}

//	Modifiers:

		typedef ft::pair<iterator, bool> pair_iterator_bool;

//		insert a single elemen
		pair_iterator_bool insert(const value_type& value) {
			iterator it = find(value.first);
			if (it != end())
				return (pair_iterator_bool(it, false));
			else
			{
				this->_tree.insert_node(value);
				it = find(value.first);
				return (pair_iterator_bool(it, true));
			}
		}
//		insert a single elemen with hint
		iterator insert(iterator position, const value_type& value) {
			(void)position;
			return (insert(value).first);
		}
//		insert a range
		template <class InputIt>
		void insert (InputIt first, InputIt last) {
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

//		Erase elements
		void erase(iterator position) {
			erase((*position).first);
		}
		size_type erase(const key_type& key) {
			if (_tree.delete_node(key) == true)
				return 1;
			return 0;
		}
		void erase(iterator start, iterator last) {
			while (start != last)
			{
				erase((*(start++)).first);
			}
		}

//		Swap content
		void swap(map<Key, T, Compare, Allocator>& rhs) {
			_tree.swap(rhs._tree);
		}

//		clears the contents
		void clear() {
			_tree.clear();
		}

//	Observers:

//		returns the function that compares keys
		key_compare key_comp() const {
			return _tree.key_comp();
		}

//		returns the function that compares keys in objects of type value_type
		value_compare value_comp() const {
			return value_compare(_tree.key_comp());
		}

// Operations:

//		Get iterator to element
		iterator find(const key_type& key) {
			node_pointer tmp = _tree.search_tree(_tree.get_root(), key);
			if (tmp == _tree.get_nil())
				return (end());
			return (iterator(_tree.get_root(), tmp, _tree.get_nil()));
		}
//		Get iterator to element
		const_iterator find(const key_type& key) const {
			node_pointer tmp = _tree.search_tree(_tree.get_root(), key);
			if (tmp == _tree.get_nil())
				return (end());
			return (const_iterator(_tree.get_root(), tmp, _tree.get_nil()));
		}

//		Count elements with a specific key
		size_type count(const key_type& key) const {
			if (find(key) != end())
				return (1);
			return (0);
		}

//		Return iterator to lower bound
		iterator lower_bound(const key_type& key) {
			return (_tree.lower_bound(key));
		}
//		Return iterator to lower bound
		const_iterator lower_bound(const key_type& key) const {
			return (_tree.lower_bound(key));
		}

//		Return iterator to upper bound
		iterator upper_bound(const key_type& key) {
			return (_tree.upper_bound(key));
		}
//		Return iterator to upper bound
		const_iterator upper_bound(const key_type& key) const {
			return (_tree.upper_bound(key));
		}

//		Get range of equal elements
		typedef pair<iterator, iterator> pair_iterator_iterator;
		// typedef done to get around compiler bug
		pair_iterator_iterator equal_range(const key_type& key) {
			return (_tree.equal_range(key));
		}
		typedef pair<const_iterator, const_iterator> pair_citerator_citerator;
		// typedef done to get around compiler bug

//		Get range of equal elements
		pair_citerator_citerator equal_range(const key_type& key) const {
			return (_tree.equal_range(key));
		}

		friend bool operator==(const map& lhs, const map& rhs) {
			return (rhs.size() == lhs.size() && equal(rhs.begin(), rhs.end(), lhs.begin()));
		}

		friend bool operator!=(const map& lhs, const map& rhs) {
			return (!(lhs == rhs));
		}

		friend bool operator<(const map& lhs, const map& rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		friend bool operator>(const map& lhs, const map& rhs) {
			return (rhs < lhs);
		}

		friend bool operator>=(const map& lhs, const map& rhs) {
			return (!(lhs < rhs));
		}

		friend bool operator<=(const map& lhs, const map& rhs) {
			return (!(rhs < lhs));
		}

		friend void swap(const map& lhs, const map& rhs) {
			lhs.swap(rhs);
		}
	};
}

#endif
