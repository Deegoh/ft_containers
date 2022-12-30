#ifndef MAP_HPP
# define MAP_HPP

#include "pair.hpp"
#include <functional>
#include <utility>

//template < class Key,// map::key_type class T,// map::mapped_type class Compare = less<Key>, // map::key_compare class Alloc = allocator<pair<const Key,T> >    // map::allocator_type > class map;


namespace ft {
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> >
	class map {
	public:
		typedef Key					key_type;
		typedef pair<const Key, T>	value_type;
		typedef Compare				key_compare;

	private:
		int _c;

	public:
		map() {}
		~map() {}

	};
}


#endif
