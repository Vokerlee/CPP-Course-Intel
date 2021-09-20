#ifndef CACHE_2Q_H_
#define CACHE_2Q_H_

#include <iostream>
#include <cstdlib>

#include "cache_mem.hpp"

class noncopyable
{
private:
    noncopyable(const noncopyable &)    = delete;
    void operator=(const noncopyable &) = delete;

protected:
    noncopyable()  = default;
    ~noncopyable() = default;
};

namespace cch
{
    const double KIN  = 0.25;
    const double KOUT = 0.5;

    template<typename Data> class CacheTest;

    template<typename Data>
    class Cache_2Q : public noncopyable
    {
        friend class CacheTest<Data>;

        CacheMem<Page<Data>> in;  
        CacheMem<Page<Data>> main;
        CacheMem<Page<Data>> out;

        void extrusion_policy(Page<Data> const page)
        {
            if (in.cur_size_ < in.mem_size_)
                in.add_page(page);
            else if (main.cur_size_ < main.mem_size_)
                main.add_page(page);
            else if (main.cur_size_ == main.mem_size_)
            {
                Page<Data> tail = main.list_.back();
                out.add_page(tail);
                main.remove_page(tail);

                if (out.cur_size_ == out.mem_size_)
                {
                    Page<Data> tail = out.list_.back();
                    out.remove_page(tail);
                }

                main.add_page(page); 
            }
            else
            {
                Page<Data> tail = in.list_.back();
                in.remove_page(tail);
                in.add_page(page);
            }
        }

    public:

        Cache_2Q() = delete;
        Cache_2Q(size_t n_pages)
        {
            // Sizes of 2Q cache buffers

            size_t out_size = KOUT * n_pages;
            if (out_size == 0)
                out_size = 1;

            size_t main_size = KIN * (n_pages - out_size);
            if (main_size == 0)
                main_size = 1;

            size_t in_size = 1;
            if (n_pages > out_size + main_size)
                in_size = n_pages - out_size - main_size;

            in   = CacheMem<Page<Data>>(in_size);
            main = CacheMem<Page<Data>>(main_size);
            out  = CacheMem<Page<Data>>(out_size);
        }

        void print_cache() const
        {
            std::cerr << "\n\n\n" << 
                        "Printing 2Q cache at: " << this << std::endl;

            std::cerr << "\t printing in memory: "   << std::endl;
            in.print();
            std::cerr << "\t printing main memory: " << std::endl;
            main.print();
            std::cerr << "\t printing out memory: "  << std::endl;
            out.print();

            std::cerr << "Cache " << this << " printed" << "\n\n\n";
        }
        
        int handle_page(const Page<Data> page)
        {
            if (in.page_at(page.id()))
            {
                in.remove_page(page);
                in.add_page(page);

                return 1; // hit
            }
            else if (out.page_at(page.id()))
            {
                extrusion_policy(page);
                out.remove_page(page);

                return 0; // miss
            }
            else if (main.page_at(page.id()))
                return 1; // hit
            else
            { 
                extrusion_policy(page);

                return 0; // miss
            }
        }
    };
}

#endif // !CACHE_2Q_H_