# ifndef STACK_HPP
# define STACK_HPP

# include <deque>
# include <iostream>
# include <iterator>
# include "../utils/iterator.hpp"
# include "../utils/utils.hpp"

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
			typedef T                                                       value_type;
			typedef Alloc                                                   allocator_type;
			typedef typename allocator_type::reference                      reference;
			typedef typename allocator_type::const_reference                const_reference;
			typedef typename allocator_type::pointer                        pointer;
			typedef typename allocator_type::const_pointer                  const_pointer;
			typedef ft::Itvec<value_type>                                   iterator;
			typedef ft::Itvec<const value_type>                             const_iterator;
			typedef ft::reverse_iterator<iterator>                          reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t                                                  size_type;

			// -------------------- Membre Functions -------------------- //
			// ---------- constructor ---------- //
			explicit vector (const allocator_type& alloc = allocator_type()) :  _size(0), _capacity(0) , _base(alloc) { this->_ptr = this->_base.allocate(0); }
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _base(alloc)
			{
				this->_ptr = this->_base.allocate(n);
				for (size_t i = 0; i < n; i++)
					this->_base.construct(this->_ptr + i, val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr): _base(alloc), _size(0), _capacity(0)
			{
				for (; first < last; first++)
					this->_size++;
				this->_capacity = this->_size;
				first -= _size;
				this->_ptr = this->_base.allocate(this->_size);
				for (size_t i = 0; i < this->_size; i++)
					this->_base.construct(_ptr + i, *(first + i));
			}

			vector (const vector& x): _size(x._size) , _capacity(x._capacity), _base(allocator_type()) 
			{
				this->_ptr = this->_base.allocate(0);
				*this = x;
			}

			// ---------- destructor ---------- //
			virtual ~vector()
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
			iterator begin() { return (iterator(this->ptr)); }
			const_iterator begin() const { return (const_iterator(this->ptr)); }

			iterator end() { return (iterator(this->_ptr + this->_size)); }
			const_iterator end() const { return (const_iterator(this->_ptr + this->_size)); }

			reverse_iterator rbegin() { return (reverse_iterator(this->_ptr + this->_size)); }
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->_ptr + this->_size)); }

			reverse_iterator rend() { return (reverse_iterator(this->ptr)); }
			const_reverse_iterator rend() const { return (const_reverse_iterator(this->ptr)); }

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
					for (size_t i = this->_size; i < n; i++)
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
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr) //Assign vector content
			{
				clear();
				insert(begin(), first, last);
				this->_capacity = _size;
			}
			void assign (size_type n, const value_type& val)
			{
				this->clear();
				for (size_t i = 0; i < n; i++)
					push_back(val);
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

			iterator insert(iterator position, const value_type& val)
			{
				iterator it;
				size_t i = 0;
				size_t j = 0;

				for (it = this->begin(); it < position; it++)
					i++;
				this->reserve(this->_size + 1);
				this->_size += 1;
				i = this->_size - 1;
				while (j > i)
				{
					this->_ptr[j] = this->_ptr[j - 1];
					j--;
				}
				this->_ptr[i] = val;
				return (begin() + i);
			}
			void insert(iterator position, size_type n, const value_type& val)
			{
				iterator it = position;
				for (size_t i = 0; i < n; i++)
				{
					it = insert(it, val);
					it++;
				}
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				iterator it = position;

				for (; first < last; first++)
				{
					it = insert(it, *first);
					it++;
				}
			}

			iterator erase (iterator position)
			{
				iterator it;
				size_t i = 0;

				this->_size--;
				for (it = this->begin(); it < position; it++)
					i++;
				for (; i < this->_size; i++)
					this->_ptr[i] = this->_ptr[i + 1];
				if (position == this->end() + 1)
					return (this->end());
				return (position);
			}
			iterator erase (iterator first, iterator last)
			{
				iterator it;
				size_t i = 0;
				size_t j = 0;
				size_t k = 0;

				for (it = this->begin(); it < first; it++)
					i++;
				for (it = this->begin(); it < last; it++)
					j++;
				k = j - i;
				this->_size -= k;
				for (; i < this->_size; i++)
					this->_ptr[i] = this->_ptr[i + k];
				return (last - k);
			}

			void swap (vector& x)
			{
				pointer tmp_ptr;
				size_t  tmp_size;
				size_t  tmp_capacity;

				tmp_ptr = this->_ptr;
				tmp_size = this->_size;
				tmp_capacity = this->_capacity;
				this->_ptr = x._ptr;
				this->_size = x._size;
				this->_capacity = x._capacity;
				x._ptr = tmp_ptr;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}

			void clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_base.destroy(this->_ptr + i);
				this->_size = 0;
			}

			// -------------------- Allocator -------------------- //
			allocator_type get_allocator() const { return (this->_base); }
	};

	// -------------------- Non-member function overloads -------------------- //
	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t a = 0; a < lhs.size(); a++)
		{
			if (lhs[a] != rhs[a])
				return false;
		}
		return true;
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs)); }
	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs)); }
	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }
	template <class T, class Alloc>
	void swap (vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }
}

#endif
