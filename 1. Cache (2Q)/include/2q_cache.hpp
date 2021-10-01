#ifndef CACHE_2Q_H_
#define CACHE_2Q_H_

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime> 
#include <iomanip>

#include "cache_mem.hpp"

namespace cch
{
    template<typename Data>
    class Cache_2Q
    {
        CacheMem<Page<Data>> in_;  
        CacheMem<Page<Data>> main_;
        CacheMem<Page<Data>> out_;

        enum class CacheHit
        {
            HIT  = 1,
            MISS = 0
        };

        int out_policy(const Page<Data>& page)
        {
            if (main_.size() < main_.max_size())
                main_.add_page(page);
            else
            {
                Page<Data> tail = main_.back();
                main_.remove_page(tail);

                main_.add_page(page);
            }

            return static_cast<int>(CacheHit::HIT);
        }

        int add_policy(const Page<Data>& page)
        {
            if (in_.size() < in_.max_size())
                in_.add_page(page);
            else if (in_.size() == in_.max_size())
            {
                Page<Data> tail = in_.back();
                in_.remove_page(tail);
                in_.add_page(page);

                if (out_.size() < out_.max_size())
                    out_.add_page(tail);
                else
                {
                    Page<Data> tail_out = out_.back();
                    out_.remove_page(tail_out);
                    
                    out_.add_page(tail);
                }
            }

            return static_cast<int>(CacheHit::MISS);
        }

    public:

        Cache_2Q(size_t n_pages, double k_out = 0.6, double k_in = 0.2)
        {
            // Sizes of 2Q cache buffers

            size_t out_size = k_out * n_pages;
            if (out_size == 0)
                out_size = 1;

            size_t main_size = k_in * n_pages;
            if (main_size == 0)
                main_size = 1;

            size_t in_size = 1;
            if (n_pages > out_size + main_size)
                in_size = n_pages - out_size - main_size;

            in_   = CacheMem<Page<Data>>(in_size);
            main_ = CacheMem<Page<Data>>(main_size);
            out_  = CacheMem<Page<Data>>(out_size);
        }

        Cache_2Q(const Cache_2Q<Data>& source)       = delete;
        void operator=(const Cache_2Q<Data>& source) = delete;

        void slow_copy(const Cache_2Q<Data>& source)
        {
            in_.  slow_copy(source.in_);
            out_. slow_copy(source.out_);
            main_.slow_copy(source.main_);
        }

        Cache_2Q(Cache_2Q<Data>&& source)
        {
            in_   = std::move(source.in_);
            out_  = std::move(source.out_);
            main_ = std::move(source.main_);
        }

        void operator=(Cache_2Q<Data>&& source)
        {
            in_   = std::move(source.in_);
            out_  = std::move(source.out_);
            main_ = std::move(source.main_);
        }

        void print() const
        {
            std::cerr << "\n\n" << "Printing 2Q cache at: " << this << std::endl;

            std::cerr << "\n\t printing \"in_\"  memory: " << std::endl;
            in_.print();
            std::cerr << "\n\t printing \"main\" memory: " << std::endl;
            main_.print();
            std::cerr << "\n\t printing \"out\"  memory: " << std::endl;
            out_.print();

            std::cerr << "\nCache " << this << " printed" << "\n\n\n";
        }

        void dump(std::ofstream& fout) const
        {
            fout << "Printing 2Q cache at address: " << this << std::endl;

            fout << "\n\t printing \"in_\"  memory: " << std::endl;
            in_.dump(fout);
            fout << "\n\t printing \"main\" memory: " << std::endl;
            main_.dump(fout);
            fout << "\n\t printing \"out\"  memory: " << std::endl;
            out_.dump(fout);

            fout << "\nCache " << this << " is printed" << "\n\n\n";
        }

        size_t size() const
        {
            return in_.max_size() + out_.max_size() + main_.max_size();
        }
        
        Data& get_page(int id)
        {
            if (in_.contains(id))
            {
                in_.update_page(id);

                return in_.get_page(id).data();
            }
            else if (main_.contains(id))
                return main_.get_page(id).data();
            else if (out_.contains(id))
            {
                out_policy(id);

                return out_.get_page(id).data();
            }
            else
            {
                add_policy(id); // miss

                return in_.get_page(id).data();
            }
        }

        int handle_page(const Page<Data>& page)
        {
            if (in_.contains(page.id()))
            {
                in_.update_page(page);

                return static_cast<int>(CacheHit::HIT);
            }
            else if (main_.contains(page.id()))
                return static_cast<int>(CacheHit::HIT);
            else if (out_.contains(page.id()))
                return out_policy(page); // hit
            else
                return add_policy(page); // miss
        }
    };
}

#endif // !CACHE_2Q_H_
