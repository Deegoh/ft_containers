//
// Created by Hajar Sabir on 5/25/22.
//

#ifndef FT_CONTAINERS_REDBLACKTREE_HPP
#define FT_CONTAINERS_REDBLACKTREE_HPP

//Include stl
#include <memory>

//Include fts
#include "utility.hpp"
#include "iterator.hpp"

// https://brilliant.org/wiki/red-black-tree/
// https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

namespace ft {
	// Colours struct
	enum Color {
		RED,
		BLACK,
		GREY
	};

	// Node Class
	template <class T>
	class Node{
	public:
		typedef	T		value_type;
		typedef Node<T>	*node_pointer;

		value_type		data;
		Color			color;
		node_pointer	parent, right, left;

		Node(const value_type &data = value_type(), Color color = RED) :
			data(data), color(color), parent(NULL), right(NULL), left(NULL) {}
		Node(const Node &other, const value_type &data) :
			data(data), color(other.color), parent(other.parent), right(other.right), left(other.left) {}
		~Node() {}

		bool isRoot() { return !parent; };

		bool isLeft() { return parent && parent->left == this; };

		bool isRight() { return parent && parent->right == this; };

		bool isRed() { return color == RED; };

		bool isBlack() { return color == BLACK; };

		bool isGrey() { return color == GREY; };

		node_pointer sibling() {
			if (isRoot())
				return NULL;
			if (isLeft())
				return parent->right;
			else
				return parent->left;
		};

		node_pointer uncle() {
			if (isRoot())
				return NULL;
			return parent->getSibling();
		};

		node_pointer grandparent() {
			if (isRoot())
				return NULL;
			return parent->parent;
		};

	}; // End of Node class

	template<class T, class Compare = ft::less<T>, bool isConst = false>
	class TreeIterators {
	public:
		typedef	T															iterator_type;
		typedef	typename iterator_traits<iterator_type>::value_type			value_type;
		typedef	typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef	typename iterator_traits<iterator_type>::pointer			pointer;
		typedef	typename iterator_traits<iterator_type>::reference			reference;
		typedef	typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef	Node<value_type>											*node_pointer;

	protected:
		node_pointer	ptr;
		Compare			compare;

	public:
		TreeIterators() : ptr(NULL) {}
		TreeIterators(node_pointer ptr) : ptr(ptr) {}
		TreeIterators(const Node<value_type> *ptr) : ptr(const_cast<node_pointer>(ptr)) {}
		template<class U>
		TreeIterators(const TreeIterators<U, Compare> &other) : ptr(const_cast<node_pointer>(other.base())) {}
		~TreeIterators() {}

		reference operator*() { return ptr->data; }
		pointer operator->() { return &ptr->data; }
		reference operator*() const { return ptr->data; }
		pointer operator->() const { return &ptr->data; }

		TreeIterators &operator++() {
			if (ptr->right) {
				ptr = ptr->right;
				while (ptr->left)
					ptr = ptr->left;
			} else {
				while (ptr->parent) {
					if (!ptr->isGrey() && !compare(ptr->parent->data, ptr->data) && ptr->parent->data != ptr->data) {
						ptr = ptr->parent;
						return (*this);
					}
					ptr = ptr->parent;
				}
			}
			return *this;

		}

		TreeIterators operator++(int) {
			TreeIterators tmp = *this;
			++*this;
			return tmp;
		}

		TreeIterators &operator--() {
			if (ptr->left) {
				ptr = ptr->left;
				while (ptr->right && !ptr->right->isGrey())
					ptr = ptr->right;
			} else {
				while (ptr->parent) {
					if (ptr->isGrey() || compare(ptr->parent->data, ptr->data)) {
						ptr = ptr->parent;
						return *this;
					}
					ptr = ptr->parent;
				}
			}
			return *this;
		}

		TreeIterators operator--(int) {
			TreeIterators tmp = *this;
			--*this;
			return tmp;
		}

		template<class U>
		bool operator==(const U &other) { return ptr == other.base(); }

		template<class U>
		bool operator!=(const U &other) { return ptr != other.base(); }

		node_pointer base() { return ptr; }

		node_pointer base() const { return ptr; }

		Compare comparator() { return compare; }

	}; // End of TreeIterators class

	// Red Black Tree Class
	template<class T, class Compare = std::less<Node<T> >, class Allocator = std::allocator<Node<T> > >
	class Tree {
	public:
		typedef	T			value_type;
		typedef Allocator	allocator_type;
		typedef	size_t		size_type;
		typedef	Node<T>		node_type;
		typedef node_type	*node_pointer;

	private:
		node_pointer	_root;
		allocator_type	_alloc;
		Compare			_compare;
		node_pointer	_end;
		node_pointer	_start;

	protected:
		Color	getColor(node_pointer node) {
			if (node == NULL)
				return BLACK;
			return node->color;
		}

