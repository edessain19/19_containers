#ifndef STACK_HPP
# define STACK_HPP

# include <deque>
# include <iostream>
# include <iterator>
# include "iterator.hpp"

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
			// -------------------- Typedef -------------------- //
			typedef T											value_type;
			typedef Alloc   									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer 			pointer;
			typedef typename allocator_type::const_pointer 		const_pointer;
			typedef It<value_type>								iterator;
			typedef It<const value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const iterator>		const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t										size_type;

			// -------------------- Membre Functions -------------------- //
			// ---------- constructor ---------- //
			explicit vector (const allocator_type& alloc = allocator_type()) :  _size(0), _capacity(0) , _base(alloc) { this->_ptr = this->_base.allocate(0); }
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _base(alloc)
			{
				this->_ptr = this->_base.allocate(n);

				for (size_t i = 0; i < n; i++)
					this->_base.construct(this->_ptr + i, val);
			}
			// template <class InputIterator>
			// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			// {

			// }
			vector (const vector& x): _size(x._size) , _capacity(x._capacity), _base(allocator_type()) 
			{
				this->_ptr = this->_base.allocate(0);
				*this = x;
			}
			
			// ---------- destructor ---------- //
			~vector()
			{
				this->clear();
				this->_base.deallocate(this->_ptr, this->_capacity);
			}
	
			// ---------- operator ---------- //
			vector& operator= (const vector& x)
			{
				this->clear();
				this->_base.deallocate(this->_ptr, this->_capacity);
				this->_ptr = this->_base.allocate(x._capacity);
				for (size_t i = 0; i < x._size; i++) 
					this->_base.construct(this->_ptr + i, *(x._ptr + i));
				this->_size = x._size;
				this->_capacity = x._capacity;
				return *this;
			}

			// -------------------- Iterator -------------------- //
			// iterator begin();
			// const_iterator begin() const;

			// iterator end();
			// const_iterator end() const;

			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;

			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			// const_iterator cbegin() const noexcept;
			// const_iterator cend() const noexcept;
			// const_reverse_iterator crbegin() const noexcept;
			// const_reverse_iterator crend() const noexcept;

			// -------------------- Capacity -------------------- //
			size_type size() const { return (this->_size); }
			size_type max_size() const { return (this->_base.max_size()); }
			void resize (size_type n, value_type val = value_type())
			{
				if (n > this->_size)
				{
					this->reserve(n);
					for (size_t i = this->_size; i < n; i++)
						this->_base.construct(this->_ptr + i, val);
				}
				else if (n < this->_size)
				{
					for (size_t i = this->_size; i > n; i--)
						this->_base.destroy(this->_ptr + i);
					this->_size = n;
				}
			}
			size_type capacity() const { return (this->_capacity); }
			bool empty() const 
			{
				if (this->_size == 0)
					return (true);
				return (false);
			}
			void reserve (size_type n)
			{
				if (n > this->_capacity)
				{
					vector cpy;

				   	cpy = *this;
					this->clear();
					this->_base.deallocate(this->_ptr, this->_capacity);
					this->_ptr = this->_base.allocate(n);
					for (size_t i = 0; i < cpy._size; i++)
						this->_base.construct(this->_ptr + i, *(cpy._ptr + i));
					this->_size = cpy._size;
					this->_capacity = n;
				}
			}

			// -------------------- Element Access -------------------- //
			reference operator[] (size_type n) { return this->at(n); }
			const_reference operator[] (size_type n) const { return this->at(n); }

			reference at (size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				else
					return (*(this->_ptr + n));
			}
			const_reference at (size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				else
					return (*(this->_ptr + n));
			}

			reference front() { return (*this->_ptr); }
			const_reference front() const { return (*this->_ptr); }

			reference back() { return (*(this->_ptr + _size - 1)); }
			const_reference back() const  { return (*(this->_ptr + _size - 1)); }

			// -------------------- Modifiers -------------------- //
			// template <class InputIterator>
			// void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val)
			{
				this->clear();
				this->_base.deallocate(this->_ptr, this->_capacity);
				this->_ptr = this->_base.allocate(n);
				for (size_t i = 0; i < n; i++)
					this->_base.construct(this->_ptr + i, val);
				this->_size = n;
				this->_capacity = n;
			}

			void push_back (const value_type& val)
			{

				if (this->_capacity < this->_size + 1)
					this->reserve(this->_size + 1);
				this->_base.construct(this->_ptr + this->_size, val);
				this->_size = this->_size + 1;
			}

			void pop_back()
			{
				this->_size--;
				this->_base.destroy(this->_ptr + this->_size);
			}

			// iterator insert (iterator position, const value_type& val);
			// void insert (iterator position, size_type n, const value_type& val);
			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);

			// iterator erase (iterator position);
			// iterator erase (iterator first, iterator last);

			void swap (vector& x)
			{
				vector tmp;

				tmp = *this;
				this->clear();
				*this = x;
				x.clear();
				x = tmp;
			}

			void clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_base.destroy(this->_ptr + i);
				this->_size = 0;
			}

			// template <class... Args>
			// iterator emplace (const_iterator position, Args&&... args);

			// template <class... Args>
			// void emplace_back (Args&&... args);

			// -------------------- Allocator -------------------- //
			allocator_type get_allocator() const { return (_base); }

			// -------------------- Non-member function overloads -------------------- //
			// template <class T, class Alloc>
			// friend bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs.V == rhs.V); }
			// template <class T, class Alloc>
			// friend bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs.V != rhs.V); }
			// template <class T, class Alloc>
			// friend bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs.V < rhs.V); }
			// template <class T, class Alloc>
			// friend bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs.V <= rhs.V); }
			// template <class T, class Alloc>
			// friend bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs.V > rhs.V); }
			// template <class T, class Alloc>
			// friend bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs.V >= rhs.V); }

			// -------------------- Non-member function overloads -------------------- //
			// template < class T, class Alloc = allocator<T> > class vector; // generic template
			// template <class Alloc> class vector<bool,Alloc>;               // bool specialization

	};
}

#endif
