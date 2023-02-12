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

void testSet() {
	testInsertSet();
}