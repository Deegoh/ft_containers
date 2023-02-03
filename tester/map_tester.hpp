//template <typename T>
//std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
//{
//	o << "key: " << iterator->first << " | value: " << iterator->second;
//	if (nl)
//		o << std::endl;
//	return ("");
//}
//
//template<typename T_MAP>
//void	printSize(T_MAP const &mp, bool print_content = 1)
//{
//	std::cout << "size: " << mp.size() << std::endl;
//	std::cout << "max_size: " << mp.max_size() << std::endl;
//	if (print_content)
//	{
//		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
//		std::cout << std::endl << "Content is:" << std::endl;
//		for (; it != ite; ++it)
//			std::cout << "- " << printPair(it, false) << std::endl;
//	}
//	std::cout << "###############################################" << std::endl;
//}
//
//void testCopyMap() {
//
//		std::list<ft::utility<const int, int> > lst;
//		unsigned int lst_size = 7;
//		for (unsigned int i = 0; i < lst_size; ++i)
//			lst.push_back(ft::utility<const int, int>(lst_size - i, i));
//		ft::map<const int, int> mp(lst.begin(), lst.end());
//		ft::map<const int, int>::iterator it = mp.begin(), ite = mp.end();
//
//		ft::map<const int, int> mp_range(it, --(--ite));
//		for (int i = 0; it != ite; ++it)
//			it->second = ++i * 5;
//
//		it = mp.begin(); ite = --(--mp.end());
//		ft::map<const int, int> mp_copy(mp);
//		for (int i = 0; it != ite; ++it)
//			it->second = ++i * 7;
//
//		std::cout << "\t-- PART ONE --" << std::endl;
//		printSize(mp);
//		printSize(mp_range);
//		printSize(mp_copy);
//
//		mp = mp_copy;
//		mp_copy = mp_range;
//		mp_range.clear();
//
//		std::cout << "\t-- PART TWO --" << std::endl;
//		printSize(mp);
//		printSize(mp_range);
//		printSize(mp_copy);
//}

void testMap(int count) {
//	testCopyMap();
	{
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
//		map_int.erase(3);

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

//	std::cout << "\t\t\t" << mp.get_root()->value.first << std::endl;
//	std::cout << "\t\t" << mp.get_root()->left->value.first << "\t\t" << mp.get_root()->right->value.first << std::endl;
//	std::cout << "\t" << mp.get_root()->left->left->value.first << "\t\t" << mp.get_root()->left->right->value.first << std::endl;
//	std::cout << "" << mp.get_root()->left->left->left->value.first << "\t\t" << mp.get_root()->left->left->right->value.first << std::endl;

		for (; it != ite; ++it)
			std::cout << it->first << ":" << it->second << " ";
		std::cout << std::endl;


//	it = mp.begin();
//	--(--ite);
//	mp.erase(it, ite);
//	it = mp.qbegin();
//	ite = mp.end();
//	it++;
//	it--;
//	ft::map<int, int> mp_range(it, ite);
//
//	for (; it != ite; ++it)
//		std::cout << it->first << ":" << it->second << " ";
//	std::cout << std::endl;
	}

	{
		std::list<ft::pair<int, std::string> > lst;
		unsigned int lst_size = 10;
		for (unsigned int i = 0; i < lst_size; ++i)
			lst.push_back(ft::pair<int, std::string>(i, std::string((lst_size - i), i + 65)));
		ft::map<int, std::string> mp(lst.begin(), lst.end());

		ft::map<int, std::string>::iterator it;
		for (it = mp.begin(); it != mp.end() ; ++it) {
			std::cout << it->first << " " << it->second << "\n";
		}
	}

	{
		ft::map<int, std::string> mp;
		mp.insert(ft::make_pair<int, std::string>(42, "lol"));
		mp.insert(ft::make_pair<int, std::string>(50, "mdr"));
		mp.insert(ft::make_pair<int, std::string>(25, "funny"));
		mp.insert(ft::make_pair<int, std::string>(46, "bunny"));
		mp.insert(ft::make_pair<int, std::string>(21, "fizz"));
		mp.insert(ft::make_pair<int, std::string>(30, "buzz"));
		mp.insert(ft::make_pair<int, std::string>(55, "fuzzy"));
		mp.insert(ft::make_pair<int, std::string>(18, "bee"));
		mp.insert(ft::make_pair<int, std::string>(23, "coconut"));
		mp.insert(ft::make_pair<int, std::string>(28, "diary"));
		mp.insert(ft::make_pair<int, std::string>(35, "fiesta"));
		mp.insert(ft::make_pair<int, std::string>(44, "hello"));
		mp.insert(ft::make_pair<int, std::string>(48, "world"));
		mp.insert(ft::make_pair<int, std::string>(53, "this is a test"));
		mp.insert(ft::make_pair<int, std::string>(80, "hey"));
		mp.insert(ft::make_pair<int, std::string>(12, "no"));
		mp.insert(ft::make_pair<int, std::string>(20, "idea"));
		mp.insert(ft::make_pair<int, std::string>(22, "123"));
		mp.insert(ft::make_pair<int, std::string>(24, "345"));
		mp.insert(ft::make_pair<int, std::string>(27, "27"));
		mp.insert(ft::make_pair<int, std::string>(29, "29"));
		mp.insert(ft::make_pair<int, std::string>(33, "33"));
		mp.insert(ft::make_pair<int, std::string>(38, "38"));
		mp.insert(ft::make_pair<int, std::string>(43, "1"));
		mp.insert(ft::make_pair<int, std::string>(45, "2"));
		mp.insert(ft::make_pair<int, std::string>(47, "3"));
		mp.insert(ft::make_pair<int, std::string>(49, "4"));
		mp.insert(ft::make_pair<int, std::string>(51, "5"));
		mp.insert(ft::make_pair<int, std::string>(54, "6"));
		mp.insert(ft::make_pair<int, std::string>(60, "7"));
		mp.insert(ft::make_pair<int, std::string>(90, "8"));

		printSize(mp);

		mp.erase(25);
		std::cout << "25 erase\n";


		printSize(mp);

	}

	{
		ft::map<int, std::string> mp;
		mp.insert(ft::make_pair<int, std::string>(10, "lol"));
		mp.insert(ft::make_pair<int, std::string>(15, "mdr"));
		mp.insert(ft::make_pair<int, std::string>(5, "funny"));
		mp.insert(ft::make_pair<int, std::string>(7, "bunny"));
		mp.insert(ft::make_pair<int, std::string>(2, "buzz"));
		mp.insert(ft::make_pair<int, std::string>(8, "fizz"));
		mp.insert(ft::make_pair<int, std::string>(6, "buzz"));
//		mp.left_rot(5);
		printSize(mp);
	}

//		it->second = ++i * 5;

//	it = map_int.begin();
//	ft::map<int, int>::iterator ite = map_int.end();
//	std::cout << &it << " " << &ite << std::endl;
//
//	int sum = 0;
//	for (int i = 0; i < count; i++)
//	{
//		int access = rand();
//		sum += map_int[access];
//	}
//	for(ft::map<int, int>::iterator it = map_int.begin(); it != map_int.end(); ++it)
//	{
//		std::cout << it->first << "\n";
//	}
//	std::cout << "should be constant with the same seed: " << sum << std::endl;
//
//	{
//		ft::map<int, int> copy = map_int;
//		for(ft::map<int, int>::iterator it = copy.begin(); it != copy.end(); ++it)
//		{
//			std::cout << it->first << "\n";
//		}
//	}
}