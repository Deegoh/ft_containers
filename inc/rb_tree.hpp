#ifndef RB_TREE_HPP
# define RB_TREE_HPP

//https://web.archive.org/web/20160731195009/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/TREE.H
//https://cs.brown.edu/people/jwicks/libstdc++/html_user/stl__tree_8h-source.html
# include <memory>
//# include "random_access_iterator.hpp"
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
		typedef rb_node<T>*			node_pointer;
		typedef const node_pointer	const_node_pointer;

		rb_node(const value_type &data = value_type(), color_type color = red) :
			value(data), color(color), parent(NULL), left(NULL), right(NULL) {}

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
		typedef	Compare		comp_type;
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
			typedef T1				value_type;
//			typedef std::ptrdiff_t	difference_type;
			typedef value_type*		value_pointer;
			typedef value_type&		value_reference;

		private:
			node_pointer _current;
			node_pointer _nil;

		public:
			iterator() : _current(NULL), _nil(NULL) {}
			iterator(node_pointer current, node_pointer nil) : _current(current), _nil(nil){}

			iterator(const iterator& src) {
				*this = src;
			}

			iterator& operator=(const iterator& rhs) {
				if (this != &rhs) {
					_current = rhs._current;
					_nil = rhs._nil;
				}
				return *this;
			}

			~iterator() {}

			operator iterator<const T1>() const {
				return (iterator<const T1>(this->_current));
			}

			bool operator==(const iterator &rhs) const {
				return (_current == rhs._current);
			}
			bool operator!=(const iterator &rhs) const {
				return (_current != rhs._current);
			}

//			friend bool operator==(const iterator &lhs, const iterator &rhs) {
//				return (lhs._current == rhs._current);
//			}
//			friend bool operator!=(const iterator &lhs, const iterator &rhs) {
//				return ((lhs._current != rhs._current));
//			}

			value_reference operator*() const {
				if (_current == NULL)
					throw std::exception();
				return (_current->value);
			}

			value_reference operator*() {
				if (_current == NULL)
					throw std::exception();
				return (_current->value);
			}

			value_pointer operator->() {
				return &_current->value;
			}
			value_pointer operator->() const {
				return &_current->value;
			}

			iterator& operator++() {
				if (this->_current != _nil)
					_current = successor(_current);
				return *this;
			}

			iterator operator++(int) {
				iterator tmp = *this;
				++*this;
				return tmp;
			}

			iterator& operator--() {
				if (this->_current == this->_nil)
					_current = maximum(this->_root);
				else
					this->_ptr = predecessor(this->_current);
				return *this;
			}

			iterator operator--(int) {
				iterator tmp = *this;
				--*this;
				return tmp;
			}

			node_pointer base() { return _current; }

			node_pointer base() const { return _current; }

		protected:
			node_pointer maximum(node_pointer node) {
				while (node->right != this->_nil)
					node = node->right;
				return node;
			}

			node_pointer minimum(node_pointer node) {
				while (node->left != this->_nil)
					node = node->left;
				return node;
			}

			node_pointer predecessor(node_pointer node) {
				if (node->left != this->_nil) { // if the left subtree is not null the predecessor is the right most node is the left subtree
					return maximum(node->left);
				}
				else { // else it is the lowest ancestor of node whose right child is also an ancestor of node
					node_pointer x = node->parent;
					while (x != NULL && node == x->left) {
						node = x;
						x = x->parent;
					}
					return x;
				}
			}

			node_pointer successor(node_pointer node) {
				if (node->right != this->_nil) {
					return minimum(node->right);
				}
				else {
					node_pointer x = node->parent;
					while (x != NULL && node == x->right) {
						node = x;
						x = x->parent;
					}
					if (x == NULL)
						return _nil;
					return x;
				}
			}

		};//end iterator

	public:

