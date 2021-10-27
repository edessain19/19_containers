# ifndef STACK_HPP
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
			typedef T                                                       value_type;
			typedef Alloc                                                   allocator_type;
			typedef typename allocator_type::reference                      reference;
			typedef typename allocator_type::const_reference                const_reference;
			typedef typename allocator_type::pointer                        pointer;
			typedef typename allocator_type::const_pointer                  const_pointer;
			typedef ft::It<value_type>                                      iterator;
			typedef ft::It<const value_type>                                const_iterator;
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
		// template <class InputIterator, std::enable_if<std::is_ >
		// 	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _base(alloc), _size(0), _maxSize(0) //Range constructor
		// 	{
		// 		for (; first < last; first++)
		// 		{
		// 			this->_size++;
		// 			this->_maxSize = (last - first) / sizeof(value_type);                                     ///////////// _maxSize is not correct in this case, how to find it?
		// 		}
		// 		first -= _size;
		// 		this->_ptr = this->_base.allocate(this->_size);
		// 		for (size_t a = 0; a < this->_size; a++)
		// 			this->_base.construct(_ptr + a, *first);
		// 	}
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
			const_reverse_iterator rend() const { return (const)reverse_iterator(this->ptr)); }

			// const_iterator cbegin() const noexcept;
			// const_iterator cend() const noexcept;
			// const_reverse_iterator crbegin() const noexcept;
			// const_reverse_iterator crend() const noexcept;

			// -------------------- Capacity -------------------- //
			size_type size() const { return (this->_size); }
			size_type max_size() const { return (this->_capacity); }
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

			// iterator insert (iterator position, const value_type& val);
			// void insert (iterator position, size_type n, const value_type& val);
			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position)
			{
				iterator it;
				vector tmp;
				size_t a = 0;
				size_t b = 0;

				if (position == this->end())
					return (this->end());
				tmp = *this;
				tmp._size--;
				this->clear();
				for (it = tmp.begin(); it < position; it++)
					a++;
				for (; b < tmp._size; b++)
				{
					if (b != a)
						this->_base.construct(this->_ptr + b, *(tmp._ptr + b));
				}
				this->_size = tmp._size;
				this->_maxSize = tmp._maxSize;
				return (position);
			}
			iterator erase (iterator first, iterator last)
			{
				iterator it;
				size_t a = 0;
				size_t b = 0;
				size_t c = 0;

				for (it = this->begin(); it < first; it++)
					a++;
				for (it = this->begin(); it < last; it++)
					b++;
				c = b - a;
				this->_size -= c;
				for (; a < this->_size; a++)
					this->_ptr[a] = this->_ptr[a + c];
				return (last - c);
			}

			void swap (vector& x)
            {
                pointer tmp;
                size_t  tmp2;
                size_t  tmp3;T

                tmp = this->_ptr;
                tmp2 = this->_size;
                tmp3 = this->capacity;
                this->_ptr = x._ptr;
                this->_size = x._size;
                this->capacity = x.capacity;
                x._ptr = tmp;
                x._size = tmp2;
                x._capacity = tmp3;
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
			allocator_type get_allocator() const { return (this->_base); }

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
	};
}

#endif