		void	setColor(node_pointer node, Color color) {
			if (node == NULL)
				return;
			node->color = color;
		}
    // Rotates
		void leftRotate(node_pointer node) {
			node_pointer right_child = node->right;
			node->right = right_child->left;

			if (node->right != NULL)
				node->right->parent = node;
			right_child->parent = node->parent;
			if (node->parent == NULL)
				_root = right_child;
			else if (node == node->parent->left)
				node->parent->left = right_child;
			else
				node->parent->right = right_child;
			right_child->left = node;
			node->parent = right_child;
		}

		void rightRotate(node_pointer node) {
			node_pointer left_child = node->left;
			node->left = left_child->right;

			if (node->left != NULL)
				node->left->parent = node;
			left_child->parent = node->parent;
			if (node->parent == NULL)
				_root = left_child;
			else if (node == node->parent->left)
				node->parent->left = left_child;
			else
				node->parent->right = left_child;
			left_child->right = node;
			node->parent = left_child;
		}


		node_pointer maxValueNode(node_pointer node) {
			node_pointer ptr = node;
			while (ptr->right != NULL && !ptr->isGrey())
				ptr = ptr->right;
			return ptr;
		}

		size_type getBlackHeight(node_pointer node) {
			size_type height = 0;
			while (node != NULL) {
				if (getColor(node) == BLACK)
					height++;
				node = node->left;
			}
			return height;
		}

		// The read-only operations, such as search or tree traversal,
		// do not affect any of the requirements. On the other hand,
		// the modifying operations insert and delete easily maintain requirements 1 and 2,
		// but with respect to the other requirements some extra effort has to be taken,
		// in order to avoid the introduction of a violation of requirement 3,
		// called a red-violation, or of requirement 4, called a black-violation.
		void	fixInsertViolation(node_pointer node) {
			node_pointer parent = NULL;
			node_pointer grandParent = NULL;
			while (node != _root && getColor(node) == RED && getColor(node->parent) == RED) {
				parent = node->parent;
				grandParent = parent->parent;
				if (parent == grandParent->left) {
					node_pointer uncle = grandParent->right;
					if (getColor(uncle) == RED) {
						setColor(uncle, BLACK);
						setColor(parent, BLACK);
						setColor(grandParent, RED);
						node = grandParent;
					} else {
						if (node == parent->right) {
							leftRotate(parent);
							node = parent;
							parent = node->parent;
						}
						rightRotate(grandParent);
						std::swap(parent->color, grandParent->color);
						node = parent;
					}
				} else {
					node_pointer uncle = grandParent->left;
					if (getColor(uncle) == RED) {
						setColor(uncle, BLACK);
						setColor(parent, BLACK);
						setColor(grandParent, RED);
						node = grandParent;
					} else {
						if (node == parent->left) {
							rightRotate(parent);
							node = parent;
							parent = node->parent;
						}
						leftRotate(grandParent);
						std::swap(parent->color, grandParent->color);
						node = parent;
					}
				}
			}
		setColor(_root, BLACK);
    }

    node_pointer	insertNode(node_pointer root, node_pointer node) {
		if (root == NULL || root->isGrey())
			return node;
		if (_compare(node->data, root->data)) { // if the node is smaller than the root
			root->left = insertNode(root->left, node);
			root->left->parent = root;
		} else if (!_compare(node->data, root->data)) {
			root->right = insertNode(root->right, node);
			root->right->parent = root;
		}
		return root;
	}

	node_pointer	minNode(node_pointer node) {
		node_pointer ptr = node;
		while (ptr->left != NULL && !ptr->isGrey())
			ptr = ptr->left;
		return ptr;
	}

	void	fixDependencies(node_pointer node) {
		if (node->left)
			node->left->parent = node;
		if (node->right)
			node->right->parent = node;
	}

	node_pointer	*selfParentPtr(node_pointer node) {
		if (!node->parent)
			return &_root;
		else if (node->isLeft())
			return &node->parent->left;
		else if (node->isRight())
			return &node->parent->right;
		throw std::exception();
	}

	void	swapNode(node_pointer lhs, node_pointer rhs) {
		*selfParentPtr(lhs) = rhs;
		*selfParentPtr(rhs) = lhs;
		std::swap(lhs->parent, rhs->parent);
		std::swap(lhs->left, rhs->left);
		std::swap(lhs->right, rhs->right);
		std::swap(lhs->color, rhs->color);
		fixDependencies(lhs);
		fixDependencies(rhs);
	}

	node_pointer swapNodeWithChild(node_pointer a, node_pointer b) {
		if (b->parent != a) throw std::exception();
		if (a->left && a->right) throw std::exception();
		if (!a->left && !a->right) throw std::exception();
		b->parent = a->parent;
		*selfParentPtr(a) = b;
		return b;
	}

