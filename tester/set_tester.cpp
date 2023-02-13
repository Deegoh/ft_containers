#include "set_tester.hpp"

void testInsertSet() {
	ft::set<std::string> st, st2;

	st.insert("lol");
	st.insert("mdr");

	st.insert("mdr");
	st.insert("funny");

	st.insert("bunny");
	st.insert("fizz");
	st.insert("buzz");

	st.insert(st.begin(), "fuzzy");

	st2.insert(st2.begin(), "beauty");
	st2.insert(st2.end(), "Hello");
	st2.insert(st2.end(), "World");

	printSize(st);
}

void testCopySet() {
	std::list<int> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(lst_size - i);

	ft::set<int> st(lst.begin(), lst.end());
	ft::set<int>::iterator it = st.begin(), ite = st.end();

	ft::set<int> st_range(it, --(--ite));
	for (int i = 0; i < 5; ++i)
		st.insert(i * 5);

	it = st.begin(); ite = --(--st.end());
	ft::set<int> st_copy(st);
	for (int i = 0; i < 7; ++i)
		st.insert(i * 7);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(st);
	printSize(st_range);
	printSize(st_copy);

	st = st_copy;
	st_copy = st_range;
	st_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(st);
	printSize(st_range);
	printSize(st_copy);
}

void testEraseSet() {
	std::list<std::string> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::string((lst_size - i), i + 65));
	ft::set<std::string> st(lst.begin(), lst.end());
	printSize(st);

	ft_erase(st, ++st.begin());

	ft_erase(st, st.begin());
	ft_erase(st, --st.end());

	ft_erase(st, st.begin(), ++(++(++st.begin())));
	ft_erase(st, --(--(--st.end())), --st.end());

	st.insert("Hello");
	st.insert("Hi there");
	printSize(st);
	ft_erase(st, --(--(--st.end())), st.end());

	st.insert("ONE");
	st.insert("TWO");
	st.insert("THREE");
	st.insert("FOUR");
	printSize(st);
	ft_erase(st, st.begin(), st.end());

}

void testCompSet() {
	ft::set<char> st;

	st.insert('a');
	st.insert('b');
	st.insert('c');
	st.insert('d');
	printSize(st);

	for (ft::set<char>::const_iterator it1 = st.begin(); it1 != st.end(); ++it1)
		for (ft::set<char>::const_iterator it2 = st.begin(); it2 != st.end(); ++it2)
			ft_comp(st, it1, it2);

	printSize(st);
}

void ft_comp(const ft::set<char> &st, const ft::set<char>::const_iterator &it1, const ft::set<char>::const_iterator &it2) {
	bool res[2];

	res[0] = st.key_comp()(*it1, *it2);
	res[1] = st.value_comp()(*it1, *it2);
	std::cout << "with [" << *it1 << " and " << *it2 << "]: ";
	std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
}

void testSet() {
	testInsertSet();
	testCopySet();
	testEraseSet();
	testCompSet();
}