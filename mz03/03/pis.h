namespace numbers
{
    class complex_stack
    {
        size_t size_, cap_;
        complex *data_;
    public:
        complex_stack(size_t size = 0) : size_(size), cap_(size + 1), data_(nullptr)
        {
            data_ = new complex[cap_];
        }

        complex_stack(const complex_stack& base) : size_(base.size_),
                                                   cap_(base.cap_), data_(nullptr)
        {
            data_ = new complex[cap_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = base[i];
            }
        }
        complex_stack(const complex_stack& base, const complex& val) : size_(base.size_),
                                                                       cap_(base.cap_), data_(nullptr)
        {
            if (size_ == cap_) {
                cap_ *= 2;
            }
            data_ = new complex[cap_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = base[i];
            }
            data_[size_] = val;
            size_++;
        }

        ~complex_stack()
        {
            delete [] data_;
        }

        size_t size() const
        {
            return size_;
        }

        complex operator[](size_t index) const
        {
            return data_[index];
        }

        void operator=(const complex_stack& base)
        {
            if (&base == this) {
                return;
            }
            if (cap_ < base.cap_) {
                delete [] data_;
                size_ = base.size_;
                cap_ = base.cap_;
                data_ = new complex[cap_];
                for (size_t i = 0; i < size_; ++i) {
                    data_[i] = base[i];
                }
            } else {
                size_ = base.size_;
                for (size_t i = 0; i < size_; ++i) {
                    data_[i] = base[i];
                }
            }
        }

        complex_stack operator<<(const complex& val) const
        {
            return complex_stack(*this, val);
        }

        complex_stack operator~() const
        {
            complex_stack other(*this);
            other.size_--;
            return other;
        }

        complex operator+() const
        {
            return data_[size_ - 1];
        }

    };
};
