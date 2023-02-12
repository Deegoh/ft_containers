#ifndef RB_TREE_HPP
# define RB_TREE_HPP

//https://web.archive.org/web/20160731195009/http://www.stepanovpapers.com/butler.hpl.hp/stl/stl/TREE.H
//https://cs.brown.edu/people/jwicks/libc++/html_user/stl__tree_8h-source.html
//https://sd.blackball.lv/library/Introduction_to_Algorithms_Third_Edition_(2009).pdf

# include <memory>
# include <functional>
# include "rbt_iterator.hpp"
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

		rb_node(const value_type &pr, color_type color, node_pointer parent, node_pointer left, node_pointer right) :
				value(pr), color(color), parent(parent), left(left), right(right) {}

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
			class Get_key_value, // key of value
			class Compare = std::less<Key>,
			typename Node_Alloc = std::allocator<rb_node<T> > >
	class rb_tree {
	public:
		typedef	Key			key_type;
		typedef	T			value_type;
		typedef	rb_node<T>	node_type;
		typedef node_type*	node_pointer;

		typedef Node_Alloc	alloc_type;
		typedef	Compare		key_compare;
		typedef	size_t		size_type;

	private:
		node_pointer _root;
		size_type _size;
		alloc_type _alloc;
		node_pointer _nil;
		key_compare _comp;

	public:

		// default
		rb_tree(const key_compare &comp = key_compare(),
				const alloc_type &alloc = alloc_type()) :
				_size(0),
				_alloc(alloc),
				_comp(comp) {
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type(), black, NULL, NULL, NULL));
			_root = _nil;
		}

		// dectruct
		~rb_tree() {
			clear_tree(_root);
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}

		node_pointer get_root() const { return (_root); }

		node_pointer get_nil() const { return (_nil); }

		Compare key_comp() const { return (Compare()); }

		bool empty() const { return (_size == 0); }

		size_type size() const { return _size; }

		size_type max_size() const { return _alloc.max_size(); }

		// insert/erase

		node_pointer insert_node(const value_type &value) {
			node_pointer node;
			node = _alloc.allocate(1);
			_alloc.construct(node, node_type(value, red, _nil, _nil, _nil));

			node_pointer y = _nil;
			node_pointer x = _root;

			while (x != _nil)
			{
				y = x;

				if (_comp(Get_key_value()(node->value), Get_key_value()(x->value)))
					x = x->left;
				else if (_comp(Get_key_value()(x->value), Get_key_value()(node->value)))
					x = x->right;
				else
				{
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					return _nil;
				}
			}

			node->parent = y;

			if (y == _nil)
				this->_root = node;
			else if (_comp(Get_key_value()(node->value), Get_key_value()(y->value)))
				y->left = node;
			else
				y->right = node;

			this->_size++;

			if (y == _nil)
			{
				node->color = black;
				return (this->_root);
			}

			if (node->parent->parent == _nil)
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

			if (key == Get_key_value()(node->value))
				return (node);

			if (node != _nil)
			{
				if (_comp(key, Get_key_value()(node->value)))
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

		//get node with min value
		node_pointer most_left(node_pointer node) const {
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
		node_pointer most_right(node_pointer node) const {
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

			if (x->parent == _nil)
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

			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;

			y->right = x;
			x->parent = y;
		}

		void transplant(node_pointer u, node_pointer v) {
			if (u->parent == _nil)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void swap(rb_tree &rhs) {
			node_pointer root = rhs._root;
			node_pointer nil = rhs._nil;
			alloc_type alloc = rhs._alloc;
			size_type size = rhs._size;
			key_compare comp = rhs._comp;

			rhs._root = _root;
			rhs._nil = _nil;
			rhs._alloc = _alloc;
			rhs._size = _size;
			rhs._comp = _comp;

			_root = root;
			_nil = nil;
			_alloc = alloc;
			_size = size;
			_comp = comp;
		}
	};
	// end rb_tree
}

#endif
