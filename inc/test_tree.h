#ifndef TEST_TREE_HPP
#define TEST_TREE_HPP

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "pair.hpp"
#include <memory>
#include "comparators.hpp"
#include <type_traits>

namespace ft {

	enum rb_tree_color { red = false, black = true };

	struct rb_tree_node_base
	{
		typedef rb_tree_node_base* base_ptr;
		typedef const rb_tree_node_base* const_base_ptr;

		rb_tree_color	_M_color;
		base_ptr		_M_parent;
		base_ptr		_M_left;
		base_ptr		_M_right;

		static base_ptr _S_minimum(base_ptr __x) {
			while (__x->_M_left != 0) __x = __x->_M_left;
			return __x;
		}

		static const_base_ptr _S_minimum(const_base_ptr __x) {
			while (__x->_M_left != 0) __x = __x->_M_left;
			return __x;
		}

		static base_ptr _S_maximum(base_ptr __x) {
			while (__x->_M_right != 0) __x = __x->_M_right;
			return __x;
		}

		static const_base_ptr _S_maximum(const_base_ptr __x) {
			while (__x->_M_right != 0) __x = __x->_M_right;
			return __x;
		}
	};

	template<typename Value>
	struct rb_tree_node : public rb_tree_node_base
	{
		typedef rb_tree_node<Value>* link_type;
		Value _M_value_field;
	};

	rb_tree_node_base* rb_tree_increment(rb_tree_node_base* __x) {
		if (__x->_M_right != 0)
		{
			__x = __x->_M_right;
			while (__x->_M_left != 0)
				__x = __x->_M_left;
		}
		else
		{
			rb_tree_node_base* __y = __x->_M_parent;
			while (__x == __y->_M_right)
				{
					__x = __y;
					__y = __y->_M_parent;
				}
			if (__x->_M_right != __y)
				__x = __y;
		}
		return __x;
	}

	const rb_tree_node_base* rb_tree_increment(const rb_tree_node_base* __x) {
		return rb_tree_increment(const_cast<rb_tree_node_base*>(__x));
	}

	rb_tree_node_base* rb_tree_decrement(rb_tree_node_base* __x) {
		if (__x->_M_color == red && __x->_M_parent->_M_parent == __x)
			__x = __x->_M_right;
		else if (__x->_M_left != 0)
			{
				rb_tree_node_base* __y = __x->_M_left;
				while (__y->_M_right != 0)
					__y = __y->_M_right;
				__x = __y;
			}
		else
			{
				rb_tree_node_base* __y = __x->_M_parent;
				while (__x == __y->_M_left)
					{
						__x = __y;
						__y = __y->_M_parent;
					}
				__x = __y;
			}
		return __x;
	}

	const rb_tree_node_base* rb_tree_decrement(const rb_tree_node_base* __x) {
		return rb_tree_decrement(const_cast<rb_tree_node_base*>(__x));
	}

	template<typename Tp>
	struct rb_tree_iterator {
		typedef Tp	value_type;
		typedef Tp& reference;
		typedef Tp* pointer;

		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t									difference_type;

		typedef rb_tree_iterator<Tp>				_Self;
		typedef rb_tree_node_base::base_ptr base_ptr;
		typedef rb_tree_node<Tp>*					 link_type;

		rb_tree_iterator() : _M_node( ) {}

		rb_tree_iterator(link_type __x) : _M_node(__x ) {}

		reference operator*() const {
			return static_cast<link_type>(_M_node)->_M_value_field;
		}

		pointer operator->() const {
			return &static_cast<link_type>(_M_node)->_M_value_field;
		}

		_Self& operator++() {
			_M_node = rb_tree_increment(_M_node);
			return *this;
		}

		_Self operator++(int) {
			_Self __tmp = *this;
			_M_node = rb_tree_increment(_M_node);
			return __tmp;
		}

		_Self& operator--() {
			_M_node = rb_tree_decrement(_M_node);
			return *this;
		}

		_Self operator--(int) {
			_Self __tmp = *this;
			_M_node = rb_tree_decrement(_M_node);
			return __tmp;
		}

		bool operator==(const _Self& __x) const
		{ return _M_node == __x._M_node;
	}

		bool operator!=(const _Self& __x) const
		{ return _M_node != __x._M_node;
	}

		base_ptr _M_node;
	};

	template<typename Tp>
	struct rb_tree_const_iterator
	{
		typedef Tp				value_type;
		typedef const Tp& reference;
		typedef const Tp* pointer;

		typedef rb_tree_iterator<Tp> iterator;

		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t									difference_type;

		typedef rb_tree_const_iterator<Tp>				_Self;
		typedef rb_tree_node_base::const_base_ptr base_ptr;
		typedef const rb_tree_node<Tp>*					 link_type;

		rb_tree_const_iterator() : _M_node( ) {
		}