		void fixDeleteViolation(node_pointer node) {
			if (node->parent) {							// case 1
				if (node->sibling() && node->sibling()->color == RED) 		// case 2
				{
					node->parent->color = RED;
					node->sibling()->color = BLACK;
					if (node->isLeft())
						leftRotate(node->parent);
					else
						rightRotate(node->parent);
				}
				if (node->parent->color == BLACK && node->sibling() &&		// case 3
					node->sibling()->color == BLACK &&
					(!node->sibling()->left || node->sibling()->left->color == BLACK) &&
					((!node->sibling()->right || node->sibling()->right->isGrey()) || node->sibling()->right->color == BLACK))
				{
					node->sibling()->color = RED;
					fixDeleteViolation(node->parent);
				}
				else if (node->parent->color == RED && node->sibling() &&		// case 4
						 node->sibling()->color == BLACK &&
						 (!node->sibling()->left || node->sibling()->left->color == BLACK) &&
						 ((!node->sibling()->right || node->sibling()->right->isGrey()) || node->sibling()->right->color == BLACK))
				{
					node->sibling()->color = RED;
					node->parent->color = BLACK;
				}
				else if (node->isLeft() && node->sibling() &&				// case 5
						 node->sibling()->color == BLACK &&
						 node->sibling()->left && node->sibling()->left->color == RED &&
						 ((!node->sibling()->right || node->sibling()->right->isGrey()) || node->sibling()->right->color == BLACK))
				{
					node->sibling()->color = RED;
					node->sibling()->left->color = BLACK;
					rightRotate(node->sibling());
				}
				else if (node->isRight() && node->sibling() &&			// still case 5
						 node->sibling()->color == BLACK &&
						 node->sibling()->right && !node->sibling()->right->isGrey() && node->sibling()->right->color == RED &&
						 (!node->sibling()->left || node->sibling()->left->color == BLACK))
				{
					node->sibling()->color = RED;
					node->sibling()->right->color = BLACK;
					leftRotate(node->sibling());
				}
				if (node->sibling())
					node->sibling()->color = node->parent->color; // case 6
				node->parent->color = BLACK;

				if (node->sibling()) {
					if (node->isLeft()) {
						if (node->sibling()->right && !node->sibling()->right->isGrey())
							node->sibling()->right->color = BLACK;
						leftRotate(node->parent);
					} else {
						if (node->sibling()->right && !node->sibling()->right->isGrey())
							node->sibling()->left->color = BLACK;
						rightRotate(node->parent);
					}
				}
			}
		}

	void	deleteNode(node_pointer node) {
		if (!node->parent && !node->left && (!node->right || node->right->isGrey()))
			_root = NULL;
		else if (!node->left && (!node->right || node->right->isGrey())) {
			if (node->isLeft())
				node->parent->left = NULL;
			else
				node->parent->right = NULL;
		} else if (node->left && node->right && !node->right->isGrey()) {
			node_pointer min = minNode(node->right);
			swapNode(node, min);
			deleteNode(node);
		} else if (!node->left) {
			node = swapNodeWithChild(node, node->right);
			fixDeleteViolation(node);
		} else if (!node->right || node->right->isGrey()) {
			node = swapNodeWithChild(node, node->left);
			fixDeleteViolation(node);
		}
	}

	// Extra
	void destroyTree(node_pointer node) {
		if (!node)
			return;

		destroyTree(node->left);
		destroyTree(node->right);

		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
	}

		void fixSEPoints() {

			if (!_root) {
				_start = _root;
				_end = _root;
				return;
			}

			node_pointer current = _root;
			while (current->left != NULL)
				current = current->left;
			_start = current;

			if (!_end)
				_alloc.construct(_end, node_type(value_type(), GREY));

			current = _root;
			while (current->right != NULL && !current->right->isGrey())
				current = current->right;
			current->right = _end;
			_end->parent = current;
		}

	public:
		Tree(const allocator_type alloc = allocator_type()) :
			_root(NULL), _alloc(alloc), _end(NULL), _start(NULL) {
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node_type(value_type(), GREY));
		}

		~Tree() {
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
		}

		node_pointer	insert(const value_type &data) {
			node_pointer node = _alloc.allocate(1);
			_alloc.construct(node, Node<value_type>(data));
			_root = insertNode(_root, node);
			fixInsertViolation(node);
			fixSEPoints();

			return node;
		}

		void remove(node_pointer node) {
			if (!node) return;
			deleteNode(node);
			fixSEPoints();
		}

		node_pointer find(const value_type &data) {
			node_pointer current = _root;
			while (current != NULL && !current->isGrey()) {
				if (!_compare(data, current->data) && !_compare(current->data, data))
					return current;
				else if (_compare(data, current->data))
					current = current->left;
				else
					current = current->right;
			}
			return _end;
		}

		void clear() {
			destroyTree(_root);
			_start = NULL;
			_end = NULL;
		}

		size_type max_size() { return _alloc.max_size(); }
		node_pointer end() { return _end; }
		node_pointer begin() { return _start; }
		node_pointer root() { return _root; }

	}; // End of Tree class
}

#endif //FT_CONTAINERS_REDBLACKTREE_HPP
