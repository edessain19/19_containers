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

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
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
			typedef value_type&																	reference;
			typedef const value_type&															const_reference;
			typedef ft::Itmap< value_type >														iterator;
			typedef ft::Itmap< value_type >														const_iterator;
			typedef typename Alloc::pointer 													pointer;
			typedef typename Alloc::const_pointer 												const_pointer;
			typedef ft::reverse_iterator<iterator> 												reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 										const_reverse_iterator;
			typedef typename allocator_type::template rebind< Node<value_type> >::other node_allocator;


			class value_compare
			{
				friend class map<key_type, mapped_type, key_compare, allocator_type>;
				
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
				this->insert(first, last);
			}
			
			map (const map& x) _alloc(x._alloc), _comp(x._comp), _tree() 
			{
				this->insert(x.begin(), x.end());
			}

			~map() { _tree.clear(_tree.getRoot());}
			
			map& operator=(const map& x)
			{
				if (this != &x)
				{
					this->clear();
					this->insert(x.begin(), x.end());
					this->_alloc = x._alloc;
					this->_comp = x._comp;
				}
				return (*this);
			}

			// -------------------- Iterator -------------------- //
			iterator begin()
			{
				return (iterator(_tree.firstNode(), _tree.getEnd()))
			}
			const_iterator begin() const
			{
				return (const_iterator(_tree.firstNode(), _tree.getEnd()));
			}
			iterator end()
			{
				return (const_iterator(_tree.getEnd(), _tree.getEnd())); 
			}
			const_iterator end() const
			{
				return (reverse_iterator(iterator(_tree.getEnd(), _tree.getEnd())));
			}
			reverse_iterator rbegin()
			{
				return (const_reverse_iterator(iterator(_tree.getEnd(), _tree.getEnd())));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(iterator(_tree.getEnd(), _tree.getEnd())));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->begin()));
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

			mapped_type& operator[] (const key_type& k)
			{
				ft::Node<value_type>* ptr = _tree.search(k);

				if (ptr == u_nullptr)
					ptr = _tree.insertNode(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
				return (ptr->data.second);
			}
			
			// -------------------- Modifiers -------------------- //
			void clear()
			{
				erase(begin(), end());
			}

			ft::pair<iterator, bool> insert( const value_type& value )
			{
				ft::Node<value_type>*	ptr;
				bool					find = true;

				if ((ptr = _tree.search(value.first)) != u_nullptr)
					find = false;
				ptr = _tree.insertNode(val);
				return (ft::make_pair<iterator, bool>(iterator(ptr, _tree.getEnd()), find));
			}

			iterator insert( iterator position, const value_type& value )
			{
				(void)position;
				return (_tree.insertNode(value), _tree.getEnd()));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					_tree.insertNode(*first);
					first++;
				}
			}
			void erase( iterator position )
			{
				iterator it;

				it = this->begin();
				while (it != position)
					it++;
				if (it == position)
					_tree.deleteNode(it.base(), it->first);
			}
			size_type erase (const key_type& k)
			{
				return (_tree.deleteNode(_tree.getRoot(), k));
			}
			void erase( iterator first, iterator last )
			{
				map cpy(first, last);

				first = cpy.begin();
				last = cpy.end();
				while (first != last)
				{
					_tree.deleteNode(_tree.getRoot(), first->first);
					first++;
				}
			}
			void swap( map& copy ) { _tree.swap(copy._tree); }

			// -------------------- Lookup -------------------- //
			size_type count( const Key& key ) const
			{
				if (_tree.search(key) == u_nullptr)
					return (0);
				return (1);
			}
			iterator find( const Key& key ) 
			{
				ft::Node<value_type>*   find;

				if ((find = _tree.search(k)) == u_nullptr)
					find = _tree.getEnd();
				return (iterator(find, _tree.getEnd())); 
			}
			const_iterator find( const Key& key ) const 
			{
				ft::Node<value_type>*   find;

				if ((find = _tree.search(k)) == u_nullptr)
					find = _tree.getEnd();
				return (iterator(find, _tree.getEnd())); 
			}
			//////////////////////////////
			ft::pair<iterator,iterator> equal_range( const Key& key )
			{
				return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
				return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}
			/////////////////////////////////////
			iterator lower_bound( const Key& key )
			{
				iterator it = this->begin();

				while (it != end())
				{
					if (_comp(it->first, k) == false)
						break;
					it++;
				}
				return (it);
			}
			const_iterator lower_bound( const Key& key ) const
			{
				iterator it = this->begin();

				while (it != end())
				{
					if (!_comp(it->first, k) == false)
						break;
					it++;
				}
				return (it);
			}
			iterator upper_bound (const key_type& key)
			{
				iterator it = this->begin();

				while (it != end())
				{
					if (_comp(k, it->first) == true)
						break;
					it++;
				}
				return (it);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				iterator it = this->begin();

				while (it != end())
				{
					if (_comp(k, it->first) == true)
						break;
					it++;
				}
				return (it);
			}

			// -------------------- Observers -------------------- //
			key_compare key_comp() const
			{
				return (_comp);
			}
			value_compare value_comp() const
			{
				return (value_compare(key_compare()));
			}

			allocator_type get_allocator() const { return (allocator_type()); }

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
	bool operator==( const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs ) { return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
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

#  	endif