//		iterator in tree
		typedef iterator<const value_type>	const_it;
		typedef iterator<value_type>		it;

		// default
		rb_tree() : _size(0) {
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type(), black, NULL, NULL, NULL));
			_root = _nil;
		}

		//copy
		rb_tree(const rb_tree& other) : _root(NULL) {
			*this = other;
		}

		// overload =
		rb_tree& operator=(const rb_tree& rhs) {
			if (this != &rhs) {
				_root = rhs._root;
				_size = rhs._size;
				_alloc = rhs._alloc;
				_nil = rhs._nil;
			}
			return *this;
		}

		// dectruct
		~rb_tree() {
			clear_tree(_root);
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}


		// accessors:

		node_pointer get_root() const {
			return _root;
		}

		node_pointer get_nil() const {
			return _nil;
		}

		Compare key_comp() const { return Compare(); }

		it begin() { return it(most_left(_root), _nil); }

		const_it begin() const { return it(most_left(_root), _nil); }

		it end() { return it(_nil, _nil); }

		const_it end() const { return const_it(_nil, _nil); }

		bool empty() const { return _size == 0; }

		size_type size() const { return _size; }

		size_type max_size() const {
			return _alloc.max_size();
		}

		// insert/erase

		node_pointer InsertNode(const value_type &value) {
			node_pointer node;
			node = _alloc.allocate(1);
			_alloc.construct(node, node_type(value, red, NULL, _nil, _nil));

			node_pointer y = NULL;
			node_pointer x = _root;

			while (x != _nil) // find nodes natural palcement
			{
				y = x;

				if (comp_type()(node->value.first, x->value.first))
					x = x->left;
				else if (!comp_type()(node->value.first, x->value.first))
					x = x->right;
				else { // x->value == value;
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					return _nil;
				}
			}
			node->parent = y;
			if (y == NULL)
				this->_root = node;
			else if (comp_type()(node->value.first, y->value.first))
				y->left = node;
			else
				y->right = node;
			this->_size++;
			if (y == NULL) {
				node->color = black;
				return (this->_root);
			}
			if (node->parent->parent == NULL)
				return node;
			FixInsert(node);
			return node;
		}

		void	FixInsert(node_pointer node) {
			node_pointer x;
			while (node->parent->color == red) {
				if (node->parent == node->parent->parent->right) // parent is gp's right child
				{
					x = node->parent->parent->left; // uncel is left
					if (x->color == red) // if unc is also red
					{
						x->color = black;
						node->parent->color = black;
						node->parent->parent->color = red;
						node = node->parent->parent;
					}
					else {
						if (node == node->parent->left) // node is left child
						{
							node = node->parent;
							right_rotate(node); // new node is old parent
						}
						node->parent->color = black;
						node->parent->parent->color = red;
						left_rotate(node->parent->parent);
					}
				}
				else { // parent id gs's left child (mirror case)
					x = node->parent->parent->right; // uncle
					if (x->color == red) {
						// mirror case
						x->color = black;
						node->parent->color = black;
						node->parent->parent->color = red;
						node = node->parent->parent;
					}
					else {
						if (node == node->parent->right) {
							// mirror case
							node = node->parent;
							left_rotate(node);
						}
						// mirror case
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

	public:
		//get node with min value
		node_pointer most_left(node_pointer &node) { //min value
			if (node == _nil)
				return (_root);

			while (node->left != _nil)
				node = node->left;

			return (node);
		}

		node_pointer most_left() {
			node_pointer tmp = _root;

			if (tmp != _nil)
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

		node_pointer most_right() {
			node_pointer tmp = _root;

			if (tmp == _nil)
				return (_root);

			while (tmp->right != _nil)
				tmp = tmp->right;

			return (tmp);
		}

		node_pointer successor(node_pointer x) {
			if (x->right != NULL) {
				return most_left(x->right);
			}

			node_pointer y = x->parent;
			while (y != NULL && x == y->right) {
				x = y;
				y = y->parent;
			}
			return y;
		}

		node_pointer predecessor(node_pointer x) {
			if (x->left != NULL) {
				return maximum(x->left);
			}

			node_pointer y = x->parent;
			while (y != NULL && x == y->left) {
				x = y;
				y = y->parent;
			}

			return y;
		}

		void clear_tree(node_pointer node) {
			if (node == _nil)
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

			if (y->left != _nil) {
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL) {
				_root = y;
			} else if (x == x->parent->left) {
				x->parent->left = y;
			} else {
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		void right_rotate(node_pointer x) {
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != _nil) {
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL) {
				_root = y;
			} else if (x == x->parent->right) {
				x->parent->right = y;
			} else {
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		void transplant(node_pointer &u, node_pointer &v) {
			if (u->parent == NULL)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

	};
	// end rb_tree
}

#endif