		rb_tree_const_iterator(link_type __x) : _M_node(__x ) {
		}

		rb_tree_const_iterator(const iterator& __it) : _M_node(__it._M_node ) {
		}

		reference operator*() const {
			return static_cast<link_type>(_M_node)->_M_value_field;
		}

		pointer operator->() const {
			return &static_cast<link_type>(_M_node)->_M_value_field;
		}

		_Self& operator++() {
			_M_node = rb_tree_increment(_M_node);
			return *this;
		}

		_Self operator++(int) {
			_Self __tmp = *this;
			_M_node = rb_tree_increment(_M_node);
			return __tmp;
		}

		_Self& operator--() {
			_M_node = rb_tree_decrement(_M_node);
			return *this;
		}

		_Self operator--(int) {
			_Self __tmp = *this;
			_M_node = rb_tree_decrement(_M_node);
			return __tmp;
		}

		bool operator==(const _Self& __x) const {
			return _M_node == __x._M_node;
		}

		bool operator!=(const _Self& __x) const {
			return _M_node != __x._M_node;
		}

		base_ptr _M_node;
	};

	template<typename Value>
	inline bool operator==(const rb_tree_iterator<Value>& __x, const rb_tree_const_iterator<Value>& __y) {
		return __x._M_node == __y._M_node;
	}

	template<typename Value>
	inline bool operator!=(const rb_tree_iterator<Value>& __x, const rb_tree_const_iterator<Value>& __y) {
		return __x._M_node != __y._M_node;
	}


	void rb_tree_rotate_left(rb_tree_node_base* const __x, rb_tree_node_base*& __root) {
		rb_tree_node_base* const __y = __x->_M_right;
		__x->_M_right = __y->_M_left;

		if (__y->_M_left !=0)
			__y->_M_left->_M_parent = __x;

		__y->_M_parent = __x->_M_parent;

		if (__x == __root)
			__root = __y;
		else if (__x == __x->_M_parent->_M_left)
			__x->_M_parent->_M_left = __y;
		else
			__x->_M_parent->_M_right = __y;

		__y->_M_left = __x;
		__x->_M_parent = __y;
	}

	void rb_tree_rotate_right(rb_tree_node_base* const __x, rb_tree_node_base*& __root) {
		rb_tree_node_base* const __y = __x->_M_left;

		__x->_M_left = __y->_M_right;
		if (__y->_M_right != 0)
			__y->_M_right->_M_parent = __x;
		__y->_M_parent = __x->_M_parent;

		if (__x == __root)
			__root = __y;
		else if (__x == __x->_M_parent->_M_right)
			__x->_M_parent->_M_right = __y;
		else
			__x->_M_parent->_M_left = __y;
		__y->_M_right = __x;
		__x->_M_parent = __y;
	}

	void rb_tree_insert_and_rebalance(const bool __insert_left,
										rb_tree_node_base* __x,
										rb_tree_node_base* __p,
										rb_tree_node_base& __header) {
		rb_tree_node_base *& __root = __header._M_parent;

		// Initialize fields in new node to insert.
		__x->_M_parent = __p;
		__x->_M_left = 0;
		__x->_M_right = 0;
		__x->_M_color = red;

		// Insert.
		// Make new node child of parent and maintain root, leftmost and
		// rightmost nodes.
		// N.B. First node is always inserted left.
		if (__insert_left)
		{
			__p->_M_left = __x; // also makes leftmost = __x when __p == &__header

			if (__p == &__header)
			{
				__header._M_parent = __x;
				__header._M_right = __x;
			}
			else if (__p == __header._M_left)
				__header._M_left = __x; // maintain leftmost pointing to min node
		}
		else
		{
			__p->_M_right = __x;

			if (__p == __header._M_right)
				__header._M_right = __x; // maintain rightmost pointing to max node
		}
		// Rebalance.
		while (__x != __root && __x->_M_parent->_M_color == red)
		{
		rb_tree_node_base* const __xpp = __x->_M_parent->_M_parent;

			if (__x->_M_parent == __xpp->_M_left)
			{
				rb_tree_node_base* const __y = __xpp->_M_right;
				if (__y && __y->_M_color == red) {
					__x->_M_parent->_M_color = black;
					__y->_M_color = black;
					__xpp->_M_color = red;
					__x = __xpp;
				}
				else
				{
					if (__x == __x->_M_parent->_M_right)
					{
						__x = __x->_M_parent;
						rb_tree_rotate_left(__x, __root);
					}
					__x->_M_parent->_M_color = black;
					__xpp->_M_color = red;
					rb_tree_rotate_right(__xpp, __root);
				}
			}
			else
			{
				rb_tree_node_base* const __y = __xpp->_M_left;
				if (__y && __y->_M_color == red)
				{
					__x->_M_parent->_M_color = black;
					__y->_M_color = black;
					__xpp->_M_color = red;
					__x = __xpp;
				}
				else
				{
					if (__x == __x->_M_parent->_M_left)
					{
						__x = __x->_M_parent;
						rb_tree_rotate_right(__x, __root);
					}
					__x->_M_parent->_M_color = black;
					__xpp->_M_color = red;
					rb_tree_rotate_left(__xpp, __root);
				}
			}
		}
		__root->_M_color = black;
	}

