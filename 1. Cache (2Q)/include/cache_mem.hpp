#ifndef CACHE_MEM_H_
#define CACHE_MEM_H_

#include <iostream>
#include <utility>
#include <cstdlib>
#include <unordered_map>
#include <list>

#include "page.hpp"

namespace cch
{
    template <typename Data>
    using EListIt = typename std::list<Data>::iterator;

    static const size_t CACHE_MEM_DEFAULT_SIZE = 0x200;

    template<typename Data>
    class CacheMem
    {
    private:
        std::list<Data> list_;       // for quick insertion and sequential access
        std::unordered_map<int, EListIt<Data>> hash_table_;  // for quick insertion and quick      access

        size_t mem_size_; // total size of cache buffer
        size_t cur_size_;

    public:

    // Ctors and assignments

        CacheMem(size_t size = CACHE_MEM_DEFAULT_SIZE) :
            mem_size_(size),
            cur_size_(0)
        {}

        CacheMem(const CacheMem<Data>& source)       = delete;
        void operator=(const CacheMem<Data>& source) = delete;

        void slow_copy(const CacheMem<Data>& source)
        {
            list_       = source.list_;
            hash_table_ = source.hash_table_;

            mem_size_ = source.mem_size_;
            cur_size_ = source.cur_size_;
        }

        CacheMem(CacheMem<Data>&& source)
        {
            list_       = std::move(source.list_);
            hash_table_ = std::move(source.hash_table_);

            mem_size_ = source.mem_size_;
            cur_size_ = source.cur_size_;
        }

        void operator=(CacheMem<Data>&& source)
        {
            list_       = std::move(source.list_);
            hash_table_ = std::move(source.hash_table_);

            mem_size_ = source.mem_size_;
            cur_size_ = source.cur_size_;
        }

    // Management

        void add_page(const Data& page)
        {
            if (cur_size_ < mem_size_)
            {
                // Insert new element
                list_.push_front(page);
                EListIt<Data> iter = list_.begin();
                hash_table_.insert({page.id(), iter});

                cur_size_++;
            }
        }

        void remove_page(const Data& page)
        {
            if (cur_size_ > 0)
            {
                // Buffer should be constant length
                const EListIt<Data> to_delete = hash_table_[page.id()];
                list_.erase(to_delete);
                hash_table_.erase(page.id());

                cur_size_--;
            }  
        }

        void update_page(const Data& page)
        {
            const EListIt<Data> page_iter = hash_table_[page.id()];
            list_.erase(page_iter);
            list_.push_front(page);
        }

    // Info

        bool page_at(int id) const
        {
            return hash_table_.find(id) != hash_table_.end();
        }

        Data back() const
        {
            return list_.back();
        }

        size_t size() const
        {
            return cur_size_;
        }

        size_t max_size() const
        {
            return mem_size_;
        }

    // Print & verification    
        
        void print() const
        {
            std::cerr << "Printing memory: "     << this      << std::endl;
            std::cerr << "Memory size: "         << mem_size_ << std::endl;
            std::cerr << "Memory current size: " << cur_size_ << std::endl;

            for (auto elem : list_)
                elem.print();
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
