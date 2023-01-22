#ifndef RB_TREE_HPP
# define RB_TREE_HPP

//https://web.archive.org/web/20160731195009/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/TREE.H
//https://cs.brown.edu/people/jwicks/libstdc++/html_user/stl__tree_8h-source.html
//https://sd.blackball.lv/library/Introduction_to_Algorithms_Third_Edition_(2009).pdf

# include <memory>
# include "reverse_iterator.hpp"
# include "utility.hpp"
# include "comparators.hpp"

namespace ft {

	enum color_type {
		red, black
	};

	// node
	template <class T>
	class rb_node {
	public:
		typedef T					value_type;
		typedef rb_node*			node_pointer;
		typedef const node_pointer	const_node_pointer;

		rb_node(const value_type &data, color_type color, node_pointer parent, node_pointer left, node_pointer right) :
				value(data), color(color), parent(parent), left(left), right(right) {}

		rb_node(const T& src) {
			*this = src;
		}

		rb_node &operator=(const rb_node& rhs) {
			if (&rhs != this)
			{
				value = rhs.value;
				color = rhs.color;
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
			}
			return (*this);
		}

		~rb_node() {}

	public:
		value_type value;
		color_type color;
		node_pointer parent;
		node_pointer left;
		node_pointer right;
	};

	//end node

	// rb_tree
	template<typename T, //pair
			typename Key, // key of pair
			class Compare = std::less<Key>,
			typename Node_Alloc = std::allocator<rb_node<T> > >
	class rb_tree {
	public:
		typedef	Key			key_type;
		typedef	T			value_type;
		typedef	rb_node<T>	node_type;
		typedef node_type*	node_pointer;

		typedef Node_Alloc	alloc_type;
		typedef	Compare		key_compare_type;
		typedef	size_t		size_type;


	private:
		node_pointer _root;
		size_type _size;
		alloc_type _alloc;
		node_pointer _nil;

	public:
//		iterator
		template<typename T1>
		class iterator {
		public:
			typedef T1							value_type;
			typedef std::ptrdiff_t				difference_type;
			typedef value_type*					pointer;
			typedef value_type&					reference;
			typedef bidirectional_iterator_tag	iterator_category;

		private:
			node_pointer _root;
			node_pointer _current;
			node_pointer _nil;

		public:
			iterator() : _root(NULL), _current(NULL), _nil(NULL) {}

			iterator(node_pointer root, node_pointer current, node_pointer nil) :
					_root(root), _current(current), _nil(nil) {}

			iterator(const iterator& src) {
				*this = src;
			}

			iterator& operator=(const iterator& rhs) {
				if (this != &rhs) {
					_root = rhs._root;
					_current = rhs._current;
					_nil = rhs._nil;
				}
				return *this;
			}

			~iterator() {}

			operator iterator<const T1>() const {
				return (iterator<const T1>(_root, _current, _nil));
			}

			bool operator==(const iterator &rhs) const {
				return (_current == rhs._current);
			}
			bool operator!=(const iterator &rhs) const {
				return (_current != rhs._current);
			}

			reference operator*() const {
				if (_current == NULL)
					throw std::exception();
				return (_current->value);
			}

			reference operator*() {
				if (_current == NULL)
					throw std::exception();
				return (_current->value);
			}

			pointer operator->() {
				return (&_current->value);
			}
			pointer operator->() const {
				return (&_current->value);
			}

			iterator& operator++() {
				if (_current != _nil)
					_current = successor(_current);
				return (*this);
			}

			iterator operator++(int) {
				iterator tmp = *this;
				++*this;
				return (tmp);
			}

			iterator& operator--() {
				if (_current != _nil)
					_current = predecessor(_current);
				else
					_current = maximum(_root);
				return (*this);
			}

			iterator operator--(int) {
				iterator tmp = *this;
				--*this;
				return (tmp);
			}

			node_pointer base() { return _current; }

			node_pointer base() const { return _current; }

		protected:
			node_pointer maximum(node_pointer node) {
				while (node->right != _nil)
					node = node->right;
				return node;
			}

			node_pointer minimum(node_pointer node) {
				while (node->left != _nil)
					node = node->left;
				return node;
			}

			node_pointer predecessor(node_pointer node) {
				if (node->left != _nil)
				{
					return maximum(node->left);
				}
				else
				{
					node_pointer tmp = node->parent;

					while (tmp != _nil && node == tmp->left)//n
					{
						node = tmp;
						tmp = tmp->parent;
					}
					return tmp;
				}
			}

