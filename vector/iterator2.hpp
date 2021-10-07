# ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace ft
{
    /*Category*/
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

    /*Base class*/
    template< class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
    class iterator
    {
        public:
            ///////////////////// Typedef //////////////////////////////////////////
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef Category  iterator_category;
    };

    /*Define properties of iterators*/
	template <class Iterator>
	class iterator_traits
	{
		public:
            typedef typename Iterator::value_type value_type;
    		typedef typename Iterator::difference_type difference_type;
    		typedef typename Iterator::pointer pointer;
    		typedef typename Iterator::reference reference;
    		typedef typename Iterator::iterator_category  iterator_category;
	};

	/*T* specialization*/ 
	template <class T> 
	class iterator_traits<T*>
	{
		public:
			typedef T value_type;
    		typedef ptrdiff_t difference_type;
    		typedef T* pointer;
    		typedef T& reference;
    		typedef ft::random_access_iterator_tag iterator_category;
	};

	/*const T* specialization*/
	template <class T> 
	class iterator_traits<const T*>
	{
		public:
			typedef T value_type;
    		typedef ptrdiff_t difference_type;
    		typedef const T* pointer;
    		typedef const T& reference;
    		typedef ft::random_access_iterator_tag iterator_category;
	};

    /*legacy*/
    template <class T>
    class It 
    {
        private:
            T* _ptr;
        public:
            typedef typename ft::iterator_traits<T*>::value_type            value_type;
            typedef typename ft::iterator_traits<T*>::difference_type       difference_type;
            typedef typename ft::iterator_traits<T*>::reference             reference; 
            typedef typename ft::iterator_traits<T*>::pointer               pointer;
            typedef typename ft::iterator_traits<T*>::iterator_category     iterator_category;

            It(pointer ptr = nullptr) : _ptr(ptr) {}
            ~It() { _ptr = nullptr; }

            reference operator*() const { return *this->_ptr; }
            pointer operator->() const { return this->_ptr; }
			It& operator++() { this->_ptr++; return *this; }
			It operator++(int) 
            { 
                It tmp = *this; 
                ++(*this); 
                return tmp; 
            }
			It& operator+= (difference_type n)
            { 
                difference_type m = n;

                if (m >= 0) 
                    while (m--) 
                        ++(*this);
                else 
                    while (m++) 
                        --(*this);
                return *this;
            }
            It operator+(difference_type n) const 
            { 
                It temp = *this;
                return temp += n;
            }
			It& operator-=(difference_type n) { return *this += -n; }
			It operator-(difference_type n) const
            {
                It temp = *this;
                return temp -= n;
            }
			It& operator--() { this->_ptr--; return *this; }
			It  operator--(int) { It tmp = *this; --(*this); return tmp; }
			reference operator[](difference_type n) const { return *(this->_ptr + n); }
    };

    /*Reverse iterator*/
	template <class Iterator> 
	class reverse_iterator
	{
		public:
			/*Member types*/
			typedef Iterator iterator_type;
    		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    		typedef typename iterator_traits<Iterator>::value_type value_type;
    		typedef typename iterator_traits<Iterator>::difference_type difference_type;
    		typedef typename iterator_traits<Iterator>::pointer pointer;
    		typedef typename iterator_traits<Iterator>::reference reference;

			/*Constructor and destructor*/
			reverse_iterator() {}
			explicit reverse_iterator (iterator_type it) : current(it) {}
			template <class Iter>
  			reverse_iterator(const reverse_iterator<Iter>& rev_it) : current(rev_it.current) {}

			/*Member functions*/
			iterator_type base() const
			{
				return this->current;
			}
			reference operator*() const
			{
				return *this->current;
			}
			reverse_iterator operator+(difference_type n) const { return current - n; }
			reverse_iterator& operator++() { return this->current--; }
			reverse_iterator operator++(int) { iterator_type tmp = this->current; --(this->current); return tmp; }
			reverse_iterator& operator+= (difference_type n) { return this->current -= n; }
			reverse_iterator operator-(difference_type n) const { return this->current + n; }
			reverse_iterator& operator--() { return this->current++; }
			reverse_iterator  operator--(int) { iterator_type tmp = this->current; ++(this->current); return tmp; }
			reverse_iterator& operator-=(difference_type n) { return this->current += n; }
			// pointer operator->() const { return this->current; }
			reference operator[](difference_type n) const { return this->current[n]; }

        protected:
			iterator_type current;
    };

    /*Non members iterator*/
    template< class T >
    bool operator==(const ft::It<T>& lhs, const ft::It<T>& rhs)
    {
        if (*lhs != *rhs)
            return false;
        return true;
    }
    template< class T >
    bool operator!=(const ft::It<T>& lhs, const ft::It<T>& rhs)
    {
        if (*lhs == *rhs)
            return false;
        return true;
    }  
    template< class T >
    bool operator<(const ft::It<T>& lhs, const ft::It<T>& rhs)
    {
        if (*lhs < *rhs)
            return true;
        return false;
    }
    template< class T >
    bool operator<=(const ft::It<T>& lhs, const ft::It<T>& rhs)
    {
        if (*lhs <= *rhs)
            return true;
        return false;
    }
    template< class T >
    bool operator>(const ft::It<T>& lhs, const ft::It<T>& rhs)
    {
        if (*lhs > *rhs)
            return true;
        return false;
    }
    template< class T >
    bool operator>=(const ft::It<T>& lhs, const ft::It<T>& rhs)
    {
        if (*lhs >= *rhs)
            return true;
        return false;
    }

    /*Non members reverse iterator*/
    template< class Iterator1, class Iterator2 >
    bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        lhs.base() == rhs.base();
    }

    template< class Iterator1, class Iterator2 >
    bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        lhs.base() != rhs.base();
    }
        
    template< class Iterator1, class Iterator2 >
    bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        lhs.base() > rhs.base();
    }
 
    template< class Iterator1, class Iterator2 >
    bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        lhs.base() >= rhs.base();
    }

    template< class Iterator1, class Iterator2 >
    bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        lhs.base() < rhs.base();
    }
        
    template< class Iterator1, class Iterator2 >
    bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        lhs.base() <= rhs.base();
    }
}

#endif