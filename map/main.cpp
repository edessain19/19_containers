#include "map.hpp"

#include <map>
#include <iostream>
#include <fstream>

#define P(x) std::cout << x << std::endl

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define NC "\e[0m"

int main()
{
	P("-------------------------------------------------------------------------");
	P("----------------------------------MAP------------------------------------");
	P("-------------------------------------------------------------------------");
	P("                                                                         ");
	P("                                                                         ");
	P("------------------------------CONSTRUCTORS-------------------------------");
	P("-------------------------------------------------------------------------");
	P("________________________________default__________________________________");

	std::map<int, std::string> s;
	ft::map<int, std::string> f;


	std::map<int, std::string> s2;
	ft::map<int, std::string> f2;

	std::map<int, std::string>::iterator iters = s2.begin();
	ft::map<int, std::string>::iterator iterf = f2.begin();
	
	int range_int[] = {-741, 520, 65, -84, -1};
	std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};
	for (int i = 0; i < 5; i++)
	{
		s2.insert(iters, std::make_pair(range_int[i], range_str[i]));
		f2.insert(iterf, ft::make_pair(range_int[i], range_str[i]));
	}

	P("------------------------------CAPACITY-----------------------------------");
	P("-------------------------------------------------------------------------");
	P("________________________________size_____________________________________");
	// P("size: " << s.size());
	// P("size: " << f.size());
	// P("size: " << s2.size());
	// P("size: " << f2.size());



	return (0);
}