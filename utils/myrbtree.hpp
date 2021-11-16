#ifndef BTREE_HPP
# define BTREE_HPP

# include "utils.hpp"
# include <memory>

namespace ft
{
	template < class T >
	struct Node
	{
		typedef T   value_type;

		value_type  data;
		Node*       parent;
		Node*       left;
		Node*       right;
		int         color;
	};

	template < class T, class Compare = ft::less<T>, class Node = ft::Node<T>, class Node_Alloc = std::allocator<Node> >
	class BTree
	{
		public:
			typedef T                               value_type;
			typedef Node                            node_type;
			typedef Node*                           node_pointer;
			typedef Compare                         key_compare;
			typedef Node_Alloc                      node_alloc;
			typedef typename node_alloc::pointer    pointer;

			pointer insert(const value_type& val)
			{
				pointer tmp = this->root;
				pointer parent = nullptr;

				while (tmp)
				{
					parent = tmp;
					if (val.first < tmp->data.first)
						tmp = tmp->left;
					else
						tmp = tmp->right;
				}
				if (parent && (val.first == parent->data.first))
					return (nullptr);
				Node_pointer toInsert = node_alloc.allocate(1);
				toInsert->data.first = val.first;
				toInsert->data.second = val.second;
				toInsert->parent = parent;
				toInsert.left = nullptr;
				toInsert.right = nullptr;
				toInsert.color = 0;
				if (!this->root)
				{
					this->root = toInsert;
					return (toInsert);
				}
				else if (toInsert->data.first < parent->data.first)
					parent->left = toInsert;
				else
					parent->right = toInsert;
				return (toInsert);
			}

			void delete(const value_type& val)
			{
				pointer tmp = this->root;
				pointer a = tmp;
				pointer b, c;
				while (tmp)
				{
					if (tmp->data.first = val.first)
						a = tmp;
					if (tmp->data.first <= val.first)
						tmp = tmp->right;
					else
						tmp = tmp->left;
				}
				if (a = tmp) // pas trouve de key correspondante
					return (nullptr);
			}

			void search(const value_type& val)
			{
				pointer tmp = this->root;

				while (tmp)
				{
					if (tmp->data.first == val.first)
						return (tmp);
					else if (val.first < tmp->data.first)
					{
						tmp = tmp->left;
					}
					else
					{
						tmp = tmp->right;
					}   
				}
				return (nullptr);
			}

			void fixInsert(NodePtr k)
			{
				NodePtr u;
				while (k->parent->color == 1) 
				{
					if (k->parent == k->parent->parent->right) {
						u = k->parent->parent->left; // uncle
						if (u->color == 1) {
							// case 3.1
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;
						} else {
							if (k == k->parent->left) {
								// case 3.2.2
								k = k->parent;
								rightRotate(k);
							}
							// case 3.2.1
							k->parent->color = 0;
							k->parent->parent->color = 1;
							leftRotate(k->parent->parent);
						}
					} 
					else 
					{
						u = k->parent->parent->right; // uncle

						if (u->color == 1) {
							// mirror case 3.1
							u->color = 0;
							k->parent->color = 0;
							k->parent->parent->color = 1;
							k = k->parent->parent;	
						} else {
							if (k == k->parent->right) {
								// mirror case 3.2.2
								k = k->parent;
								leftRotate(k);
							}
							// mirror case 3.2.1
							k->parent->color = 0;
							k->parent->parent->color = 1;
							rightRotate(k->parent->parent);
						}
					}
					if (k == root)
						break;
				}
				root->color = 0;
			}

			void leftRotate(NodePtr x) 
			{
				NodePtr y = x->right;
				x->right = y->left;
				if (y->left != TNULL) {
					y->left->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == nullptr) {
					this->root = y;
				} else if (x == x->parent->left) {
					x->parent->left = y;
				} else {
					x->parent->right = y;
				}
				y->left = x;
				x->parent = y;
			}

			void rightRotate(NodePtr x) 
			{
				NodePtr y = x->left;
				x->left = y->right;
				if (y->right != TNULL) {
					y->right->parent = x;
				}
				y->parent = x->parent;
				if (x->parent == nullptr) {
					this->root = y;
				} else if (x == x->parent->right) {
					x->parent->right = y;
				} else {
					x->parent->left = y;
				}
				y->right = x;
				x->parent = y;
			}

		private:
			node_pointer root;
	};
}

#endif