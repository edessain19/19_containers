# ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <deque>
#include <limits>
#include "../utils/utils.hpp"
#include "../utils/iterator.hpp"
#include "../utils/myrbtree.hpp"

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef	Key 																		key_type;
			typedef	T																			mapped_type;
			typedef typename ft::pair<const Key, T>												value_type;
			typedef size_t 																		size_type;
			typedef ptrdiff_t 																	difference_type;
			typedef Compare 																	key_compare;
			typedef Alloc 																		allocator_type;
			typedef ft::Itmap< mapped_type, key_compare, Node<value_type> >						iterator;
			typedef ft::Itmap< const mapped_type, const key_compare, const Node<value_type> >	const_iterator;
			typedef typename Alloc::pointer 													pointer;
			typedef typename Alloc::const_pointer 												const_pointer;
			typedef ft::reverse_iterator<iterator> 												reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 										const_reverse_iterator;
			typedef	ft::Node<T>																	Node;
			
			// typedef iterator LegacyBidirectionalIterator to value_type;
			// typedef const_iterator LegacyBidirectionalIterator to const value_type;

			class value_compare
			{
				protected:
					Compare _comp;
					value_compare (Compare c) : _comp(c) {}

				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					bool operator() (const value_type& x, const value_type& y) const { return _comp(x.first, y.first); }
			};

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
			_comp(comp), _base(alloc), _size(0), _tree() {}
			
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			_comp(comp), _base(alloc), _tree()
			{
				while (first <= last)
					_tree.insert(*first);
				_size = _tree->_size;
			}
			
			// map (const map& x)
			// {
			// 	*this = x;
			// }

			~map() { clear(); }
			
			// map& operator= (const map& x);

			// // -------------------- Iterator -------------------- //
			iterator begin()
			{
				return (iterator(_tree->firstnode()));
			}
			const_iterator begin() const
			{
				return (iterator(_tree->firstnode()));
			}
			iterator end()
			{
				return (iterator(_tree->lastnode())++);
			}
			const_iterator end() const
			{
				return (iterator(_tree->lastnode())++);
			}
			reverse_iterator rbegin()
			{
				return (iterator(_tree->lastnode()));
			}
			const_reverse_iterator rbegin() const
			{
				return (iterator(_tree->lastnode()));
			}
			reverse_iterator rend()
			{
				return (iterator(_tree->firstnode()));
			}
			const_reverse_iterator rend() const
			{
				return (iterator(_tree->firstnode()));
			}

			// -------------------- Capacity -------------------- //
			bool empty() const 
			{
				if (_tree->getSize() == 0)
					return (true);
				return (false);
			}
			size_type size() const { return (_tree.getSize()); }
			size_type max_size() const { return (_tree.getCapacity()); }
			
			// -------------------- Modifiers -------------------- //
			void clear()
			{
				_tree.clear_all();
			}

			ft::pair<iterator, bool> insert( const value_type& value )
			{
				iterator it = find(value.first);

				if (it != end() && _tree.getSize() != 0)
					return ft::pair<iterator, bool>(iterator(it), false);
				insertNode(value);
				return ft::pair<iterator, bool>(iterator(value), true);
			}

			iterator insert( iterator position, const value_type& value )
			{
				position = nullptr;
				return (_tree.insert(value));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				if ((*first).first > (*last).first)
					return ;
				while (first <= last)
				{
					_tree.insert((*first).first);
					first++;
				}
			}
			void erase( iterator position )
			{
				_tree.delete_node((*position).first);
			}
			size_type erase (const key_type& k)
			{
				_tree.delete_node(k);
				return(1);
			}
			void erase( iterator first, iterator last )
			{
				if ((*first).first > (*last).first)
					return ;
				while (first <= last)
				{
					this->tree.delete_node((*first).first);
					first++;
				}
			}
			void swap( map& copy ) { _tree.swap(copy._tree); }

			// -------------------- Lookup -------------------- //
			size_type count( const Key& key ) const
			{
				if (_tree.search(key) == nullptr)
					return (0);
				return (1);
			}
			iterator find( const Key& key ) { return (iterator(_tree.search(key))); }
			const_iterator find( const Key& key ) const { return (iterator(_tree.search(key))); }
			//////////////////////////////
			ft::pair<iterator,iterator> equal_range( const Key& key )
			{
				iterator it = this->begin();
				
				for (; it != this->end() && !_comp(key, (*it).first); it++)
				{
					if (!_comp((*it).first, key) && !_comp(key, (*it).first))
					{
						iterator it2 = it++;
						return ft::pair<iterator,iterator>(it2, it);
					}
				}
				return ft::pair<iterator,iterator>(it, it);
			}

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
				const_iterator it = this->begin();
				
				for (; it != this->end() && !_comp(key (*it).first); it++)
				{
					if (!_comp((*it).first, key) && !_comp(key, (*it).first))
					{
						const_iterator it2 = it++;
						return ft::pair<const_iterator,const_iterator>(it2, it);
					}
				}
				return ft::pair<const_iterator,const_iterator>(it, it);
			}
			/////////////////////////////////////
			iterator lower_bound( const Key& key )
			{
				iterator it = this->begin();

				while ((*it).first <= key)
					it++;
				return (it);
			}
			const_iterator lower_bound( const Key& key ) const
			{
				iterator it = this->begin();

				while ((*it).first <= key)
					it++;
				return (it);
			}
			iterator upper_bound (const key_type& key)
			{
				iterator it = this->begin();

				while ((*it).first > key)
					it++;
				return (it);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				iterator it = this->begin();

				while ((*it).first > k)
					it++;
				return (it);
			}

			// -------------------- Observers -------------------- //
			key_compare key_comp() const
			{
				return (key_compare());
			}
			value_compare value_comp() const
			{
				return (value_compare());
			}

			allocator_type get_allocator() const { return (this->_base); }

		private:
			key_compare _comp;
			Alloc   _base;
			T*      _ptr;
			size_t  _size;
			size_t  _capacity;
			BTree<Key, T, ft::pair< const Key, T > > _tree;
	};

	// -------------------- Non Member function -------------------- //
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (!(lhs == rhs)); }
	template< class Key, class T, class Compare, class Alloc >
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (!(rhs < lhs)); }
	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (rhs < lhs); }
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (!(lhs < rhs)); }
	template< class Key, class T, class Compare, class Alloc >
	void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }
}


#   endif