	rb_tree_node_base* rb_tree_rebalance_for_erase(rb_tree_node_base* const __z, rb_tree_node_base& __header) {
		rb_tree_node_base *& __root = __header._M_parent;
		rb_tree_node_base *& __leftmost = __header._M_left;
		rb_tree_node_base *& __rightmost = __header._M_right;
		rb_tree_node_base* __y = __z;
		rb_tree_node_base* __x = 0;
		rb_tree_node_base* __x_parent = 0;

		if (__y->_M_left == 0)// __z has at most one non-null child. y == z.
		{
			__x = __y->_M_right;         // __x might be null.
		}
		else
		{
			if (__y->_M_right == 0)// __z has exactly one non-null child. y == z.
			{
				__x = __y->_M_left;// __x is not null.
			}
			else // __z has two non-null children.	Set __y to
			{
				__y = __y->_M_right;//	 __z's successor.	__x might be null.
				while (__y->_M_left != 0)
					__y = __y->_M_left;
				__x = __y->_M_right;
			}
		}

		if (__y != __z)
		{
			// relink y in place of z.	y is z's successor
			__z->_M_left->_M_parent = __y;
			__y->_M_left = __z->_M_left;
			if (__y != __z->_M_right)
			{
				__x_parent = __y->_M_parent;
				if (__x)
				{
					__x->_M_parent = __y->_M_parent;
				}
				__y->_M_parent->_M_left = __x;	 // __y must be a child of _M_left
				__y->_M_right = __z->_M_right;
				__z->_M_right->_M_parent = __y;
			}
			else
			{
				__x_parent = __y;
			}

			if (__root == __z)
				__root = __y;
			else if (__z->_M_parent->_M_left == __z)
				__z->_M_parent->_M_left = __y;
			else
				__z->_M_parent->_M_right = __y;

			__y->_M_parent = __z->_M_parent;
			std::swap(__y->_M_color, __z->_M_color);
			__y = __z;
			// __y now points to node to be actually deleted
		}
		else
		{// __y == __z
			__x_parent = __y->_M_parent;
			if (__x)
				__x->_M_parent = __y->_M_parent;

			if (__root == __z)
				__root = __x;
			else
			{
				if (__z->_M_parent->_M_left == __z)
					__z->_M_parent->_M_left = __x;
				else
					__z->_M_parent->_M_right = __x;
			}

			if (__leftmost == __z)
			{
				if (__z->_M_right == 0)                // __z->_M_left must be null also
					__leftmost = __z->_M_parent;
					// makes __leftmost == _M_header if __z == __root
				else
					__leftmost = rb_tree_node_base::_S_minimum(__x);
			}
			if (__rightmost == __z) {
				if (__z->_M_left == 0) // __z->_M_right must be null also
					__rightmost = __z->_M_parent;
					// makes __rightmost == _M_header if __z == __root
				else // __x == __z->_M_left
					__rightmost = rb_tree_node_base::_S_maximum(__x);
			}
		}

		if (__y->_M_color != red) {
			while (__x != __root && (__x == 0 || __x->_M_color == black))
			{
				if (__x == __x_parent->_M_left) {
					rb_tree_node_base *__w = __x_parent->_M_right;
					if (__w->_M_color == red) {
						__w->_M_color = black;
						__x_parent->_M_color = red;
						rb_tree_rotate_left(__x_parent, __root);
						__w = __x_parent->_M_right;
					}
					if ((__w->_M_left == 0 || __w->_M_left->_M_color == black) &&
						(__w->_M_right == 0 || __w->_M_right->_M_color == black)) {
						__w->_M_color = red;
						__x = __x_parent;
						__x_parent = __x_parent->_M_parent;
					} else {
						if (__w->_M_right == 0 || __w->_M_right->_M_color == black) {
							__w->_M_left->_M_color = black;
							__w->_M_color = red;
							rb_tree_rotate_right(__w, __root);
							__w = __x_parent->_M_right;
						}

						__w->_M_color = __x_parent->_M_color;
						__x_parent->_M_color = black;

						if (__w->_M_right)
							__w->_M_right->_M_color = black;

						rb_tree_rotate_left(__x_parent, __root);
						break;
					}
				}
				else
				{
					// same as above, with _M_right <-> _M_left.
					rb_tree_node_base *__w = __x_parent->_M_left;
					if (__w->_M_color == red)
					{
						__w->_M_color = black;
						__x_parent->_M_color = red;
						rb_tree_rotate_right(__x_parent, __root);
						__w = __x_parent->_M_left;
					}
					if ((__w->_M_right == 0 || __w->_M_right->_M_color == black) &&
						(__w->_M_left == 0 || __w->_M_left->_M_color == black))
					{
						__w->_M_color = red;
						__x = __x_parent;
						__x_parent = __x_parent->_M_parent;
					}
					else
					{
						if (__w->_M_left == 0 || __w->_M_left->_M_color == black)
						{
							__w->_M_right->_M_color = black;
							__w->_M_color = red;
							rb_tree_rotate_left(__w, __root);
							__w = __x_parent->_M_left;
						}

						__w->_M_color = __x_parent->_M_color;
						__x_parent->_M_color = black;

						if (__w->_M_left)
							__w->_M_left->_M_color = black;

						rb_tree_rotate_right(__x_parent, __root);
						break;
					}
				}
			}

			if (__x)
				__x->_M_color = black;
		}
		return __y;
	}


