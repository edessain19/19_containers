# ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <cstddef>

namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};

	// -------------------- Iterator -------------------- //
    template< class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
    class iterator
    {
        public:
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef Category  iterator_category;
    };

	// -------------------- Iterator Traits -------------------- //
    // ---------- Iterator Traits ---------- //
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

    // ---------- Iterator Traits <T*> ---------- //
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

    // ---------- Iterator Traits <const T*> ---------- //
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

    // ---------- Iterator ---------- //
    template<class Category = ft::random_access_iterator_tag, class T = int, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
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

            It(pointer ptr = nullptr);
            ~It();
            reference operator*() const;
            pointer operator->();
            It& operator++();
            It operator++(int);
            It& operator--();
            It operator--(int);
            // friend of non member overload
            friend bool operator==(const It& a, const It& b) { return a._ptr == b._ptr; }
            friend bool operator!=(const It& a, const It& b) { return a._ptr != b._ptr; }
            It& operator=(const It & x) { this->_ptr = x._ptr; return *this; }
            It& operator+=(difference_type n) const;
            It& operator+(const It & x) const;
            It& operator-=(const It & x) const;
            It& operator-(const It & x) const;
            bool operator<(const It & x) const;
            bool operator<=(const It & x) const;
            bool operator>(const It & x) const;
            bool operator>=(const It & x) const;
            It& operator[](difference_type n);
    };

    // ---------- Reverse Iterator ---------- //
	template <class Iterator> 
	class reverse_iterator
	{
		public:
			typedef Iterator                                                iterator_type;
    		typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
    		typedef typename iterator_traits<Iterator>::value_type          value_type;
    		typedef typename iterator_traits<Iterator>::difference_type     difference_type;
    		typedef typename iterator_traits<Iterator>::pointer             pointer;
    		typedef typename iterator_traits<Iterator>::reference           reference;


			reverse_iterator() {}
			explicit reverse_iterator (iterator_type it) : current(it) {}
			template <class Iter>
  			reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.current) {}

			iterator_type base() const { return (this->current); }
			reference operator*() const { return (*this->current); }
			reverse_iterator operator+(difference_type n) const { return (this->current - n); }
			reverse_iterator& operator++() { return (this->current--); }
			reverse_iterator operator++(int) { reverse_iterator temp = *this; --(*this); return temp; } // Pierre Help!!
			reverse_iterator& operator+= (difference_type n) { return (*(this->current - n)); }
			reverse_iterator operator-(difference_type n) const { return (this->current + n); }
			reverse_iterator& operator--() { return (this->current++); }
			reverse_iterator  operator--(int) { reverse_iterator temp = *this; ++(*this); return temp; }
			reverse_iterator& operator-=(difference_type n) { return (*(this->current + n)); }
			pointer operator->() const { return &(operator*()); }
			reference operator[](difference_type n) const { return ((this->current[n])); } // comment on sait que current est le dernier ??? 
        protected:
			iterator_type current;
    };
    // template< class Iterator1, class Iterator2 >
    // bool operator==( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

    // template< class Iterator1, class Iterator2 >
    // constexpr bool operator==( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

        
    // template< class Iterator1, class Iterator2 >
    // bool operator!=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

    // template< class Iterator1, class Iterator2 >
    // constexpr bool operator!=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

        
    // template< class Iterator1, class Iterator2 >
    // bool operator<( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

    // template< class Iterator1, class Iterator2 >
    // constexpr bool operator<( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

        
    // template< class Iterator1, class Iterator2 >
    // bool operator<=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

    // template< class Iterator1, class Iterator2 >
    // constexpr bool operator<=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

    // template< class Iterator1, class Iterator2 >
    // bool operator>( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

    // template< class Iterator1, class Iterator2 >
    // constexpr bool operator>( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

        
    // template< class Iterator1, class Iterator2 >
    // bool operator>=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

    // template< class Iterator1, class Iterator2 >
    // constexpr bool operator>=( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );

    // template< class Iterator1, std::three_way_comparable_with<Iterator1> Iterator2 >
    // constexpr std::compare_three_way_result_t<Iterator1, Iterator2>
    //     operator<=>( const std::reverse_iterator<Iterator1>& lhs, const std::reverse_iterator<Iterator2>& rhs );
}

#endif