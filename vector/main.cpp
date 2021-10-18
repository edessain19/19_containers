#include <vector>
#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"

#define P(x) std::cout << x << std::endl

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define NC "\e[0m"

template <class T>
std::string verif(T elem)
{
	std::string value;

	if (elem)
		return (" | " GRN "[OK]" NC);
	else
		return (" | " RED "[K0]" NC);
}


int main()
{
	P("-------------------------------------------------------------------------");
    P("---------------------------------VECTOR----------------------------------");
    P("-------------------------------------------------------------------------");
    P("                                                                         ");
	P("                                                                         ");
    P("------------------------------CONSTRUCTORS-------------------------------");
	P("-------------------------------------------------------------------------");
	P("________________________________default__________________________________");
	std::vector<std::string> s;
	ft::vector<std::string> f;
	std::vector<std::string> s2(5, "hello");
	ft::vector<std::string> f2(5, "hello");
	P("------------------------------CAPACITY-----------------------------------");
	P("-------------------------------------------------------------------------");
	P("________________________________size_____________________________________");
	P("size: " << s.size());
	P("size: " << f.size());
	P("size: " << s2.size());
	P("size: " << f2.size());
	P("________________________________max_size__________________________________");
	P("max size: " << s.max_size());
	P("max size: " << f.max_size());
	P("max size: " << s2.max_size());
	P("max size: " << f2.max_size());
	P("________________________________capacity__________________________________");
	P("capacity: " << s.capacity());
	P("capacity: " << f.capacity());
	P("capacity: " << s2.capacity());
	P("capacity: " << f2.capacity());
	P("________________________________resize____________________________________");
	s.resize(7, "heyyy");
	f.resize(7, "heyyy");

	s2.resize(7, "heyyy");
	f2.resize(7, "heyyy");
	P("resize: " << s.size());
	P("resize: " << f.size());
	P("resize: " << s2.size());
	P("resize: " << f2.size());
	P("------------------------------Element access-----------------------------");
	P("-------------------------------------------------------------------------");
	P("________________________________operator []______________________________");
	P("[3]: " << s2[3]);
	P("[3]: " << f2[3]);
	P("________________________________at_______________________________________");
	P("at: " << s2.at(3));
	P("at: " << f2.at(3));
	P("________________________________front____________________________________");
	P("front: " << s2.front());
	P("front: " << f2.front());
	P("________________________________back_____________________________________");
	P("back: " << s2.back());
	P("back: " << f2.back());
	P("------------------------------Modifiers----------------------------------");
	P("-------------------------------------------------------------------------");
	P("________________________________Assign___________________________________");
	s2.assign(15, "ASSIGNED");
	f2.assign(15, "ASSIGNED");
	P("back: " << s2.back());
	P("back: " << f2.back());
	P("size: " << s2.size());
	P("size: " << f2.size());
	P("________________________________Push back________________________________");
	P("size: " << s2.size());
	P("size: " << f2.size());
	s2.push_back("bonjour");
	f2.push_back("bonjour");
	P("back: " << s2.back());
	P("back: " << f2.back());
	P("size: " << s2.size());
	P("size: " << f2.size());
	P("________________________________Pop back__________________________________");
	s2.pop_back();
	f2.pop_back();
	P("back: " << s2.back());
	P("back: " << f2.back());
	P("size: " << s2.size());
	P("size: " << f2.size());
	P("________________________________Insert__________________________________");
	P("________________________________Erase___________________________________");
	P("________________________________Swap___________________________________");
	// std::string ref1 = s2.at(0);
    // std::string ref2 = f2.at(0);

	std::vector<std::string> s3(10, "yoyo");
	ft::vector<std::string> f3(10, "yoyo");
	s2.swap(s3);
	f2.swap(f3);
	P("back: " << s2.back());
	P("back: " << f2.back());
	P("size: " << s2.size());
	P("size: " << f2.size());
	P("back: " << s3.back());
	P("back: " << f3.back());
	P("size: " << s3.size());
	P("size: " << f3.size());
	P("------------------------------Iterators----------------------------------");
	P("-------------------------------------------------------------------------");
	// P("________________________________Begin____________________________________");
	// std::vector<std::string>::iterator s_iter_begin = s2.begin();
    // ft::vector<std::string>::iterator f_iter_begin = f2.begin();
	
	// P("begin = " << *s_iter_begin);
	// P("begin = " << *f_iter_begin);
	// P("________________________________End____________________________________");
	// std::vector<std::string>::iterator s_iter_end = s2.end();
    // ft::vector<std::string>::iterator f_iter_end = f2.end();
	
	// P("end = " << *s_iter_end);
	// P("end = " << *f_iter_end);
	P("-------------------------------OPERATORS------------------------------------");
	P("----------------------------------------------------------------------------");
    P("__________________________________==________________________________________");
    std::vector<std::string>  s5(s);
    ft::vector<std::string>  f5(f);

    // P("operator '==' : " << (s == s5));
	// // f == f5;
	// P("operator '==' : " << (f == f5));
	return 0;
}