	template<typename _Key, typename Value, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<Value> >
	class rb_tree
	{
		typedef typename _Alloc::template rebind<rb_tree_node<Value> >::other _Node_allocator;

	protected:
		typedef rb_tree_node_base* base_ptr;
		typedef const rb_tree_node_base* const_base_ptr;

		typedef rb_tree_node<Value> rb_tree_node;

	public:
		typedef _Key key_type;
		typedef Value value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef rb_tree_node* link_type;
		typedef const rb_tree_node* _Constlink_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef _Alloc allocator_type;

		allocator_type get_allocator() const {
			return *static_cast<const _Node_allocator*>(&this->_M_impl);
		}

	protected:
		rb_tree_node* _M_get_node() {
			return _M_impl._Node_allocator::allocate(1);
		}

		void _M_put_node(rb_tree_node* __p) {
			_M_impl._Node_allocator::deallocate(__p, 1);
		}

		link_type _M_create_node(const value_type& __x) {
			link_type __tmp = _M_get_node();
			try {
				get_allocator().construct(&__tmp->_M_value_field, __x);
			}
			catch(...)
			{
				_M_put_node(__tmp);
	//			__throw_exception_again;
			}
			return __tmp;
		}

		link_type _M_clone_node(_Constlink_type __x) {
			link_type __tmp = _M_create_node(__x->_M_value_field);
			__tmp->_M_color = __x->_M_color;
			__tmp->_M_left = 0;
			__tmp->_M_right = 0;
			return __tmp;
		}

		void destroy_node(link_type __p) {
			get_allocator().destroy(&__p->_M_value_field);
			_M_put_node(__p);
		}

	protected:
		template<typename _Key_compare,
					bool _Is_pod_comparator = std::is_pod<_Key_compare>::value>
		struct rb_tree_impl : public _Node_allocator {
			_Key_compare			_M_key_compare;
			rb_tree_node_base		_M_header;
			size_type				 _M_node_count; // Keeps track of size of tree.

			rb_tree_impl(const _Node_allocator& __a = _Node_allocator(),
						const _Key_compare& __comp = _Key_compare())
			: _Node_allocator(__a), _M_key_compare(__comp), _M_node_count(0)
			{
				this->_M_header._M_color = red;
				this->_M_header._M_parent = 0;
				this->_M_header._M_left = &this->_M_header;
				this->_M_header._M_right = &this->_M_header;
			}
		};

		// Specialization for _Comparison types that are not capable of
		// being base classes / super classes.

		template<typename _Key_compare>
		struct rb_tree_impl<_Key_compare, true> : public _Node_allocator {
			_Key_compare			_M_key_compare;
			rb_tree_node_base		_M_header;
			size_type				 _M_node_count; // Keeps track of size of tree.

			rb_tree_impl(const _Node_allocator& __a = _Node_allocator(),
						const _Key_compare& __comp = _Key_compare())
			: _Node_allocator(__a), _M_key_compare(__comp), _M_node_count(0)
			{
				this->_M_header._M_color = red;
				this->_M_header._M_parent = 0;
				this->_M_header._M_left = &this->_M_header;
				this->_M_header._M_right = &this->_M_header;
			}
		};

		rb_tree_impl<_Compare> _M_impl;

	protected:
		base_ptr& _M_root() {
			return this->_M_impl._M_header._M_parent;
		}

		const_base_ptr _M_root() const {
			return this->_M_impl._M_header._M_parent;
		}

		base_ptr& _M_leftmost( ) {
			return this->_M_impl._M_header._M_left;
		}

		const_base_ptr _M_leftmost() const {
			return this->_M_impl._M_header._M_left;
		}

		base_ptr& _M_rightmost( ) {
			return this->_M_impl._M_header._M_right;
		}

