#include <stack>
#include "stack.hpp"
#include <string>


#define P(x) std::cout << x << std::endl
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define NC "\e[0m"

template <class T>
std::string verif(T elem)
{
	std::string value;
	if (elem)
		return (" Verif: " GRN " [OK]" NC);
	else
		return (" Verif: " RED " [K0]" NC);
}

void t_stack(void)
{
	ft::stack<std::string> f;
	ft::stack<std::string> f2;
	std::stack<std::string> s;
	std::stack<std::string> s2;

	P("~~~~~~~~~~~~~~~ STACK ~~~~~~~~~~~~~~~----");
	P("---------> empty <----");
	P("empty ? " << s.empty() << verif(s.empty() == f.empty()) );
	P("size = " << s.size() << verif(s.size() == f.size()) );

	P("---------> push <----");
	s.push("one");
	f.push("one");
	P("top = " << s.top() << verif(s.top() == f.top()) );
	P("empty ? " << s.empty() << verif(s.empty() == f.empty()) );
	P("size = " << s.size() << verif(s.size() == f.size()) );

	P("---------> pop <----");
	s.pop();
	f.pop();
	P("empty ? " << s.empty() << verif(s.empty() == f.empty()) );
	P("size = " << s.size() << verif(s.size() == f.size()) );

	P("~~~~~~~~~~~~~~~----> Test Operator <-------------");
	s.push("deux");
	f.push("deux");

	P("---------> operator == <----");
	P("operator '==' : " << (s == s2) << verif((s == s2) == (f == f2)));

	P("---------> operator != <----");
	P("operator '!=' : " << (s != s2) << verif((s != s2) == (f != f2)));

	P("---------> operator < <----");
	P("operator '<' : " << (s < s2) << verif((s < s2) == (f < f2)));

	P("---------> operator <= <----");
	P("operator '<=' : " << (s <= s2) << verif((s <= s2) == (f <= f2)));

	P("---------> operator > <----");
	P("operator '>' : " << (s > s2) << verif((s > s2) == (f > f2)));

	P("---------> operator >= <----");
	P("operator '>=' : " << (s >= s2) << verif((s >= s2) == (f >= f2)));
}

int main(void)
{
	t_stack();
	return (0);
}