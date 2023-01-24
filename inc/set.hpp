#ifndef SET_HPP
#define SET_HPP

# include <functional>
# include <utility>
# include "utility.hpp"
# include "rb_tree.hpp"


namespace ft {
	template<
			class T, // set::key_type/value_type
			class Compare = std::less<T>, // set::key_compare/value_compare
			class Alloc = std::allocator<T> // set::allocator_type
			>
	class set {
	public:
//	typedef
		typedef T											key_type;
		typedef T											value_type;
		typedef Compare										key_compare;
		typedef Compare										value_compare;
		typedef Alloc										alloc_type;
		typedef typename alloc_type::reference				reference;
		typedef typename alloc_type::const_reference		const_reference;
		typedef typename alloc_type::pointer				pointer;
		typedef typename alloc_type::const_pointer			const_pointer;
		typedef ft::rb_tree<value_type, key_type, Compare>	tree_type;
		typedef typename tree_type::iterator				iterator;
		typedef typename tree_type::const_iterator			const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename std::ptrdiff_t						difference_type;
		typedef typename tree_type::size_type				size_type;
		typedef typename tree_type::node_pointer			node_pointer;

	private:
		key_compare _key_comp;
		value_compare _value_comp;
		tree_type _tree;
		alloc_type _alloc;

	public:
//	Member functions:

//		constructs the set
//		empty (1)
		explicit set(const key_compare& comp = key_compare(),
					 const alloc_type& alloc = alloc_type()) :
					 _key_comp(comp),
					 _value_comp(comp),
					 _tree(),
					 _alloc(alloc) {}
//		range (2)
		template<class InputIt>
		set(InputIt first,
			InputIt last,
			const key_compare& comp = key_compare(),
			const alloc_type& alloc = alloc_type()) :
			_key_comp(comp),
			_value_comp(comp),
			_tree(),
			_alloc(alloc) {
					insert(first, last);
		}
//		copy (3)
		set(const set& src) {
			*this = src;
		}

//		destructs the set
		~set();
//		assigns values to the container
		set& operator= (const set& rhs) {
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

//	Iterators:

//		Return iterator to beginning
		iterator begin() { return _tree.begin(); }
//		Return iterator to beginning
		const_iterator begin() const { return _tree.begin(); }

//		Return iterator to end
		iterator end() { return _tree.end(); }
//		Return iterator to end
		const_iterator end() const { return _tree.end(); }

//		Return reverse iterator to reverse beginning
		reverse_iterator rbegin() { return _tree.rbegin(); }
//		Return reverse iterator to reverse beginning
		const_reverse_iterator rbegin() const { return _tree.rbegin(); }

//		Return reverse iterator to reverse end
		reverse_iterator rend() { return _tree.rend(); };
//		Return reverse iterator to reverse end
		const_reverse_iterator rend() const { return _tree.rend(); }

//	Capacity:

//		Test whether container is empty
		bool empty() const { return _tree.empty(); }

//		Return container size
		size_type size() const { return _tree.size(); }

//		Return maximum size
		size_type max_size() const { return _tree.max_size(); }

//	Modifiers:

//		Insert element
//		single element (1)
		typedef  pair<iterator, bool> pair_iterator_bool;
		pair_iterator_bool insert (const value_type& value) {
			iterator it;
			_tree.insert_node(value);
			it = find(value);
			return pair_iterator_bool(it, true);
		}
//		with hint (2)
		iterator insert (iterator position, const value_type& value) {
			(void)position;
			return (insert(value).first);
		}
//		range (3)
		template<class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

//		Erase elements
//		position (1)
		void erase (iterator position) {
			erase((*position).first);
		}
//		single element (2)
		size_type erase (const value_type& value) {
			if (_tree.delete_node(value) == true)
				return 1;
			return 0;
		}
//		range (3)
		void erase (iterator first, iterator last) {
			while (first != last)
			{
				erase((*(first++)).first);
			}
		}

//		Swap content
		void swap(set& rhs) {
			_tree.swap(rhs._tree);
		}

//		Clear content
		void clear() {
			_tree.clear();
		}

//	Observers:

//		Return comparison object
		key_compare key_comp() const {
			return _tree.key_comp();
		}
//		Return comparison object
		value_compare value_comp() const {
			return _tree.key_comp();
		}

//	Operations:

//		Get iterator to element
		iterator find (const value_type& value) const {
			node_pointer tmp = _tree.search_tree(_tree.get_root(), value);
			if (tmp == _tree.get_nil())
				return (end());
			return (iterator(_tree.get_root(), tmp, _tree.get_nil()));
		}
//		Count elements with a specific value
		size_type count (const value_type& value) const {
			if (find(value) != end())
				return (1);
			return (0);
		}
//		Return iterator to lower bound
		iterator lower_bound(const value_type& value) {
			return (_tree.lower_bound(value));
		}
		const_iterator lower_bound(const value_type& value) const {
			return (_tree.lower_bound(value));
		}
//		Return iterator to upper bound
		iterator upper_bound (const value_type& value) {
			return (_tree.upper_bound(value));
		}
		const_iterator upper_bound(const value_type& value) const {
			return (_tree.upper_bound(value));
		}
//		Get range of equal elements
		pair<const_iterator, const_iterator> equal_range (const value_type& value) const {
			return (_tree.equal_range(value));
		}


//	Allocator:

//		Get allocator
		alloc_type get_allocator() const {
			return (_alloc);
		}

	};
}

#endif
