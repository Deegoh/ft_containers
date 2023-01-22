#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

# include "iterator_traits.hpp"
# include <exception>

namespace ft {

	template<class T,
			class Node,
			class Category = bidirectional_iterator_tag,
			class Distance = std::ptrdiff_t,
			class Pointer = T*,
			class Reference = T&>
	class rbt_iterator : public iterator_traits<iterator<T, Category> > {
	public:
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
		typedef Node*		node_pointer;

	private:
		node_pointer _root;
		node_pointer _current;
		node_pointer _nil;

	public:
		rbt_iterator() : _root(NULL), _current(NULL), _nil(NULL) {}

		rbt_iterator(node_pointer root, node_pointer current, node_pointer nil) :
		_root(root), _current(current), _nil(nil) {}

		rbt_iterator(const rbt_iterator& src) {
			*this = src;
		}

		rbt_iterator& operator=(const rbt_iterator& rhs) {
			if (this != &rhs) {
				_root = rhs._root;
				_current = rhs._current;
				_nil = rhs._nil;
			}
			return (*this);
		}

		~rbt_iterator() {}

		operator rbt_iterator<const T, Node>() const {
			return (rbt_iterator<const T, Node>(_root, _current, _nil));
		}

		bool operator==(const rbt_iterator &rhs) const {
			return (_current == rhs._current);
		}
		bool operator!=(const rbt_iterator &rhs) const {
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

		rbt_iterator& operator++() {
			if (_current != _nil)
				_current = successor(_current);
			return (*this);
		}

		rbt_iterator operator++(int) {
			rbt_iterator tmp = *this;
			++*this;
			return (tmp);
		}

		rbt_iterator& operator--() {
			if (_current != _nil)
				_current = predecessor(_current);
			else
				_current = maximum(_root);
			return (*this);
		}

		rbt_iterator operator--(int) {
			rbt_iterator tmp = *this;
			--*this;
			return (tmp);
		}

		node_pointer base() { return (_current); }

		node_pointer base() const { return (_current); }

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
			return (maximum(node->left));
		else
		{
			node_pointer tmp = node->parent;

			while (tmp != NULL && node == tmp->left)
			{
				node = tmp;
				tmp = tmp->parent;
			}
			return (tmp);
		}
	}

	node_pointer successor(node_pointer node) {
		if (node->right != _nil)
			return (minimum(node->right));
		else
		{
			node_pointer tmp = node->parent;

			while (tmp != NULL && node == tmp->right)
			{
				node = tmp;
				tmp = tmp->parent;
			}

			if (tmp == NULL)
				return (_nil);

			return (tmp);
		}
	}

	};//end iterator
}
#endif
