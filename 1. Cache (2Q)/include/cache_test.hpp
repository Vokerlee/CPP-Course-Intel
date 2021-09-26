#ifndef Cache_2QEST_H_
#define Cache_2QEST_H_

#include "2q_cache.hpp"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace cch
{
    template<typename Data>
    class CacheTest
    {
        size_t n_pages_;
        std::vector<Page<Data>> pages_;

        static size_t n_tests;

    public:

        CacheTest(size_t n_pages) :
            n_pages_(n_pages)
        {
            srand(time(NULL));

            for (size_t i = 0; i < n_pages; ++i)
                pages_.push_back(Page<Data>(rand() % n_tests, rand() % n_tests));
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

        void test_cache(Cache_2Q<Data>& cache, bool silence = true) const
        {
            int hits = 0;

            if (silence)
            {
                for (size_t i = 0; i < n_pages_; ++i)
                    hits += cache.handle_page(pages_[i]);
            }
            else
            {
                for (size_t i = 0; i < n_pages_; ++i)
                {
                    std::cerr << "Accessing page with id: " << pages_[i].id() << std::endl;
                    hits += cache.handle_page(pages_[i]);
                    cache.print();
                }
            }

            std::cerr << "Hits: " << hits << std::endl   <<
                         "Memory accesses: " << n_pages_ << std::endl;
        }
    };

    template<typename Data>
    size_t CacheTest<Data>::n_tests = 5000;
}

#endif // !Cache_2QEST_H_