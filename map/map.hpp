# ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <limits>

namespace ft
{
    template < class Key, class T, class Compare = ft::less<Key>, class Alloc = allocator<pair<const Key,T>>
    class map
    {
        private:
            size_t  _size;
            t_map   *_map;
            init_map();

        public:
            typedef Key                     key_type;             
            typedef T                       mapped_type;
            typedef ft::pair<Key, T>        value_type;
            typedef Compare                 key_compare;

        /* TODO
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
        map (const map& x);
        */

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