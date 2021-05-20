# ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
#include <deque>

//Namespaces provide a method for preventing name conflicts in large projects
namespace ft
{
	template <typename T, typename Container = std::deque<T> > // double-ended queue is an indexed sequence container that allows fast insertion and deletion at both its beginning and its end.
	class stack
	{
		private:
			size_t		_size;
			Container	_cont;

		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;
			
			explicit stack(const Container &cont_ = Container()): _size(cont_.size()), _cont(cont_) {} //Constructs an adaptor object, adaptor because the object contruction depends on the template parameter; explicit to protect the function

			// Capacity
			bool empty() const { return (_cont.empty()); }
			size_t size() const { return _size; }

			// Element access
			T &top() { return _cont.back(); }
			const T &top() const { return _cont.back(); }

			// Modifiers
			void push (const value_type& val) {_cont.push_back(val); _size++;} //add an element at the stack
			void pop() {_cont.pop_back(); _size--;} // Delete the last element of the stack
	

	};
}

# endif

/////////////////////////////////////////////////////
// https://www.cplusplus.com/reference/stack/stack/
// https://www.softwaretestinghelp.com/stacks-and-queues-in-stl/#Stack_Operations
// https://www.javatpoint.com/cpp-stack
// https://en.cppreference.com/w/cpp/container/deque
// 