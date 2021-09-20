#ifndef PAGE_H_
#define PAGE_H_

#include <iostream>
#include <cstdlib>

namespace cch
{
    template<typename Data>
    class Page
    {
        int    id_   = 0; // page id
        size_t size_ = 0; // page size

        Data   data_ = 0; // data

    public:

        Page(int id = 0, Data data = 0) :
            id_(id),
            size_(sizeof(data)),
            data_(data)
        {
            if (data == 0)
                size_ = 0;
        }

        int id() const
        {
            return id_; 
        }

        size_t size() const
        {
            return size_;
        }

        Data data() const
        {
            return data_;
        }

        bool operator==(const Page& page) const
        {
            return (id_ == page.id_);
        }

        void print() const
        {
            std::cerr << "Page ID: " << id_ << " " << "Page size: " << size_ << " " << "Page data " << data_ << std::endl;
        }

        bool ok() const
        {
            if (size_ < 0)
            {
                std::cerr << "Page with invalid size: " << std::endl;
                print();

                return false;
            }
            else
                return true;
        }
    };
}

#endif // !PAGE_H_