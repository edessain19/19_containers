#ifndef STACK_HPP
# define STACK_HPP

# include <deque>
# include <iostream>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector 
	{
		private:
			size_t												_size;
			size_t												_capacity;
			Alloc												_base;
			T*													_ptr;
		public:
			typedef T											value_type;
			typedef Alloc   									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer 		const_pointer;
			typedef ft::iterator<value_type>					iterator;
			typedef ft::iterator<const value_type>				const_iterator;
			typedef ft::reverse_iterator<value_type>			reverse_iterator;
			typedef ft::reverse_iterator<const value_type>		const_reverse_iterator;
			// typedef iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t										size_type;

			// ---------- constructor ---------- //
			explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _base(0), _ptr(0);
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector (const vector& x);
	}
}