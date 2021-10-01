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
        std::list<Data> list_; // for quick insertion and sequential access
        std::unordered_map<int, EListIt<Data>> hash_table_; // for quick insertion and quick access

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

        Data& get_page(int id)
        {
            return *(hash_table_[id]);
        }

        void add_page(const Data& page)
        {
            if (cur_size_ < mem_size_)
            {
                // Insert new element
                list_.push_front(page);
                const EListIt<Data> iter = list_.begin();
                hash_table_.insert({page.id(), iter});

                cur_size_++;
            }
        }

        void remove_page(const int id)
        {
            if (cur_size_ > 0)
            {
                // Buffer should be constant length
                const EListIt<Data> to_delete = hash_table_[id];
                list_.erase(to_delete);
                hash_table_.erase(id);

                cur_size_--;
            }  
        }

        void remove_page(const Data& page)
        {
            remove_page(page.id());
        }

        void update_page(const int id)
        {
            const EListIt<Data> page_iter = hash_table_[id];
            list_.splice(list_.begin(), list_, page_iter); // slower?
            hash_table_[id] = list_.begin();
        }

        void update_page(const Data& page)
        {
            const EListIt<Data> page_iter = hash_table_[page.id()];
            list_.erase(page_iter);
            list_.push_front(page); // faster?
            hash_table_[page.id()] = list_.begin();
        }

    // Info

        bool contains(int id) const
        {
            return hash_table_.contains(id);
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
            std::cerr << "Address of memory: "   << this      << std::endl;
            std::cerr << "Memory capacity: "     << mem_size_ << std::endl;
            std::cerr << "Memory current size: " << cur_size_ << std::endl;
        }

        void dump(std::ofstream& fout) const
        {
            fout << "Address of memory: "   << this      << std::endl;
            fout << "Memory capacity: "     << mem_size_ << std::endl;
            fout << "Memory current size: " << cur_size_ << std::endl;

            fout << "Pages dump:" << std::endl;

            for (auto elem : list_)
                elem.dump(fout);
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
