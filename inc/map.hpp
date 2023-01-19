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
//
//// typedefs:
//
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator alloc_type;
		typedef typename alloc_type::reference reference;
		typedef typename alloc_type::const_reference const_reference;
		typedef typename alloc_type::pointer pointer;
		typedef typename alloc_type::const_pointer const_pointer;
		typedef ft::rb_tree<value_type, key_type, Compare> tree_type;

		typedef typename tree_type::it						iterator;
		typedef typename tree_type::const_it				const_iterator;
		typedef typename tree_type::reverse_iterator		reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename tree_type::size_type				size_type;
//		typedef typename tree_type::difference_type			difference_type;
//
//

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
		map(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last,
			const Compare &comp = Compare(),
			const alloc_type& alloc = alloc_type()) :
			_key_comp(comp),
			_value_comp(comp),
			_tree(),
			_alloc(alloc) {
				insert(first, last);
		}

//		copy constructor
		explicit map(const map &src) {
			*this = src;
		}

//		destructor
		~map() {}

		map<Key, T, Compare, Allocator> &operator=(const map &rhs) {
			if (&rhs != this)
			{
				_key_comp = rhs._key_comp;
				_value_comp = rhs._value_comp;
				_tree = rhs._tree;
				_alloc = rhs._alloc;
			}
			return (*this);
		}

//		returns the associated allocator
		alloc_type get_allocator() const {
			return (_alloc);
		}

//	Element access:
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

//		access or insert specified element
		mapped_type& operator[](const key_type& key) {
			return((*((insert(ft::make_pair(key, T()))).first)).second);
		}

//	Iterators:
//
//		Return iterator to beginning
		iterator begin() { return _tree.begin(); }
//		Return const iterator to beginning
		const_iterator begin() const { return _tree.begin(); }
//
//		Return iterator to end
		iterator end() { return _tree.end(); }
//		Return const iterator to end
		const_iterator end() const { return _tree.end(); }

////		Returns a reverse iterator to the beginning
//		reverse_iterator rbegin() { return _tree.rbegin(); }
////		Returns a const reverse iterator to the beginning
//		const_reverse_iterator rbegin() const { return _tree.rbegin(); }

////		Return reverse iterator to reverse end
//		reverse_iterator rend() { return _tree.rend(); }
////		Return const reverse iterator to reverse end
//		const_reverse_iterator rend() const { return _tree.rend(); }
//
////	Capacity:
//
//		checks whether the container is empty
		bool empty() const { return _tree.empty(); }
//		returns the number of elements
		size_type size() const { return _tree.size(); }
//		returns the maximum possible number of elements
		size_type max_size() const { return _tree.max_size(); }
//
//		void swap(map<Key, T, Compare>& x) {
//			_tree.swap(x.t);
//		}
//
////	Modifiers:
//
////		Erases all elements from the container. After this call, size() returns zero.
//		clears the contents
		void clear() {
			_tree.clear();
		}
//
//
		typedef ft::pair<iterator, bool> pair_iterator_bool;
//		// typedef done to get around compiler bug

//		insert a single elemen
		pair_iterator_bool insert(const value_type& val) {
			iterator it = find(val.first);
			if (it->first ==  val.first)
			{
				return (ft::make_pair<iterator, bool>(it, false));
			}
			_tree.insert_node(val);
			return (pair_iterator_bool(it, true));
		}

//		insert a single elemen with hint
		iterator insert(iterator position, const value_type& val) {
			(void)position;
			insert(val);
			find(val.first);
			return (iterator(find(val.first), _tree.get_nil()));
		}

//		insert a range
		template <class InputIt>
		void insert (InputIt first, InputIt last) {
			for (; first != last ; first++) {
				insert(*first);
			}
		}


//		void erase(iterator position) { _tree.erase(position); }
		size_type erase(const key_type& key) {
			return _tree.delete_node(key);
		}
//		void erase(iterator first, iterator last) { _tree.erase(first, last); }

	// map operations:

		iterator find(const key_type& key) {
			return iterator(_tree.get_root(), _tree.search_tree(_tree.get_root(), key), _tree.get_nil());
		}
		const_iterator find(const key_type& key) const {
			return const_iterator(_tree.get_root(), _tree.search_tree(_tree.get_root(), key), _tree.get_nil());
		}

		size_type count(const key_type& key) const { return _tree.count(key); }

		iterator lower_bound(const key_type& key) {
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound(const key_type& key) const {
			return _tree.lower_bound(key);
		}

		iterator upper_bound(const key_type& key) {
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound(const key_type& key) const {
			return _tree.upper_bound(key);
		}

		typedef pair<iterator, iterator> pair_iterator_iterator;
		// typedef done to get around compiler bug
		pair_iterator_iterator equal_range(const key_type& key) {
			return _tree.equal_range(key);
		}
		typedef pair<const_iterator, const_iterator> pair_citerator_citerator;
		// typedef done to get around compiler bug
		pair_citerator_citerator equal_range(const key_type& key) const {
			return _tree.equal_range(key);
		}
//
//
//	Observers:
//		returns the function that compares keys
		key_compare key_comp() const { return _tree.key_comp(); }
//		returns the function that compares keys in objects of type value_type
		value_compare value_comp() const { return value_compare(_tree.key_comp()); }
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