		const_base_ptr _M_rightmost() const {
			return this->_M_impl._M_header._M_right;
		}

		link_type _M_begin( ) {
			return static_cast<link_type>(this->_M_impl._M_header._M_parent);
		}

		_Constlink_type _M_begin() const {
			return static_cast<_Constlink_type>(this->_M_impl._M_header._M_parent);
		}

		link_type _M_end( ) {
			return static_cast<link_type>(&this->_M_impl._M_header);
		}

		_Constlink_type _M_end() const {
			return static_cast<_Constlink_type>(&this->_M_impl._M_header);
		}

		static const_reference _S_value(_Constlink_type __x ) {
			return __x->_M_value_field;
		}

		static const _Key& _S_key(_Constlink_type __x ) {
			return _KeyOfValue()(_S_value(__x));
		}

		static link_type _S_left(base_ptr __x ) {
			return static_cast<link_type>(__x->_M_left);
		}

		static _Constlink_type _S_left(const_base_ptr __x ) {
			return static_cast<_Constlink_type>(__x->_M_left);
		}

		static link_type _S_right(base_ptr __x ) {
			return static_cast<link_type>(__x->_M_right);
		}

		static _Constlink_type _S_right(const_base_ptr __x ) {
			return static_cast<_Constlink_type>(__x->_M_right);
		}

		static const_reference _S_value(const_base_ptr __x ) {
			return static_cast<_Constlink_type>(__x)->_M_value_field;
		}

		static const _Key& _S_key(const_base_ptr __x ) {
			return _KeyOfValue()(_S_value(__x));
		}

		static base_ptr _S_minimum(base_ptr __x ) {
			return rb_tree_node_base::_S_minimum(__x);
		}

		static const_base_ptr _S_minimum(const_base_ptr __x ) {
			return rb_tree_node_base::_S_minimum(__x);
		}

		static base_ptr _S_maximum(base_ptr __x ) {
			return rb_tree_node_base::_S_maximum(__x);
		}

		static const_base_ptr _S_maximum(const_base_ptr __x ) {
			return rb_tree_node_base::_S_maximum(__x);
		}

	public:
		typedef rb_tree_iterator<value_type>			 iterator;
		typedef rb_tree_const_iterator<value_type> const_iterator;

		typedef ft::reverse_iterator<iterator>			 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		iterator _M_insert(base_ptr __x, base_ptr __y, const value_type& __v);

		link_type _M_copy(_Constlink_type __x, link_type __p);

		void _M_erase(link_type __x);

	public:
		// allocation/deallocation
		rb_tree() {}

		rb_tree(const _Compare& __comp) : _M_impl(allocator_type(), __comp) { }

		rb_tree(const _Compare& __comp, const allocator_type& __a)
			: _M_impl(__a, __comp) { }

		rb_tree(const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x)
			: _M_impl(__x.get_allocator(), __x._M_impl._M_key_compare)
		{
			if (__x._M_root() != 0)
			{
				_M_root() = _M_copy(__x._M_begin(), _M_end());
				_M_leftmost() = _S_minimum(_M_root());
				_M_rightmost() = _S_maximum(_M_root());
				_M_impl._M_node_count = __x._M_impl._M_node_count;
			}
		}

		~rb_tree() {
			_M_erase(_M_begin());
		}

		rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& operator=(const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x);

		// Accessors.
		_Compare key_comp() const {
			return _M_impl._M_key_compare;
		}

		iterator begin( ) {
			return static_cast<link_type>(this->_M_impl._M_header._M_left);
		}

		const_iterator begin() const {
			return static_cast<_Constlink_type>(this->_M_impl._M_header._M_left);
		}

		iterator end( ) {
			return static_cast<link_type>(&this->_M_impl._M_header);
		}

		const_iterator end() const {
			return static_cast<_Constlink_type>(&this->_M_impl._M_header);
		}

		reverse_iterator rbegin( ) {
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}

		reverse_iterator rend( ) {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		bool empty() const {
			return _M_impl._M_node_count == 0;
		}

		size_type size() const {
			return _M_impl._M_node_count;
		}

		size_type max_size() const {
			return size_type(-1);
		}

		void swap(rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __t);

		// Insert/erase.
		pair<iterator,bool> insert_unique(const value_type& __x);

		iterator insert_equal(const value_type& __x);

		iterator insert_unique(iterator __position, const value_type& __x);

		iterator insert_equal(iterator __position, const value_type& __x);

		template<typename _InputIterator>
		void insert_unique(_InputIterator __first, _InputIterator __last);

		template<typename _InputIterator>
		void insert_equal(_InputIterator __first, _InputIterator __last);

		void erase(iterator __position);

		size_type erase(const key_type& __x);

		void erase(iterator __first, iterator __last);

		void erase(const key_type* __first, const key_type* __last);

		void clear() {
			_M_erase(_M_begin());
			_M_leftmost() = _M_end();
			_M_root() = 0;
			_M_rightmost() = _M_end();
			_M_impl._M_node_count = 0;
		}

		// Set operations.
		iterator find(const key_type& __x);

		const_iterator find(const key_type& __x) const;

		size_type count(const key_type& __x) const;

		iterator lower_bound(const key_type& __x);

		const_iterator lower_bound(const key_type& __x) const;

		iterator upper_bound(const key_type& __x);

		const_iterator upper_bound(const key_type& __x) const;

		pair<iterator,iterator> equal_range(const key_type& __x);

		pair<const_iterator, const_iterator> equal_range(const key_type& __x) const;
	};

