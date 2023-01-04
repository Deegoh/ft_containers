#ifndef MAP_HPP
# define MAP_HPP
//#include <function.h>

//https://web.archive.org/web/20160731194845/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/MAP.H
//https://cs.brown.edu/people/jwicks/libstdc++/html_user/stl__map_8h-source.html

# include "pair.hpp"
# include "rb_tree.hpp"
# include <functional>
//# include <utility>

namespace ft {

	template<
				class Key,//map::key_type
				class T,//map::mapped_type
				class Compare = std::less<Key>,//map::key_compare
				class Allocator = std::allocator<pair<const Key, T> >//map::allocator_type>
			>
	class map {
	public:

// typedefs:

		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
//		typedef ft::random_access_iterator<value_type> iterator;
//		typedef ft::random_access_iterator<const value_type> const_iterator;
////		typedef ft::bidirectional_iterator<value_type>			iterator;
////		typedef ft::bidirectional_iterator<const value_type>	const_iterator;
//		typedef ft::reverse_iterator<iterator> reverse_iterator;
//		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
//		typedef typename allocator_type::difference_type difference_type;
//		typedef typename allocator_type::size_type size_type;

//		typedef typename rep_type::pointer					pointer;
//		typedef typename rep_type::reference				reference;
//		typedef typename rep_type::const_reference			const_reference;
		typedef ft::rb_tree<key_type, value_type, ft::select1st<value_type>, key_compare> rep_type;

		typedef typename rep_type::iterator					iterator;
		typedef typename rep_type::const_iterator			const_iterator;
		typedef typename rep_type::reverse_iterator			reverse_iterator;
		typedef typename rep_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename rep_type::size_type				size_type;
		typedef typename rep_type::difference_type			difference_type;


//		compares objects of type value_type (class)
		class value_compare : public std::binary_function<value_type, value_type, bool> {
			friend class map<Key, T, Compare>;

		protected:
			Compare comp;

			value_compare(Compare c) : comp(c) {}

		public:
			bool operator()(const value_type &x, const value_type &y) const {
				return comp(x.first, y.first);
			}
		};

	private:
		rep_type t;  // red-black tree representing map
		allocator_type _alloc;

	public:

//	copilien
//		empty container constructor (default constructor)
		explicit map(const Compare &comp = Compare(),
					 const allocator_type& alloc = allocator_type()) :
					 t(comp, false),
					 _alloc(alloc) {}

//		range constructor
		template <class InputIt>
		map(InputIt first, InputIt last,
			const Compare &comp = Compare(),
			const allocator_type& alloc = allocator_type()) :
			t(comp, alloc) {
			t.insert(first, last);
		}

//		copy constructor
		explicit map(const map<Key, T, Compare> &x) : t(x.t, false), _alloc() {}

//		destructor
		~map() {}

		map<Key, T, Compare, Allocator> &operator=(const map<Key, T, Compare> &rhs) {
			if (&rhs != this)
				t = rhs.t;
			return *this;
		}

//		returns the associated allocator
		allocator_type get_allocator() const {
			return (_alloc);
		}

//	Element access:

//		access specified element with bounds checking
		mapped_type& at(const Key& key) {
			(void)key;
//			TODO find if key exist
			throw std::out_of_range("out_of_range exception");
		}

//		access specified element with bounds checking
		const mapped_type& at(const Key& key) const {
			(void)key;
//			TODO find if key exist
			throw std::out_of_range("out_of_range exception");
		}

//		access or insert specified element
//		mapped_type& operator[](const Key& key) {
//			return(*((this->insert(make_pair(key,mapped_type()))).first));
//		}

		reference operator[](const key_type& k) {
			return (*((insert(value_type(k, T()))).first)).second;
		}

//	Iterators:

//		Return iterator to beginning
		iterator begin() { return t.begin(); }
//		Return const iterator to beginning
		const_iterator begin() const { return t.begin(); }

//		Return iterator to end
		iterator end() { return t.end(); }
//		Return const iterator to end
		const_iterator end() const { return t.end(); }

//		Returns a reverse iterator to the beginning
		reverse_iterator rbegin() { return t.rbegin(); }
//		Returns a const reverse iterator to the beginning
		const_reverse_iterator rbegin() const { return t.rbegin(); }

//		Return reverse iterator to reverse end
		reverse_iterator rend() { return t.rend(); }
//		Return const reverse iterator to reverse end
		const_reverse_iterator rend() const { return t.rend(); }

//	Capacity:

//		checks whether the container is empty
		bool empty() const { return t.empty(); }
//		returns the number of elements
		size_type size() const { return t.size(); }
//		returns the maximum possible number of elements
		size_type max_size() const { return t.max_size(); }

		void swap(map<Key, T, Compare>& x) {
			t.swap(x.t);
		}

//	Modifiers:

//		Erases all elements from the container. After this call, size() returns zero.
//		clears the contents
		void clear() {}


		typedef pair<iterator, bool> pair_iterator_bool;
		// typedef done to get around compiler bug
		pair_iterator_bool insert(const value_type& x) { return t.insert(x); }
		iterator insert(iterator position, const value_type& x) {
			return t.insert(position, x);
		}
		void insert(const value_type* first, const value_type* last) {
			t.insert(first, last);
		}
		void erase(iterator position) { t.erase(position); }
		size_type erase(const key_type& x) { return t.erase(x); }
		void erase(iterator first, iterator last) { t.erase(first, last); }

	// map operations:

		iterator find(const key_type& x) { return t.find(x); }
		const_iterator find(const key_type& x) const { return t.find(x); }
		size_type count(const key_type& x) const { return t.count(x); }
		iterator lower_bound(const key_type& x) {return t.lower_bound(x); }
		const_iterator lower_bound(const key_type& x) const {
			return t.lower_bound(x);
		}
		iterator upper_bound(const key_type& x) {return t.upper_bound(x); }
		const_iterator upper_bound(const key_type& x) const {
			return t.upper_bound(x);
		}
//		typedef pair<iterator, iterator> pair_iterator_iterator;
		// typedef done to get around compiler bug
		pair<iterator, iterator> equal_range(const key_type& x) {
			return t.equal_range(x);
		}
//		typedef pair<const_iterator, const_iterator> pair_citerator_citerator;
		// typedef done to get around compiler bug
		pair<const_iterator, const_iterator> equal_range(const key_type& x) const {
			return t.equal_range(x);
		}


//	Observers:
//		returns the function that compares keys
		key_compare key_comp() const { return t.key_comp(); }
//		returns the function that compares keys in objects of type value_type
		value_compare value_comp() const { return value_compare(t.key_comp()); }
	};

	template <class Key, class T, class Compare>
	bool operator==(const map<Key, T, Compare>& x, const map<Key, T, Compare>& y) {
		return x.size() == y.size() && equal(x.begin(), x.end(), y.begin());
	}

	template <class Key, class T, class Compare>
	bool operator<(const map<Key, T, Compare>& x, const map<Key, T, Compare>& y) {
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

}

#endif
