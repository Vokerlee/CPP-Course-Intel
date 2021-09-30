#ifndef PAGE_H_
#define PAGE_H_

#include <iostream>
#include <cstdlib>
#include <fstream>

namespace cch
{
    template<typename Data>
    class Page
    {
        int  id_;   // page id
        Data data_; // data

        static size_t size_; // page size

    public:

        Page(int id = -1, Data data = 0) :
            id_(id),
            data_(data)
        {}

        int id() const
        {
            return id_; 
        }

        size_t size() const
        {
            return size_;
        }

        Data& data() const
        {
            return data_;
        }

        bool operator==(const Page& page) const
        {
            return (id_ == page.id_);
        }

        void print() const
        {
            std::cerr << "Page: ID = " << id_ << " " << ", size = " << size_ << " " << "data = " << data_ << std::endl;
        }

        void dump(std::ofstream& fout) const
        {
            fout << "Page: ID = " << id_ << " " << ", size = " << size_ << " " << "data = " << data_ << std::endl;
        }
    };

    template<typename Data>
    size_t Page<Data>::size_ = sizeof(Data);
}

#endif // !PAGE_H_
