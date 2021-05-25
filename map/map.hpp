# ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <limits>

namespace ft
{
    template < template Key, template T, template Compare = ft::less<Key> >
    class map
    {
        private:
            typedef	struct	s_map
			{
				struct s_map			*prev;
				struct s_map			*next;
				pair<Key, T>	        *value;
			}				t_map;
            size_t  _size;
            t_map   *_map;
            init_map();

        public:
            typedef Key                     key_type;             
            typedef T                       mapped_type;
            typedef ft::pair<Key, T>        value_type;
            typedef Compare                 key_compare;

    };
}

/////////////// Function ///////////////

template <class Key, class T>
ft::map<T>::init_map()
{
        _size = 0;
        _map = new t_map;
        _map->next = nullptr;
        _map->prev = nullptr;
        _map->value = new ft::pair<KEY, T>():
}


#   endif