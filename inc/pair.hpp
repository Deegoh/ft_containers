#ifndef PAIR_HPP
#define PAIR_HPP

template <class T1, class T2>
struct pair {
	T1 first;
	T2 second;
	pair() {}
	template<class U, class V>
	pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {};
	pair(const T1& a, const T2& b) : first(a), second(b) {}
};

template <class T1, class T2>
inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y) {
	return x.first == y.first && x.second == y.second;
}

template <class T1, class T2>
inline bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y) {
	return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
}

template <class T1, class T2>
inline pair<T1, T2> make_pair(const T1& x, const T2& y) {
	return pair<T1, T2>(x, y);
}

#endif