			node_pointer successor(node_pointer node) {
				if (node->right != _nil)
				{
					return minimum(node->right);
				}
				else
				{
					node_pointer tmp = node->parent;

					while (tmp != _nil && node == tmp->right)//n
					{
						node = tmp;
						tmp = tmp->parent;
					}

					if (tmp == _nil)//n
						return _nil;

					return tmp;
				}
			}

		};//end iterator

	public:

//		iterator in tree
		typedef iterator<const value_type>		const_it;
		typedef iterator<value_type>			it;
		typedef ft::reverse_iterator<it>		reverse_iterator;
		typedef ft::reverse_iterator<const_it>	const_reverse_iterator;

		// default
		rb_tree() : _size(0) {
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type(), black, NULL, NULL, NULL));
			_root = _nil;
		}

//		//copy
//		rb_tree(const rb_tree& other) : _root(NULL) {
//			*this = other;
//		}
//
//		// overload =
//		rb_tree& operator=(const rb_tree& rhs) {
//			if (this != &rhs) {
//				_root = rhs._root;
//				_size = rhs._size;
//				_alloc = rhs._alloc;
//				_nil = rhs._nil;
//			}
//			return (*this);
//		}

		// dectruct
		~rb_tree() {
			clear_tree(_root);
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}


		// accessors:

		node_pointer get_root() const { return (_root); }

		node_pointer get_nil() const { return (_nil); }

		Compare key_comp() const { return Compare(); }

		it begin() { return it(_root, most_left(), _nil); }

		const_it begin() const { return const_it(_root, most_left(), _nil); }

		it end() { return it(_root, _nil, _nil); }

		const_it end() const { return const_it(_root, _nil, _nil); }

		reverse_iterator rbegin() {
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend() {
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(begin()));
		}

		bool empty() const { return (_size == 0); }

		size_type size() const { return _size; }

		size_type max_size() const { return _alloc.max_size(); }

		// insert/erase

		node_pointer insert_node(const value_type &value) {
			node_pointer node;
			node = _alloc.allocate(1);
			_alloc.construct(node, node_type(value, red, _nil, _nil, _nil)); //n

			node_pointer y = _nil;//n
			node_pointer x = _root;

			while (x != _nil)
			{
				y = x;

				if (key_compare_type()(node->value.first, x->value.first))
					x = x->left;
				else if (key_compare_type()(x->value.first, node->value.first))
					x = x->right;
				else
				{
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					return _nil;
				}
			}

			node->parent = y;

			if (y == _nil)//n
				this->_root = node;
			else if (key_compare_type()(node->value.first, y->value.first))
				y->left = node;
			else
				y->right = node;

			this->_size++;

			if (y == _nil)//n
			{
				node->color = black;
				return (this->_root);
			}

			if (node->parent->parent == _nil)//n
				return (node);

			fix_insert(node);

			return node;
		}

		void	fix_insert(node_pointer node) {
			node_pointer x;

			while (node->parent->color == red)
			{
				if (node->parent == node->parent->parent->right)
				{
					x = node->parent->parent->left;
					if (x->color == red)
					{
						x->color = black;
						node->parent->color = black;
						node->parent->parent->color = red;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->left)
						{
							node = node->parent;
							right_rotate(node);
						}

						node->parent->color = black;
						node->parent->parent->color = red;
						left_rotate(node->parent->parent);
					}
				}
				else
				{
					x = node->parent->parent->right;
					if (x->color == red)
					{
						x->color = black;
						node->parent->color = black;
						node->parent->parent->color = red;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right)
						{
							node = node->parent;
							left_rotate(node);
						}

						node->parent->color = black;
						node->parent->parent->color = red;
						right_rotate(node->parent->parent);
					}
				}
				if (node == _root)
					break;
			}
			_root->color = black;
		}

		void clear() {
			clear_tree(_root);
			_root = _nil;
			_size = 0;
		}

		node_pointer search_tree(node_pointer node, key_type key) const {
			if (node == _nil)
				return (_nil);

			if (key == node->value.first)
				return (node);

			if (node != _nil)
			{
				if (key_compare_type()(key, node->value.first))
					return (search_tree(node->left, key));

				return (search_tree(node->right, key));
			}
			return (_nil);
		}

		bool delete_node(key_type key) {
			node_pointer x,y,z;

			z = search_tree(_root, key);
			if (z == _nil)
				return (false);

			y = z;
			color_type y_clr_save = y->color;

			if (z->left == _nil)
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == _nil)
			{
				x = z->left;
				transplant(z, z->left);
			}
			else
			{
				y = most_left(z->right);
				y_clr_save = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				transplant(z,y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}

			_alloc.destroy(z);
			_alloc.deallocate(z, 1);
			_size--;

			if (y_clr_save == black)
				fix_delete(x);

			return (true);
		}

		void fix_delete(node_pointer x) {
			node_pointer w;

			while (x != _root && x->color == black)
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->color == red)
					{
						w->color = black;
						x->parent->color = red;
						left_rotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == black && w->right->color == black)
					{
						w->color = red;
						x = x->parent;
					}
					else
					{
						if (w->right->color == black)
						{
							w->left->color = black;
							w->color = red;
							right_rotate(w);
							w = x->parent->right;
						}

						w->color = x->parent->color;
						x->parent->color = black;
						w->right->color = black;
						left_rotate(x->parent);
						x = _root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->color == red) {
						w->color = black;
						x->parent->color = red;
						right_rotate(x->parent);
						w = x->parent->left;
					}
					if (w->left->color == black && w->right->color == black)
					{
						w->color = red;
						x = x->parent;
					}
					else
					{
						if (w->left->color == black)
						{
							w->right->color = black;
							w->color = red;
							left_rotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = black;
						w->left->color = black;
						right_rotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = black;
		}

	public:

		//get node with min value
		node_pointer most_left(node_pointer &node) {
			if (node == _nil)
				return (_root);

			while (node->left != _nil)
				node = node->left;

			return (node);
		}

		node_pointer most_left() const {
			node_pointer tmp = _root;

			if (tmp == _nil)
				return (_root);

			while (tmp->left != _nil)
				tmp = tmp->left;

			return (tmp);
		}

		//get node with max value
		node_pointer most_right(node_pointer &node) {
			if (node == _nil)
				return (_root);

			while (node->right != _nil)
				node = node->right;

			return (node);
		}

		node_pointer most_right() const {
			node_pointer tmp = _root;

			if (tmp == _nil)
				return (_root);

			while (tmp->right != _nil)
				tmp = tmp->right;

			return (tmp);
		}

		void clear_tree(const node_pointer &node) {
			if(node == _nil)
				return;

			clear_tree(node->left);
			clear_tree(node->right);

//			delete node;
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			_size--;
		}

		// Rotates
		void left_rotate(node_pointer x) {
			node_pointer y = x->right;
			x->right = y->left;

			if (y->left != _nil)
				y->left->parent = x;

			y->parent = x->parent;

			if (x->parent == _nil)//n
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;

			y->left = x;
			x->parent = y;
		}

		void right_rotate(node_pointer x) {
			node_pointer y = x->left;
			x->left = y->right;

			if (y->right != _nil)
				y->right->parent = x;

			y->parent = x->parent;

			if (x->parent == _nil)//n
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;

			y->right = x;
			x->parent = y;
		}

		void transplant(node_pointer u, node_pointer v) {
			if (u->parent == _nil)//n
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void swap(rb_tree &rhs) {
			std::swap(_root, rhs._root);
			std::swap(_nil, rhs._nil);
			std::swap(_alloc, rhs._alloc);
			std::swap(_size, rhs._size);
		}

		it lower_bound (const key_type& key) {
			it start = begin();

			for (; start != end() ; start++) {
				if ((*start).first >= key)
					return start;
			}

			return end();
		}

		const_it lower_bound (const key_type& key) const{
			const_it start = begin();

			for (; start != end() ; start++) {
				if ((*start).first >= key)
					return start;
			}

			return end();
		}

		it upper_bound (const key_type& key) {
			it start = begin();

			for (; start != end() ; start++) {
				if ((*start).first > key)
					return start;
			}

			return end();
		}

		const_it upper_bound (const key_type& key) const{
			const_it start = begin();

			for (; start != end() ; start++) {
				if ((*start).first > key)
					return start;
			}

			return end();
		}

		pair<const_it,const_it> equal_range (const key_type& key) const {
			return (ft::make_pair<const_it, const_it>(lower_bound(key), upper_bound(key)));
		}

		pair<it,it> equal_range (const key_type& key) {
			return (ft::make_pair<it , it>(lower_bound(key), upper_bound(key)));
		}

	};
	// end rb_tree
}

#endif
