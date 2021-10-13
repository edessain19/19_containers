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