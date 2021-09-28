#ifndef Cache_2QEST_H_
#define Cache_2QEST_H_

#include "2q_cache.hpp"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

namespace cch
{
    template<typename Data>
    class CacheTest
    {
        size_t n_pages_;
        size_t max_id_;

        std::vector<Page<Data>> pages_;

    public:

        CacheTest(size_t n_pages, size_t max_id) :
            n_pages_(n_pages),
            max_id_(max_id)
        {
            srand(time(NULL));

            for (size_t i = 0; i < n_pages; ++i)
                pages_.push_back(Page<Data>(rand() % max_id, rand() % max_id));
        }

        void print_test_file(Cache_2Q<Data>& cache, std::ofstream& fout) const
        {   
            fout << cache.size() << std::endl << n_pages_ << std::endl;

            for (size_t i = 0; i < n_pages_; i++)
                fout << pages_[i].id() << std::endl;
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
}

#endif // !Cache_2QEST_H_