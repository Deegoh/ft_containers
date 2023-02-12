#include "map_tester.hpp"

#include "base.hpp"

void testCopyMap() {
	std::list<ft::pair<const int, int> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::pair<const int, int>(lst_size - i, i));
	ft::map<const int, int> mp(lst.begin(), lst.end());
	ft::map<const int, int>::iterator it = mp.begin(), ite = mp.end();

	ft::map<const int, int> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;

	it = mp.begin(); ite = --(--mp.end());
	ft::map<const int, int> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);
}

void testInsertMap(int count) {
	ft::map<int, int> map_int;
	ft::map<int, int> map_int2;
	cmp(map_int, map_int2);
	ft::map<int, int>::iterator it;

	int i;
	for (i = 1; i <= count; ++i) {
		map_int.insert(ft::make_pair(i, i * count));
	}

	i = 3;
	map_int.insert(ft::make_pair(i, i * count));

	i = 0;
	for (it = map_int.begin(); it != map_int.end(); it++) {
		std::cout << i++;
		std::cout << ":first[" << it->first << "] second[" << it->second
				  << "]" << "\n";
	}

	std::cout << "\nerase key 3\n" << std::endl;
	map_int.erase(3);

	i = 0;
	for (it = map_int.begin(); it != map_int.end(); it++) {
		std::cout << i++;
		std::cout << ":first[" << it->first << "] second[" << it->second
				  << "]" << "\n";
	}

	std::cout << "size_max " << map_int.max_size() << std::endl;

	ft::map<char, foo<float> > mp_cf;
//	std::cout << mp_cf['a'] << std::endl;
	mp_cf['a'] = 2.3;
	std::cout << mp_cf['a'] << std::endl;

	std::list<ft::pair<const int, int> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i) {
		std::cout << "key:" << lst_size - i << " value:" << i << std::endl;
		lst.push_back(ft::pair<const int, int>(lst_size - i, i));
	}


	ft::map<int, int> mp(lst.begin(), lst.end());
	it = mp.begin();
	ft::map<int, int>::iterator ite = mp.end();

	for (; it != ite; ++it)
		std::cout << it->first << ":" << it->second << " ";
	std::cout << std::endl;
}


template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	mp.erase(param);
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	mp.erase(param, param2);
	printSize(mp);
}

void testEraseMap() {
	std::list<ft::pair<const int, std::string> > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::pair<const int, std::string>(i, std::string((lst_size - i), i + 65)));
	ft::map<const int, std::string> mp(lst.begin(), lst.end());
	printSize(mp);

	ft_erase(mp, ++mp.begin());

	ft_erase(mp, mp.begin());
	ft_erase(mp, --mp.end());

	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
	ft_erase(mp, --(--(--mp.end())), --mp.end());

	mp[10] = "Hello";
	mp[11] = "Hi there";
	printSize(mp);
	ft_erase(mp, --(--(--mp.end())), mp.end());

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	printSize(mp);
	ft_erase(mp, mp.begin(), mp.end());
}

void testCompMap() {
	ft::map<char, int> mp1;
	ft::map<char, int> mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	cmp(mp1, mp1); // 0
	cmp(mp1, mp2); // 1

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

	cmp(mp1, mp2); // 2
	cmp(mp2, mp1); // 3

	(++(++mp1.begin()))->second = 42;

	cmp(mp1, mp2); // 4
	cmp(mp2, mp1); // 5

	swap(mp1, mp2);

	cmp(mp1, mp2); // 6
	cmp(mp2, mp1); // 7

}


void testMap(int count) {
	testCopyMap();
	testInsertMap(count);
	testEraseMap();
	testCompMap();
}

