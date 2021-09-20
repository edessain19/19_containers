# ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "list.hpp"

namespace List
{
	template < typename T >
	class iterator
	{
		protected:
			
			typedef struct	s_list
			{
				struct s_list	*prev;
				struct s_list	*next;
				T				value;
			}				t_list;
			
			void	begin()
			{
				while (_list->prev)
					_list = _list->prev;
			}
			
			void	end()
			{
				while (_list->next)
					_list = _list->next;
			}
			
			t_list	*_list;
		
		public:
			typedef char	var;
			iterator(void): _list(NULL) {}
			iterator(void* p_list): _list(static_cast<t_list *>(p_list)) {} // compilation error if the cast fails
			iterator(const iterator<T>& copy) { *this = copy;}
			virtual ~iterator(void) {}

			t_list*		get_list(void) {return (_list);}
			T&			operator*  (void) {return (_list->value);}
			
			iterator&	operator=  (const iterator<T>& copy)
			{
				_list = copy._list;
				return (*this);
			}
			
			bool		operator== (const iterator<T>& copy) const {return (_list == copy._list);}
			bool		operator!= (const iterator<T>& copy) const {return (_list != copy._list);}
			
			iterator&	operator++ () // equal to ++var
			{
				if (_list->next == NULL)
					this->begin();
				else
					_list = _list->next;
				return (*this);
			}


			iterator	operator++ (int) // the (int) means that ++ is after the var // equal to var++ 
			{
				iterator<T> tmp(*this);
				operator++();
				return (tmp);
			} 

			iterator&	operator-- () // equal to --var
			{
				if (_list->prev == NULL)
					this->end();
				else
					_list = _list->prev;
				return (*this);
			}

			iterator	operator-- (int) // equal to var-- 
			{
				iterator<T> tmp(*this);
				operator--();
				return (tmp);
			}
	};

	template < typename T >
	class reverse_iterator: public iterator<T>
	{
		public:
			reverse_iterator(void): iterator<T>() {}
			reverse_iterator(void* p_list): iterator<T>(p_list) {}
			reverse_iterator(const reverse_iterator<T>& copy): iterator<T>() { this->_list = copy._list;}
			virtual ~reverse_iterator(void) {}

			// Pre-increments by one
			reverse_iterator& operator++()
			{
				if (this->_list->prev == 0) 
					this->end(); 
				else 
					this->_list = this->_list->prev; 
				return (*this);
			}
			// Post-increments by one - return a copy
			reverse_iterator operator++(int)
			{
				reverse_iterator<T> tmp(*this); 
				operator++(); 
				return tmp;
			}

			// Pre-decrements by one
			reverse_iterator& operator--()
			{
				if (this->_list->next == 0) 
					this->begin(); 
				else 
					this->_list = this->_list->next; 
				return (*this);
			}

			// Post-decrements by one - return a copy
			reverse_iterator operator-- (int)
			{
				reverse_iterator<T> tmp(*this);
				operator--();
				return tmp;
			}
	};
}

#	endif