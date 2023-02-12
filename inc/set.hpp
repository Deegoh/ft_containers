#ifndef SET_HPP
#define SET_HPP

# include <functional>
# include <utility>
# include "utility.hpp"
# include "rb_tree.hpp"


namespace ft {

	template<class T, class Key>
	struct select1stset : public std::unary_function<T, Key> {
		const Key& operator()(const T& x) const {
			return x;
		}
	};

	template<
			class T, // set::key_type/value_type
			class Compare = std::less<T>, // set::key_compare/value_compare
			class Alloc = std::allocator<T> // set::allocator_type
			>
	class set {
	public:
//	typedef
		typedef T												key_type;
		typedef T												value_type;
		typedef Compare											key_compare;
		typedef Compare											value_compare;
		typedef Alloc											alloc_type;
		typedef typename alloc_type::reference					reference;
		typedef typename alloc_type::const_reference			const_reference;
		typedef typename alloc_type::pointer					pointer;
		typedef typename alloc_type::const_pointer				const_pointer;
		typedef ft::rb_tree<value_type, key_type,
			ft::select1stset<value_type, key_type> , Compare>	tree_type;
		typedef typename tree_type::node_type					node_type;
		typedef ft::rbt_iterator<const value_type, node_type>	iterator;
		typedef ft::rbt_iterator<const value_type, node_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename std::ptrdiff_t							difference_type;
		typedef typename tree_type::size_type					size_type;
		typedef typename tree_type::node_pointer				node_pointer;

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
		~set() {}
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
		iterator begin() {
			return (iterator(_tree.get_root(), _tree.most_left(), _tree.get_nil()));
		}
//		Return iterator to beginning
		const_iterator begin() const {
			return (const_iterator(_tree.get_root(), _tree.most_left(), _tree.get_nil()));
		}

//		Return iterator to end
		iterator end() {
			return (iterator(_tree.get_root(), _tree.get_nil(), _tree.get_nil()));
		}
//		Return iterator to end
		const_iterator end() const {
			return (const_iterator(_tree.get_root(), _tree.get_nil(), _tree.get_nil()));
		}

//		Return reverse iterator to reverse beginning
		reverse_iterator rbegin() {
			return (reverse_iterator(end()));
		}
//		Return reverse iterator to reverse beginning
		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(end()));
		}

//		Return reverse iterator to reverse end
		reverse_iterator rend() {
			return (reverse_iterator(begin()));
		}
//		Return reverse iterator to reverse end
		const_reverse_iterator rend() const {
			return (const_reverse_iterator(begin()));
		}

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
			iterator it = find(value);
			if (it != end())
				return ft::pair<iterator, bool>(it, false);
			else {
				this->_tree.insert_node(value);
				it = find(value);
				return ft::pair<iterator, bool>(it, true);
			}
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
			erase((*position));
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
				erase((*(first++)));
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
		iterator lower_bound(const key_type& key) {
			iterator start = begin();

			for (; start != end() ; start++) {
				if ((*start) >= key)
					break;
			}

			return start;
		}
//		Return iterator to lower bound
		const_iterator lower_bound(const key_type& key) const {
			const_iterator start = begin();

			for (; start != end() ; start++) {
				if ((*start) >= key)
					break;
			}

			return start;
		}

//		Return iterator to upper bound
		iterator upper_bound(const key_type& key) {
			iterator start = begin();

			for (; start != end() ; start++) {
				if ((*start) > key)
					break;
			}

			return start;
		}
//		Return iterator to upper bound
		const_iterator upper_bound(const key_type& key) const {
			const_iterator start = begin();

			for (; start != end() ; start++) {
				if ((*start) > key)
					break;
			}

			return start;
		}

//		Get range of equal elements
		typedef pair<iterator, iterator> pair_iterator_iterator;
		// typedef done to get around compiler bug
		pair_iterator_iterator equal_range(const key_type& key) {
			return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
		}
		typedef pair<const_iterator, const_iterator> pair_citerator_citerator;
		// typedef done to get around compiler bug

//		Get range of equal elements
		pair_citerator_citerator equal_range(const key_type& key) const {
			return (ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
		}

//	Allocator:

//		Get allocator
		alloc_type get_allocator() const {
			return (_alloc);
		}

		friend bool operator==(const set& lhs, const set& rhs) {
			return (rhs.size() == lhs.size() && equal(rhs.begin(), rhs.end(), lhs.begin()));
		}

		friend bool operator!=(const set& lhs, const set& rhs) {
			return (!(lhs == rhs));
		}

		friend bool operator<(const set& lhs, const set& rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		friend bool operator>(const set& lhs, const set& rhs) {
			return (rhs < lhs);
		}

		friend bool operator>=(const set& lhs, const set& rhs) {
			return (!(lhs < rhs));
		}

		friend bool operator<=(const set& lhs, const set& rhs) {
			return (!(rhs < lhs));
		}

		friend void swap(const set& lhs, const set& rhs) {
			lhs.swap(rhs);
		}

	};
}

#endif
