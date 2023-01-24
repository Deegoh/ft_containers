#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {

	template <class T1, class T2>
	class pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

//		default
		pair() : first(), second() {}

//		copy / move constructor
		template<class U, class V>
		explicit pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

//		initialization
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair(const pair& rhs) : first(rhs.first), second(rhs.second) {}

		operator pair<const T1, T2>() const {
			return (pair<const T1, T2>(this->first, this->second));
		}

//		copy
		pair& operator=(const pair& pr) {
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		};

		friend bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y) {
			return x.first == y.first && x.second == y.second;
		}

		friend bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y) {
			return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
		}

		friend bool operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
			return !(x == y);
		}

		friend bool operator>(const pair<T1, T2>& x, const pair<T1, T2>& y) {
			return y < x;
		}

		friend bool operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
			return !(y < x);
		}

		friend bool operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y) {
			return !(x < y);
		}
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair(const T1& x, const T2& y) {
		return pair<T1, T2>(x, y);
	}

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1& x, T2& y) {
		return pair<T1, T2>(x, y);
	}

	//	select1st
	template<typename Pair>
	struct select1stmap : public std::unary_function<Pair, typename Pair::first_type> {
		const typename Pair::first_type& operator()(const Pair& x) const {
			return x.first;
		}
	};

	template<class T, class Key>
	struct select1stset : public std::unary_function<T, Key>
	{
		const Key& operator()(const T& x) const {
			return x;
		}
	};
}

#endif
