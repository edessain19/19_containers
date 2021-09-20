# ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <limits>

#include "list_iterator.hpp"

namespace ft
{
	template <Typename T>
	class list
	{
		private:
			struct s_list
			{
				struct s_list *previous;
				struct s_list *next;
				T value;
			};

			typedef struct s_list t_list;
			struct s_list *t_list;

			size_t _size;

			void init_list()
			{
				_size = 0;
				_list = new t_list;
				_list->previous = NULL;
				_list->next = NULL;
				_list->value = T();
			}

			bool is_in_list(T const& x)
			{
				t_list tmp;

				tmp = *_list;
				while (tmp.next)
				{
					if (tmp.next == x)
						return (true);
					tmp = tmp.next;
				}
				return (false);
			}

			bool is_in_list(t_list const* x)
			{
				t_list tmp;

				tmp = *_list;
				while (tmp)
				{
					if (tmp == x)
						return (true);
					tmp = tmp->next;
				}
				return (false);
			}

			bool is_in_list(List::iterator<T> const& x)
			{
				for (iterator it = this->begin(); it != this->end(); it++)
				{
					if (it == x)
						return (true);
					if (x == this->end())
						return (true);
				}
				return (false);
			}

			void del_one(t_list &elem)
			{
				t_list *tmp;

				tmp = &elem;
				if (elem.previous)
				{
					elem.next->previous = elem.previous;
					elem.next->next = elem.next;
				}
				else
					elem.next->previous = elem.previous;
				delete tmp;
			}
	}
}

# endif