#ifndef CACHE_MEM_H_
#define CACHE_MEM_H_

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <list>

#include "page.hpp"

namespace cch
{
    template<typename Data>
    class CacheMem
    {
    public:
        std::list<Data> list_;                       // for quick insertion and sequential access
        std::unordered_map<int, Data*> hash_table_;  // for quick insertion and quick      access

    public:

        size_t mem_size_ = 0; // total size of cache buffer
        size_t cur_size_ = 0;

        CacheMem() = default;
        CacheMem(size_t size) :
            mem_size_(size),
            cur_size_(0)
        {
            for (size_t i = 0; i < size; ++i) // initial filling
                list_.push_back(Data());
        }

        void print() const
        {
            std::cerr << "Printing memory: "     << this      << std::endl;
            std::cerr << "Memory size: "         << mem_size_ << std::endl;
            std::cerr << "Memory current size: " << cur_size_ << std::endl;

            for (auto v : list_)
                v.print();
        }

        void add_page(Data page)
        {
            // Insert new element
            list_.push_front(page);
            hash_table_.insert({page.id(), &page}); // not to copy the page

            // Delete old element
            Data* deleted = &list_.back();
            hash_table_.erase(deleted->id());
            list_.pop_back();

            cur_size_++;
        }

        void remove_page(Data page)
        {
            // Buffer should be constant length
            hash_table_.erase(page.id());
            list_.remove(page);
            list_.push_back(Data());

            cur_size_--;
        }

        bool page_at(int id) const
        {
            try 
            {
                hash_table_.at(id);
            }
            
            catch(std::out_of_range)
            {
                return false;
            }

            return true;
        }

        bool ok() const
        {
            if (mem_size_ < 0)
                return false;
            else
                return true;
        }
    };

}

#endif // !CACHE_MEM_H_