	template<typename _Key,
			 typename Value,
			 typename _KeyOfValue,
			 typename _Compare,
			 typename _Alloc>
	inline bool operator==(const rb_tree<_Key, Value,_KeyOfValue, _Compare, _Alloc>& __x,
			const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __y) {
		return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
	inline bool operator<(const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x,
			const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __y) {
		return std::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
	inline bool operator!=(const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x,
			const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __y) {
		return !(__x == __y);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
	inline bool operator>(const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x,
			const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __y) {
		return __y < __x;
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
	inline bool operator<=(const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x,
			const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __y) {
		return !(__y < __x);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
	inline bool operator>=(const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x,
			const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __y) {
		return !(__x < __y);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
					 typename _Compare, typename _Alloc>
	inline void swap(rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x,
					 rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __y) {
		__x.swap(__y);
	}

	template<typename _Key,
			typename Value,
			typename _KeyOfValue,
			typename _Compare,
			typename _Alloc>
		rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>&
		rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
		operator=(const rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __x) {
			if (this != &__x)
			{
				// Note that _Key may be a constant type.
				clear();
				_M_impl._M_key_compare = __x._M_impl._M_key_compare;
				if (__x._M_root() != 0)
				{
					_M_root() = _M_copy(__x._M_begin(), _M_end());
					_M_leftmost() = _S_minimum(_M_root());
					_M_rightmost() = _S_maximum(_M_root());
					_M_impl._M_node_count = __x._M_impl._M_node_count;
				}
			}
			return *this;
		}

	template<typename _Key,
			typename Value,
			typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::iterator
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
	_M_insert(base_ptr __x, base_ptr __p, const Value& __v) {
		link_type __z = _M_create_node(__v);
		bool __insert_left;

		__insert_left = __x != 0 || __p == _M_end() || _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__p));

		rb_tree_insert_and_rebalance(__insert_left, __z, __p, this->_M_impl._M_header);
		++_M_impl._M_node_count;
		return iterator(__z);
	}

	template<typename _Key,
			typename Value,
			typename _KeyOfValue,
			typename _Compare,
			typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::iterator
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>:: insert_equal(const Value& __v)
	{
		link_type __x = _M_begin();
		link_type __y = _M_end();
		while (__x != 0)
		{
			__y = __x;
			__x = _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__x)) ?
					_S_left(__x) : _S_right(__x);
		}
		return _M_insert(__x, __y, __v);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
		void rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
		swap(rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>& __t) {
			if (_M_root() == 0)
			{
				if (__t._M_root() != 0)
				{
					_M_root() = __t._M_root();
					_M_leftmost() = __t._M_leftmost();
					_M_rightmost() = __t._M_rightmost();
							_M_root()->_M_parent = _M_end();

					__t._M_root() = 0;
					__t._M_leftmost() = __t._M_end();
					__t._M_rightmost() = __t._M_end();
				}
			}
			else if (__t._M_root() == 0)
			{
				__t._M_root() = _M_root();
				__t._M_leftmost() = _M_leftmost();
				__t._M_rightmost() = _M_rightmost();
				__t._M_root()->_M_parent = __t._M_end();

				_M_root() = 0;
				_M_leftmost() = _M_end();
				_M_rightmost() = _M_end();
			}
			else
			{
				std::swap(_M_root(),__t._M_root());
				std::swap(_M_leftmost(),__t._M_leftmost());
				std::swap(_M_rightmost(),__t._M_rightmost());

				_M_root()->_M_parent = _M_end();
				__t._M_root()->_M_parent = __t._M_end();
			}
			// No need to swap header's color as it does not change.
			std::swap(this->_M_impl._M_node_count, __t._M_impl._M_node_count);
			std::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);
		}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
		pair<typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::iterator, bool>
		rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
		insert_unique(const Value& __v) {
			link_type __x = _M_begin();
			link_type __y = _M_end();
			bool __comp = true;
			while (__x != 0)
			{
				__y = __x;
				__comp = _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__x));
				__x = __comp ? _S_left(__x) : _S_right(__x);
			}
			iterator __j = iterator(__y);
			if (__comp) {
				if (__j == begin())
					return pair<iterator, bool>(_M_insert(__x, __y, __v), true);
				else
					--__j;
			}
			if (_M_impl._M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__v)))
				return pair<iterator,bool>(_M_insert(__x, __y, __v), true);
			return pair<iterator,bool>(__j, false);
		}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
		typename rb_tree<_Key, Value, _KeyOfValue, _Compare, _Alloc>::iterator
		rb_tree<_Key, Value, _KeyOfValue, _Compare, _Alloc>::
		insert_unique(iterator __position, const Value& __v) {
			if (__position._M_node == _M_leftmost())
			{
				// begin()
				if (size() > 0 && _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node)))
					return _M_insert(__position._M_node, __position._M_node, __v);
				// First argument just needs to be non-null.
				else
					return insert_unique(__v).first;
			}
			else if (__position._M_node == _M_end())
			{
				// end()
				if (_M_impl._M_key_compare(_S_key(_M_rightmost()), _KeyOfValue()(__v)))
					return _M_insert(0, _M_rightmost(), __v);
				else
					return insert_unique(__v).first;
			}
			else
			{
				iterator __before = __position;
				--__before;
				if (_M_impl._M_key_compare(_S_key(__before._M_node), _KeyOfValue()(__v))
						&& _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node)))
				{
					if (_S_right(__before._M_node) == 0)
						return _M_insert(0, __before._M_node, __v);
					else
						return _M_insert(__position._M_node, __position._M_node, __v);
					// First argument just needs to be non-null.
				}
				else
					return insert_unique(__v).first;
			}
		}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
		typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::iterator
		rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
		insert_equal(iterator __position, const Value& __v) {
			if (__position._M_node == _M_leftmost())
			{
				// begin()
				if (size() > 0
						&& !_M_impl._M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)))
					return _M_insert(__position._M_node, __position._M_node, __v);
				// first argument just needs to be non-null
				else
					return insert_equal(__v);
			}
			else if (__position._M_node == _M_end())
			{
				// end()
				if (!_M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(_M_rightmost())))
					return _M_insert(0, _M_rightmost(), __v);
				else
					return insert_equal(__v);
			}
			else
			{
				iterator __before = __position;
				--__before;
				if (!_M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__before._M_node))
						&& !_M_impl._M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)))
					{
						if (_S_right(__before._M_node) == 0)
							return _M_insert(0, __before._M_node, __v);
						else
							return _M_insert(__position._M_node, __position._M_node, __v);
						// First argument just needs to be non-null.
					}
				else
					return insert_equal(__v);
			}
		}

	template<typename _Key, typename Value, typename _KoV,
			typename _Cmp, typename _Alloc>
	template<class _II>
	void rb_tree<_Key,Value,_KoV,_Cmp,_Alloc>:: insert_equal(_II __first, _II __last) {
		for ( ; __first != __last; ++__first)
			insert_equal(*__first);
	}

	template<typename _Key, typename Value, typename _KoV,
			typename _Cmp, typename _Alloc>
	template<class _II>
	void rb_tree<_Key,Value,_KoV,_Cmp,_Alloc>::insert_unique(_II __first, _II __last) {
		for ( ; __first != __last; ++__first)
			insert_unique(*__first);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	inline void rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::erase(iterator __position) {
		link_type __y = static_cast<link_type>(rb_tree_rebalance_for_erase(__position._M_node, this->_M_impl._M_header));
		destroy_node(__y);
		--_M_impl._M_node_count;
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::size_type
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::erase(const _Key& __x) {
		pair<iterator,iterator> __p = equal_range(__x);
		size_type __n = std::distance(__p.first, __p.second);
		erase(__p.first, __p.second);
		return __n;
	}

	template<typename _Key, typename Value, typename _KoV,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key, Value, _KoV, _Compare, _Alloc>::link_type
	rb_tree<_Key,Value,_KoV,_Compare,_Alloc>::
	_M_copy(_Constlink_type __x, link_type __p) {
			// Structural copy.	__x and __p must be non-null.
		link_type __top = _M_clone_node(__x);
		__top->_M_parent = __p;

		try
		{
			if (__x->_M_right)
				__top->_M_right = _M_copy(_S_right(__x), __top);

			__p = __top;
			__x = _S_left(__x);

			while (__x != 0)
			{
				link_type __y = _M_clone_node(__x);
				__p->_M_left = __y;
				__y->_M_parent = __p;
				if (__x->_M_right)
					__y->_M_right = _M_copy(_S_right(__x), __y);
				__p = __y;
				__x = _S_left(__x);
			}
		}
		catch(...)
		{
			_M_erase(__top);
//			__throw_exception_again;
		}
		return __top;
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	void rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::_M_erase(link_type __x) {
		// Erase without rebalancing.
		while (__x != 0)
		{
			_M_erase(_S_right(__x));
			link_type __y = _S_left(__x);
			destroy_node(__x);
			__x = __y;
		}
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	void rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>:: erase(iterator __first, iterator __last) {
		if (__first == begin() && __last == end())
			clear();
		else
			while (__first != __last)
				erase(__first++);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	void rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::erase(const _Key* __first, const _Key* __last) {
		while (__first != __last)
			erase(*__first++);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::iterator
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::find(const _Key& __k) {
		link_type __x = _M_begin(); // Current node.
		link_type __y = _M_end(); // Last node which is not less than __k.

		while (__x != 0)
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		iterator __j = iterator(__y);
		return (__j == end() || _M_impl._M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::const_iterator
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>:: find(const _Key& __k) const {
		_Constlink_type __x = _M_begin(); // Current node.
		_Constlink_type __y = _M_end(); // Last node which is not less than __k.

		while (__x != 0)
		{
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
		}
		const_iterator __j = const_iterator(__y);
		return (__j == end() || _M_impl._M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::size_type
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>:: count(const _Key& __k) const {
		pair<const_iterator, const_iterator> __p = equal_range(__k);
		const size_type __n = std::distance(__p.first, __p.second);
		return __n;
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::iterator
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::lower_bound(const _Key& __k) {
		link_type __x = _M_begin(); // Current node.
		link_type __y = _M_end(); // Last node which is not less than __k.

		while (__x != 0)
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		return iterator(__y);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::const_iterator
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
	lower_bound(const _Key& __k) const {
		_Constlink_type __x = _M_begin(); // Current node.
		_Constlink_type __y = _M_end(); // Last node which is not less than __k.

		while (__x != 0)
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		return const_iterator(__y);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::iterator
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
	upper_bound(const _Key& __k) {
		link_type __x = _M_begin(); // Current node.
		link_type __y = _M_end(); // Last node which is greater than __k.

		while (__x != 0)
			if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		return iterator(__y);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::const_iterator
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
	upper_bound(const _Key& __k) const {
		_Constlink_type __x = _M_begin(); // Current node.
		_Constlink_type __y = _M_end(); // Last node which is greater than __k.

		while (__x != 0)
			if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);

		return const_iterator(__y);
	}

	template<typename _Key, typename Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	inline pair<typename rb_tree<_Key,Value,_KeyOfValue,
		_Compare,_Alloc>::iterator,
		typename rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::iterator>
	rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::
	equal_range(const _Key& __k) {
		return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
	}

	template<typename _Key, typename Value, typename _KoV,
			typename _Compare, typename _Alloc>
	inline pair<typename rb_tree<_Key, Value, _KoV,
		_Compare, _Alloc>::const_iterator,
		typename rb_tree<_Key, Value, _KoV, _Compare, _Alloc>::const_iterator>
	rb_tree<_Key, Value, _KoV, _Compare, _Alloc>::
	equal_range(const _Key& __k) const {
		return pair<const_iterator, const_iterator>(lower_bound(__k), upper_bound(__k));
	}

	unsigned int rb_tree_black_count(const rb_tree_node_base* __node,
									  const rb_tree_node_base* __root) {
		if (__node == 0)
			return 0;
		unsigned int __sum = 0;
		do
		{

			if (__node->_M_color == black)
				++__sum;
			if (__node == __root)
				break;
			__node = __node->_M_parent;
		} while (1);
		return __sum;
	}

//	template<typename _Key, typename Value, typename _KeyOfValue,
//			typename _Compare, typename _Alloc>
//		bool
//		rb_tree<_Key,Value,_KeyOfValue,_Compare,_Alloc>::__rb_verify() const
//		{
//			if (_M_impl._M_node_count == 0 || begin() == end())
//		return _M_impl._M_node_count == 0 && begin() == end()
//					 && this->_M_impl._M_header._M_left == _M_end()
//					 && this->_M_impl._M_header._M_right == _M_end();
//
//			unsigned int __len = rb_tree_black_count(_M_leftmost(), _M_root());
//			for (const_iterator __it = begin(); __it != end(); ++__it)
//		{
//			_Constlink_type __x = static_cast<_Constlink_type>(__it._M_node);
//			_Constlink_type __L = _S_left(__x);
//			_Constlink_type __R = _S_right(__x);
//
//			if (__x->_M_color == red)
//				if ((__L && __L->_M_color == red)
//				|| (__R && __R->_M_color == red))
//					return false;
//
//			if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L)))
//				return false;
//			if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__x)))
//				return false;
//
//			if (!__L && !__R && rb_tree_black_count(__x, _M_root()) != __len)
//				return false;
//		}
//
//			if (_M_leftmost() != rb_tree_node_base::_S_minimum(_M_root()))
//		return false;
//			if (_M_rightmost() != rb_tree_node_base::_S_maximum(_M_root()))
//		return false;
//			return true;
//		}
}
#endif
