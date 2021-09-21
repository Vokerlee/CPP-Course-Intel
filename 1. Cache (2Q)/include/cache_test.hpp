#ifndef Cache_2QEST_H_
#define Cache_2QEST_H_

#include "2q_cache.hpp"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace cch
{
    const size_t MAX_TEST_NUM = 15;

    template<typename Data>
    class CacheTest
    {
        size_t n_pages_;
        std::vector<Page<Data>> pages_;

    public:

        CacheTest(size_t n_pages) :
            n_pages_(n_pages)
        {
            srand(time(NULL));

            for (size_t i = 0; i < n_pages; ++i)
                pages_.push_back(Page<Data>(rand() % MAX_TEST_NUM, rand() % MAX_TEST_NUM));
        }

        void print_data() const
        {
            std::cerr << "Printing test data: "          << std::endl;
            std::cerr << "Number of pages: " << n_pages_ << std::endl;
            std::cerr << "Printing generated pages: \n"  << std::endl;

            for (size_t i = 0; i < n_pages_; ++i)
                pages_[i].print();

            std::cerr << std::endl;
        }

        void fill_cache(Cache_2Q<Data>& cache) const
        {
            for (int i = 0; i < cache.main.mem_size_; ++i)
                cache.main.add_page(pages_[i]);
        }

        void test_cache(Cache_2Q<Data>& cache) const
        {
            int hits = 0;

            for (size_t i = 0; i < n_pages_; ++i)
            {
                std::cerr << "Accessing page with id: " << pages_[i].id() << std::endl;
                hits += cache.handle_page(pages_[i]);
                cache.print();
            }

            std::cerr << "Hits: " << hits << std::endl <<
                         "Memory accesses << " << n_pages_ << std::endl;
        }
    };
}

#endif // !Cache_2QEST_H_